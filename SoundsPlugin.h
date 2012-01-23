#ifndef SOUNDSPLUGIN_H
#define SOUNDSPLUGIN_H

#include "SDK/Plugin.h"

#include <QtCore/QDebug>

#define qDebug() qDebug() << "[Sounds]"
#define qWarning() qWarning() << "[Sounds]"

namespace KittySDK
{
	class SettingWidget;
	class Message;

	class SoundsPlugin: public Plugin
	{
		Q_OBJECT

		public:
			SoundsPlugin(PluginCore *pcore);
			~SoundsPlugin();

			void init();
			void load();
			void unload();

			void playSound(const QString &id);

		public slots:
			void applySettings();
			void execAction(const QString &name, const QMap<QString, QVariant> &args);

		private slots:
			void setMuted(bool muted);

		private:
			QMap<QString, QString> m_sounds;
			SettingWidget *m_settings;
			QAction *m_muteAction;
			bool m_muted;
	};
}

#endif // SOUNDSPLUGIN_H
