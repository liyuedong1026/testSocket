#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QTime>
#include <QWaitCondition>
// 200KB/S
#define MAX_SPEED  (200*1024)
// 每一次4KB,一秒200KB,每20ms发送一次,timer间隔20ms
#define TIME_INTERVAL (20)

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

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(startSendData()));
}

MainWindow::~MainWindow()
{
    if (NULL != m_client) {
        m_client->disconnect();
        m_client->deleteLater();
    }
    delete ui;
}

void MainWindow::sendData()
{
    qDebug() << "sendData";
    if (NULL == m_client) {
        return;
    }

    qDebug("size = %lld", m_filesize);
    qint64 len = 0;
    do {
        QTime startTime = QTime::currentTime();
        char buf[4*1024] = {0};
        len = 0;
        len = m_file.read(buf,sizeof(buf));
        len = m_client->write(buf,len);
        m_sendsize += len;
        QTime stopTime = QTime::currentTime();
        int elapsed = startTime.msecsTo(stopTime);
        qDebug("sendData ms %d size %d", elapsed, m_sendsize);
        if (elapsed<TIME_INTERVAL) {
            sleep(TIME_INTERVAL-elapsed);
        }
    } while(len > 0);
}

void MainWindow::sleep(unsigned int mSec)
{
    QTime dieTime = QTime::currentTime().addMSecs(mSec);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::startSendData()
{
    qDebug() << "startSendData";
    m_timer.stop();
    sendData();
}

void MainWindow::on_btn_send_pressed()
{
    qDebug() << "on_btn_send_pressed";
    QString head = QString("%1##%2").arg(m_filename).arg(m_filesize);//自定义文件头部

     //发送头部信息
    qint64 len = m_client->write(head.toUtf8());
    if(len > 0)//头部信息发送成功
    {
        m_timer.start(20);
    }
}

void MainWindow::on_btn_openfile_pressed()
{
    QString filepath = QFileDialog::getOpenFileName(this,"open","../");

    if(!filepath.isEmpty())
    {
        m_filename.clear();
        m_filesize = 0;
        QFileInfo info(filepath);
        m_filename = info.fileName();
        m_filesize = info.size();
        m_sendsize = 0;
        m_file.setFileName(filepath);
    }
    m_file.open(QIODevice::ReadOnly);
}
