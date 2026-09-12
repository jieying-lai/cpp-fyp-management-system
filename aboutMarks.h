#ifndef ABOUTMARKS_H
#define ABOUTMARKS_H

#include <string>
using namespace std;
#define MAX_MARKS 200
struct MarksRecord {
    string studentId, studentName;
    string titleId, titleName;
    string supervisorId, moderatorId;

    int fyp1_report_s, fyp1_report_m; double fyp1_report_avg;
    int fyp1_pres_s, fyp1_pres_m;     double fyp1_pres_avg;
    int fyp1_effort_s, fyp1_effort_m; double fyp1_effort_avg;
    double fyp1_total;

    int fyp2_report_s, fyp2_report_m; double fyp2_report_avg;
    int fyp2_demo_s, fyp2_demo_m;     double fyp2_demo_avg;
    int fyp2_pres_s, fyp2_pres_m;     double fyp2_pres_avg;
    int fyp2_effort_s, fyp2_effort_m; double fyp2_effort_avg;
    double fyp2_total;

    double overall;
};

string getLetterGrade(double total);

bool getValidMark(int &mark, int max);
void saveMarks(MarksRecord records[], int count);
int readMarks(MarksRecord records[], int &count);

#endif

