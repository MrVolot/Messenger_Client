#pragma once
#include <string>

class Contact
{
    std::string name_;
    long long id_;
public:
    Contact(const std::string& name, long long id);
    std::string& getName();
    long long getId();

    bool operator==(const Contact& rhs);
    bool operator>(const Contact& rhs);
    bool operator<(const Contact& rhs);
    bool operator!=(const Contact& rhs);
};
