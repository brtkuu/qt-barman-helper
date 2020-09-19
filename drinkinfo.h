#ifndef DRINKINFO_H
#define DRINKINFO_H

#include <QDialog>

namespace Ui {
class drinkInfo;
}

class drinkInfo : public QDialog
{
    Q_OBJECT

public:
    explicit drinkInfo(QWidget *parent = nullptr, QString name = "", QString instructions = "", QString url = "", QString ingredients = "");
    ~drinkInfo();

private:
    Ui::drinkInfo *ui;

};

#endif // DRINKINFO_H
