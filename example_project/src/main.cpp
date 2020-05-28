#include <iostream>

#include "mpplib/shared_gcptr.hpp"

class UserData
{
private:
    int m_data;

public:
    UserData(int data)
        : m_data{ data }
    {
        std::cout << "UserData()" << std::endl;
    };

    ~UserData() { std::cout << "~UserData()" << std::endl; };
};

int main(int argc, char* argv[])
{
    return 0;
}