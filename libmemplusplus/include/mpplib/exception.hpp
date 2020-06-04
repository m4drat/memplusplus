#pragma once

#include <exception>
#include <string>

namespace mpp {
    class Exception : virtual public std::exception
    {
    public:
        /** Constructor (C strings).
         *  @param message C-style string error message.
         *                 The string contents are copied upon construction.
         *                 Hence, responsibility for deleting the char* lies
         *                 with the caller.
         */
        explicit Exception(const char* message)
            : m_errorMsg(message)
        {}

        /** Constructor (C++ STL strings).
         *  @param message The error message.
         */
        explicit Exception(const std::string& message)
            : m_errorMsg(message)
        {}

        /** Destructor.
         * Virtual to allow for subclassing.
         */
        virtual ~Exception() throw()
        {}

        /** Returns a pointer to the (constant) error description.
         *  @return A pointer to a const char*. The underlying memory
         *          is in posession of the Exception object. Callers must
         *          not attempt to free the memory.
         */
        virtual const char* what() const throw()
        {
            return m_errorMsg.c_str();
        }

    protected:
        /** Error message.
         */
        std::string m_errorMsg;
    };

    class NoMemoryException : public Exception
    {
    public:
        NoMemoryException()
            : Exception("No memory avaliable!\n")
        {}
    };

    class UnmapMemoryException : public Exception
    {
    public:
        UnmapMemoryException()
            : Exception("Cannot unmap memory!\n")
        {}
    };
}