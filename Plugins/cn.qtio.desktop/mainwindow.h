#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <ctkPluginContext.h>
#include <service/event/ctkEventAdmin.h>
#include <service/event/ctkEventHandler.h>
#include <service/pluginadmin/pluginAdmin.h>
#include <service/log/ctkLogService.h>
namespace Ui {
    class MainWindow;
}

class MainWindow :public QMainWindow,
    public ctkEventHandler
{
    Q_OBJECT
        Q_INTERFACES(ctkEventHandler)

public:
    explicit MainWindow(ctkPluginContext* context, QWidget* parent = nullptr);

    ~MainWindow() override;
signals:
    void queuedPublished(const ctkDictionary&);

    void directPublished(const ctkDictionary&);

protected:
    void closeEvent(QCloseEvent* event) override;
private slots:

    void on_subscriber_pushButton_clicked();

    void on_send_pushButton_clicked();

    void on_post_pushButton_clicked();

    void on_queued_pushButton_clicked();

    void on_direct_pushButton_clicked();

    void subscribeSlot(const ctkEvent& even);
private:
    void handleEvent(const ctkEvent& event) Q_DECL_OVERRIDE;
    Ui::MainWindow* ui;
    ctkDictionary m_dictionary;
    ctkEventAdmin* m_eventAdmin;
    ctkPluginContext* m_context;
    PluginAdmin* m_pluginAdmin;
    ctkLogService* m_logService;
};

#endif // MAINWINDOW_H
