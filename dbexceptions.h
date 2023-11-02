#pragma once
#include <exception>
#include <string>

namespace DatabaseException
{
    struct DatabaseException : public std::exception
    {
        const char* base_exception_text;
        const char* exception_text;

        DatabaseException(const char* err = "Default DatabaseException")
            : base_exception_text("DatabaseError : "), exception_text(err) {}
        virtual ~DatabaseException() = default;

        virtual const char* what() const throw()
        {
            return exception_text;
        }
    };

    struct ConnectionException : public DatabaseException
    {
        ConnectionException(const char* err = "Default ConnectionException")
            : DatabaseException(err) { base_exception_text = "ConnectionError : "; }
        virtual ~ConnectionException() = default;

        virtual const char* what() const throw()
        {
            return exception_text;
        }
    };

    struct QueryException : public DatabaseException
    {
        QueryException(const char* err = "Default QueryException")
            : DatabaseException(err) {}
        virtual ~QueryException() = default;

        virtual const char* what() const throw()
        {
            return exception_text;
        }
    };

    struct HandlerException : public DatabaseException
    {
        HandlerException(const char* err = "Default HandlerException")
            : DatabaseException(err) {}
        virtual ~HandlerException() = default;

        virtual const char* what() const throw()
        {
            return exception_text;
        }
    };
}
