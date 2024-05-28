#ifndef PLUGINADMINSERVICE_H
#define PLUGINADMINSERVICE_H

#include <QObject>
#include <service/pluginadmin/pluginAdmin.h>
#include <ctkPluginContext.h>
#include <service/event/ctkEventAdmin.h>

class PluginAdminService :public QObject,public PluginAdmin
{
    Q_OBJECT
    Q_INTERFACES(PluginAdmin)

public:
    explicit PluginAdminService(ctkPluginContext* context,QObject *parent = nullptr);
    ~PluginAdminService();

public:
    void installAllPlugin() Q_DECL_OVERRIDE;
    void startAllPlugin() Q_DECL_OVERRIDE;
    void stopAllPlugin() Q_DECL_OVERRIDE;
    void uninstallAllPlugin() Q_DECL_OVERRIDE;

signals:

private slots:

private:
    ctkPluginContext *m_context;
    ctkDictionary m_dictionary;
    ctkProperties m_properties;
    //事件管理服务插件
    ctkEventAdmin *m_eventAdmin;
    QSharedPointer<ctkPluginFramework> m_framework;
    QStringList m_libFilter;
    QString m_path;
};

#endif // PLUGINADMINSERVICE_H
