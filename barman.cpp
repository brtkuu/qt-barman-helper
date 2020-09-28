#include "barman.h"
#include "ui_barman.h"
#include <curl/curl.h>
#include <json.hpp>
#include <QListWidget>
#include <QMessageBox>
#include <string.h>


using json = nlohmann::json;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

// Getting response from api
QString getResponse(char* url){
    CURL* curl;
    QString response;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    std::string response_string;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        response = QString::fromStdString(response_string);
        curl_global_cleanup();
        curl = NULL;


}
    return response;
}

// Changing two-part query space to underscore
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

// Search button
void Barman::on_pushButton_clicked()
{
    ui->listWidget->clear(); //Clear list
    QString queryQStr = ui->lineEdit->text(); //Getting query string
    QByteArray ba = queryQStr.toLocal8Bit(); //Changing QString to QByteArray for chenage it to char
    const char *c_str2 = ba.data();
    char url[200] = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=";
    strncat(url, c_str2, 100);
    QString res = getResponse(url);

    std::string respString = res.toUtf8().data();
    json j = json::parse(respString);
    for(unsigned long i =0; i<j["drinks"].size(); i++){
    std::string drinkName = j["drinks"][i]["strDrink"];
    QListWidgetItem *item =new QListWidgetItem(QIcon(":/res/drink-icon.png"), QString::fromStdString(drinkName));
    ui->listWidget->addItem(item);
    }
}


//DoubleClick on list element handle
void Barman::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    std::string stringText = space2underscore(item->text().toStdString()); //Changeing spacer on underscore
    const char *c_str2 = stringText.c_str();
    char url[200] = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=";
    strncat(url, c_str2, 100);
    QString res = getResponse(url);
    json j = json::parse(res.toStdString());
    std::string name = j["drinks"][0]["strDrink"];
    std::string instructions = j["drinks"][0]["strInstructions"];
    std::string imgUrl = j["drinks"][0]["strDrinkThumb"];
    QString ingredients = "";
    for(int i=1; i<=15; i++ ){
        std::string iStr = std::to_string(i);
        if(!j["drinks"][0]["strIngredient"+iStr].size()){
               break;
        }
        std::string ingredient = j["drinks"][0]["strIngredient"+iStr];
        ingredients += QString::fromStdString(ingredient);
        if(j["drinks"][0]["strMeasure"+iStr].size()){
            ingredients += " - ";
            ingredients += QString::fromStdString(j["drinks"][0]["strMeasure"+iStr]);
        }
            ingredients += "\n";
    }
    drinkInfo = new class drinkInfo(this, QString::fromStdString(name), QString::fromStdString(instructions),QString::fromStdString(imgUrl), ingredients); //initialization drinkInfo window
    drinkInfo->show();
}
