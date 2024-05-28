#ifndef PLUGINADMINACTIVATOR_H
#define PLUGINADMINACTIVATOR_H

#include "pluginadminthread.h"
#include "pluginadmindialog.h"

#include <ctkPluginActivator.h>

#include <QObject>

class PluginAdminActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(ctkPluginActivator)
    Q_PLUGIN_METADATA(IID "pluginadmin")

public:
    PluginAdminActivator();

    void start(ctkPluginContext* context) Q_DECL_OVERRIDE;
    void stop(ctkPluginContext* context) Q_DECL_OVERRIDE;

private:
    QThread *m_pluginAdminThread;
    PluginAdminDialog* m_pluginAdminDialog;
};

#endif // PLUGINADMINACTIVATOR_H
