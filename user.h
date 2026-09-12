#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

const int MAX_USERS = 100;
struct User {
    string id;
    string name;
    string email;
    string password;
    string role;
};

#endif

