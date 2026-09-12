#include "read_user.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int read_users(User users[]) {
    ifstream file("users.txt");
    string line;
    int count = 0;

    while (getline(file, line) && count < MAX_USERS) {
        stringstream ss(line);
        getline(ss, users[count].id, ',');
        getline(ss, users[count].name, ',');
        getline(ss, users[count].email, ',');
        getline(ss, users[count].password, ',');
        getline(ss, users[count].role, ',');

        if (!users[count].id.empty()) {
            count++;
        }
    }
    file.close();
    return count; 
}

void save_users(User users[], int count) {
    ofstream file("users.txt");
    for (int i = 0; i < count; i++) {
        file << users[i].id << ","
             << users[i].name << ","
             << users[i].email << ","
             << users[i].password << ","
             << users[i].role << "\n";
    }
    file.close();
}

