/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Student {
public:
    string name;
    string id;
};

vector<Student> students;
map<string, string> attendance; // ID -> status

void addStudent() {
    Student s;

    cin.ignore();
    cout << "Name: ";
    getline(cin, s.name);

    cout << "ID: ";
    cin >> s.id;

    students.push_back(s);
}

void markAttendance() {
    for (auto s : students) {
        int choice;
        cout << "\n" << s.name << " (" << s.id << ")\n";
        cout << "1. Present  2. Absent  3. Late\nChoice: ";
        cin >> choice;

        if (choice == 1) attendance[s.id] = "Present";
        else if (choice == 2) attendance[s.id] = "Absent";
        else if (choice == 3) attendance[s.id] = "Late";
        else {
            cout << "Invalid, default Absent\n";
            attendance[s.id] = "Absent";
        }
    }
}

void showReport() {
    int present = 0, absent = 0, late = 0;

    for (auto a : attendance) {
        if (a.second == "Present") present++;
        else if (a.second == "Absent") absent++;
        else if (a.second == "Late") late++;
    }

    cout << "\n--- REPORT ---\n";
    cout << "Present: " << present << endl;
    cout << "Absent: " << absent << endl;
    cout << "Late: " << late << endl;
}

int main() {
    int choice;

    do {
        cout << "\n1. Add Student\n2. Mark Attendance\n3. Report\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: markAttendance(); break;
        case 3: showReport(); break;
        }
    } while (choice != 0);

    return 0;
}