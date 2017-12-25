#ifndef IC_READ_H
#define IC_READ_H

#include <QMainWindow>

namespace Ui {
class IC_read;
}

class IC_read : public QMainWindow
{
    Q_OBJECT

public:
    explicit IC_read(QWidget *parent = 0);
    ~IC_read();

private:
    Ui::IC_read *ui;
};

#endif // IC_READ_H
