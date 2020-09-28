#include "login.h"
#include "ui_login.h"
#include "barman.h"
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/options/insert.hpp>
#include <bsoncxx/json.hpp>
#include <json.hpp>
#include <bsoncxx/builder/stream/document.hpp>


using json = nlohmann::json;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;


// Connect with local mongo database
mongocxx::instance instance{};
mongocxx::uri uri("mongodb://localhost:27017");
mongocxx::client client(uri);
mongocxx::database db = client["barmandb"];
mongocxx::collection loginColl = db["login"];

// Create mongo querry document
bsoncxx::document::value createDoc(std::string username, std::string password) {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
      << "login" << username
      << "passwd" << password
      << bsoncxx::builder::stream::finalize;

    return doc_value;
}

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{

    ui->setupUi(this);
    // Set password edit lines
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
}
// Clear all edit lines in add/delete user form
void Login::clearEdits() {
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
}


Login::~Login()
{
    delete ui;
}

// Login button
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

// Add button
void Login::on_pushButton_2_clicked()
{
    std::string username = ui->lineEdit_3->text().toStdString();
    std::string password = ui->lineEdit_4->text().toStdString();
    std::string bosspasswd = ui->lineEdit_5->text().toStdString();

    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            loginColl.find_one({make_document(kvp("login", "boss"))});

    if(maybe_result) {
       std::string rawResult = bsoncxx::to_json(maybe_result->view());
       json j = json::parse(rawResult);
       std::string resPasswd = j["passwd"];
       if(resPasswd == bosspasswd){
           bsoncxx::document::value doc_value = createDoc(username, password);

           bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
            loginColl.insert_one(doc_value.view());
           ui->label_7->setText("Account created!");
       }else {
           ui->label_7->setText("Access denied");
           clearEdits();
       }

    }else {
        ui->label_7->setText("You have not boss account");
        clearEdits();
    }
}

//Delete button
void Login::on_pushButton_3_clicked()
{
    std::string username = ui->lineEdit_3->text().toStdString();
    std::string password = ui->lineEdit_4->text().toStdString();
    std::string bosspasswd = ui->lineEdit_5->text().toStdString();

    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            loginColl.find_one({make_document(kvp("login", "boss"))});

    if(maybe_result) {
       std::string rawResult = bsoncxx::to_json(maybe_result->view());
       json j = json::parse(rawResult);
       std::string resPasswd = j["passwd"];
       if(resPasswd == bosspasswd){
           bsoncxx::document::value doc_value = createDoc(username, password);

           bsoncxx::stdx::optional<mongocxx::result::delete_result> result =
            loginColl.delete_one(doc_value.view());
           ui->label_7->setText("Account deleted!");
           clearEdits();
       }else {
           ui->label_7->setText("Access denied");
           clearEdits();
       }

    }else {
        ui->label_7->setText("You have not boss account");
        clearEdits();
    }
}
