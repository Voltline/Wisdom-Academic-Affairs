#include "mainwindow.h"
#include "dbhandler.h"
#include "classinfo.h"
#include "coursedatabase.h"
#include "CourseSystem.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <iostream>
#include <QTextStream>
using namespace CourseSystem;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "WAA-Github_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //test
    MainWindow w;
    w.show();
    CourseDatabase cdb;
    /*测试 multiCourse的冲突检测 线段树
    multiCourseTime t1, t2;
    t1.push_back(CourseTime(1, 1, 3));
    t1.push_back(CourseTime(2, 1, 3));
    t2.push_back(CourseTime(2, 2, 5));
    qDebug() << (t1^t2);
    */
    //测试数据库
    auto ans{ cdb.get_class_from_dept("计算机科学与技术学院") };
    for (const auto& l : ans)
    {
        l.display();
    }
    //测试ClassSystem
    std::map<QString, CourseSystem::Course> courses;
    for(auto courseinfo : ans)
    {
        courses[courseinfo.course_basic_ID].push_teacherCourse(courseinfo);
    }
    for(auto [x,y] : courses)
    {
        y.debug();
    }
    return a.exec();
}
