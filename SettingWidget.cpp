#include "SettingWidget.h"
#include "ui_SettingWidget.h"

#include "SDK/SoundsConstants.h"
#include "SDK/PluginCore.h"
#include "SDK/constants.h"

#include <QtCore/QDebug>
#include <QtGui/QFileDialog>
#include <QtGui/QSound>

using namespace KittySDK;

KittySDK::SettingWidget::SettingWidget(PluginCore *core, QWidget *parent): SettingPage(core, parent), m_ui(new Ui::SettingWidget)
{
  m_ui->setupUi(this);

  setIcon(Icons::I_SOUND);

  addItem(Sounds::S_MSG_RECV, tr("Message received"));
  addItem(Sounds::S_MSG_RECV_FIRST, tr("Message received (first)"));
  addItem(Sounds::S_MSG_SENT, tr("Message sent"));
  addItem(Sounds::S_CONTACT_AVAIL, tr("Contact available"));
  addItem(Sounds::S_CONTACT_UNAVAIL, tr("Contact unavailable"));
  addItem(Sounds::S_ERROR, tr("Error"));
  addItem(Sounds::S_FILE_REQ, tr("File transfer request"));
}

KittySDK::SettingWidget::~SettingWidget()
{
  delete m_ui;
}

void KittySDK::SettingWidget::addItem(const QString &id, const QString &descr)
{
  if(!id.isEmpty() && !descr.isEmpty()) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, descr);
    item->setText(1, id);
    item->setText(2, core()->setting(id).toString());
    m_ui->treeWidget->addTopLevelItem(item);
  }
}

void KittySDK::SettingWidget::apply()
{
  for(int i = 0; i < m_ui->treeWidget->topLevelItemCount(); i++) {
    QTreeWidgetItem *item = m_ui->treeWidget->topLevelItem(i);

    core()->setSetting(item->text(1), item->text(2));
  }
}

void KittySDK::SettingWidget::reset()
{
  for(int i = 0; i < m_ui->treeWidget->topLevelItemCount(); i++) {
    QTreeWidgetItem *item = m_ui->treeWidget->topLevelItem(i);

    item->setText(2, core()->setting(item->text(1)).toString());
  }

  on_treeWidget_currentItemChanged(0, 0);
}

void KittySDK::SettingWidget::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
  m_ui->pathEdit->setEnabled(current);
  m_ui->playButton->setEnabled(current);
  m_ui->browseButton->setEnabled(current);

  if(current) {
    m_ui->pathEdit->setText(current->text(2));
  }
}

void KittySDK::SettingWidget::on_browseButton_clicked()
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

void KittySDK::SettingWidget::on_playButton_clicked()
{
  QSound::play(m_ui->pathEdit->text());
}
