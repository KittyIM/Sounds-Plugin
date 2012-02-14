#include "SoundsSettingsPage.h"
#include "ui_SoundsSettingsPage.h"

#include <SoundsConstants.h>
#include <SDKConstants.h>
#include <IPluginCore.h>

#include <QtCore/QDebug>
#include <QtGui/QFileDialog>
#include <QtGui/QSound>

namespace Sounds
{

SettingsPage::SettingsPage(KittySDK::IPluginCore *core, QWidget *parent):
	KittySDK::ISettingsPage(core, parent),
	m_ui(new Ui::SettingsPage)
{
	m_ui->setupUi(this);

	setIcon(KittySDK::Icons::I_SOUND);

	addItem(KittySDK::Sounds::S_MSG_RECV, tr("Message received"));
	addItem(KittySDK::Sounds::S_MSG_RECV_FIRST, tr("Message received (first)"));
	addItem(KittySDK::Sounds::S_MSG_SENT, tr("Message sent"));
	addItem(KittySDK::Sounds::S_CONTACT_AVAIL, tr("Contact available"));
	addItem(KittySDK::Sounds::S_CONTACT_UNAVAIL, tr("Contact unavailable"));
	addItem(KittySDK::Sounds::S_ERROR, tr("Error"));
	addItem(KittySDK::Sounds::S_FILE_REQ, tr("File transfer request"));
}

SettingsPage::~SettingsPage()
{
	delete m_ui;
}

void SettingsPage::addItem(const QString &id, const QString &descr)
{
	if(!id.isEmpty() && !descr.isEmpty()) {
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, descr);
		item->setText(1, id);
		item->setText(2, core()->setting(id).toString());
		m_ui->treeWidget->addTopLevelItem(item);
	}
}

void SettingsPage::apply()
{
	for(int i = 0; i < m_ui->treeWidget->topLevelItemCount(); i++) {
		QTreeWidgetItem *item = m_ui->treeWidget->topLevelItem(i);

		core()->setSetting(item->text(1), item->text(2));
	}
}

void SettingsPage::reset()
{
	for(int i = 0; i < m_ui->treeWidget->topLevelItemCount(); i++) {
		QTreeWidgetItem *item = m_ui->treeWidget->topLevelItem(i);

		item->setText(2, core()->setting(item->text(1)).toString());
	}

	on_treeWidget_currentItemChanged(0, 0);
}

void SettingsPage::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	m_ui->pathEdit->setEnabled(current);
	m_ui->playButton->setEnabled(current);
	m_ui->browseButton->setEnabled(current);

	if(current) {
		m_ui->pathEdit->setText(current->text(2));
	}
}

void SettingsPage::on_browseButton_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Choose sound file"), "", "*.wav");
	if(!filePath.isEmpty()) {
		QDir kittyDir(core()->kittyDir());
		QString relativePath = kittyDir.relativeFilePath(filePath);

		if(!relativePath.contains("..")) {
			filePath = relativePath;
		}

		m_ui->pathEdit->setText(filePath);
		m_ui->treeWidget->currentItem()->setText(2, filePath);
	}
}

void SettingsPage::on_playButton_clicked()
{
	QSound::play(m_ui->pathEdit->text());
}

}
