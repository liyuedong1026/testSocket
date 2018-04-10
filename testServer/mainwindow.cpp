#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PORT_VALUE (5555)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("testServer");

    m_server = new QTcpServer();
    m_port = PORT_VALUE;
    if (NULL != m_server) {
        connect(m_server, SIGNAL(newConnection()), this, SLOT(serverNewConnect()));
        m_server->listen(QHostAddress::Any, m_port);
    }
}

MainWindow::~MainWindow()
{
    if (NULL != m_server) {
        m_server->close();
        m_server->deleteLater();
    }
    delete ui;
}

void MainWindow::serverNewConnect()
{
    if (NULL != m_server) {
        m_socket = m_server->nextPendingConnection();
        if (NULL != m_socket) {
            connect(m_socket, SIGNAL(readyRead()), this, SLOT(socketReadData()));
            connect(m_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        }
        qDebug() << "A Client connect!";
    }
}

void MainWindow::socketReadData()
{
    if (NULL != m_socket) {
        QByteArray buffer;
        //读取缓冲区数据
        buffer = m_socket->readAll();
        if(!buffer.isEmpty())
        {
            qDebug() << "A Client socketReadData!";
        }
    }
}

void MainWindow::socketDisconnected()
{
    qDebug() << "Disconnected!";
}
