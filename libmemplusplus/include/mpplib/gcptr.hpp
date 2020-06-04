#pragma once

namespace mpp {

    /**
     * This class exist only because, we want to implement runtime polymorphism
     * for different type of smart pointers (unique/shared/...).
     * Only because we have this class we can create vector of GcPtr's
     * with different pointer types, and than downcast each of them to
     * appropriate smart pointer type using dynamic_cast<>(ptr). 
     * FIX: no, we cant downcast them, cause we can't create vector of template class 
     * objects, thus we need one generic abstract class for all kinds of smart pointers
     */
    class GcPtr
    {
    public:
        virtual ~GcPtr(){};

        virtual void* GetVoid() const = 0;
        virtual void UpdatePtr(void* t_newPtr) = 0;
        virtual uint32_t UseCount() = 0;

        virtual std::ostream& Print(std::ostream& t_out) const
        {
            return t_out;
        }

        friend std::ostream& operator<<(std::ostream& t_out, const GcPtr& t_gcPtr)
        {
            return t_gcPtr.Print(t_out);
        }
    };
}