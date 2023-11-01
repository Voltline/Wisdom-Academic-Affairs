#pragma once
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseHandler
{
public:
    const static QString database_name;
    const static QString hostname;
    const static QString username;
    const static QString password;
    const static int port;
private:
    QSqlDatabase db;
    bool is_open;
public:
    DatabaseHandler();
    DatabaseHandler(const DatabaseHandler& db_handler);
    DatabaseHandler(DatabaseHandler&& db_handler) noexcept;
    ~DatabaseHandler();

    QStringList get_tables() const;
};
