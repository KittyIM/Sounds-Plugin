#ifndef SOUNDS_PLUGIN_H
#define SOUNDS_PLUGIN_H

#include <IPlugin.h>

#include <QtCore/QDebug>

#define qDebug() qDebug() << "[Sounds]"
#define qWarning() qWarning() << "[Sounds]"

namespace Sounds
{
	class SettingsPage;

	class Plugin: public KittySDK::IPlugin
	{
		Q_OBJECT

		public:
			Plugin(KittySDK::IPluginCore *pcore);
			~Plugin();

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
			SettingsPage *m_settings;

			bool m_muted;
	};
}

#endif // SOUNDS_PLUGIN_H
