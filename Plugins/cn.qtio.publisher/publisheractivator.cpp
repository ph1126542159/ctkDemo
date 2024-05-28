#include "publisheractivator.h"

#include <QDebug>
#include <QThread>
#include <service/event/ctkEventAdmin.h>

void PublisherActivator::start(ctkPluginContext* context)
{
    ctkServiceReference ref = context->getServiceReference<ctkEventAdmin>();
    ctkEventAdmin* eventAdmin = qobject_cast<ctkEventAdmin*>(context->getService(ref));
    ctkProperties props;
    props.insert("type", "消息类型");
    ctkEvent event("cn/qtio/eventAdmin/subscriber/handleEvent", props);
    if (eventAdmin) {
        //sendEvent:同步通信
        eventAdmin->sendEvent(event);
    }
}

void PublisherActivator::stop(ctkPluginContext* context)
{
    Q_UNUSED(context)
}
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
Q_EXPORT_PLUGIN2(Publisher, PublisherActivator)
#endif
