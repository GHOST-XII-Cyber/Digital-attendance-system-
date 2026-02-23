/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

// Student class
class Student {
public:
    string name;
    string id;
    int level;
};

class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;
};

vector<Student> students;
vector<AttendanceSession> sessions;

// Add student
void addStudent() {
    Student s;

    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter ID: ";
    cin >> s.id;

    cout << "Enter Level: ";
    cin >> s.level;

    students.push_back(s);
}

// View students
void viewStudents() {
    for (auto s : students) {
        cout << s.name << " - " << s.id << endl;
    }
}

// Create session
void createSession() {
    AttendanceSession s;

    cout << "Course Code: ";
    cin >> s.courseCode;

    cout << "Date: ";
    cin >> s.date;

    cout << "Start Time: ";
    cin >> s.startTime;

    cout << "Duration: ";
    cin >> s.duration;

    sessions.push_back(s);
    cout << "Session created!\n";
}

// View sessions
void viewSessions() {
    for (auto s : sessions) {
        cout << s.courseCode << " | " << s.date << " | " << s.startTime << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Create Session\n";
        cout << "4. View Sessions\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: viewStudents(); break;
        case 3: createSession(); break;
        case 4: viewSessions(); break;
        }
    } while (choice != 0);

    return 0;
}