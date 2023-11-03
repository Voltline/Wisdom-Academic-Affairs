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
    qDebug() << "Database Test";


    DatabaseHandler db;
    qDebug() << db.database_name;
    auto list{ db.get_tables() };
    for (const auto& s : list)
    {
        qDebug() << s;
    }

    /*
    db.prepare(QString("insert into takes values(?, ?, ?, ?, ?, ?)"));
    db.add_bind_value("43460");
    db.add_bind_value("408");
    db.add_bind_value("2");
    db.add_bind_value("Fall");
    db.add_bind_value(2023.0);
    db.add_bind_value("A");
    db.exec();
    */

    db.exec("select * from takes where id = '43460'");
    qDebug() << db.last_error();
    auto fields_name{ db.fields_name() };
    for (const auto& s : fields_name)
    {
        std::cout << s.toStdString() << "\t";
    }
    std::cout << std::endl;
    auto ans{ db.get_select_results() };
    for (const auto& l : ans)
    {
        for (const auto& v : l)
        {
            std::cout << v.toString().toStdString() << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Test!!" << std::endl;
    return a.exec();
}
