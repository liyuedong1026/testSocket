#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_send_pressed();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_client;
    QString m_strIP;
    int m_port;
};

#endif // MAINWINDOW_H
