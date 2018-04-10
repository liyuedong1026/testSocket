#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
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

public slots:
    void serverNewConnect();
    void socketReadData();
    void socketDisconnected();

private:
    Ui::MainWindow *ui;
    QTcpServer* m_server;
    QTcpSocket* m_socket;
    int m_port;
};

#endif // MAINWINDOW_H
