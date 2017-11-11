#include "wikiform.h"
#include "ui_wikiform.h"

WikiForm::WikiForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WikiForm)
{
    ui->setupUi(this);
}

WikiForm::~WikiForm()
{
    delete ui;
}

void WikiForm::on_TextEdit_BasicInfo_textChanged()
{

}

void WikiForm::on_TextEdit_General_textChanged()
{

}

void WikiForm::on_Edit_Page_textChanged(const QString &arg1)
{

}


void WikiForm::on_Edit_Url_textChanged(const QString &arg1)
{

}

void WikiForm::on_btn_load_clicked()
{

}
