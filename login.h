#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <barman.h>
#include <register.h>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;

    Barman *barman;

    Register *registerView;
};

#endif // LOGIN_H
