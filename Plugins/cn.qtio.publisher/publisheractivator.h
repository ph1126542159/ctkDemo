#ifndef TESTPLUGINACTIVATOR_H
#define TESTPLUGINACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class PublisherActivator : public QObject, public ctkPluginActivator
{
    Q_OBJECT
        Q_INTERFACES(ctkPluginActivator)
        Q_PLUGIN_METADATA(IID "Publisher")

public:
    void start(ctkPluginContext* context) Q_DECL_OVERRIDE;
    void stop(ctkPluginContext* context) Q_DECL_OVERRIDE;
};

#endif // TESTPLUGINACTIVATOR_H
