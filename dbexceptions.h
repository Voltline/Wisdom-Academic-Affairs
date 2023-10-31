#pragma once
#include <exception>

namespace DatabaseException
{
    struct DatabaseException : public std::exception
    {
        const char* exception_text;

        DatabaseException(const char* err = "Default DatabaseException")
            : exception_text(err) {}
        virtual ~DatabaseException() = default;

        virtual const char* what() const throw()
        {
            return exception_text;
        }
    };

    struct ConnectionException : public DatabaseException
    {
        ConnectionException(const char* err = "Default ConnectionException")
            : DatabaseException(err) {}
        virtual ~ConnectionException() = default;

        virtual const char* what() const throw()
        {
            return exception_text;
        }
    };
}
