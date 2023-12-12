#include "mainwindow.h"
#include "dbhandler.h"
#include "classinfo.h"
#include "coursedatabase.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <iostream>
#include <QTextStream>

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
    /*
    auto ans{ cdb.get_all_class_info() };
    for (const auto& l : ans)
    {
        l.display();
    }
    */
    auto ans = cdb.get_one_class_info("COMS0031121009");
    for (const auto& l : ans)
    {
        l.display();
    }

    return a.exec();
}
