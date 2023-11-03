#pragma once
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariantList>
#include <QVariant>
#include <tuple>
#include <vector>

class DatabaseHandler
{
public:
    const static QString database_name;
    const static QString hostname;
    const static QString username;
    const static QString password;
    const static int port;
private:
    QSqlDatabase _db;
    QSqlQuery _query;
    bool is_open;
public:
    DatabaseHandler();
    DatabaseHandler(const DatabaseHandler& db_handler);
    DatabaseHandler(DatabaseHandler&& db_handler) noexcept;
    ~DatabaseHandler();

    QStringList get_tables() const;
    bool prepare(const QString& sql_statement);
    void add_bind_value(const QVariant& val);
    void bind_value(int place, const QVariant& val);
    bool exec(const QString& sql_statement);
    bool exec();
    std::tuple<QSqlRecord, QSqlQuery> record();
    const QSqlError last_error() const;
    QMap<QString, QVariant> bound_values() const;
    std::vector<QString> fields_name() const;
    std::vector<QVariantList> get_select_results();
};
