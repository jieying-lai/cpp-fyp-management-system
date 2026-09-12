#include "aboutMarks.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

// --- Helper conversion ---
int toInt(const string &s) {
    return s.empty() ? 0 : stoi(s);
}
double toDouble(const string &s) {
    return s.empty() ? 0.0 : stod(s);
}

// --- Letter grade conversion ---
string getLetterGrade(double total) {
    if (total >= 85) return "A";
    else if (total >= 75) return "B";
    else if (total >= 65) return "C";
    else if (total >= 50) return "D";
    else return "F";
}

// --- Input validation for marks ---
bool getValidMark(int &mark, int max) {
    string input;
    getline(cin, input);

    if (input.empty()) return false;

    // Check if all digits
    for (char c : input) {
        if (!isdigit(c)) return false;
    }

    int val = stoi(input);
    if (val < 0 || val > max) return false;

    mark = val;
    return true;
}


// --- Save to CSV file ---
void saveMarks(MarksRecord records[], int count) {
    ofstream out("marks.txt");
    if (!out) return;

    // Header
    out << "StudentID,StudentName,TitleID,TitleName,SupervisorID,ModeratorID,"
        << "FYP1_Report_S,FYP1_Report_M,FYP1_Report_Avg,"
        << "FYP1_Pres_S,FYP1_Pres_M,FYP1_Pres_Avg,"
        << "FYP1_Effort_S,FYP1_Effort_M,FYP1_Effort_Avg,"
        << "FYP1_Total,"
        << "FYP2_Report_S,FYP2_Report_M,FYP2_Report_Avg,"
        << "FYP2_Demo_S,FYP2_Demo_M,FYP2_Demo_Avg,"
        << "FYP2_Pres_S,FYP2_Pres_M,FYP2_Pres_Avg,"
        << "FYP2_Effort_S,FYP2_Effort_M,FYP2_Effort_Avg,"
        << "FYP2_Total,Overall\n";

    for (int i = 0; i < count; i++) {
        MarksRecord &r = records[i];
        out << r.studentId << ","
            << r.studentName << ","
            << r.titleId << ","
            << r.titleName << ","
            << r.supervisorId << ","
            << r.moderatorId << ","

            << r.fyp1_report_s << ","
            << r.fyp1_report_m << ","
            << r.fyp1_report_avg << ","

            << r.fyp1_pres_s << ","
            << r.fyp1_pres_m << ","
            << r.fyp1_pres_avg << ","

            << r.fyp1_effort_s << ","
            << r.fyp1_effort_m << ","
            << r.fyp1_effort_avg << ","

            << r.fyp1_total << ","

            << r.fyp2_report_s << ","
            << r.fyp2_report_m << ","
            << r.fyp2_report_avg << ","

            << r.fyp2_demo_s << ","
            << r.fyp2_demo_m << ","
            << r.fyp2_demo_avg << ","

            << r.fyp2_pres_s << ","
            << r.fyp2_pres_m << ","
            << r.fyp2_pres_avg << ","

            << r.fyp2_effort_s << ","
            << r.fyp2_effort_m << ","
            << r.fyp2_effort_avg << ","

            << r.fyp2_total << ","
            << r.overall
            << "\n";
    }

    out.close();
}

// --- Read from CSV file ---
int readMarks(MarksRecord records[], int &count) {
    ifstream in("marks.txt");
    if (!in) return 0;

    string line;
    count = 0;

    // Check for header
    if (getline(in, line)) {
        if (line.find("StudentID") == string::npos) {
            // no header, rewind
            in.seekg(0);
        }
    }

    while (getline(in, line) && count < MAX_MARKS) {
        stringstream ss(line);
        string field;
        MarksRecord &r = records[count];

        getline(ss, r.studentId, ',');
        getline(ss, r.studentName, ',');
        getline(ss, r.titleId, ',');
        getline(ss, r.titleName, ',');
        getline(ss, r.supervisorId, ',');
        getline(ss, r.moderatorId, ',');

        // FYP1 Report
        getline(ss, field, ','); r.fyp1_report_s = toInt(field);
        getline(ss, field, ','); r.fyp1_report_m = toInt(field);
        getline(ss, field, ','); r.fyp1_report_avg = toDouble(field);

        // FYP1 Pres
        getline(ss, field, ','); r.fyp1_pres_s = toInt(field);
        getline(ss, field, ','); r.fyp1_pres_m = toInt(field);
        getline(ss, field, ','); r.fyp1_pres_avg = toDouble(field);

        // FYP1 Effort
        getline(ss, field, ','); r.fyp1_effort_s = toInt(field);
        getline(ss, field, ','); r.fyp1_effort_m = toInt(field);
        getline(ss, field, ','); r.fyp1_effort_avg = toDouble(field);

        // FYP1 Total
        getline(ss, field, ','); r.fyp1_total = toDouble(field);

        // FYP2 Report
        getline(ss, field, ','); r.fyp2_report_s = toInt(field);
        getline(ss, field, ','); r.fyp2_report_m = toInt(field);
        getline(ss, field, ','); r.fyp2_report_avg = toDouble(field);

        // FYP2 Demo
        getline(ss, field, ','); r.fyp2_demo_s = toInt(field);
        getline(ss, field, ','); r.fyp2_demo_m = toInt(field);
        getline(ss, field, ','); r.fyp2_demo_avg = toDouble(field);

        // FYP2 Pres
        getline(ss, field, ','); r.fyp2_pres_s = toInt(field);
        getline(ss, field, ','); r.fyp2_pres_m = toInt(field);
        getline(ss, field, ','); r.fyp2_pres_avg = toDouble(field);

        // FYP2 Effort
        getline(ss, field, ','); r.fyp2_effort_s = toInt(field);
        getline(ss, field, ','); r.fyp2_effort_m = toInt(field);
        getline(ss, field, ','); r.fyp2_effort_avg = toDouble(field);

        // FYP2 Total
        getline(ss, field, ','); r.fyp2_total = toDouble(field);

        // Overall
        getline(ss, field, ','); r.overall = toDouble(field);

        count++;
    }

    in.close();
    return count;
}



