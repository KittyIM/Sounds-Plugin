#include "SoundsPlugin.h"

#include "SoundsSettingsPage.h"

#include <SoundsConstants.h>
#include <SDKConstants.h>

#include <QtGui/QAction>
#include <QtGui/QSound>

namespace Sounds
{

Plugin::Plugin(KittySDK::IPluginCore *pcore):
	KittySDK::IPlugin(pcore),
	m_settings(0),
	m_muted(false)
{
	m_info = new KittySDK::IPluginInfo();
	m_info->setName(tr("Sounds"));
	m_info->setId("sounds");
	m_info->setVersion("0.0.1");
	m_info->setAuthor("arturo182");
	m_info->setEmail("arturo182@tlen.pl");
	m_info->setURL("http://www.arturpacholec.pl/");
}

Plugin::~Plugin()
{
	delete m_info;
}

void Plugin::init()
{
	core()->addIcon(Icons::I_MUTE, QPixmap(":/glyphs/sound_mute.png"));

	m_sounds.insert(Sounds::S_MSG_RECV, core()->setting(Sounds::S_MSG_RECV).toString());
	m_sounds.insert(Sounds::S_MSG_RECV_FIRST, core()->setting(Sounds::S_MSG_RECV_FIRST).toString());
	m_sounds.insert(Sounds::S_MSG_SENT, core()->setting(Sounds::S_MSG_SENT).toString());
	m_sounds.insert(Sounds::S_CONTACT_AVAIL, core()->setting(Sounds::S_CONTACT_AVAIL).toString());
	m_sounds.insert(Sounds::S_CONTACT_UNAVAIL, core()->setting(Sounds::S_CONTACT_UNAVAIL).toString());
	m_sounds.insert(Sounds::S_ERROR, core()->setting(Sounds::S_ERROR).toString());
	m_sounds.insert(Sounds::S_FILE_REQ, core()->setting(Sounds::S_FILE_REQ).toString());
}

void Plugin::load()
{
	m_settings = new SettingsPage(core());
	core()->addSettingPage(m_settings, KittySDK::SettingPages::S_DISPLAY);

	QAction *muteAction = new QAction(tr("Mute sounds"), this);
	connect(muteAction, SIGNAL(triggered(bool)), SLOT(setMuted(bool)));
	muteAction->setCheckable(true);
	muteAction->setProperty("icon_id", Icons::I_MUTE);

	core()->addAction(Actions::A_MUTE, muteAction);
	core()->addToolbarAction(KittySDK::Toolbars::TB_PLUGINS, muteAction);
}

void Plugin::unload()
{
	delete m_settings;
}

void Plugin::playSound(const QString &id)
{
	if(m_sounds.contains(id) && !m_muted) {
		QSound::play(m_sounds.value(id));
	}
}

void Plugin::applySettings()
{
	QMutableMapIterator<QString, QString> it(m_sounds);
	while(it.hasNext()) {
		it.next();

		it.setValue(core()->setting(it.key()).toString());
	}
}

void Plugin::execAction(const QString &name, const QMap<QString, QVariant> &args)
{
	if(name == "addSound") {
		if(args.contains("id") && args.contains("description")) {
			m_settings->addItem(args.value("id").toString(), args.value("description").toString());
		}
	} else if(name == "playSound") {
		if(args.contains("id")) {
			playSound(args.value("id").toString());
		}
	} else if(name == "retranslate") {
		m_info->setName(tr("Sounds"));
		core()->action(Actions::A_MUTE)->setText(tr("Mute sounds"));
	} else {
		qWarning() << "Got unknown execAction request" << name;
	}
}

void Plugin::setMuted(bool muted)
{
	m_muted = muted;
}

KITTY_PLUGIN(Plugin)
}
