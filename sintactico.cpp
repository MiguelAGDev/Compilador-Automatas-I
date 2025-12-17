#include "sintactico.h"
#include "ui_sintactico.h"

Sintactico::Sintactico(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sintactico)
{
    ui->setupUi(this);
}

Sintactico::~Sintactico()
{
    delete ui;
}
