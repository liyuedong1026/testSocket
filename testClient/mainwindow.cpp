#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("testClient");

    m_strIP = "127.0.0.1";
    m_port = 5555;

    m_client = new QTcpSocket(this);

    if (NULL != m_client) {
        m_client->abort();
        m_client->connectToHost(m_strIP, m_port);
        if(m_client->waitForConnected(30000)){
            qDebug() << "Connect successfully!";
        }
        else {
            qDebug() << "Connect fail!";
        }
    }
}

MainWindow::~MainWindow()
{
    if (NULL != m_client) {
        m_client->disconnect();
        m_client->deleteLater();
    }
    delete ui;
}

void MainWindow::on_btn_send_pressed()
{

}
