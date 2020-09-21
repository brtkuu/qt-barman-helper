#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <barman.h>

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

    void on_pushButton_3_clicked();

    void clearEdits();

private:
    Ui::Login *ui;

    Barman *barman;

};

#endif // LOGIN_H
