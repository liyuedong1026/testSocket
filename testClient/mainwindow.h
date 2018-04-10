#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sendData();


public slots:
    void startSendData();

private slots:
    void on_btn_send_pressed();

    void on_btn_openfile_pressed();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_client;
    QTimer m_timer;
    QString m_strIP;
    int m_port;
    QFile m_file;
    QString m_filename;
    qint64 m_filesize;
    qint64 m_sendsize;
};

#endif // MAINWINDOW_H
