#include "SoundsPlugin.h"

#include "SoundsSettingsPage.h"

#include <SoundsConstants.h>
#include <SDKConstants.h>

#include <QtGui/QAction>
#include <QtGui/QSound>

namespace Sounds
{

Plugin::Plugin(KittySDK::IPluginCore *pcore): KittySDK::IPlugin(pcore)
{
	m_info = new KittySDK::IPluginInfo("Sounds", "0.0.1", "arturo182", "arturo182@tlen.pl", "http://www.arturpacholec.pl/");
}

Plugin::~Plugin()
{
	delete m_info;
}

void Plugin::init()
{
	core()->addIcon(KittySDK::Icons::I_SOUND_MUTE, QPixmap(":/glyphs/sound_mute.png"));

	m_muteAction = new QAction(core()->icon(KittySDK::Icons::I_SOUND_MUTE), tr("Mute sounds"), this);
	m_muteAction->setCheckable(true);
	connect(m_muteAction, SIGNAL(triggered(bool)), this, SLOT(setMuted(bool)));

	m_sounds.insert(KittySDK::Sounds::S_MSG_RECV, core()->setting(KittySDK::Sounds::S_MSG_RECV).toString());
	m_sounds.insert(KittySDK::Sounds::S_MSG_RECV_FIRST, core()->setting(KittySDK::Sounds::S_MSG_RECV_FIRST).toString());
	m_sounds.insert(KittySDK::Sounds::S_MSG_SENT, core()->setting(KittySDK::Sounds::S_MSG_SENT).toString());
	m_sounds.insert(KittySDK::Sounds::S_CONTACT_AVAIL, core()->setting(KittySDK::Sounds::S_CONTACT_AVAIL).toString());
	m_sounds.insert(KittySDK::Sounds::S_CONTACT_UNAVAIL, core()->setting(KittySDK::Sounds::S_CONTACT_UNAVAIL).toString());
	m_sounds.insert(KittySDK::Sounds::S_ERROR, core()->setting(KittySDK::Sounds::S_ERROR).toString());
	m_sounds.insert(KittySDK::Sounds::S_FILE_REQ, core()->setting(KittySDK::Sounds::S_FILE_REQ).toString());
}

void Plugin::load()
{
	m_settings = new SettingsPage(core());
	core()->addSettingPage(m_settings, KittySDK::SettingPages::S_DISPLAY);

	core()->addToolbarAction(KittySDK::Toolbars::TB_PLUGINS, m_muteAction);
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
