#include "barman.h"
#include "ui_barman.h"
#include <curl/curl.h>
#include <json.hpp>
#include <QListWidget>
#include <QMessageBox>
#include <mongocxx/v_noabi/mongocxx/client.hpp>
#include <mongocxx/v_noabi/mongocxx/stdx.hpp>
#include <mongocxx/v_noabi/mongocxx/uri.hpp>
#include <mongocxx/v_noabi/mongocxx/instance.hpp>

using json = nlohmann::json;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

QString getRequest(char* url){
    CURL* curl;
    QString response;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    std::string response_string;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, "WZMYAGdjYMbkkVpM0D25jGym3zO7ZQMd");

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        response = QString::fromStdString(response_string);
        curl_global_cleanup();
        curl = NULL;


}
    return response;
}

std::string space2underscore(std::string text) {
    for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
        if(*it == ' ') {
            *it = '_';
        }
    }
    return text;
}

Barman::Barman(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Barman)
{
    ui->setupUi(this);
}

Barman::~Barman()
{
    delete ui;
}


void Barman::on_pushButton_clicked()
{
    ui->listWidget->clear();
    QString queryQStr = ui->lineEdit->text();
    QByteArray ba = queryQStr.toLocal8Bit();
    const char *c_str2 = ba.data();
    char url[200] = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=";
    strncat(url, c_str2, 100);
    QString res = getRequest(url);

    std::string respString = res.toUtf8().data();
    json j = json::parse(respString);
    for(unsigned long i =0; i<j["drinks"].size(); i++){
    std::string drinkName = j["drinks"][i]["strDrink"];
    QListWidgetItem *item =new QListWidgetItem(QIcon(":/res/drink-icon.png"), QString::fromStdString(drinkName));
    ui->listWidget->addItem(item);
    }
}



void Barman::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    std::string stringText = space2underscore(item->text().toStdString());
    const char *c_str2 = stringText.c_str();
    char url[200] = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=";
    strncat(url, c_str2, 100);
    QString res = getRequest(url);
    json j = json::parse(res.toStdString());
    std::string name = j["drinks"][0]["strDrink"];
    std::string instructions = j["drinks"][0]["strInstructions"];
    std::string imgUrl = j["drinks"][0]["strDrinkThumb"];
    drinkInfo = new class drinkInfo(this, QString::fromStdString(name), QString::fromStdString(instructions),QString::fromStdString(imgUrl));
    drinkInfo->show();
}
