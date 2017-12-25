#include "icread.h"
#include "ui_icread.h"

IcRead::IcRead(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IcRead)
{
    ui->setupUi(this);
}

IcRead::~IcRead()
{
    delete ui;
}
