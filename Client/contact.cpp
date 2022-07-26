#include "contact.h"

std::string &Contact::getName()
{
    return name_;
}

long long Contact::getId()
{
    return id_;
}

Contact::Contact(const std::string& name, long long id): name_{name}, id_{id}
{

}

bool Contact::operator==(const Contact& rhs){
    return id_==rhs.id_;
}

bool Contact::operator>(const Contact& rhs){
    return id_>rhs.id_;
}

bool Contact::operator<(const Contact& rhs){
    return id_<rhs.id_;
}

bool Contact::operator!=(const Contact& rhs){
    return id_!=rhs.id_;
}

