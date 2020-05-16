#pragma once

#include <string>
#include <vector>

/**
	Global GC class
*/
class GC
{
public:
    /**
     * Init method
    */
    void init();

    /*
        Calculate disatance between two pointers
    */
    ptrdiff_t CalcDist(void *ptr1, void *ptr2);

    /**
     * Default constructor
    */
    GC() : m_references(0)
    {
        std::cout << "In GC constructor" << std::endl;
        init();
    };


private:
    int m_references;
};