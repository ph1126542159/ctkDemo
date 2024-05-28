#ifndef PLUGINADMINDIALOG_H
#define PLUGINADMINDIALOG_H

#include <QDialog>

#include <ctkPluginContext.h>
#include <service/event/ctkEventAdmin.h>
#include <service/pluginadmin/pluginAdmin.h>

namespace Ui {
class Dialog;
}

class PluginAdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginAdminDialog(ctkPluginContext *context,QWidget *parent = nullptr);
    ~PluginAdminDialog();

private slots:
    void on_install_pushButton_clicked();

    void on_start_pushButton_clicked();

    void on_stop_pushButton_clicked();

    void on_uninstall_pushButton_clicked();

private:
    Ui::Dialog *ui;
    PluginAdmin *m_pluginAdmin;
    ctkPluginContext *m_context;
};

#endif // PLUGINADMINDIALOG_H
