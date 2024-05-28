#include "pluginadmindialog.h"
#include "ui_dialog.h"

#include <ctkPluginException.h>
#include <ctkPluginFramework.h>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFrameworkLauncher.h>
#include <service/event/ctkEventConstants.h>
#include <service/event/ctkEventHandler.h>

#include <QDebug>

PluginAdminDialog::PluginAdminDialog(ctkPluginContext *context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_context(context)
{
    ui->setupUi(this);
    //插件管理器
    ctkServiceReference pluginAdminRef = context->getServiceReference<PluginAdmin>();
    m_pluginAdmin = qobject_cast<PluginAdmin *>(context->getService(pluginAdminRef));
    if(!m_pluginAdmin){
        qDebug() << QStringLiteral("获取插件管理器失败！");
    }
}

PluginAdminDialog::~PluginAdminDialog()
{
    delete ui;
}

void PluginAdminDialog::on_install_pushButton_clicked()
{
    m_pluginAdmin->installAllPlugin();
}

void PluginAdminDialog::on_start_pushButton_clicked()
{
    m_pluginAdmin->startAllPlugin();
}

void PluginAdminDialog::on_stop_pushButton_clicked()
{
    m_pluginAdmin->stopAllPlugin();
}

void PluginAdminDialog::on_uninstall_pushButton_clicked()
{
    m_pluginAdmin->uninstallAllPlugin();
}
