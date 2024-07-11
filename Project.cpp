#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <regex>

using namespace std;

// User Class
class User {
protected:
    string name;
    string email;
    string password;

public:
    User() {}

    User(string name, string email, string password)
        : name(name), email(email), password(password) {}

    virtual void login() = 0;

    virtual ~User() {}

    bool isValidEmail(const string& email) const {
        // Regular expression for basic email validation
        const regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
        return regex_match(email, pattern);
    }
};

// Address Class
class Address {
private:
    string street;
    string city;
    string country;

public:
    Address() {}

    Address(string street, string city, string country)
        : street(street), city(city), country(country) {}

        string getCity() const {
        return city;
    }

    void setCity(string city) {
        this->city = city;
    }

    friend ostream& operator<<(ostream& os, const Address& address) {
        os << "Address: " << address.street << ", " << address.city << ", " << address.country;
        return os;
    }

    friend ofstream& operator<<(ofstream& ofs, const Address& address) {
        ofs << address.street << " " << address.city << " " << address.country << endl;
        return ofs;
    }
};

class Student : public User {
private:
    string studentId;
    Address address;
    int marks[8]; // To store marks for Quiz1, Quiz2, OHT1, OHT2, Assign1, Assign2, SemProj, Final

public:
    Student() {}

    Student(string name, string email, string password, string studentId, Address address)
        : User(name, email, password), studentId(studentId), address(address) {
            for (int i = 0; i < 8; i++) {
                marks[i] = 0; // Initialize all marks 
            }
        }

    void registerStudent() {
        cout << name << " from " << address.getCity() << " has been successfully registered as a student" << endl;
    }

    void displayMenu() {
    int choice;
    while (true) {
        cout << "\n========== Menu ==========\n";
        cout << "1. Check Marks\n";
        cout << "2. Exit\n";
        cout << "===========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayGrades(); // Call the function to display marks
                break;
            case 2:
                cout << "Exiting...\n";
                return; // Exit the function and return to the main program
            default:
                cout << "Invalid choice! Please enter again.\n";
                break;
        }
    }
}


void login() override {
    string a, b;
    cout << "============Welcome to the Student Login============\n";
    cout << "\n\nLogin Credentials\n";
    cout << "Email: ";
    cin >> a;

    while (!isValidEmail(a)) {
        cout << "Invalid Email Format. Please enter a valid email: ";
        cin >> a;
    }

    cout << "Password: ";
    char ch;
    b = "";
    while ((ch = getch()) != '\r') {
        b.push_back(ch);
        cout << "*";
    }
    cout << endl;

    ifstream file("studentData.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, email, password, street, city, country;
        ss >> id >> name >> email >> password >> street >> city >> country;

        //cout << "DEBUG: Read line: " << line << endl; // Add this line for debug

        if (a == email && b == password) {
            this->studentId = id;
            this->name = name;
            this->email = email;
            this->password = password;
            this->address = Address(street, city, country);
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << name << ", the diligent student, has logged in" << endl;
        displayGrades();
    } else {
        cout << "Invalid Email or Password" << endl;
    }
}


   void displayGrades() {
    ifstream file("StudentMarks.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        ss >> id;

        if (id == studentId) {
            found = true;
            cout << "Grades for student ID: " << studentId << endl;
            int choice;
            cout << "Choose the marks to view:\n";
            cout << "1. Quiz1\n";
            cout << "2. Quiz2\n";
            cout << "3. Quiz3\n";
            cout << "4. OHT1\n";
            cout << "5. OHT2\n";
            cout << "6. Assignment1\n";
            cout << "7. Assignment2\n";
            cout << "8. Final\n";
            cout << "9. Semester Project\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice >= 1 && choice <= 9) {
                // Adjust index for array access (0-based index)
                int index = choice - 1;
                ss >> marks[index];
                cout << "Mark " << choice << ": " << marks[index] << endl;
                displayMenu();

            } else {
                cout << "Invalid choice. Please enter a number between 1 and 9.\n";
            }
        }
    }

    file.close();

    if (!found) {
        cout << "No marks found for student ID: " << studentId << endl;
    }
}

};

// Admin Class
class Admin : public User {
private:
    string AdminID;
    string AdminEmail;
    string AdminPassword;
    string AdminName;

    bool isLoggedIn;    

public:
    Admin() : isLoggedIn(false) {}

    Admin(string AdminID, string AdminEmail, string AdminPassword, string AdminName) {
        this->AdminID = AdminID;
        this->AdminEmail = AdminEmail;
        this->AdminPassword = AdminPassword;
        this->AdminName = AdminName;
    }

    void loadFromFile() {
        ifstream file("adminData.txt");
        if (file.is_open()) {
            string line;
            getline(file, line);
            file.close();

            stringstream ss(line);
            getline(ss, AdminID, ' ');
            getline(ss, AdminEmail, ' ');
            getline(ss, AdminPassword, ' ');
            getline(ss, AdminName);
        } else {
            cout << "Unable to open file for reading.\n";
        }
    }

    void login() {
        string a, b;
        cout << "============Welcome to the Admin Side Login============\n";
        cout << "\n\nLogin Credentials\n";
        cout << "Email: \n";
        cin >> a;

        while(!isValidEmail(a)){
            cout << "Invalid Email Format. Please enter a valid email.";
            cin >> a;
        }

        cout << "Password: \n";
        char ch;
        b = "";
        while((ch = getch()) != '\r') {
            b.push_back(ch);
            cout << "*";
        }
        cout << endl;

        loadFromFile();

        if (a == AdminEmail && b == AdminPassword) {
            isLoggedIn = true;
            cout << "Login Successful!!, Welcome to Admin Portal" << endl;
            displaymenu();

        } else {
            cout << "Invalid Email or Password" << endl;
        }
    }

    void logout() {
        string c;
        cout << "Do you want to logout? yes or no\n";
        cin >> c;

        if (c == "yes") {
            cout << "You have been logged out.\n";
            isLoggedIn = false;
        } else if (c == "no") {
            cout << "Continuing session.\n";
        } else {
            cout << "You entered wrong key!!!\n";
        }
    }

static void addStudent() {
    string studentID, name, email, password, street, city, country;

    cout << "Enter student ID: ";
    cin >> studentID;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter street: ";
    cin.ignore();
    getline(cin, street);
    cout << "Enter city: ";
    getline(cin, city);
    cout << "Enter country: ";
    getline(cin, country);

    Address studentAddress(street, city, country);
    Student newStudent(name, email, password, studentID, studentAddress);

    ofstream files("studentIDs.txt", ios::app);
    if (files.is_open()){
        files << studentID << endl;
        files.close();
    }

    ofstream file("studentData.txt", ios::app);
    if (file.is_open()) {
        file << studentID << " " << name << " " << email << " " << password << " " << studentAddress << endl;
        file.close();
        
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void displaymenu(){
    int choice;
        cout << "Student added successfully.\n";
         do {
        cout << "\nMain Menu\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Remove Student\n";
        cout << "4. View All Results\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                updateStudentData();
                break;
            case 3:
                removeStudent();
                break;
            case 4:
                viewAllResults();
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 5);
}

void removeStudent() {
    string studentID;
    bool studentFound = false;
    
    do {
        cout << "Enter the student ID to remove (or type 'exit' to quit): ";
        cin >> studentID;

        if (studentID == "exit") {
            cout << "Exiting without removing any student.\n";
            return;
        }

        // Check if the student ID exists in the studentData.txt file
        ifstream file("studentData.txt");
        studentFound = false;

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line.find(studentID) != string::npos) {
                    studentFound = true;
                    break;
                }
            }
            file.close();
        } else {
            cout << "Unable to open studentData.txt for processing.\n";
            return;
        }

        if (!studentFound) {
            cout << "Student ID not found. Please try again.\n";
        }
    } while (!studentFound);

    // Remove student from studentData.txt
    ifstream file("studentData.txt");
    ofstream temp("temp.txt");

    if (file.is_open() && temp.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find(studentID) != string::npos) {
                studentFound = true;
            } else {
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
        if (studentFound) {
            remove("studentData.txt");
            rename("temp.txt", "studentData.txt");
        } else {
            remove("temp.txt");
        }
    } else {
        cout << "Unable to open studentData.txt for processing.\n";
    }

    if (studentFound) {
        // Remove student ID from studentIDs.txt
        ifstream idFile("studentIDs.txt");
        ofstream idTemp("idTemp.txt");

        if (idFile.is_open() && idTemp.is_open()) {
            string idLine;
            while (getline(idFile, idLine)) {
                if (idLine.find(studentID) == string::npos) {
                    idTemp << idLine << endl;
                }
            }
            idFile.close();
            idTemp.close();
            remove("studentIDs.txt");
            rename("idTemp.txt", "studentIDs.txt");
            cout << "Student removed successfully.\n";
        } else {
            cout << "Unable to open studentIDs.txt for processing.\n";
        }
    } else {
        cout << "Student ID not found.\n";
    }
}

static void updateStudentData() {
    string studentID, newEmail, newPassword, newCity;
    bool studentFound = false;

    cout << "Enter student ID to update: ";
    cin >> studentID;

    ifstream inputFile("studentData.txt");
    ofstream tempFile("temp.txt");

    if (!inputFile.is_open()) {
        cout << "Unable to open file for reading.\n";
        return;
    }
    if (!tempFile.is_open()) {
        cout << "Unable to open temporary file.\n";
        inputFile.close();
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string id, name, email, password, street, city, country;
        iss >> id >> name >> email >> password >> street >> city >> country;

        if (id == studentID) {
            studentFound = true;

            cout << "Enter new email (or press Enter to keep current): ";
            cin.ignore(); // Clear input buffer
            getline(cin, newEmail);
            if (newEmail.empty()) {
                newEmail = email;
            }

            cout << "Enter new password (or press Enter to keep current): ";
            getline(cin, newPassword);
            if (newPassword.empty()) {
                newPassword = password;
            }

            cout << "Enter new city (or press Enter to keep current): ";
            getline(cin, newCity);
            if (newCity.empty()) {
                newCity = city;
            }

            tempFile << id << " " << name << " " << newEmail << " " << newPassword << " " << street << " " << newCity << " " << country << " " << endl;
        } else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (studentFound) {
        if (remove("studentData.txt") == 0 && rename("temp.txt", "studentData.txt") == 0) {
            cout << "Student data updated successfully.\n";
        } else {
            cout << "Failed to update student data.\n";
        }
    } else {
        cout << "Student ID not found.\n";
    }
}




    void viewAllResults() const {
        string studentID;
        cout << "Enter the student ID to view results: ";
        cin >> studentID;

        ifstream file("studentData.txt");
        if (file.is_open()) {
            string line;
            bool studentFound = false;
            while (getline(file, line)) {
                if (line.find(studentID) != string::npos) {
                    cout << line << endl;
                    studentFound = true;
                }
            }
            file.close();

            if (!studentFound) {
                cout << "No results found for the given student ID.\n";
            }
        } else {
            cout << "Unable to open file for reading.\n";
        }
    }

    bool getIsLoggedIn() const {
        return isLoggedIn;
    }
};

// Teacher Class
class Teacher : public User {
private:
    string TeacherID;
    string TeacherName;
    string TeacherEmail;
    string TeacherPassword;

public:
    Teacher() {}

    Teacher(string TeacherID, string TeacherName, string TeacherEmail, string TeacherPassword) {
        this->TeacherID = TeacherID;
        this->TeacherName = TeacherName;
        this->TeacherEmail = TeacherEmail;
        this->TeacherPassword = TeacherPassword;
    }

    bool loadTeacherData(const string& email, const string& password) {
        ifstream file("TeacherData.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string id, name, emailFromFile, passwordFromFile;
                ss >> emailFromFile >> passwordFromFile >> name >> name;

                if (emailFromFile == email && passwordFromFile == password) {
                    TeacherID = id;
                    TeacherName = name;
                    TeacherEmail = emailFromFile;
                    TeacherPassword = passwordFromFile;
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    void login() override {
        string email, password;
        cout << "============Welcome to the Teacher Side Login============\n";
        cout << "\n\nLogin Credentials\n";
        cout << "Email: ";
        cin >> email;

        while (!isValidEmail(email)) {
            cout << "Invalid Email Format. Please enter a valid email: ";
            cin >> email;
        }

        cout << "Password: ";
        char ch;
        password = "";
        while ((ch = getch()) != '\r') {
            password.push_back(ch);
            cout << "*";
        }
        cout << endl;

        if (loadTeacherData(email, password)) {
            cout << TeacherName << ", the dedicated teacher, has logged in" << endl;
            menu();
        } else {
            cout << "Invalid Email or Password" << endl;
        }
    }


    void menu() {
        int option;
        do {
            cout << "\nTeacher Menu\n";
            cout << "1. Add Marks\n";
            cout << "2. Exit\n";
            cout << "Select an option: ";
            cin >> option;
            switch (option) {
            case 1:
                addMarks();
                break;
            case 2:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option! Please try again.\n";
            }
        } while (option != 2);
    }

void addMarks() {
    string studentID;
    int quiz1, quiz2, ht1, ht2, assign1, assign2, semProj, final;
    bool studentFound = false;

    cout << "Enter student ID: ";
    cin >> studentID;

    // Check if the student ID exists in studentIDs.txt
    ifstream idFile("studentIDs.txt");
    string id;
    while (idFile >> id) {
        if (id == studentID) {
            studentFound = true;
            break;
        }
    }
    idFile.close();

    if (!studentFound) {
        cout << "Student ID not found. Marks cannot be added.\n";
        return;
    }

    cout << "Enter marks for Quiz 1: ";
    cin >> quiz1;
    cout << "Enter marks for Quiz 2: ";
    cin >> quiz2;
    cout << "Enter marks for Hourly Test 1: ";
    cin >> ht1;
    cout << "Enter marks for Hourly Test 2: ";
    cin >> ht2;
    cout << "Enter marks for Assignment 1: ";
    cin >> assign1;
    cout << "Enter marks for Assignment 2: ";
    cin >> assign2;
    cout << "Enter marks for Semester Project: ";
    cin >> semProj;
    cout << "Enter marks for Final: ";
    cin >> final;

    // Open StudentMarks.txt and write the marks
    ofstream marksFile("StudentMarks.txt", ios::app);
    if (marksFile.is_open()) {
        marksFile << studentID << " " << quiz1 << " " << quiz2 << " " << ht1 << " " << ht2 << " " << assign1 << " " << assign2 << " " << semProj << " " << final << endl;
        marksFile.close();
        cout << "Marks added successfully for student ID: " << studentID << endl;
    } else {
        cout << "Unable to open StudentMarks.txt for writing.\n";
    }
}


};

void displayMenu() {
    system("cls"); // Clear the screen
    cout << "************************************************************" << endl;
    cout << "*               Secure and Accessible IST Learning System               *" << endl;
    cout << "************************************************************" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Teacher Login" << endl;
    cout << "3. Student Login" << endl;
    cout << "4. Exit" << endl;
    cout << "************************************************************" << endl;
}

int main() {
    
    Admin admin;
    Teacher t;
    Student s;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                cout << "Admin Login" << endl;
                admin.login(); // Call admin login function
                break;
            case 2:
                cout << "Teacher Login" << endl;
                t.login(); // Call teacher login function
                break;
            case 3:
                cout << "Student Login" << endl;
                s.login(); // Call student login function
                break;
            case 4:
                cout << "Exiting..." << endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        cout << "Press any key to continue...";
        getch(); // Wait for a key press before clearing the screen
    } while (choice != 4);

    return 0;
}

