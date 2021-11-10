#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objPankki=new Pankki;
}

MainWindow::~MainWindow()
{
    delete ui;
    ui=nullptr;
    delete objPankki;
    objPankki=nullptr;
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
    qDebug()<<json_doc["name"];
    QString book=json_doc["name"].toString()+" : "+json_doc["author"].toString()+" : "+json_doc["isbn"].toString();
    ui->txtBooks->setText(book);
}


void MainWindow::on_btnLogin_clicked()
{
    QJsonObject json; //luodaan JSON objekti ja lisätään data
    json.insert("username",ui->lineEditUsername->text());
    json.insert("password",ui->lineEditPassword->text());
    QString site_url="http://localhost:3000/login";
    QString credentials="newAdmin:newPass";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->post(request, QJsonDocument(json).toJson());
}
void MainWindow::loginSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data=="true"){
        qDebug()<<"Oikea tunnus ...avaa form";
        objPankki->show();
    }
    else {
        ui->lineEditPassword->setText("");
        ui->lineEditUsername->setText("");
        qDebug()<<"tunnus ja salasana ei täsmää";
    }
}
