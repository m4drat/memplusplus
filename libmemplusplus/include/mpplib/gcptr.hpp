#pragma once

namespace mpp {

    /**
     * This class exist only because, we want to implement runtime polymorphism
     * for different type of smart pointers (unique/shared/...).
     * Only because we have this class we can create vector of GcPtr's
     * with different pointer types, and than downcast each of them to
     * appropriate smart pointer type using dynamic_cast<>(ptr)
     */
    class GcPtr
    {
    public:
        virtual ~GcPtr(){};
    }
}