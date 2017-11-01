#include "wikisearchform.h"
#include "ui_wikisearchform.h"

WikiSearchForm::WikiSearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WikiSearchForm)
{
    ui->setupUi(this);
}

WikiSearchForm::~WikiSearchForm()
{
    delete ui;
}
