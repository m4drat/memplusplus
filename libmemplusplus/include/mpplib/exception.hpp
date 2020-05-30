#pragma once

#include <exception>
#include <string>

namespace mpp {
    class Exception : virtual public std::exception
    {
    private:
        std::string errorMessage;

    public:
        Exception(const std::string& msg)
            : errorMessage(msg)
        {}

        virtual ~Exception() throw()
        {}

        virtual const char* what() const throw()
        {
            return errorMessage.c_str();
        }
    };

    class NoMemoryException : public Exception
    {
    private:
        std::string errorMessage{ "No memory avaliable" };

    public:
        NoMemoryException()
            : Exception(errorMessage)
        {}
    };

    class UnmapMemoryException : public Exception
    {
    private:
        std::string errorMessage{ "Cannot unmap memory" };

    public:
        UnmapMemoryException()
            : Exception(errorMessage)
        {}
    };
}