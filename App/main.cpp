#include <ctkPluginContext.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFrameworkLauncher.h>

#include <QDebug>
#include <QDirIterator>
#include <QApplication>
#include <QCoreApplication>
#include <QTextCodec>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //启动框架
    QString path = QCoreApplication::applicationDirPath() + "/plugins";
    ctkPluginFrameworkLauncher::addSearchPath(path, true);
    ctkProperties properties;
    properties.insert(ctkPluginConstants::FRAMEWORK_STORAGE_CLEAN, ctkPluginConstants::FRAMEWORK_STORAGE_CLEAN_ONFIRSTINIT);
    ctkPluginFrameworkFactory fwFactory(properties);
    QSharedPointer<ctkPluginFramework> framework = fwFactory.getFramework();
    try {
        framework->init();
        framework->start();
    }
    catch (const ctkPluginException& exc) {
        qCritical() << QStringLiteral("插件框架启动失败。") << exc;
        return -1;
    }

    //安装插件
    //获取插件上下文
    ctkPluginContext* pluginContext = framework->getPluginContext();
    QStringList libFilter;

    //安装插件
    //平台判断
#if defined(Q_OS_WIN)
    libFilter << "*.dll";
#elif defined(Q_OS_LINUX)
    libFilter << "*.so";
#elif defined(Q_OS_MAC)
    libFilter << "*.dylib";
#endif
    QDirIterator dirIter(path, libFilter, QDir::Files);
    QString fileLocation;
    while (dirIter.hasNext()) {
        try {
            fileLocation = dirIter.next();
            qDebug() << QStringLiteral("1.安装插件：") << fileLocation;
            pluginContext->installPlugin(QUrl::fromLocalFile(fileLocation));
        }
        catch (const ctkPluginException& exc) {
            qCritical() << Q_FUNC_INFO << fileLocation << exc.what();
            return -1;
        }
    }

    //启动插件
    foreach(const QSharedPointer<ctkPlugin> &plugin, pluginContext->getPlugins()) {
        try {
            QHash<QString, QString> headers = plugin->getHeaders();
            qDebug() << QStringLiteral("2.启动插件，清单信息:") << headers;
            plugin->start();
        }
        catch (const ctkPluginException& exc) {
            qCritical() << exc.what();
            return -1;
        }
    }

    return a.exec();
}
