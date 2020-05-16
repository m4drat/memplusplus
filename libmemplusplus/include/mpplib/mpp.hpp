#pragma once

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