#ifndef SINTACTICO_H
#define SINTACTICO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Sintactico;
}
QT_END_NAMESPACE

class Sintactico : public QWidget
{
    Q_OBJECT

public:
    Sintactico(QWidget *parent = nullptr);
    ~Sintactico();

private:
    Ui::Sintactico *ui;
};
#endif // SINTACTICO_H
