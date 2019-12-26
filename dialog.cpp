#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(int n,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog), n(n)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(n));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    bool ok;
    int tmp_n = ui->lineEdit->text().toInt(&ok);
    if(ok) {
        n = tmp_n;
    }
}
