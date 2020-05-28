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

    void PrintData() { std::cout << m_data << std::endl; }
};

int main(int argc, char* argv[])
{
    mpp::SharedGcPtr<UserData> ptr(new UserData(1337));
    mpp::SharedGcPtr<UserData> ptr2(ptr);
    mpp::SharedGcPtr<UserData> ptr3(ptr);
    mpp::SharedGcPtr<UserData> ptr4(ptr3);

    mpp::SharedGcPtr<UserData> ptr5(nullptr);
    ptr4 = ptr5;

    mpp::SharedGcPtr<UserData> ptr6(ptr3);

    mpp::SharedGcPtr<UserData> ptr7 = new UserData(1338);

    return 0;
}