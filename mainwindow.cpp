#include "mainwindow.h"


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
    ui->MainPageLabel->setVisible(false);
    ui->About->setVisible(false);
    ui->AboutFrame->setVisible(false);
    ui->testbutton->setStyleSheet("color: rgb(0, 126, 249); border: none;");
    ui->testbutton_2->setStyleSheet("color: rgb(0, 126, 249); border: none;");
    ui->testbutton_3->setStyleSheet("color: rgb(0, 126, 249); border: none;");
    ui->aboutButton->setStyleSheet("color: rgb(0, 126, 249); border: none;");
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
    //设置候选词
    //设置候选词model
    stringListModel = new QStringListModel(this);
    completer = new QCompleter();
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);
    //设置候选
    trie = new Trie();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateClassTableView(const QString& dept)
{
    CourseDatabase cdb;
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

void MainWindow::updateAnsTableView(const vector<vector<CourseSystem::Course> > courses)
{
    showAnsTableModel.clear();
    showAnsTableModel.setHorizontalHeaderLabels(
                {"学期", "课程序号","课程名称"});
    int cnt = 0;
    int cnt_item=0;
    for(auto line : courses)
    {
        ++cnt;
        for(auto course : line)
        {
            showAnsTableModel.setItem(cnt_item, 0,
               new QStandardItem{QString::fromStdString("第"+std::to_string(cnt)+"学期")});
            showAnsTableModel.setItem(cnt_item, 1,
               new QStandardItem{course.get_course_basic_ID()});
            showAnsTableModel.setItem(cnt_item, 2,
               new QStandardItem{course.get_course_name()});
            ++cnt_item;
        }
    }
    ui->Plan_2->setModel(&showAnsTableModel);
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
    ui->frame_2->setVisible(false);
    ui->MainPageLabel->setVisible(false);
    ui->Plan->setVisible(false);
    ui->PlanLabel->setVisible(false);
    ui->About->setVisible(false);
    ui->AboutFrame->setVisible(false);
    ui->testbutton->setStyleSheet("color: rgb(0, 126, 249); background-color: #2E334A; border: none;");
    ui->testbutton_2->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->testbutton_3->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->aboutButton->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
}


void MainWindow::on_testbutton_2_clicked()
{
    ui->ClassTable->setVisible(false);
    ui->AllClassLabel->setVisible(false);
    ui->frame_2->setVisible(false);
    ui->MainPageLabel->setVisible(false);
    ui->Plan->setVisible(true);
    ui->PlanLabel->setVisible(true);
    ui->About->setVisible(false);
    ui->AboutFrame->setVisible(false);
    ui->testbutton->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->testbutton_2->setStyleSheet("color: rgb(0, 126, 249); background-color: #2E334A; border: none;");
    ui->testbutton_3->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->aboutButton->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    updateClassTableView(arg1);
}


void MainWindow::on_testbutton_3_clicked()
{
    ui->ClassTable->setVisible(false);
    ui->AllClassLabel->setVisible(false);
    ui->frame_2->setVisible(true);
    ui->MainPageLabel->setVisible(true);
    ui->Plan->setVisible(false);
    ui->PlanLabel->setVisible(false);
    ui->About->setVisible(false);
    ui->AboutFrame->setVisible(false);
    ui->testbutton->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->testbutton_2->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->testbutton_3->setStyleSheet("color: rgb(0, 126, 249); background-color: #2E334A; border: none;");
    ui->aboutButton->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
}


void MainWindow::on_aboutButton_clicked()
{
    ui->ClassTable->setVisible(false);
    ui->AllClassLabel->setVisible(false);
    ui->frame_2->setVisible(false);
    ui->MainPageLabel->setVisible(false);
    ui->Plan->setVisible(false);
    ui->PlanLabel->setVisible(false);
    ui->About->setVisible(true);
    ui->AboutFrame->setVisible(true);
    ui->testbutton->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->testbutton_2->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->testbutton_3->setStyleSheet("color: rgb(0, 126, 249); background-color: #181E36; border: none;");
    ui->aboutButton->setStyleSheet("color: rgb(0, 126, 249); background-color: #2E334A; border: none;");
}


void MainWindow::on_pushButton_sov1_clicked()
{
    std::map<QString, CourseSystem::Course> courses;
    for(auto courseinfo : ans_set)
    {
        courses[courseinfo.course_basic_ID].push_teacherCourse(courseinfo);
    }
    vector<CourseSystem::Course> vec;
    for(auto [x,y]: courses)
    {
        vec.push_back(y);
    }
    //更新候选词列表
    trie = new Trie();
    for(auto x : vec)
    {
        trie->insert(0, x.get_course_name());
    }
    //处理用户选择
    vector<double> credit;
    credit.push_back(ui->doubleSpinBox_d1->value());
    credit.push_back(ui->doubleSpinBox_d2->value());
    credit.push_back(ui->doubleSpinBox_d3->value());
    credit.push_back(ui->doubleSpinBox_d4->value());
    credit.push_back(ui->doubleSpinBox_d5->value());
    credit.push_back(ui->doubleSpinBox_d6->value());
    credit.push_back(ui->doubleSpinBox_d7->value());
    credit.push_back(ui->doubleSpinBox_10->value());
    int limit = ui->spinBox->value();
    //

    auto topans = DataStructureAlgorithm::TopSort(vec, credit, limit).sov();
    updateAnsTableView(topans);

}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    auto it = trie->find(arg1);
    QStringList stringlist;
    for(const auto &x : it.second)
    {
        stringlist.append(x.first);
    }
    stringListModel->setStringList(stringlist);
    completer->setModel(stringListModel);
}


void MainWindow::on_lineEdit_editingFinished()
{
    QItemSelectionModel *selectionModel = ui->Plan_2->selectionModel();
    // 获取所有选中的行
    QModelIndexList selectedRows = selectionModel->selectedRows();

}


void MainWindow::on_pushButton_sov1_pressed()
{
    ui->pushButton_sov1->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(48, 79, 255); border-radius: 25px;");
}


void MainWindow::on_pushButton_sov1_released()
{
    ui->pushButton_sov1->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(48, 149, 255); border-radius: 25px;");
}


void MainWindow::on_pushButton_sov2_pressed()
{
    ui->pushButton_sov2->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(48, 79, 255); border-radius: 25px;");
}


void MainWindow::on_pushButton_sov2_released()
{
    ui->pushButton_sov2->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(48, 149, 255); border-radius: 25px;");
}

