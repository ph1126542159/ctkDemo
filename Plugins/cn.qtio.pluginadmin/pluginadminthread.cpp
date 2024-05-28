#include "pluginadminthread.h"

PluginAdminThread::PluginAdminThread(ctkPluginContext *context):
    m_context(context),
    m_pluginAdmin(nullptr)
{

}

PluginAdminThread::~PluginAdminThread()
{
    if(nullptr != m_pluginAdmin)
    {
        m_pluginAdmin->deleteLater();
        m_pluginAdmin = nullptr;
    }
}

void PluginAdminThread::run()
{
    m_pluginAdmin = new PluginAdminService(m_context);
    exec();
}
