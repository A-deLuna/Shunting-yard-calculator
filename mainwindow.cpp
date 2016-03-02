#ifndef TEST
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "shunting-yard.hpp"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
    ui->plainTextEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
}

void MainWindow::onReturnPressed() {
    std::string s = ui->lineEdit->text().toStdString();
    std::vector<std::string> v;
    ui->plainTextEdit->setPlainText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    try {
        long long ans = parse(s, v);
        ui->lineEdit_4->setText(toBase(ans, 2).c_str());
        ui->lineEdit_5->setText(toBase(ans, 16).c_str());


        for(auto op : v) {
            ui->plainTextEdit->appendPlainText(op.c_str());
        }

        ui->lineEdit_2->setText(std::to_string(ans).c_str());
    }
    catch(std::string exception) {
        ui->lineEdit_3->setText(exception.c_str());
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
#endif
