
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* const parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      mediawiki(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{

}

void MainWindow::on_mPageEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_mWikiEdit_textChanged(const QString &arg1)
{

}

void MainWindow::on_pushButton1_clicked()
{

}

void MainWindow::on_pushButton2_clicked()
{

}

