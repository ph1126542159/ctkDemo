#include "pluginadminactivator.h"
#include <QDebug>

PluginAdminActivator::PluginAdminActivator():
    m_pluginAdminThread(nullptr)
{

}

void PluginAdminActivator::start(ctkPluginContext *context)
{
    qDebug() << "插件启动";
    m_pluginAdminThread = new PluginAdminThread(context);
    m_pluginAdminThread->start();

    m_pluginAdminDialog = new PluginAdminDialog(context);
    m_pluginAdminDialog->setWindowTitle(QStringLiteral("插件管理器"));
    m_pluginAdminDialog->show();
}

void PluginAdminActivator::stop(ctkPluginContext *context)
{
    Q_UNUSED(context)
    if(m_pluginAdminThread)
    {
        m_pluginAdminThread->exit();
        m_pluginAdminThread->wait();
        m_pluginAdminThread->deleteLater();
        m_pluginAdminThread = nullptr;
    }
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
Q_EXPORT_PLUGIN2(PluginAdmin, PluginAdminActivator)
#endif
