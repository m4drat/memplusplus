#pragma once

#include <exeption>

namespace mpp {
    class Exception : public std::exception
    {
    private:
        std::string m_msg;

    public:
        Exception(const std::string& msg)
            : m_msg(msg)
        {}

        virtual const char* what() const noexcept override
        {
            return m_msg.c_str();
        }
    }

    class NoMemoryException : public Exception
    {
    private:
        std::string m_msg{ "no memory avaliable" };

    public:
        NoMemoryException() {}

        virtual const char* what() const noexcept override
        {
            return m_msg.c_str();
        }
    }
}