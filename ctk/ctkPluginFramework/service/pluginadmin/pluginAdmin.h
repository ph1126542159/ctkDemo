#ifndef PLUGINADMIN_H
#define PLUGINADMIN_H

#include <QSharedPointer>
#include <ctkPluginFramework.h>

struct PluginAdmin
{
    virtual ~PluginAdmin() {}

    virtual void installAllPlugin() = 0;
    virtual void startAllPlugin() = 0;
    virtual void stopAllPlugin() = 0;
    virtual void uninstallAllPlugin() = 0;
};

Q_DECLARE_INTERFACE(PluginAdmin, "pluginadmin")
#endif // PLUGINADMIN_H
