#include "login.h"
#include "read_user.h"
#include "getMaskedPassword.h"
#include "pauseAndClear.h"
#include "colour.h"
#include <cctype>

#include <iostream>
using namespace std;

bool login (string &id, string &role){
	
	string email, password;
    
    cout << "Enter your email: ";
    getline(cin, email);

    if (email.empty()) {
            cout << RED << "\nYou pressed Enter without typing anything! Please enter your email.\n" << RESET;
            return false;
        }
    for (int i = 0; email[i] != '\0'; i++) {
        email[i] = tolower((unsigned char)email[i]);
    }
    
    cout << "Enter password: ";
    password = getMaskedPassword();

    User users[MAX_USERS];
    int count = read_users(users);

    for (int i = 0; i < count; i++) {
        if (users[i].email == email && users[i].password == password) {
            cout << BRIGHT_GREEN << "Login success! Welcome " << BRIGHT_WHITE << users[i].name 
                 << RESET << " (" << users[i].role << ")\n";
	        id = users[i].id;
	        role = users[i].role;
	        return true;
		}
	}    
		cout << RED << "Invalid email or password. Fail to login.\n" << RESET;
    	return false;
}
