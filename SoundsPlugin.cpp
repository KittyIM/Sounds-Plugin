#include "SoundsPlugin.h"

#include "SDK/SoundsConstants.h"
#include "SettingWidget.h"
#include "SDK/constants.h"

#include <QtGui/QAction>
#include <QtGui/QSound>

using namespace KittySDK;

KittySDK::SoundsPlugin::SoundsPlugin(PluginCore *pcore): Plugin(pcore)
{
	m_info = new PluginInfo("Sounds", "0.0.1", "arturo182", "arturo182@tlen.pl", "http://www.arturpacholec.pl/");
}

KittySDK::SoundsPlugin::~SoundsPlugin()
{
	delete m_info;
}

void KittySDK::SoundsPlugin::init()
{
	core()->addIcon(Icons::I_SOUND_MUTE, QPixmap(":/glyphs/sound_mute.png"));

	m_muteAction = new QAction(core()->icon(Icons::I_SOUND_MUTE), tr("Mute sounds"), this);
	m_muteAction->setCheckable(true);
	connect(m_muteAction, SIGNAL(triggered(bool)), this, SLOT(setMuted(bool)));

	m_sounds.insert(Sounds::S_MSG_RECV, core()->setting(Sounds::S_MSG_RECV).toString());
	m_sounds.insert(Sounds::S_MSG_RECV_FIRST, core()->setting(Sounds::S_MSG_RECV_FIRST).toString());
	m_sounds.insert(Sounds::S_MSG_SENT, core()->setting(Sounds::S_MSG_SENT).toString());
	m_sounds.insert(Sounds::S_CONTACT_AVAIL, core()->setting(Sounds::S_CONTACT_AVAIL).toString());
	m_sounds.insert(Sounds::S_CONTACT_UNAVAIL, core()->setting(Sounds::S_CONTACT_UNAVAIL).toString());
	m_sounds.insert(Sounds::S_ERROR, core()->setting(Sounds::S_ERROR).toString());
	m_sounds.insert(Sounds::S_FILE_REQ, core()->setting(Sounds::S_FILE_REQ).toString());
}

void KittySDK::SoundsPlugin::load()
{
	m_settings = new SettingWidget(core());
	core()->addSettingPage(m_settings, SettingPages::S_DISPLAY);

	core()->addToolbarAction(Toolbars::TB_PLUGINS, m_muteAction);
}

void KittySDK::SoundsPlugin::unload()
{
	delete m_settings;
}

void KittySDK::SoundsPlugin::playSound(const QString &id)
{
	if(m_sounds.contains(id) && !m_muted) {
		QSound::play(m_sounds.value(id));
	}
}

void KittySDK::SoundsPlugin::applySettings()
{
	QMutableMapIterator<QString, QString> it(m_sounds);
	while(it.hasNext()) {
		it.next();

		it.setValue(core()->setting(it.key()).toString());
	}
}

void KittySDK::SoundsPlugin::execAction(const QString &name, const QMap<QString, QVariant> &args)
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

void KittySDK::SoundsPlugin::setMuted(bool muted)
{
	m_muted = muted;
}

KITTY_PLUGIN(SoundsPlugin)
