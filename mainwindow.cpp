#include <QAxObject>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interface0.h"


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




void MainWindow::on_pushButtonSuivant_clicked()
{
    Interface0 *interface0 = new Interface0();
    this->hide();
    interface0->show();
}

