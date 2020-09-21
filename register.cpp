#include "register.h"
#include "ui_register.h"
#include <cstdint>
#include <vector>
#include <bsoncxx/json.hpp>
#include <json.hpp>
#include <QDebug>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

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
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
      << "login" << "test"
      << "passwd" << "test"
      << bsoncxx::builder::stream::finalize;
}
