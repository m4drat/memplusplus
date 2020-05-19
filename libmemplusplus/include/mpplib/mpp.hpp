#pragma once

#include <cstddef>
#include <iostream>

/**
 * Global GC class
 */
class GC
{
public:
    /**
     * Init method
     */
    static void init();

    /**
     * Calculate disatance between two pointers
     */
    static auto CalcDist(void* ptr1, void* ptr2);

    /**
     * Default constructor
     */
    GC()
    {
        std::cout << "In GC constructor" << std::endl;
        init();
    };

private:
    int m_references{ 0 };
    int m_references2{ 0 };
    int m_references3{ 0 };
    int m_references4{ 0 };
    int m_references5{ 0 };
};