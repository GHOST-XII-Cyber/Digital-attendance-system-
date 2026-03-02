#include <iostream>
#include <vector>
#include <string>
#include <iomanip>   // for table formatting
#include <limits>
#include <fstream>   // for CSV file writing/reading
using namespace std;
class Student {
public:
    string id;
    string name;
    string program;
    int year;
    Student(string id, string name, string program, int year) {
        this->id = id;
        this->name = name;
        this->program = program;
        this->year = year;
    }
    void display() {
        cout << "\n-----------------------------\n";
        cout << "Name: " << name << endl;
        cout << "Student ID: " << id << endl;
        cout << "Course: " << program << endl;
        cout << "Year: " << year << endl;
        cout << "-----------------------------\n";
    }
};
struct AttendanceRecord {
    string id;
    string name;
    string date;
    string courseCode;
    string timeJoined;
    string status;
};
vector<Student> students;
vector<AttendanceRecord> attendanceRecords;
// Register Student
void registerStudent() {
    string id, name, program;
    int year;
    cout << "\n--- Register New Student ---\n";
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Program: ";
    getline(cin, program);
    cout << "Enter Year: ";
    cin >> year;
    students.push_back(Student(id, name, program, year));
    cout << "\n==============================\n";
    cout << "   STUDENT REGISTERED SUCCESSFULLY   \n";
    cout << "==============================\n";
}
// View All Students
void viewStudents() {
    cout << "\n==============================\n";
    cout << "        REGISTERED STUDENTS          \n";
    cout << "==============================\n";
    if (students.empty()) {
        cout << "No students registered yet.\n";
    } else {
        for (auto &s : students) s.display();
    }
}
// My Course Hub (store attendance record + save to CSV per course)
void myCourseHub() {
    string id, name, date, courseCode;
    int hour, minute, duration;
    cout << "\n==============================\n";
    cout << "         MY COURSE HUB         \n";
    cout << "==============================\n";
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    cout << "Enter Time Joined (HH MM): ";
    cin >> hour >> minute;
    cout << "Enter Duration (hours): ";
    cin >> duration;
    // Determine attendance status
    string status;
    if ((hour > 6 || (hour == 6 && minute >= 0)) &&
        (hour < 9 || (hour == 9 && minute <= 30))) {
        status = "Early";
    } else if ((hour > 9 || (hour == 9 && minute > 30)) &&
               (hour < 10 || (hour == 10 && minute <= 30))) {
        status = "Late";
    } else {
        status = "Absent";
    }
    // Prevent duplicates
    for (auto &rec : attendanceRecords) {
        if (rec.id == id && rec.courseCode == courseCode && rec.date == date) {
            cout << "\nRecord already exists for this student and course/date.\n";
            return;
        }
    }
    // Save record
    AttendanceRecord record;
    record.id = id;
    record.name = name;
    record.date = date;
    record.courseCode = courseCode;
    record.timeJoined = to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
    record.status = status;
    attendanceRecords.push_back(record);
    // Use course-based filename
    string filename = courseCode + ".csv";
    // Check if file is empty
    ifstream checkFile(filename);
    bool isEmpty = (checkFile.peek() == ifstream::traits_type::eof());
    checkFile.close();
    // Write to CSV file
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        if (isEmpty) {
            // Write header row once
            file << "ID,Name,Date,Course,Time,Status,StartTime,Duration" << endl;
        }
        // Write student record with session info
        file << record.id << "," << record.name << "," << record.date << ","
             << record.courseCode << "," << record.timeJoined << "," << record.status << ","
             << hour << ":" << (minute < 10 ? "0" : "") << minute << "," << duration << endl;
        file.close();
        cout << "\nRecord saved successfully to " << filename << "\n";
    } else {
        cout << "Error: Could not open CSV file.\n";
    }
}
// Student Log (read from course-based CSV file)
void viewStudentLog() {
    string searchId, searchCourse;
    cout << "\n==============================\n";
    cout << "          STUDENT LOG          \n";
    cout << "==============================\n";
    cout << "Enter Student ID: ";
    cin >> searchId;
    cout << "Enter Course Code: ";
    cin >> searchCourse;
    string filename = searchCourse + ".csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << "\n";
        return;
    }
    string line;
    bool found = false;
    getline(file, line); // skip header
    while (getline(file, line)) {
        AttendanceRecord rec;
        size_t pos = 0;
        vector<string> fields;
        while ((pos = line.find(',')) != string::npos) {
            fields.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        fields.push_back(line);
        if (fields.size() >= 8) {
            rec.id = fields[0];
            rec.name = fields[1];
            rec.date = fields[2];
            rec.courseCode = fields[3];
            rec.timeJoined = fields[4];
            rec.status = fields[5];
            if (rec.id == searchId && rec.courseCode == searchCourse) {
                found = true;
                cout << "\n-------------------------------------------------------------\n";
                cout << left << setw(12) << "ID"
                     << setw(20) << "Name"
                     << setw(12) << "Date"
                     << setw(12) << "Course"
                     << setw(10) << "Time"
                     << setw(10) << "Status"
                     << setw(12) << "StartTime"
                     << setw(10) << "Duration" << endl;
                cout << "-------------------------------------------------------------\n";
                cout << left << setw(12) << rec.id
                     << setw(20) << rec.name
                     << setw(12) << rec.date
                     << setw(12) << rec.courseCode
                     << setw(10) << rec.timeJoined
                     << setw(10) << rec.status
                     << setw(12) << fields[6]
                     << setw(10) << fields[7] << endl;
                cout << "-------------------------------------------------------------\n";
                break;
            }
        }
    }
    file.close();
    if (!found) {
        cout << "No matching record found.\n";
    }
}
// Main Program
int main() {
    int choice;
    do {
        cout << "\n==============================\n";
        cout << "   STUDENT ATTENDANCE SYSTEM   \n";
        cout << "==============================\n";
        cout << "1. Register Student\n";
        cout << "2. View All Students\n";
        cout << "3. My Course Hub\n";
        cout << "4. Student Log\n";
        cout << "5. Exit\n";
        cout << "Enter choice (1-5): ";
        cin >> choice;
        switch(choice) {
        case 1:
            registerStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            myCourseHub();
            break;
        case 4:
            viewStudentLog();
            break;
        case 5:
            cout << "\n==============================\n";
            cout << " Thank you for using our service.    \n";
            cout << " Goodbye, and have a great day!      \n";
            cout << "==============================\n";
            break;
        default:
            cout << "\n==============================\n";
            cout << "   Invalid choice! Try again.        \n";
            cout << "==============================\n";
        }
    } while (choice != 5);
    return 0;
}