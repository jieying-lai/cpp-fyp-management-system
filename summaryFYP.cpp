#include "summaryFYP.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

#include "aboutMarks.h"
#include "read_user.h"
#include "colour.h"
#include "pauseAndClear.h"

using namespace std;

void summaryFYPResults(const string& userId, bool isAdmin) {
	
    MarksRecord records[MAX_MARKS];
    int count = 0;
    readMarks(records, count);

    User users[MAX_USERS];
    int userCount = read_users(users);

    string mode = "all";
    if (!isAdmin) {
        cout << BRIGHT_YELLOW << "[1] Supervision list\n[2] Moderation list\nEnter choice: " << RESET;
        string input;
        getline(cin, input);
        if (input == "1") mode = "supervision";
        else if (input == "2") mode = "moderation";
        else {
            cout << RED << "Invalid input. Showing supervision by default.\n" << RESET;
            mode = "supervision";
        }
    }

    int distinction=0, firstClass=0, secondUpper=0, secondLower=0, passGrade=0, fail=0;
    struct FailInfo { string id; string name; };
    FailInfo failList[MAX_MARKS];
    int failCount = 0;

	system("cls");
	cout << BRIGHT_WHITE << "==================================" << RESET << endl;
    cout << BG_BLUE << BRIGHT_WHITE << "\t--- FYP Summary ---\n" << RESET;
    cout << BRIGHT_WHITE << "==================================" << RESET << endl;

    for (int i = 0; i < count; i++) {
        MarksRecord &r = records[i];

        if (!isAdmin) {
            if (mode == "supervision" && r.supervisorId != userId) continue;
            if (mode == "moderation" && r.moderatorId != userId) continue;
        }

        double total = r.fyp1_total + r.fyp2_total;
        string grade = getLetterGrade(total);

        if (grade == "A+" || grade == "A" || grade == "A-") distinction++;
        else if (grade == "B+" || grade == "B") firstClass++;
        else if (grade == "B-") secondUpper++;
        else if (grade == "C+") secondLower++;
        else if (grade == "C") passGrade++;
        else if (grade == "F") {
            fail++;
            failList[failCount].id = r.studentId;
            failList[failCount].name = r.studentName;
            failCount++;
        }
    }

    cout << BRIGHT_GREEN << "Number of Distinction (A+ / A / A-): " << BRIGHT_WHITE << distinction << "\n";
    cout << BRIGHT_GREEN << "Number of First Class (B+ / B): " << BRIGHT_WHITE << firstClass << "\n";
    cout << BRIGHT_GREEN << "Number of Second Upper (B-): " << BRIGHT_WHITE << secondUpper << "\n";
    cout << BRIGHT_GREEN << "Number of Second Lower (C+): " << BRIGHT_WHITE << secondLower << "\n";
    cout << BRIGHT_GREEN << "Number of Pass (C): " << BRIGHT_WHITE << passGrade << "\n";
    cout << BRIGHT_RED << "Number of Fail (F): " << BRIGHT_WHITE << fail << "\n";
    cout << RESET;

    if (fail > 0) {
        cout << BRIGHT_RED << "\nList of Failing Students:\n" << RESET;
        cout << left << setw(15) << "Student ID" << setw(25) << "Student Name" << "\n";
        cout << string(40, '-') << "\n";
        for (int i = 0; i < failCount; i++) {
            cout << left << setw(15) << failList[i].id << setw(25) << failList[i].name << "\n";
        }
    }

    pauseAndClear();
}

