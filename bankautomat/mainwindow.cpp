#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnShowBooks_clicked()
{
    QString site_url="http://localhost:3000/book";
    QString credentials="newAdmin:newPass";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getBookSlot(QNetworkReply*)));
    reply = manager->get(request);
}

void MainWindow::getBookSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString book;
    foreach (const QJsonValue &value, json_array) {
    QJsonObject json_obj = value.toObject();
    book+=QString::number(json_obj["id_book"].toInt())+","+json_obj["name"].toString()+","+json_obj["author"].toString()+"\r";
    }
    qDebug()<<book;
    ui->txtBooks->setText(book);
    reply->deleteLater();
    manager->deleteLater();
}


void MainWindow::on_btnShowOneBook_clicked()
{
    QString site_url="http://localhost:3000/book/1";
    QString credentials="newAdmin:newPass";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    oneBookManager = new QNetworkAccessManager(this);
    connect(oneBookManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getOneBookSlot(QNetworkReply*)));
    reply = oneBookManager->get(request);
}
void MainWindow::getOneBookSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj = json_array[0].toObject();
    qDebug()<<json_obj["name"];
    QString book=json_obj["name"].toString()+" : "+json_obj["author"].toString()+" : "+json_obj["isbn"].toString();
    ui->txtBooks->setText(book);
}
