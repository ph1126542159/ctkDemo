#include "pluginadminservice.h"
#include <service/event/ctkEventConstants.h>
#include <QCoreApplication>
#include <QDirIterator>
#include <QJsonArray>
#include <QThread>
#include <ctkPluginException.h>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFrameworkLauncher.h>

PluginAdminService::PluginAdminService(ctkPluginContext *context, QObject *parent) :
    QObject(parent),
    m_context(context),
    m_eventAdmin(nullptr),
    m_framework(nullptr)
{
    //注册插件管理服务
    context->registerService<PluginAdmin>(this);
    ctkServiceReference eventRef = context->getServiceReference<ctkEventAdmin>();
    m_eventAdmin = qobject_cast<ctkEventAdmin*>(context->getService(eventRef));
    if(eventRef){
        context->ungetService(eventRef);
    }

    m_path = QCoreApplication::applicationDirPath() + "/plugins";
    ctkPluginFrameworkLauncher::addSearchPath(m_path,true);
#if defined(Q_OS_WIN)
    m_libFilter << "*.dll";
#elif defined(Q_OS_LINUX)
    m_libFilter << "*.so";
#elif defined(Q_OS_MAC)
    m_libFilter << "*.dylib";
#endif
}

PluginAdminService::~PluginAdminService()
{
}

void PluginAdminService::installAllPlugin()
{
    QDirIterator dirIter(m_path, m_libFilter, QDir::Files);
    QString fileLocation;
    while(dirIter.hasNext()) {
        try {
            fileLocation = dirIter.next();
            if(!fileLocation.contains(QString("pluginadmin"))){
                m_context->installPlugin(QUrl::fromLocalFile(fileLocation));
                qDebug() << QStringLiteral("1.1 安装插件：") << fileLocation;
            } else {
                qDebug() << QStringLiteral("1.2 未重复安装插件：" )<< fileLocation;
            }
        }
        catch (const ctkPluginException& exc) {
            qCritical() << fileLocation << exc.what();
        }
    }
}

void PluginAdminService::startAllPlugin()
{
    foreach (const QSharedPointer<ctkPlugin> &plugin, m_context->getPlugins()) {
        try {
            if(QString("system.plugin") != plugin->getSymbolicName()
                    && QString("pluginadmin") != plugin->getSymbolicName()){
                plugin->start();
                qDebug() <<QStringLiteral( "2.1 启动插件：" )<< plugin->getSymbolicName();
            } else {
                qDebug() <<QStringLiteral( "2.2 未重复启动插件：") << plugin->getSymbolicName();
            }
        }
        catch (const ctkPluginException& exc) {
            qCritical() << exc.what();
        }
    }
}

void PluginAdminService::stopAllPlugin()
{
    foreach (const QSharedPointer<ctkPlugin> &plugin, m_context->getPlugins()) {
        try {
            if(QString("system.plugin") != plugin->getSymbolicName()
                    && QString("pluginadmin") != plugin->getSymbolicName()){
                qDebug() << QStringLiteral("3.1 停止插件：" )<< plugin->getSymbolicName();
                plugin->stop();
            } else {
                qDebug() << QStringLiteral(".2 未停止运行插件：" )<< plugin->getSymbolicName();
            }
        }
        catch (const ctkPluginException& exc) {
            qCritical() << exc.what();
        }
    }
}

void PluginAdminService::uninstallAllPlugin()
{
    foreach (const QSharedPointer<ctkPlugin> &plugin, m_context->getPlugins()) {
        try {
            if(QString("system.plugin") != plugin->getSymbolicName()
                    && QString("pluginadmin") != plugin->getSymbolicName()){
                qDebug() << QStringLiteral("4.1 卸载插件：" )<< plugin->getSymbolicName();
                plugin->uninstall();
            }
        }
        catch (const ctkPluginException& exc) {
            qCritical() << exc.what();
        }
    }

    foreach (const QSharedPointer<ctkPlugin> &plugin, m_context->getPlugins()) {
        qDebug() << QStringLiteral("4.2 未卸载插件：" )<< plugin->getSymbolicName();
    }
}

















