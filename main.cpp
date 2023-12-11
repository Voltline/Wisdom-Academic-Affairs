#include "mainwindow.h"
#include "dbhandler.h"
#include "classinfo.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
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

    db.exec("select * from courses;");
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
            qDebug() << v.toString();
        }
    }
    std::cout << std::endl;
    ClassInfo cp1{ "COMS0031131051", "03", "Database System Principle and Practice",
                   "Dandan Zhu", "Computer Science and Technology", "Fall", "Professional Compulsory",
                   Mon, 4.0, 6, 5, 1, 18, std::vector<QString>{"COMS0031121009", "COMS0031131990"} };
    std::cout << cp1 << std::endl;
    return a.exec();
}
