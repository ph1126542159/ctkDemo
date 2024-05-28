#ifndef SUBSCRIBERACTIVATOR_H
#define SUBSCRIBERACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>
#include <service/event/ctkEventAdmin.h>
#include <service/event/ctkEventHandler.h>

class SubscriberActivator :
    public QObject,
    public ctkPluginActivator,
    public ctkEventHandler
{
    Q_OBJECT
        Q_INTERFACES(ctkPluginActivator)
        Q_INTERFACES(ctkEventHandler)
        Q_PLUGIN_METADATA(IID "Subscriber")

public:
    void start(ctkPluginContext* context) Q_DECL_OVERRIDE;
    void stop(ctkPluginContext* context) Q_DECL_OVERRIDE;

private:
    void handleEvent(const ctkEvent& event) Q_DECL_OVERRIDE;

private:
    ctkEventAdmin* m_eventAdmin;
};

#endif // SUBSCRIBERACTIVATOR_H
