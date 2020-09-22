#include "drinkinfo.h"
#include "ui_drinkinfo.h"
#include <QTextDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>


drinkInfo::drinkInfo(QWidget *parent, QString name, QString instructions, QString url, QString ingredients) :
    QDialog(parent),
    ui(new Ui::drinkInfo)
{
    ui->setupUi(this);
    ui->drinkName->setText(name); //Set title
    ui->instructions->setPlainText(instructions); // Set instruction
    ui->instructions->setReadOnly(true); //Change browserWindow on read only
    std::string strAvatarUrl = url.toUtf8().constData();
    ui->plainTextEdit->setPlainText(ingredients);
    ui->plainTextEdit->setReadOnly(true);
    QLabel *lable = ui->label;
    QUrl urlCB(QString().fromStdString(strAvatarUrl));
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.get(QNetworkRequest(urlCB));
    QObject::connect(reply, &QNetworkReply::finished, &loop, [&reply, &lable,&loop](){ //Getting image without download it
     if (reply->error() == QNetworkReply::NoError)
     {
         QByteArray jpegData = reply->readAll();
         QPixmap pixmap;
         pixmap.loadFromData(jpegData);

         if (!pixmap.isNull())
         {
             lable->clear();
             lable->setPixmap(pixmap); //Set image
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
