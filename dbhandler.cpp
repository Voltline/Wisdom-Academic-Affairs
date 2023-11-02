#include "dbhandler.h"
#include "dbexceptions.h"
#include <QDebug>

const QString DatabaseHandler::database_name = "Lighthouse-Server";
const QString DatabaseHandler::hostname = "124.223.215.89";
const QString DatabaseHandler::username = "waa_admin";
const QString DatabaseHandler::password = "";
const int DatabaseHandler::port = 10080;

DatabaseHandler::DatabaseHandler()
    : _db(QSqlDatabase::addDatabase("QODBC"))
    , _query(_db)
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
    : _db(db_handler._db)
    , _query(_db)
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
    : _db(std::move(db_handler._db))
    , _query(std::move(db_handler._query))
    , is_open(db_handler.is_open) {}

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

const QSqlError DatabaseHandler::last_error() const
{
    return _query.lastError();
}

QMap<QString, QVariant> DatabaseHandler::bound_values() const
{
    if (last_error() == QSqlError() && _query.isSelect())
    {
        return _query.boundValues();
    }
    else
    {
        if (!_query.isSelect())
            throw DatabaseException::HandlerException{"Handler Exception : Last SQL statement is not select!"};
        else
            throw DatabaseException::QueryException{"Query Exception : Last select query has syntax error!"};
    }
}

std::vector<QString> DatabaseHandler::fields_name() const
{
    if (is_open)
    {
        if (_query.isSelect() && last_error() == QSqlError())
        {
            std::vector<QString> ans;
            auto rec{ _query.record() };
            int _size{ rec.count() };
            for (int i = 0; i < _size; i++)
            {
                ans.push_back(rec.fieldName(i));
            }
            return ans;
        }
        else
        {
            if (!_query.isSelect())
                throw DatabaseException::HandlerException{"Handler Exception : Last SQL statement is not select!"};
            else
                throw DatabaseException::QueryException{"Query Exception : Last select query has syntax error!"};
        }
    }
    return std::vector<QString>{};
}

std::vector<QVariantList> DatabaseHandler::get_select_results()
{
    if (is_open)
    {
        if (_query.isSelect() && last_error() == QSqlError())
        {
            std::vector<QVariantList> ans;
            std::vector<QString> fields{ fields_name() };
            while (_query.next())
            {
                QVariantList data_tuple{};
                for (const auto& s : fields)
                {
                    data_tuple.append(_query.value(s));
                }
                ans.push_back(data_tuple);
            }
            return ans;
        }
        else
        {
            if (!_query.isSelect())
                throw DatabaseException::HandlerException{"Handler Exception : Last SQL statement is not select!"};
            else
                throw DatabaseException::QueryException{"Query Exception : Last select query has syntax error!"};
        }
    }
    return std::vector<QVariantList>{};
}
