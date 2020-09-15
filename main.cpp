#include "barman.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Barman w;
    w.show();
    return a.exec();
}
