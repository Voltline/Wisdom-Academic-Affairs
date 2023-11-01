#include "dbhandler.h"
#include "dbexceptions.h"
#include <QDebug>

const QString DatabaseHandler::database_name = "Lighthouse-Server";
const QString DatabaseHandler::hostname = "124.223.215.89";
const QString DatabaseHandler::username = "waa_admin";
const QString DatabaseHandler::password = "";
const int DatabaseHandler::port = 10080;

DatabaseHandler::DatabaseHandler()
    : db(QSqlDatabase::addDatabase("QODBC"))
{
    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(database_name);
    db.setUserName(username);
    db.setPassword(password);

    if (!db.open())
    {
        qDebug() << db.lastError();
        throw DatabaseException::ConnectionException{"ConnectionError : Database Connection Failed!"};
        is_open = false;
    }
    else is_open = true;
}


DatabaseHandler::DatabaseHandler(const DatabaseHandler& db_handler)
    : db(db_handler.db)
{
    if (!db.open())
    {
        throw DatabaseException::ConnectionException{"ConnectionError : Database Connection Failed!"};
        is_open = false;
    }
    else is_open = true;
}

DatabaseHandler::DatabaseHandler(DatabaseHandler&& db_handler) noexcept
    : db(std::move(db_handler.db)), is_open(db_handler.is_open) {}

DatabaseHandler::~DatabaseHandler()
{
    db.close();
    is_open = false;
}

QStringList DatabaseHandler::get_tables() const
{
    if (!is_open)
    {
        throw DatabaseException::QueryException{"QueryError : Connection has not been established!"};
    }
    return db.tables();
}

