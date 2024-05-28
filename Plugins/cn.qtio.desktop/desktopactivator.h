#ifndef DESKTOPACTIVATOR_H
#define DESKTOPACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>
#include "mainwindow.h"

class DesktopActivator :
        public QObject,
        public ctkPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(ctkPluginActivator)
    Q_PLUGIN_METADATA(IID "Desktop")

public:

    DesktopActivator();

    void start(ctkPluginContext* context) Q_DECL_OVERRIDE;
    void stop(ctkPluginContext* context) Q_DECL_OVERRIDE;

private:
    MainWindow *m_mainWindow;
};

#endif // DESKTOPACTIVATOR_H
