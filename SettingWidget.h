#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "SDK/SettingPage.h"

class QTreeWidgetItem;

namespace Ui
{
	class SettingWidget;
}

namespace KittySDK
{
	class PluginCore;

	class SettingWidget: public SettingPage
	{
		Q_OBJECT

		public:
			explicit SettingWidget(PluginCore *core, QWidget *parent = 0);
			~SettingWidget();

			void addItem(const QString &id, const QString &descr);

			void apply();
			void reset();

		private slots:
			void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

			void on_browseButton_clicked();

			void on_playButton_clicked();

		private:
			Ui::SettingWidget *m_ui;
	};
}

#endif // SETTINGWIDGET_H
