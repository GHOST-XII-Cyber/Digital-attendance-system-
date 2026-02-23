/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
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

    void display() {
        cout << "Name: " << name << ", ID: " << id << ", Level: " << level << endl;
    }
};

vector<Student> students;

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
    cout << "Student added successfully!\n";
}

// View students
void viewStudents() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        students[i].display();
    }
}

int main() {
    int choice;

    do {
        cout << "\n--- STUDENT MANAGEMENT ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        }
    } while (choice != 0);

    return 0;
}