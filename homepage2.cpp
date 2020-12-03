#include "homepage2.h"
#include "ui_homepage2.h"

homePage2::homePage2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homePage2)
{
    ui->setupUi(this);
}

homePage2::~homePage2()
{
    delete ui;
}
