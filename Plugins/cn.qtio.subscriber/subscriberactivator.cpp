#include "subscriberactivator.h"

#include <QDebug>
#include <service/event/ctkEventConstants.h>

void SubscriberActivator::start(ctkPluginContext* context)
{
    //事件管理服务
    ctkServiceReference eventAdminRef = context->getServiceReference<ctkEventAdmin>();
    m_eventAdmin = qobject_cast<ctkEventAdmin*>(context->getService(eventAdminRef));
    if (!m_eventAdmin) {
        qDebug() << "事件管理服务获取失败！";
    }

    //消息订阅
    ctkDictionary props;
    props.insert(ctkEventConstants::EVENT_TOPIC, "cn/qtio/eventAdmin/subscriber/handleEvent");
    context->registerService<ctkEventHandler>(this, props);
}

void SubscriberActivator::stop(ctkPluginContext* context)
{
    Q_UNUSED(context)
}

void SubscriberActivator::handleEvent(const ctkEvent& event)
{
    //订阅消息测试打印
    // foreach(QString propertyName, event.getPropertyNames()) {
    //     qDebug() << "key:"
    //         << propertyName
    //         << "value:"
    //         << event.getProperty(propertyName);
    // }
}
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
Q_EXPORT_PLUGIN2(Subscriber, SubscriberActivator)
#endif
