#include "ic_read.h"
#include "ui_ic_read.h"

IC_read::IC_read(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IC_read)
{
    ui->setupUi(this);
}

IC_read::~IC_read()
{
    delete ui;
}
