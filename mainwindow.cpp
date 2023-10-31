#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::update_test()
{
    int cnt = 0;
    while(true)
    {
        ++cnt;
        ui->label->setText(QString::fromStdString(std::to_string(cnt)));
        _sleep(50);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QtConcurrent::run(this, &MainWindow::update_test);
}

