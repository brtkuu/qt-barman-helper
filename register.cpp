#include "register.h"
#include "ui_register.h"
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

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_2_clicked()
{
    this->close();
}

void Register::on_pushButton_clicked()
{

}
