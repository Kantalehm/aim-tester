#ifndef HOMEPAGE2_H
#define HOMEPAGE2_H

#include <QDialog>

namespace Ui {
class homePage2;
}

class homePage2 : public QDialog
{
    Q_OBJECT

public:
    explicit homePage2(QWidget *parent = nullptr);
    ~homePage2();

private:
    Ui::homePage2 *ui;
};

#endif // HOMEPAGE2_H
