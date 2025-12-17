#include "sintactico.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sintactico w;
    w.show();
    return a.exec();
}
