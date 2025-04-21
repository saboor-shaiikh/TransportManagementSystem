#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function to clear the screen
void clearScreen() {
    system("cls");
}

// Class representing a generic person (e.g., student or admin)
class Person {
public:
    string name;

    // Constructor with optional parameter for name
    Person(string n = "") : name(n) {}

    // Virtual function to display information about the person
    virtual void displayInfo() {
        cout << "+----------------------------------------------------------------+\n";
        cout << "1). Name: " << name;
    }
};

// Class representing a bus route
class BusRoute {
private:
    // Array to hold fees for different routes
    static double routeFees[5];
    // Array to hold timings for different routes
    static string routeTimings[5];

public:
    // Function to get the fee for a given route
    static double getRouteFee(int route) {
        if (route >= 1 && route <= 5) {
            return routeFees[route - 1];
        }
        return 0;
    }

    // Function to display route fees and timings
    static void displayRouteFees() {
        clearScreen();
        cout << "\n\t\t\tRoute 1 Shalimaar: $" << routeFees[0] << " (Pick-up: 7:30 AM, Drop-off: 3:30 PM)" << endl;
        cout << "\t\t\tRoute 2 Wapda Town: $" << routeFees[1] << " (Pick-up: 7:15 AM, Drop-off: 3:15 PM)" << endl;
        cout << "\t\t\tRoute 3 Faisal Town: $" << routeFees[2] << " (Pick-up: 7:45 AM, Drop-off: 3:45 PM)" << endl;
        cout << "\t\t\tRoute 4 Gulberg: $" << routeFees[3] << " (Pick-up: 8:00 AM, Drop-off: 4:00 PM)" << endl;
        cout << "\t\t\tRoute 5 Model Town: $" << routeFees[4] << " (Pick-up: 7:00 AM, Drop-off: 3:00 PM)" << endl;
    }
};

// Static data initialization for BusRoute class
double BusRoute::routeFees[5] = {500, 600, 700, 800, 900};
string BusRoute::routeTimings[5] = {
    "Pick-up: 7:30 AM, Drop-off: 3:30 PM",
    "Pick-up: 7:15 AM, Drop-off: 3:15 PM",
    "Pick-up: 7:45 AM, Drop-off: 3:45 PM",
    "Pick-up: 8:00 AM, Drop-off: 4:00 PM",
    "Pick-up: 7:00 AM, Drop-off: 3:00 PM"
};

// Class representing a student
class Student : public Person {
public:
    int rollNumber;
    int route;
    double feesPaid;
    string fatherName;
    string contactNumber;
    string email;

    // Constructor with parameters for student details
    Student(string n = "", int roll = 0, int rt = 0, double fee = 0,
            string fName = "", string contact = "", string mail = "")
        : Person(n), rollNumber(roll), route(rt), feesPaid(fee),
          fatherName(fName), contactNumber(contact), email(mail) {}

    // Function to display information about the student
    void displayInfo() override {
        Person::displayInfo();
        cout << "\n2). SAP ID: " << rollNumber << "\n3). Route: " << route << "\n4). Fee Paid: $" << feesPaid;
        double pendingFees = calculatePendingFees();
        if (pendingFees > 0) {
            cout << "\n5). Pending Fees: $" << pendingFees;
        } else {
            cout << "\n5). Fees cleared";
        }
        cout << "\n6). Father's Name: " << fatherName;
        cout << "\n7). Contact Number: " << contactNumber;
        cout << "\n8). Email: " << email << endl;
        cout << "+----------------------------------------------------------------+\n";
    }

    // Function to submit a fee and update the total fees paid
    void submitFee(double fee) {
        feesPaid += fee;
        cout << "Fee submitted successfully!" << endl;
    }

    // Function to get the roll number of the student
    int getRollNumber() {
        return rollNumber;
    }

    // Function to set a new route for the student
    void setRoute(int newRoute) {
        route = newRoute;
    }

    // Function to get the current route of the student
    int getRoute() {
        return route;
    }

    // Function to calculate pending fees for the student
    double calculatePendingFees() {
        double routeFee = BusRoute::getRouteFee(route);
        double pendingFees = routeFee - feesPaid;
        return (pendingFees > 0) ? pendingFees : 0;
    }
};

// Class representing an admin
class Admin : public Person {
private:
    string username;
    string password;

public:
    // Constructor with parameters for admin details
    Admin(string n = "", string u = "", string p = "")
        : Person(n), username(u), password(p) {}

    // Function to get the username of the admin
    string getUsername() {
        return username;
    }

    // Function to get the password of the admin
    string getPassword() {
        return password;
    }

    // Function to set a new password for the admin
    void setPassword(string p) {
        password = p;
    }
};

// Class representing a school
class School {
private:
    // Array to hold pointers to student objects
    Student* students[100];
    // Variable to keep track of the number of students
    int numStudents;

public:
    // Constructor initializes the number of students to zero
    School() : numStudents(0) {}

    // Function to register a new student in the school
    void registerStudent(Student* student) {
        if (numStudents < 100) {
            students[numStudents++] = student;
            cout << "Student registered successfully!" << endl;
        } else {
            cout << "Maximum student capacity reached." << endl;
        }
    }

    // Function to delete a student from the school
    void deleteStudent(int rollNumber) {
        for (int i = 0; i < numStudents; i++) {
            if (students[i]->getRollNumber() == rollNumber) {
                delete students[i];
                // Shift students in the array to remove the deleted student
                for (int j = i; j < numStudents - 1; j++) {
                    students[j] = students[j + 1];
                }
                numStudents--;
                cout << "Student deleted successfully!" << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    }

    // Function to find a student in the school using roll number
    Student* findStudent(int rollNumber) {
        for (int i = 0; i < numStudents; i++) {
            if (students[i]->getRollNumber() == rollNumber) {
                return students[i];
            }
        }
        return nullptr;
    }

    // Function to display information of all students in the school
    void displayAllData() {
        cout << "\n\t\tALL STUDENTS DATA:\n";
        for (int i = 0; i < numStudents; i++) {
            students[i]->displayInfo();
        }
    }

    // Function to get the number of students in the school
    int getNumStudents() {
        return numStudents;
    }

    // Function to get the array of student pointers
    Student** getStudents() {
        return students;
    }

    // Destructor to delete all students
    ~School() {
        for (int i = 0; i < numStudents; i++) {
            delete students[i];
        }
    }
};

// Class for handling file operations
class FileHandler {
public:
    // Function to write student data to a file
    static void writeStudentData(Student* student) {
        ofstream file("students.txt", ios::app);
        if (file.is_open()) {
            file << student->getRollNumber() << ','
                 << student->getRoute() << ','
                 << student->calculatePendingFees() << ','
                 << student->name << ','
                 << student->fatherName << ','
                 << student->contactNumber << ','
                 << student->email << '\n';
            file.close();
        }
    }

    // Function to read student data from a file and register in the school
    static void readStudentData(School& school) {
        ifstream file("students.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string temp;
                int rollNumber, route;
                double feesPaid;
                string name, fatherName, contactNumber, email;

                getline(ss, temp, ',');
                rollNumber = stoi(temp);
                getline(ss, temp, ',');
                route = stoi(temp);
                getline(ss, temp, ',');
                feesPaid = stod(temp);
                getline(ss, temp, ',');
                name = temp;
                getline(ss, temp, ',');
                fatherName = temp;
                getline(ss, temp, ',');
                contactNumber = temp;
                getline(ss,temp, ',');
                email = temp;

                // Create a new Student object and register it in the school
                Student* student = new Student(name, rollNumber, route, feesPaid, fatherName, contactNumber, email);
                school.registerStudent(student);
            }
            file.close();
        }
    }

    // Function to write admin data to a binary file
    public:
    static void writeAdminData(Admin* admin) {
        ofstream file("admin.dat", ios::binary | ios::app);
        if (file.is_open()) {
            // Write the sizes of the username and password
            size_t usernameSize = admin->getUsername().size();
            size_t passwordSize = admin->getPassword().size();
            file.write((char*)&usernameSize, sizeof(usernameSize));
            file.write((char*)&passwordSize, sizeof(passwordSize));
            
            // Write the username and password data
            file.write(admin->getUsername().c_str(), usernameSize);
            file.write(admin->getPassword().c_str(), passwordSize);
            file.close();
        }
    }

    // Function to authenticate admin using the stored data
    static bool authenticateAdmin(string username, string password) {
        ifstream file("admin.dat", ios::binary);
        if (file.is_open()) {
            while (file) {
                // Read the sizes of the username and password
                size_t usernameSize, passwordSize;
                file.read((char*)&usernameSize, sizeof(usernameSize));
                file.read((char*)&passwordSize, sizeof(passwordSize));

                // Break the loop if file reading fails
                if (!file) break;

                // Read the stored username and password
                char* buffer = new char[usernameSize + passwordSize + 1];
                file.read(buffer, usernameSize);
                buffer[usernameSize] = '\0';
                string fileUsername(buffer);

                file.read(buffer + usernameSize + 1, passwordSize);
                buffer[usernameSize + passwordSize + 1] = '\0';
                string filePassword(buffer + usernameSize + 1);

                // Clean up buffer memory
                delete[] buffer;

                // Compare the input credentials with stored data
                if (fileUsername == username && filePassword == password) {
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    // Function to check if an admin account exists
    static bool isAdminExists() {
        ifstream file("admin.dat", ios::binary);
        if (file.is_open()) {
            file.close(); // Close the file and return true if it exists
            return true;
        }
        return false;
    }
};

// Class representing the transport management system
class TransportManagementSystem {
private:
    School school; // An instance of the School class

public:
    // Function to start the transport management system
    void run() {
        // Read student data from file and populate the school
        FileHandler::readStudentData(school);

        // Check if an admin account exists, if not prompt to create one
        if (!FileHandler::isAdminExists()) {
            cout << "No admin account found. Please sign up as an admin first." << endl;
            adminSignup();
        }

        // Main loop for the program
        while (true) {
            clearScreen();
            int choice;
            cout << "\n\t\t\t\tMain Menu:" << endl;
            cout << "\t\t1. Admin login" << endl;
            cout << "\t\t2. Exit" << endl;
            cout << "\t\tEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                // Admin login process
                clearScreen();
                string username, password;
                cout << "\n\n\n\n\t\t\t\tEnter admin username: ";
                cin.ignore();
                getline(cin, username);
                cout << "\n\t\t\t\tEnter admin password: ";
                getline(cin, password);

                // Authenticate the admin and run the admin interface
                if (FileHandler::authenticateAdmin(username, password)) {
                    runAdminInterface();
                } else {
                    cout << "Invalid admin credentials. Please try again." << endl;
                }
            } else if (choice == 2) {
                // Exit the program
                cout << "Exiting the program." << endl;
                break;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    // Function to handle the admin interface
    void runAdminInterface() {
        while (true) {
            clearScreen();
            int choice;
            cout << "\n\t\t\t\tAdmin Main Menu:" << endl;
            cout << "\t\t1. Register a new student" << endl;
            cout << "\t\t2. Submit fee" << endl;
            cout << "\t\t3. Search for a student" << endl;
            cout << "\t\t4. Update bus route" << endl;
            cout << "\t\t5. Delete a student" << endl;
            cout << "\t\t6. Display all student data" << endl;
            cout << "\t\t7. Admin signup" << endl;
            cout << "\t\t8. Logout" << endl;
            cout << "\t\tEnter your choice: ";
            cin >> choice;

            // Handle different choices in the admin menu
            switch (choice) {
                case 1:
                    registerStudent();
                    break;
                case 2:
                    submitFee();
                    break;
                case 3:
                    searchStudent();
                    break;
                case 4:
                    updateBusRoute();
                    break;
                case 5:
                    deleteStudent();
                    break;
                case 6:
                    displayAllData();
                    break;
                case 7:
                    adminSignup();
                    break;
                case 8:
                    // Logout and return to the main menu
                    cout << "Logging out..." << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

            // Ask the admin if they want to continue
            char runAgain;
            cout << "\nDo you want to continue as admin? (y/n): ";
            cin >> runAgain;
            if (runAgain != 'y' && runAgain != 'Y') {
                break;
            }
        }
    }

    // Function to handle admin signup
    void adminSignup() {
        clearScreen();
        string adminName, username, password, confirmPassword;

        cout << "\n\n\n\n\t\t\t\tAdmin Signup:\n\n" << endl;
        cout << "Enter admin name: ";
        cin.ignore();
        getline(cin, adminName);
        cout << "Enter admin username: ";
        getline(cin, username);

        // Prompt for password and confirmation
        while (true) {
            cout << "Enter admin password: ";
            getline(cin, password);
            cout << "Re-enter admin password: ";
            getline(cin, confirmPassword);

            if (password == confirmPassword) {
                break;  // Passwords match, proceed
            } else {
                cout << "Passwords do not match. Please try again." << endl;
            }
        }

        // Create a new Admin object and write data to file
        Admin* newAdmin = new Admin(adminName, username, password);
        FileHandler::writeAdminData(newAdmin);
        delete newAdmin;
        cout << "Admin registered successfully!" << endl;
    }

    // Function to register a new student
    void registerStudent() {
        clearScreen();
        string name, fatherName, contactNumber, email;
        int rollNumber, route;
        double feesPaid = 0.0;

        cout << "\n\n\n\n\t\t\t\tRegister a New Student:\n\n" << endl;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        // Check if roll number already exists
        bool rollNumberExists = true;
        while (rollNumberExists) {
            cout << "Enter SAP ID: ";
            cin >> rollNumber;
            cin.ignore();

            if (school.findStudent(rollNumber) != nullptr) {
                cout << "Roll number already exists. Please enter a unique roll number." << endl;
            } else {
                rollNumberExists = false;  // Roll number is unique
            }
        }

        // Prompt user to select a bus route
        while (true) {
            cout << "Select bus route:" << endl;
            BusRoute::displayRouteFees();
            cout << "Enter route (1 / 2 / 3 / 4 / 5): ";
            cin >> route;
            if (route >= 1 && route <= 5) {
                break;  // Valid route selected
            } else {
                cout << "Invalid route number. Please enter a number between 1 and 5." << endl;
                cout << "Would you like to enter the route number again? (y/n): ";
                char choice;
                cin >> choice;
                if (choice != 'y' && choice != 'Y') {
                    cout << "Route selection cancelled." << endl;
                    return;
                }
            }
        }

        // Prompt for additional student information
        cout << "Enter father's name: ";
        cin.ignore();
        getline(cin, fatherName);
        cout << "Enter contact number: ";
        getline(cin, contactNumber);
        cout << "Enter email: ";
        getline(cin, email);

        // Create a new Student object and register it in the school
        Student* newStudent = new Student(name, rollNumber, route, feesPaid, fatherName, contactNumber, email);
        school.registerStudent(newStudent);
        FileHandler::writeStudentData(newStudent);
        cout << "Student registered successfully!" << endl; }// Function to submit fee for a student
void submitFee() {
    clearScreen();
    int rollNumber;
    cout << "\n\n\n\n\t\t\t\tSubmit Fee:\n\n" << endl;
    cout << "Enter roll number of the student: ";
    cin >> rollNumber;

    // Find the student with the provided roll number
    Student* student = school.findStudent(rollNumber);
    if (student) {
        // Calculate the pending fees and display it
        double pendingFees = student->calculatePendingFees();
        cout << "Pending Fees for SAP ID " << rollNumber << ": $" << pendingFees << endl;

        if (pendingFees == 0) {
            cout << "Fees are already cleared for SAP ID " << rollNumber << "." << endl;
            return;
        }

        // Ask for the amount to submit and process the payment
        double fee;
        while (true) {
            cout << "Enter fee amount to submit: $";
            cin >> fee;

            if (fee > pendingFees) {
                cout << "You cannot pay more than the pending fees. Please enter a valid amount." << endl;
            } else {
                // Submit the fee and update the student's account
                student->submitFee(fee);
                cout << "Fee submitted successfully!" << endl;
                break;
            }
        }
    } else {
        // If student is not found, display a message
        cout << "Student not found!" << endl;
    }
}

// Function to search for a student
void searchStudent() {
    clearScreen();
    int rollNumber;
    cout << "\n\n\n\n\t\t\t\tSearch for a Student:\n\n" << endl;
    cout << "Enter roll number of the student to search: ";
    cin >> rollNumber;

    // Find the student and display their information
    Student* student = school.findStudent(rollNumber);
    if (student) {
        cout << "Student found:" << endl;
        student->displayInfo();
    } else {
        // If student is not found, display a message
        cout << "Student not found!" << endl;
    }
}

// Function to update bus route for a student
void updateBusRoute() {
    clearScreen();
    int rollNumber, newRoute;
    cout << "\n\n\n\n\t\t\t\tUpdate Bus Route:\n\n" << endl;
    cout << "Enter roll number of the student: ";
    cin >> rollNumber;

    // Find the student with the provided roll number
    Student* student = school.findStudent(rollNumber);
    if (student) {
        // Prompt for a new bus route and update the student's route
        while (true) {
            cout << "Enter new bus route (1 / 2 / 3 / 4 / 5): ";
            cin >> newRoute;
            if (newRoute >= 1 && newRoute <= 5) {
                student->setRoute(newRoute);
                cout << "Bus route updated successfully!" << endl;
                break;  // Valid route number entered
            } else {
                cout << "Invalid route number. Please enter a number between 1 and 5." << endl;
                cout << "Would you like to enter the route number again? (y/n): ";
                char choice;
                cin >> choice;
                if (choice != 'y' && choice != 'Y') {
                    cout << "Route update cancelled." << endl;
                    return;
                }
            }
        }
    } else {
        // If student is not found, display a message
        cout << "Student not found!" << endl;
    }
}

// Function to delete a student
void deleteStudent() {
    clearScreen();
    int rollNumber;
    cout << "\n\n\n\n\t\t\t\tDelete a Student:\n\n" << endl;
    cout << "Enter roll number of the student to delete: ";
    cin >> rollNumber;

    // Delete the student with the provided roll number
    school.deleteStudent(rollNumber);
}

// Function to display all student data
void displayAllData() {
    clearScreen();
    cout << "\n\n\n\n\t\t\t\tDisplay All Student Data:\n\n" << endl;
    school.displayAllData();
}
};
int main() 
{ 
    clearScreen(); // Create an instance of the transport management system 
    TransportManagementSystem tms; // Start running the system
    tms.run();
    return 0; 
	}