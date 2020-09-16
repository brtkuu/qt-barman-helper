#ifndef BARMAN_H
#define BARMAN_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <drinkinfo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Barman; }
QT_END_NAMESPACE

class Barman : public QMainWindow
{
    Q_OBJECT

public:
    Barman(QWidget *parent = nullptr);
    ~Barman();

private slots:
    void on_pushButton_clicked();


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Barman *ui;
    drinkInfo *drinkInfo;
};
#endif // BARMAN_H
