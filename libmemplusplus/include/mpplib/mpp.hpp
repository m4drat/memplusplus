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
    void init();

    /**
     * Calculate disatance between two pointers
     */
    ptrdiff_t CalcDist(void *ptr1, void *ptr2);

    /**
     * Default constructor
     */
    GC()
        : m_references(0), m_references2(0), m_references3(1), m_references4(1),
          m_references5(1)
    {
        std::cout << "In GC constructor" << std::endl;
        init();
    };

private:
    int m_references;
    int m_references2;
    int m_references3;
    int m_references4;
    int m_references5;
};