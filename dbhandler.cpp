#include "dbhandler.h"
#include "dbexceptions.h"
#include <QDebug>

const QString DatabaseHandler::database_name = "Lighthouse-Server";
const QString DatabaseHandler::hostname = "124.223.215.89";
const QString DatabaseHandler::username = "waa_admin";
const QString DatabaseHandler::password = "";
const int DatabaseHandler::port = 10080;

DatabaseHandler::DatabaseHandler()
    : _db(QSqlDatabase::addDatabase("QODBC")), _query(_db)
{
    _db.setHostName(hostname);
    _db.setPort(port);
    _db.setDatabaseName(database_name);
    _db.setUserName(username);
    _db.setPassword(password);

    if (!_db.open())
    {
        qDebug() << _db.lastError();
        is_open = false;
        throw DatabaseException::ConnectionException{"ConnectionError : Database Connection Failed!"};
    }
    else is_open = true;
}


DatabaseHandler::DatabaseHandler(const DatabaseHandler& db_handler)
    : _db(db_handler._db), _query(_db)
{
    if (!_db.open())
    {
        qDebug() << _db.lastError();
        is_open = false;
        throw DatabaseException::ConnectionException{"ConnectionError : Database Connection Failed!"};
    }
    else is_open = true;
}

DatabaseHandler::DatabaseHandler(DatabaseHandler&& db_handler) noexcept
    : _db(std::move(db_handler._db)), _query(std::move(db_handler._query)), is_open(db_handler.is_open) {}

DatabaseHandler::~DatabaseHandler()
{
    _db.close();
    is_open = false;
}

QStringList DatabaseHandler::get_tables() const
{
    if (!is_open)
    {
        throw DatabaseException::QueryException{"QueryError : Connection has not been established!"};
    }
    return _db.tables();
}

bool DatabaseHandler::query(const QString& sql_statement)
{
    if (is_open)
    {
        _db.transaction();
        bool query_ans{ _query.exec(sql_statement) };
        _db.commit();
        return query_ans;
    }
    else throw DatabaseException::QueryException{"QueryError : Connection has not been established!"};
}

std::tuple<QSqlRecord, QSqlQuery> DatabaseHandler::record()
{
    if (is_open)
    {
        return std::tuple<QSqlRecord, QSqlQuery>{_query.record(), _query};
    }
    else throw DatabaseException::QueryException{"QueryError : Connection has not been established!"};
}
