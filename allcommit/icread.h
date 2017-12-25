#ifndef ICREAD_H
#define ICREAD_H

#include <QDialog>

namespace Ui {
class IcRead;
}

class IcRead : public QDialog
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit IcRead(QWidget *parent = 0);
    ~IcRead();

private:
    Ui::IcRead *ui;
};

#endif // ICREAD_H
