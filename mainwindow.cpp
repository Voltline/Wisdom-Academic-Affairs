#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint);
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


void MainWindow::on_QuitButton_clicked()
{
    this->close();
}


void MainWindow::on_MinButton_clicked()
{
    this->showMinimized();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton))
    {
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse_press)
    {
        move(event->globalPos() - mousePoint);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}
