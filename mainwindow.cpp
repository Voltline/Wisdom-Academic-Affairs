#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coursedatabase.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    ui->ClassTable->setVisible(false);
    ui->Plan->setVisible(false);
    ui->classTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //自动设置行高
    ui->classTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//自动设置列宽
    ui->AllClassLabel->setVisible(false);
    ui->PlanLabel->setVisible(false);
    //查询数据库添加下拉菜单
    CourseDatabase cdb;
    auto ans = cdb.get_all_class_info();
    vector<QString> deplist;
    for(auto it  : ans)
        deplist.push_back(it.department);
    std::sort(deplist.begin(), deplist.end());
    auto end = unique(deplist.begin(), deplist.end());
    for(auto it = deplist.begin(); it != end; ++it)
        ui->comboBox->addItem(*it);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateClassTableView(const QString& dept)
{
    CourseDatabase cdb;
    vector<ClassInfo> ans_set;
    if (dept == "...") ans_set = cdb.get_all_class_info();
    else ans_set = cdb.get_class_from_dept(dept);
    std::sort(ans_set.begin(), ans_set.end());
    showClassTableModel.clear();
    showClassTableModel.setHorizontalHeaderLabels(
                {"学期", "课程序号","课程名称","课程类别",
                 "开课院系", "教师", "排课安排",
                 "学分", "人数上限"});
    for (size_t i = 0; i < ans_set.size(); i++)
    {
        showClassTableModel.setItem(i, 0,
           new QStandardItem{(ans_set[i].semester == "Fall") ? "第一学期" : "第二学期"});
        showClassTableModel.setItem(i, 1,
           new QStandardItem{ans_set[i].course_basic_ID+"."+ans_set[i].course_sp_ID});
        showClassTableModel.setItem(i, 2,
           new QStandardItem{ans_set[i].course_name});
        showClassTableModel.setItem(i, 3,
           new QStandardItem{ans_set[i].category});
        showClassTableModel.setItem(i, 4,
           new QStandardItem{ans_set[i].department});
        showClassTableModel.setItem(i, 5,
           new QStandardItem{ans_set[i].teacher});
        QString time_period;
        auto times = ans_set[i].times;
        for (size_t j = 0; j < times.size(); j++)
        {
            time_period +=  toWeekdayString(times[j].day) + " " + QString::number(times[j].beg)
                                 + "-" + QString::number(times[j].beg + times[j].last - 1);
            if (times.size() != 1 && j != times.size() - 1) time_period += '\n';
        }
        showClassTableModel.setItem(i, 6, new QStandardItem{time_period});
        showClassTableModel.setItem(i, 7,
           new QStandardItem{QString::number(ans_set[i].credit, 'f', 1)});
        showClassTableModel.setItem(i, 8,
           new QStandardItem{QString::number(ans_set[i].limits)});
    }
    ui->classTable->setModel(&showClassTableModel);
}


void MainWindow::on_QuitButton_clicked()
{
    this->close();
    exit(0);
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
    Q_UNUSED(event);
    mouse_press = false;
}

void MainWindow::on_testbutton_clicked()
{
    ui->ClassTable->setVisible(true);
    ui->AllClassLabel->setVisible(true);
    ui->Plan->setVisible(false);
    ui->PlanLabel->setVisible(false);
    ui->testbutton->setStyleSheet("color: rgb(0, 126, 249); background-color: #2E334A; border: none;");
    ui->testbutton_2->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
}


void MainWindow::on_testbutton_2_clicked()
{
    ui->ClassTable->setVisible(false);
    ui->AllClassLabel->setVisible(false);
    ui->Plan->setVisible(true);
    ui->PlanLabel->setVisible(true);
    ui->testbutton->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->testbutton_2->setStyleSheet("color: rgb(0, 126, 249); background-color: #2E334A; border: none;");
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    updateClassTableView(arg1);
}

