#include "mainwindow.h"
#include "dbhandler.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <iostream>

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
    qDebug() << "Test";
//    DatabaseHandler db;
//    qDebug() << db.database_name;
    std::cout << "Test!!" << std::endl;
    return a.exec();
}
