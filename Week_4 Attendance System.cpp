/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Student {
public:
    string name;
    string id;
};

vector<Student> students;

// Save to file
void saveStudents() {
    ofstream file("students.txt");

    for (auto s : students) {
        file << s.name << "," << s.id << endl;
    }

    file.close();
}

// Load from file
void loadStudents() {
    ifstream file("students.txt");

    Student s;
    while (getline(file, s.name, ',') && getline(file, s.id)) {
        students.push_back(s);
    }

    file.close();
}

void addStudent() {
    Student s;

    cin.ignore();
    cout << "Name: ";
    getline(cin, s.name);

    cout << "ID: ";
    cin >> s.id;

    students.push_back(s);
}

void viewStudents() {
    for (auto s : students) {
        cout << s.name << " - " << s.id << endl;
    }
}

int main() {
    loadStudents();

    int choice;

    do {
        cout << "\n1. Add Student\n2. View Students\n3. Save\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: viewStudents(); break;
        case 3: saveStudents(); break;
        }
    } while (choice != 0);

    saveStudents(); // auto save
    return 0;
}