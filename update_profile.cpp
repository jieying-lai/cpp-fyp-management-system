#include <iostream>
#include <fstream>
#include <string>
#include "update_profile.h"
#include "pauseAndClear.h"
#include "colour.h"
#include "getMaskedPassword.h"

using namespace std;

void updateProfile(const string &id) {
    User users[MAX_USERS];
    int count = read_users(users);

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (users[i].id == id) {
            index = i;
            break;
        }
    }

    while (true) {
        system("cls");
        cout << BRIGHT_WHITE << "======================================" << RESET << endl;
        cout << BG_BLUE << BRIGHT_WHITE << "\t--- Update Profile ---\n" << RESET;
        cout << BRIGHT_WHITE << "======================================" << RESET << endl;

        cout << "[1] Update Name\n";
        cout << "[2] Update Email\n";
        cout << "[3] Update Password\n";
        cout << BRIGHT_YELLOW << "\n[0] Cancel\n" << RESET;

        cout << "Enter your choice: ";
        string action;
        getline(cin, action);

        if (action == "0") {
            cout << BRIGHT_YELLOW << "\nUpdate canceled.\n" << RESET;
            pauseAndClear();
            return;
        }

        string newValue;
        bool updated = false;

        if (action == "1") {
            cout << BRIGHT_CYAN << "\nOriginal Name: " << users[index].name << "\n" << RESET;
            cout << "Enter new Name " << BRIGHT_YELLOW << "(or 'C' to cancel)" << RESET << ": ";
            getline(cin, newValue);

            if (newValue == "C" || newValue == "c") {
                pauseAndClear();
                continue;
            }
            if (newValue.empty()) {
                cout << RED << "Name cannot be empty. Please try again.\n" << RESET;
                pauseAndClear();
                continue;
            }

            for (char &c : newValue) c = toupper(c);
            users[index].name = newValue;
            updated = true;
        }

        else if (action == "2") {
            cout << BRIGHT_CYAN << "Original Email: " << users[index].email << "\n" << RESET;
            cout << "Enter new Email " << BRIGHT_YELLOW << "(or 'C' to cancel)" << RESET << ": ";
            getline(cin, newValue);

            if (newValue == "C" || newValue == "c") {
                pauseAndClear();
                continue;
            }
            if (newValue.empty()) {
                cout << RED << "Email cannot be empty.\n" << RESET;
                pauseAndClear();
                continue;
            }
            if (newValue.find('@') == string::npos || newValue.find('.') == string::npos) {
                cout << RED << "Invalid email format. Must contain '@' and '.'\n" << RESET;
                pauseAndClear();
                continue;
            }

            ifstream file("users.txt");
            string line;
            bool duplicate = false;
            while (getline(file, line)) {
                string userEmail;
                int column = 0;
                for (char c : line) {
                    if (c == ',') {
                        column++;
                        continue;
                    }
                    if (column == 2) userEmail += c;
                }
                if (userEmail == newValue) {
                    duplicate = true;
                    break;
                }
            }
            file.close();

            if (duplicate) {
                cout << RED << "Email already exists. Please try again.\n" << RESET;
                pauseAndClear();
                continue;
            }

            for (char &c : newValue) c = tolower(c);
            users[index].email = newValue;
            updated = true;
        }

        else if (action == "3") {
            cout << BRIGHT_CYAN << "Original Password: " << users[index].password << "\n" << RESET;
            cout << "Enter new Password " << BRIGHT_YELLOW << "(or 'C' to cancel)" << RESET << ": ";
            newValue = getMaskedPassword();

            if (newValue == "C" || newValue == "c") {
                pauseAndClear();
                continue;
            }
            if (newValue.empty()) {
                cout << RED << "Password cannot be empty.\n" << RESET;
                pauseAndClear();
                continue;
            }
            if (newValue.length() < 8) {
                cout << RED << "Password must be at least 8 characters.\n" << RESET;
                pauseAndClear();
                continue;
            }

            cout << "Confirm Password: ";
            string confirmPassword = getMaskedPassword();
            if (newValue != confirmPassword) {
                cout << RED << "Passwords do not match. Try again.\n" << RESET;
                pauseAndClear();
                continue;
            }

            users[index].password = newValue;
            updated = true;
        }

        else {
            cout << RED << "Invalid choice. Please try again.\n" << RESET;
            pauseAndClear();
            continue;
        }

        if (updated) {
            ofstream outFile("users.txt", ios::trunc);
            for (int i = 0; i < count; i++) {
                outFile << users[i].id << ","
                        << users[i].name << ","
                        << users[i].email << ","
                        << users[i].password << ","
                        << users[i].role << "\n";
            }
            outFile.close();
            cout << BRIGHT_GREEN << "\nProfile updated successfully!\n" << RESET;
            pauseAndClear();
        }
    }
}

