#pragma once

#include "mpplib/utils/profiler_definitions.hpp"

#include <iostream>

namespace mpp {

/**
 * @brief Base class to all types of smart pointers (shared, unique, ...)
 */
class GcPtr
{
public:
    /**
     * @brief Destructor of GcPtr object.
     */
    virtual ~GcPtr(){};

    /**
     * @brief Get pointer to controlled object as void.
     * @return void* pointer to controlled object
     */
    virtual void* GetVoid() const = 0;

    /**
     * @brief Update pointer to controlled object
     * @param t_newPtr new pointer to controlled object
     */
    virtual void UpdatePtr(void* t_newPtr) = 0;

    /**
     * @brief Use count of current object controlled by gcPtr of any type.
     * @return uint32_t use count
     */
    virtual uint32_t UseCount() = 0;

    /**
     * @brief base print method
     * @param t_out ostream to write to.
     * @return std::ostream& that was used
     */
    virtual std::ostream& Print(std::ostream& t_out) const
    {
        return t_out;
    }

    /**
     * @brief Overloaded "<<" operator to dump GcPtr.
     * @param t_out stream to write to.
     * @param t_gcPtr actual object to dump.
     * @return std::ostream& that was used
     */
    friend std::ostream& operator<<(std::ostream& t_out, const GcPtr& t_gcPtr)
    {
        return t_gcPtr.Print(t_out);
    }
};
}