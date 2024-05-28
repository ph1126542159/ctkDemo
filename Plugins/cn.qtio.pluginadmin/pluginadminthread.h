#ifndef PLUGINADMINTHREAD_H
#define PLUGINADMINTHREAD_H

#include <QThread>
#include <ctkPluginContext.h>
#include "pluginadminservice.h"

class PluginAdminThread : public QThread
{
public:
    PluginAdminThread(ctkPluginContext* context);
    ~PluginAdminThread();
    // QThread interface
protected:
    void run();

private:
    PluginAdminService *m_pluginAdmin;
    ctkPluginContext *m_context;
};

#endif // PLUGINADMINTHREAD_H
