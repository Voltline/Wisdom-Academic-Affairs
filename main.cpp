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
#include "CourseSystem.h"
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
//    CourseDatabase cdb;
//    auto ans{ cdb.get_all_class_info() };
//    for (const auto& l : ans)
//    {
//        l.display();
//    }
    multiCourseTime t1, t2;
    t1.push_back(CourseTime(1, 1, 3));
    t1.push_back(CourseTime(2, 1, 3));
    t2.push_back(CourseTime(1, 1, 3));

    qDebug() << judge_conflict(t1, t2);
    return a.exec();
}
