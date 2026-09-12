#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include "read_user.h"
#include "title_manage.h"
#include "colour.h"
#include "pauseAndClear.h"
#include "list.h"
#include "aboutMarks.h"

using namespace std;
struct ShortlistRecord {
    string studentId, studentName;
    string opt1, status1;
    string opt2, status2;
    string opt3, status3;
};

int readShortlist(ShortlistRecord records[], int &count) {
    ifstream file("shortlist.txt");
    count = 0;
    if (!file.is_open()) return 0;

    while (file.good()) {
        ShortlistRecord r;
        getline(file, r.studentId, ',');
        if (r.studentId.empty()) break;
        getline(file, r.studentName, ',');
        getline(file, r.opt1, ','); getline(file, r.status1, ',');
        getline(file, r.opt2, ','); getline(file, r.status2, ',');
        getline(file, r.opt3, ','); getline(file, r.status3);

        records[count++] = r;
    }
    file.close();
    return count;
}

void listSupervisionOrModerationByLecturer(const string& lecturerId) {
    
    ShortlistRecord shortlist[MAX_USERS];
    int shortlistCount = 0;
    readShortlist(shortlist, shortlistCount);

  
    Title titles[MAX_TITLES];
    int titleCount = 0;
    readTitles(titles, titleCount);

    system("cls");
    
    int no = 1;
    bool hasSupervision = false;
    cout << left << setw(5) << "No."
         << setw(15) << "Student ID"
         << setw(25) << "Student Name"
         << setw(12) << "Title ID"
         << setw(30) << "Title Name" << "\n";
    cout << string(100, '-') << "\n";
	cout << BRIGHT_YELLOW << "[Supervision] Students under your supervision:\n" << RESET;

    for (int i = 0; i < shortlistCount; i++) {
        
        string approvedTitle = "";
        if (shortlist[i].status1 == "APPROVED") approvedTitle = shortlist[i].opt1;
        else if (shortlist[i].status2 == "APPROVED") approvedTitle = shortlist[i].opt2;
        else if (shortlist[i].status3 == "APPROVED") approvedTitle = shortlist[i].opt3;

        if (!approvedTitle.empty()) {
		    for (int t = 0; t < titleCount; t++) {
		        if (titles[t].id == approvedTitle && titles[t].supervisorId == lecturerId) {
		            hasSupervision = true;
		
		            string titleDisplay = titles[t].name;
		            if (titleDisplay.length() > 27) {   // keep space for "..."
		                titleDisplay = titleDisplay.substr(0, 27) + "...";
		            }
		
		            cout << left << setw(5)  << no++
		                 << setw(15) << shortlist[i].studentId
		                 << setw(25) << shortlist[i].studentName
		                 << setw(12) << titles[t].id
		                 << setw(30) << titleDisplay << "\n";
			    }
			}
		}
	}
    if (!hasSupervision) {
        cout << RED << "No students under your supervision.\n" << RESET;
    }

    cout << "\n";
    cout << BRIGHT_YELLOW << "[Moderation] Students under your moderation:\n" << RESET;

    MarksRecord records[MAX_MARKS];
    int count = 0;
    readMarks(records, count);

    no = 1;
    bool hasModeration = false;
    
    for (int i = 0; i < count; i++) {
        if (records[i].moderatorId == lecturerId) {
            hasModeration = true;
            cout << left << setw(5) << no++
                 << setw(15) << records[i].studentId
                 << setw(25) << records[i].studentName
                 << setw(12) << records[i].titleId
                 << setw(30) << records[i].titleName << "\n";
        }
    }

    if (!hasModeration) {
        cout << RED << "No students under your moderation.\n" << RESET;
    }

    pauseAndClear();
}

