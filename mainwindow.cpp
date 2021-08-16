#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
void MainWindow::pop_cat(){
    QString token;
    QString generate_char;
    qsrand(QTime::currentTime().msec());
    for (int i=1;i<=200;i++){
        generate_char = QString((qrand()%79)+45);
        if (QString("0123456789@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_").contains(generate_char)){
            token+=generate_char;
        }else{
            token+="_";
        }
    }
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    QUrl url = QUrl("https://stats.popcat.click/pop?pop_count=800&captcha_token="+token);
    QNetworkRequest req(url);
    QNetworkReply * reply = mgr.get(req);
    eventLoop.exec();
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==201){
        ui->success_times->setText(QString::number(ui->success_times->text().toInt()+1));
        ui->total_pops->setText(QString::number(ui->total_pops->text().toInt()+800));
    }else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==0){
        ui->failure_times->setText(QString::number(ui->failure_times->text().toInt()+1));
        ui->textEdit->setPlainText(ui->textEdit->toPlainText()+"\n"+QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()));
        ui->textEdit->setPlainText(ui->textEdit->toPlainText()+"\n"+"No Internet\n沒有連線\n------------------------------------------------------------------");
        return;
    }else
    {
        ui->failure_times->setText(QString::number(ui->failure_times->text().toInt()+1));
    }
    ui->textEdit->setPlainText(ui->textEdit->toPlainText()+"\n"+QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()));
    ui->textEdit->setPlainText(ui->textEdit->toPlainText()+"\n"+QString(reply->readAll())+"------------------------------------------------------------------");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pop_cat();
    QTimer* timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()) ,this, SLOT(pop_cat()));
    timer->start(30000);

}

MainWindow::~MainWindow()
{
    //delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->setPlainText("");
}
