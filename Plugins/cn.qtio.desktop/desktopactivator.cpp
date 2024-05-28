#include "desktopactivator.h"

DesktopActivator::DesktopActivator()
{

}

void DesktopActivator::start(ctkPluginContext *context)
{
    m_mainWindow = new MainWindow(context);
    m_mainWindow->setWindowTitle(QStringLiteral("程序主窗口"));
    m_mainWindow->show();
}

void DesktopActivator::stop(ctkPluginContext *context)
{
    Q_UNUSED(context)
    if(m_mainWindow){
        m_mainWindow->deleteLater();
    }
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
Q_EXPORT_PLUGIN2(Desktop, DesktopActivator)
#endif
