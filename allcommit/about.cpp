#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QString title=QString::fromLocal8Bit("¹ØÓÚ");
    this->setWindowTitle(title);
}

About::~About()
{
    delete ui;
}
