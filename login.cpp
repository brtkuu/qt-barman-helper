#include "login.h"
#include "ui_login.h"
#include "barman.h"
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <cstdint>
#include <vector>
#include <bsoncxx/json.hpp>
#include <json.hpp>

using json = nlohmann::json;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

mongocxx::instance instance{}; // This should be done only once.
mongocxx::uri uri("mongodb://localhost:27017");
mongocxx::client client(uri);
mongocxx::database db = client["barmandb"];
mongocxx::collection loginColl = db["login"];

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{

    std::string login = ui->lineEdit->text().toStdString();
    std::string passwd = ui->lineEdit_2->text().toStdString();
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            loginColl.find_one({make_document(kvp("login", login))});
    if(maybe_result) {
       std::string rawResult = bsoncxx::to_json(maybe_result->view());
       json j = json::parse(rawResult);
       std::string resLogin = j["login"];
       std::string resPasswd = j["passwd"];
       if(resLogin == login && resPasswd == passwd){
           hide();
           barman = new class Barman(this);
           barman->show();
       }else {
           ui->label_3->setText("Wrong password");
       }

    }else {
        ui->label_3->setText("Wrong login");
    }
}

void Login::on_pushButton_2_clicked()
{
    registerView = new class Register(this);
    registerView->show();
}
