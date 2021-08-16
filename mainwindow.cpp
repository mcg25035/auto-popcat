#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
void MainWindow::pop_cat(){
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    QUrl url = QUrl("https://stats.popcat.click/pop?pop_count=800&captcha_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJDb3VudHJ5Q29kZSI6IlRXIiwiQ291bnRyeU5hbWUiOiJUYWl3YW4iLCJJUCI6IjQ5LjIxNy40Ni4xNSIsIklEIjoyMywiZXhwIjoxNjI5MDk5NjMzfQ.sQk5A5H1_9LLM4BB4xi7fgCcTkcRX4tO-h7XjHXDRhM");
    QNetworkRequest req(url);
    QNetworkReply * reply = mgr.get(req);
    eventLoop.exec();
    ui->textEdit->setPlainText(ui->textEdit->toPlainText()+"\n"+QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()));
    ui->textEdit->setPlainText(ui->textEdit->toPlainText()+"\n"+QString(reply->readAll()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer* timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()) ,this, SLOT(pop_cat()));
    timer->start(30000);

}

MainWindow::~MainWindow()
{
    //delete ui;
}

