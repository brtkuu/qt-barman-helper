#include "drinkinfo.h"
#include "ui_drinkinfo.h"
#include <QTextDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>


drinkInfo::drinkInfo(QWidget *parent, QString name, QString instructions, QString url) :
    QDialog(parent),
    ui(new Ui::drinkInfo)
{
    ui->setupUi(this);
    ui->drinkName->setText(name);
    ui->instructions->setPlainText(instructions);
    ui->instructions->setReadOnly(true);
    std::string strAvatarUrl = url.toUtf8().constData();
    QLabel *lable = ui->label;
    QUrl urlCB(QString().fromStdString(strAvatarUrl));
    QNetworkAccessManager manager;
    QEventLoop loop;

    QNetworkReply *reply = manager.get(QNetworkRequest(urlCB));
    QObject::connect(reply, &QNetworkReply::finished, &loop, [&reply, &lable,&loop](){
     if (reply->error() == QNetworkReply::NoError)
     {
         QByteArray jpegData = reply->readAll();
         QPixmap pixmap;
         pixmap.loadFromData(jpegData);

         if (!pixmap.isNull())
         {
             lable->clear();
             lable->setPixmap(pixmap);
             lable->setScaledContents(true);
         }
     }
     loop.quit();
   });

   loop.exec();
}

drinkInfo::~drinkInfo()
{
    delete ui;
}
