#ifndef ALGORITHMEXCEPTION_H
#define ALGORITHMEXCEPTION_H
#include <exception>
namespace AlgorithmException
{
    struct TopsortException:public std::exception
    {
        const char* base_exception_text;
        const char* exception_text;

        TopsortException(const char* err = "Default DatabaseException")
            : base_exception_text("DatabaseError : "), exception_text(err) {}
        virtual ~TopsortException() = default;

        virtual const char* what() const throw()
        {
            return exception_text;
        }
    };
}
#endif // ALGORITHMEXCEPTION_H
