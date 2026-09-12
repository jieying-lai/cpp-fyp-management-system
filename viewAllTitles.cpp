#include "viewAllTitles.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include "pauseAndClear.h"
#include "title_manage.h"
#include "colour.h"

using namespace std;

void viewAllTitles() {
    readTitles(titles, titleCount);
    system("cls");

    if (titleCount == 0) {
        cout << BRIGHT_RED << "\nNo titles available.\n" << RESET;
        pauseAndClear();
        return;
    }

    const int pageSize = 10;
    int currentPage = 0;
    int totalPages = (titleCount + pageSize - 1) / pageSize; 

    bool running = true;
    while (running) {
        system("cls");

        cout << BRIGHT_WHITE << "\t\t\t================================" << RESET << endl;
        cout << BG_BLUE << BRIGHT_WHITE << "\t\t\t--- All Available FYP Titles ---\n" << RESET;
        cout << BRIGHT_WHITE << "\t\t\t================================" << RESET << endl;

        cout << BRIGHT_CYAN
             << left << setw(12) << "Title ID"
             << setw(60) << "Title Name"
             << setw(12) << "Status"
             << RESET << endl;

        cout << BRIGHT_WHITE << string(85, '-') << RESET << endl;

        int start = currentPage * pageSize;
        int end = min(start + pageSize, titleCount);
        for (int i = start; i < end; i++) {
            cout << left << setw(12) << titles[i].id
                 << setw(62) << titles[i].name.substr(0, 60)
                 << setw(12) << titles[i].status << endl;
        }

        cout << BRIGHT_YELLOW << "\nShowing " << end << "/" << titleCount
             << " (Page " << (currentPage + 1) << "/" << totalPages << ")" << RESET << endl;

        cout << CYAN << "\nOptions: \n[N]ext\n[P]revious\n " << BRIGHT_YELLOW <<"\n[R]etrun" << RESET << endl;
        cout << "Enter choice: ";

        string input;
        getline(cin, input);

        if (!input.empty() && input.back() == '\r') {
            input.pop_back();
        }

        if (input == "N" || input == "n") {
            if (currentPage < totalPages - 1) {
                currentPage++;
            } else {
                cout << RED << "\nYou are already on the last page!" << RESET << endl;
                pauseAndClear();
            }
        } else if (input == "P" || input == "p") {
            if (currentPage > 0) {
                currentPage--;
            } else {
                cout << RED << "\nYou are already on the first page!" << RESET << endl;
                pauseAndClear();
            }
        } else if (input == "R" || input == "r") {
            running = false;
        } else {
            cout << RED << "\nInvalid choice! Please enter [N, P, or R]." << RESET << endl;
            pauseAndClear();
        }
    }
}

