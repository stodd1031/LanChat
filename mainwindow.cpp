#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    network = new Host(&MainWindow::updateTextBox, this);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_lineEdit_returnPressed()
{
    // ui->textEdit->append(ui->lineEdit->text());
    network->send(ui->lineEdit->text());
}

void MainWindow::updateTextBox(QString string)
{
    ui->textEdit->append(string);
}

void MainWindow::on_pushButton_3_clicked()
{
    network = new Client(&MainWindow::updateTextBox, this, ui->lineEdit_ip->text(), ui->lineEdit_port->text(), ui->lineEdit_username->text());
    if (network->getConnected())
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

