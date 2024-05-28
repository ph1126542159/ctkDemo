#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QDirIterator>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include <QThread>
#include <QTimer>
#include <QUuid>
#include <ctkPluginException.h>
#include <ctkPluginFramework.h>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFrameworkLauncher.h>
#include <service/event/ctkEventConstants.h>
#include <service/event/ctkEventHandler.h>


MainWindow::MainWindow(ctkPluginContext* context, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_eventAdmin(nullptr),
    m_context(context)
{
    ui->setupUi(this);

    //事件管理服务
    ctkServiceReference eventAdminRef = m_context->getServiceReference<ctkEventAdmin>();
    m_eventAdmin = qobject_cast<ctkEventAdmin*>(m_context->getService(eventAdminRef));
    if (!m_eventAdmin) {
        qDebug() << QStringLiteral("事件管理服务获取失败！");
    }

    //插件管理服务
    ctkServiceReference pluginAdminRef = context->getServiceReference<PluginAdmin>();
    m_pluginAdmin = qobject_cast<PluginAdmin*>(context->getService(pluginAdminRef));
    if (!m_pluginAdmin) {
        qDebug() << QStringLiteral("插件管理服务获取失败！");
    }

    //消息订阅
    ctkDictionary props;
    props.insert(ctkEventConstants::EVENT_TOPIC, "cn/qtio/eventAdmin/MainWindow/handleEvent");
    context->registerService<ctkEventHandler>(this, props);

    //注册异步信号
    m_eventAdmin->publishSignal(this, SIGNAL(queuedPublished(ctkDictionary)), "cn/qtio/eventAdmin/subscriber/handleEvent", Qt::QueuedConnection);
    //注册同步信号
    m_eventAdmin->publishSignal(this, SIGNAL(directPublished(ctkDictionary)), "cn/qtio/eventAdmin/subscriber/handleEvent", Qt::DirectConnection);

    // //订阅消息
    m_eventAdmin->subscribeSlot(this, SLOT(subscribeSlot(const ctkEvent&)), props, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event);
}
void MainWindow::subscribeSlot(const ctkEvent& event) {
    //查看消息包所有信息
    m_logService->log(ctkLogService::LOG_INFO, QStringLiteral("MainWindow::subscribeSlot(const ctkEvent& event)"));

    // foreach(QString propertyName, event.getPropertyNames()) {
    //     qDebug() << "key:"
    //         << propertyName
    //         << "value:"
    //         << event.getProperty(propertyName);
    // }
}
void MainWindow::handleEvent(const ctkEvent& event)
{
    m_logService->log(ctkLogService::LOG_INFO, QStringLiteral("MainWindow::handleEvent(const ctkEvent& event)"));
}

void MainWindow::on_subscriber_pushButton_clicked()
{

    try {
        //日志服务
        ctkServiceReference logServiceRef = m_context->getServiceReference("ctkLogService");
        m_logService = qobject_cast<ctkLogService*>(m_context->getService(logServiceRef));
        if (!m_logService) {
            qDebug() << QStringLiteral("日志服务获取失败！");
        }
        else {
            m_logService->log(ctkLogService::LOG_INFO, QStringLiteral("====================MainWindow::init()==========================="));
        }
    }
    catch (...) {

    }
}

void MainWindow::on_send_pushButton_clicked()
{
    ctkProperties props;
    //消息包类型
    props.insert("packType", "MainWindow");
    //发送方式
    props.insert("sendType", "sendEvent");
    //事件业务
    props.insert("handleEvent", "MainWindow::on_send_pushButton_clicked()");
    ctkEvent event("cn/qtio/eventAdmin/MainWindow/handleEvent", props);
    if (m_eventAdmin) {
        //sendEvent:同步发布
        m_eventAdmin->sendEvent(event);
    }
}

void MainWindow::on_post_pushButton_clicked()
{
    ctkProperties props;
    //消息包类型
    props.insert("packType", "MainWindow");
    //发送方式
    props.insert("sendType", "postEvent");
    //事件业务
    props.insert("handleEvent", "MainWindow::on_send_pushButton_clicked()");
    ctkEvent event("cn/qtio/eventAdmin/subscriber/handleEvent", props);
    if (m_eventAdmin) {
        //postEvent:异步发布
        m_eventAdmin->postEvent(event);
    }
}

void MainWindow::on_direct_pushButton_clicked()
{
    ctkDictionary props;
    //消息包类型
    props.insert("packType", "MainWindow");
    //发送方式
    props.insert("sendType", "sendEvent");
    //事件业务
    props.insert("handleEvent", "MainWindow::on_send_pushButton_clicked()");
    emit queuedPublished(props);
}

void MainWindow::on_queued_pushButton_clicked()
{
    ctkDictionary props;
    //消息包类型
    props.insert("packType", "MainWindow");
    //发送方式
    props.insert("sendType", "postEvent");
    //事件业务
    props.insert("handleEvent", "MainWindow::on_send_pushButton_clicked()");
    emit queuedPublished(props);
}
