#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pankki.h"

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnShowBooks_clicked();
    void getBookSlot (QNetworkReply *reply);
    void getOneBookSlot (QNetworkReply *reply);
    void loginSlot (QNetworkReply *reply);

    void on_btnShowOneBook_clicked();

    void on_btnLogin_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *oneBookManager;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    Pankki *objPankki;
};
#endif // MAINWINDOW_H
