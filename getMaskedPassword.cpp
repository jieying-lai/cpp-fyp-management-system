#include "getMaskedPassword.h"
#include <iostream>
#include <conio.h>

using namespace std;

string getMaskedPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch(); // Read char without displaying it
        if (ch == 13) { // Enter key
            cout << endl;
            break;
        }
        else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.erase(password.end() - 1);
                cout << "\b \b"; // Erase last '*'
            }
        }
        else {
            password.push_back(ch);
            cout << '*'; // Print '*'
        }
    }
    return password;
}

