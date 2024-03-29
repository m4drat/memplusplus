#pragma once

#include <exception>
#include <string>

namespace mpp {
    /**
     * @brief Defines general exceptions class for all project.
     *
     * All other exceptions should be inherited from this class.
     */
    class Exception : virtual public std::exception
    {
    public:
        /**
         * @brief Constructor (C strings).
         * @param message C-style string error message. The string contents are copied upon
         * construction. Hence, responsibility for deleting the char* lies with the caller.
         */
        explicit Exception(const char* message)
            : m_errorMsg(message)
        {
        }

        /**
         * @brief Constructor (C++ STL strings).
         * @param message The error message.
         */
        explicit Exception(const std::string& message)
            : m_errorMsg(message)
        {
        }

        //! @brief Copy constructor.
        Exception(const Exception&) = default;

        //! @brief Move constructor.
        Exception(Exception&&) = default;

        //! @brief Copy assignment operator.
        Exception& operator=(const Exception&) = default;

        //! @brief Move assignment operator.
        Exception& operator=(Exception&&) = default;

        //! @brief Virtual destructor.
        ~Exception() override = default;

        /**
         * @brief Returns a pointer to the (constant) error description.
         * @return A pointer to a const char*. The underlying memory is in posession of the
         * Exception object. Callers must not attempt to free the memory.
         */
        const char* what() const noexcept override
        {
            return m_errorMsg.c_str();
        }

    protected:
        /**
         * @brief Error message.
         */
        std::string m_errorMsg;
    };

    /**
     * @brief No memory exception class.
     */
    class NoMemoryException : public Exception
    {
    public:
        /**
         * @brief Default constructor.
         */
        NoMemoryException()
            : Exception("No memory avaliable!\n")
        {
        }
    };

    /**
     * @brief Unmap memory exception class.
     */
    class UnmapMemoryException : public Exception
    {
    public:
        /**
         * @brief Default constructor.
         */
        UnmapMemoryException()
            : Exception("Cannot unmap memory!\n")
        {
        }
    };
}