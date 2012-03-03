#ifndef SOUNDS_SETTINGPAGE_H
#define SOUNDS_SETTINGPAGE_H

#include <ISettingsPage.h>

class QTreeWidgetItem;

namespace Sounds
{
	namespace Ui
	{
		class SettingsPage;
	}

	class PluginCore;

	class SettingsPage: public KittySDK::ISettingsPage
	{
		Q_OBJECT

		public:
			explicit SettingsPage(KittySDK::IPluginCore *core, QWidget *parent = 0);
			~SettingsPage();

			void addItem(const QString &id, const QString &descr);

			void apply();
			void reset();
			void retranslate();

		signals:
			void applied();

		private slots:
			void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
			void on_browseButton_clicked();
			void on_playButton_clicked();

		private:
			Ui::SettingsPage *m_ui;
	};
}

#endif // SOUNDS_SETTINGPAGE_H
