//M Waiz Shabbir L22-6991
//Zainab Farooq L22-6818



///////////////PRRRRRROOOOOOJJJJJEEEECCCCCCT////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;
int term = 0;

class Manager;

class Approval {
protected:
    bool decision;
    string date;

public:
    Approval(bool dec) : decision(dec) {
        time_t now = time(0);
        date = ctime(&now);
    }

    bool getDecision() const {
        return decision;
    }

    string getDate() const {
        return date;
    }
};

class Leave {
public:
    virtual string getLeaveType() = 0;
};

class Casual : public Leave {
public:
    string getLeaveType() override {
        return "Casual";
    }
};

class Earned : public Leave {
public:
    string getLeaveType() override {
        return "Earned";
    }
};
class Official : public Leave {
public:
    string getLeaveType() override {
        return "Official";
    }
};

class Unpaid : public Leave {
public:
    string getLeaveType() override {
        return "Unpaid";
    }
};

class LeaveApplication {
protected:
    string leaveFrom;
    string leaveTo;
    string reason;
    Leave* leaveType;
    string employeeId;
    int days;
    string status;

public:
    LeaveApplication(Leave* type, int d, string from, string to, string reason, const string& empId, string stat)
        : leaveType(type), days(d), leaveFrom(from), leaveTo(to), reason(reason), employeeId(empId)
    {
        status = stat;
    }


    void showLeaveDetails() {
        // Output statement to display information to the user.
        cout << "Leave Type: " << leaveType->getLeaveType() << " For days: " << days << ", From: " << leaveFrom << ", To: " << leaveTo << ", Reason: " << reason << ", Status: " << status << endl;
    }
    bool IsEmpty()
    {
        // Conditional statement to handle specific logic.
        if (days == 0)
            return false;
        else
            return true;
    }

    string getLeaveType() {
        return leaveType->getLeaveType();
    }

    string getLeaveFrom() const {
        return leaveFrom;
    }

    string getLeaveTo() const {
        return leaveTo;
    }

    string getReason() const {
        return reason;
    }

    string getEmployeeId() const {
        return employeeId;
    }
    int getdays() const {
        return days;
    }
};

// Splits a date string into individual day, month, and year integers

void tokenizeDate(const string& dateStr, int& day, int& month, int& year) {
    stringstream ss(dateStr);
    string token;
    // Declaring a vector to store multiple elements of the same type.
    vector<int> dateParts;

    while (getline(ss, token, '-')) {
        dateParts.push_back(stoi(token));
    }

    day = dateParts[0];
    month = dateParts[1];
    year = dateParts[2];
}

// Stores attendance data including date, status, and working hours

class Attendance
{
    string month;
    string date;
    string status;
    int hours;
public:
    Attendance(string mon, string da, const string status, int hour) : status(status) {
        month = mon;
        date = da;

        if (status == "P")
        {
            hours = hour + 8;
        }
        // Simplified nested conditionals for better readability.
        else if (status == "A")
        {
            hours = 0;
        }
        else
            hours = hour;

    }

    string getDetails() const {
        return "Date: " + date + "-" + month + ", Status: " + status;
    }
    int gethours() {
        return hours;
    }
    string getdate() {
        return date;
    }
    string getmonth() {
        return month;
    }
    string getstatus() {
        return status;
    }

};

// Represents an employee and manages their leave and attendance

class Employee {
protected:
    string id;
    string name;
    int casualLeaves = 15;
    int earnedLeaves = 21;
    vector<LeaveApplication*> leaveApplications;
    vector<Attendance*> attendances;

public:
    Employee(string empId, string empName) : id(empId), name(empName) {}

    string getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    // Adds a leave application for the employee, with validation for leave limits

     void addLeave(LeaveApplication* leave) {

        if ((leave->getLeaveType() == "Casual" && leave->getdays() < casualLeaves && leave->getdays() <= 4) || (leave->getLeaveType() == "Earned" && leave->getdays() < earnedLeaves && leave->getdays() > 4) || leave->getLeaveType() == "Official" || leave->getLeaveType() == "Unpaid")
        {
            leaveApplications.push_back(leave);
        }
        else
        {
            // Output statement to display information to the user.
            cout << "Leave not Applied\n";
        }

    }

    void showLeaveDetails() {                 //For one single Employee if required

        cout << "Leave details for " << name << " (ID: " << id << "):\n";
        for (const auto& leave : leaveApplications) {
            leave->showLeaveDetails();
        }
    }
    void showRemainingLeave()
    {
        cout << "Casual Leaves : " << casualLeaves << " AND Earned Leaves : " << earnedLeaves << endl;
    }
    vector<LeaveApplication*>& getleaveApplications()
    {
        return leaveApplications;
    }
    vector<Attendance*>& getAttendances()
    {
        return attendances;
    }
    bool deductLeaves(const string& leaveType, const int days) {
        if (leaveType == "Casual" && casualLeaves > days) {
            casualLeaves = casualLeaves - days;
            return true;
        }
        else if (leaveType == "Earned" && earnedLeaves > days) {
            earnedLeaves = earnedLeaves - days;
            return true;
        }
        else
        {
            return false;
        }

    }
    bool checkLeaves(const string& leaveType, const int days) {
        if (leaveType == "Casual" && casualLeaves > days) {
            return true;
        }
        else if (leaveType == "Earned" && earnedLeaves > days) {
            return true;
        }
        else
        {
            return false;
        }

    }
    void addAttendance(string month, string date, string status, int hours);

    void showAttendance() const {
        cout << "Attendance details for " << name << " (ID: " << id << "):\n";
        for (const auto& att : attendances) {
            cout << att->getDetails() << ", Hours : " << att->gethours() << endl;
        }
    }

    void weeklyAttendanceReport(const string& startDay, const string& endDay, string mon) {
        int totalHours = 0, daysPresent = 0, daysOnLeave = 0, outDays = 0, daysAbsent = 0;

        for (const auto& att : attendances) {
            if (stoi(att->getdate()) >= stoi(startDay) && stoi(att->getdate()) <= stoi(endDay) && att->getmonth() == mon) {
                totalHours += att->gethours();
                if (att->getstatus() == "P") daysPresent++;
                else if (att->getstatus() == "L") daysOnLeave++;
                else if (att->getstatus() == "O") outDays++;
                else if (att->getstatus() == "A") daysAbsent++;
            }
        }

        cout << "Weekly Report (" << startDay << " to " << endDay << "):\n"
            << "Present: " << daysPresent << ", Absent: " << daysAbsent
            << ", On Leave: " << daysOnLeave << ", Out Days: " << outDays
            << ", Hours Worked: " << totalHours << "\n";
    }

    void monthlyAttendanceReport(const string& month, int check) { // check to check the purpose 0 aya to just show, 1 aya tou calculate
        int totalHours = 0, daysPresent = 0, daysOnLeave = 0, outDays = 0, daysAbsent = 0;

        for (const auto& att : attendances) {
            if (att->getmonth() == month) {
                totalHours += att->gethours();
                if (att->getstatus() == "P") daysPresent++;
                else if (att->getstatus() == "L") daysOnLeave++;
                else if (att->getstatus() == "O") outDays++;
                else if (att->getstatus() == "A") daysAbsent++;
            }
        }
        int percentage = (totalHours / 160) * 100; //Assuming that there are 160 working hours in each month

        if (check == 1 && percentage < 80)
        {
            cout << "Monthly Report (" << month << "):\n"
                << "Present: " << daysPresent << ", Absent: " << daysAbsent
                << ", On Leave: " << daysOnLeave << ", Out Days: " << outDays
                << ", Hours Worked: " << totalHours << "\n";
        }
        else if (check == 0)
        {

            cout << "Monthly Report for (" << id << "):\n"
                << "Present: " << daysPresent << ", Absent: " << daysAbsent
                << ", On Leave: " << daysOnLeave << ", Out Days: " << outDays
                << ", Hours Worked: " << totalHours << "\n";
        }
    }

};

class Guard : public Employee
{
public:
    Guard(const string& id, const string& name) : Employee(id, name) {}

    // Allows a guard to mark attendance for employees (but not themselves)

    void markAttendance(Employee* emp, string month, string date, const string& status, int hours) {
        if (this == emp) {
            // Output statement to display information to the user.
            cout << "A guard cannot mark their own attendance.\n";
        }
        else {
            emp->addAttendance(month, date, status, hours);
        }
    }
};

class Supervisor : public Approval, public Employee {
public:
    Supervisor(bool dec, string empId, string empName) : Approval(dec), Employee(empId, empName) {}

    // Handles leave approval by Supervisor or Director based on leave type and duration
       /* void approveLeave(LeaveApplication* leave, bool decision) {
    // Conditional statement to handle specific logic.
    // Simplified nested conditionals for better readability.
            if (leave->getEmployeeId() == getId()) {
    // Output statement to display information to the user.
                cout << "Supervisor cannot approve their own leave." << endl;
                return;
            }
    // Conditional statement to handle specific logic.
    // Simplified nested conditionals for better readability.
            if (leave->getdays() <= 4) {
    // Conditional statement to handle specific logic.
    // Simplified nested conditionals for better readability.
                if (decision) {
    // Output statement to display information to the user.
                    cout << "Leave approved by Supervisor: " << leave->getLeaveType() << endl;
                    deductLeaves(leave->getLeaveType(), leave->getdays());
                }
                else {
    // Output statement to display information to the user.
                    cout << "Leave denied by Supervisor: " << leave->getLeaveType() << endl;
                }
            }
            else {
    // Output statement to display information to the user.
                cout << "Supervisor can only approve Short Leaves " << endl;
            }
        }*/
};

class Director : public Approval, public Employee {
public:
    Director(bool dec, string empId, string empName) : Approval(dec), Employee(empId, empName) {}

    // Handles leave approval by Supervisor or Director based on leave type and duration
       /* void approveLeave(LeaveApplication* leave, bool decision) {
    // Conditional statement to handle specific logic.
    // Simplified nested conditionals for better readability.
            if (leave->getEmployeeId() == getId()) {
    // Output statement to display information to the user.
                cout << "Director cannot approve their own leave." << endl;
                return;
            }
    // Conditional statement to handle specific logic.
    // Simplified nested conditionals for better readability.
            if (leave->getdays() > 4) {
    // Conditional statement to handle specific logic.
    // Simplified nested conditionals for better readability.
                if (decision) {
    // Output statement to display information to the user.
                    cout << "Leave approved by Director: " << leave->getLeaveType() << endl;
                    deductLeaves(leave->getLeaveType(), leave->getdays());
                }
                else {
    // Output statement to display information to the user.
                    cout << "Leave denied by Director: " << leave->getLeaveType() << endl;
                }
            }
            else {
    // Output statement to display information to the user.
                cout << "Director can only approve longer Leaves" << endl;
            }
        }*/
};

class FileManager {
public:
    virtual void saveData(const string& data) = 0;
    virtual string loadData() = 0;
};

class FileIO : public FileManager {
    string filePath;

public:
    FileIO(const string& path) : filePath(path) {}

    void saveData(const string& data) override {
        ofstream file(filePath, ios::app); 
        if (file.is_open()) {
            file << data << endl;
            file.close();
        }
    }
    string loadData() override {
        ifstream file(filePath);
        string data, line;
        if (file.is_open()) {
            while (getline(file, line)) {
                data += line + "\n";
            }
        }
        return data;
    }
};

// Marks attendance for days during which leave is taken

void markLeaveAttendance(Employee* emp, string leaveType, const string& leaveFrom, const string& leaveTo) {
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;

    // Splits a date string into individual day, month, and year integers
    tokenizeDate(leaveFrom, startDay, startMonth, startYear);
    // Splits a date string into individual day, month, and year integers
    tokenizeDate(leaveTo, endDay, endMonth, endYear);

    while (startYear < endYear || (startYear == endYear && startMonth <= endMonth)) {
        int daysInMonth = 31;
        if (startMonth == 2) {
            daysInMonth = (startYear % 4 == 0 && (startYear % 100 != 0 || startYear % 400 == 0)) ? 29 : 28;
        }
        else if (startMonth == 4 || startMonth == 6 || startMonth == 9 || startMonth == 11) {
            daysInMonth = 30;
        }

        for (int day = startDay; day <= daysInMonth && (startMonth < endMonth || day <= endDay); ++day) {
            stringstream dayStream, monthStream;
            dayStream << (day < 10 ? "0" : "") << day;
            monthStream << (startMonth < 10 ? "0" : "") << startMonth;

            if (leaveType == "Official")
                emp->addAttendance(monthStream.str(), dayStream.str(), "P", 0); ////////////need to confirm this thingi
            else
                emp->addAttendance(monthStream.str(), dayStream.str(), "L", 8);
        }

        startDay = 1;
        startMonth++;
        if (startMonth > 12) {
            startMonth = 1;
            startYear++;
        }
    }
}

class Manager {
    // Declaring a vector to store multiple elements of the same type.
    vector<Employee*> employees;
    FileManager* attendanceFile;
    FileManager* leaveFile;

public:
    Manager() {
        attendanceFile = new FileIO("attendance_data.txt");
        leaveFile = new FileIO("leave_data.txt");
    }
    void addEmployee(Employee* emp) {
        bool twin = false;
        for (const auto& empl : employees) {
            if (empl->getId() == emp->getId())
                twin = true;
        }
        if (twin == false)
            employees.push_back(emp);
        else
            cout << "Employee Already Here!!\n";
    }
    vector<Employee*>& getEmployees() {
        return employees;
    }

    void DisplayEmployees() {
        cout << "Employees:\n";
        for (const auto& emp : employees) {
            cout << "ID: " << emp->getId() << ", Name: " << emp->getName() << endl;
        }
    }


    void RecordAttendance() {
        for (auto emp : employees) {
            auto& att = emp->getAttendances();
            for (auto a : att) {
                string record = "ID: " + emp->getId() + ", Name: " + emp->getName() + ", Date: " + a->getdate() + "-" + a->getmonth() + ", Status: " + a->getstatus();
                attendanceFile->saveData(record);
            }
        }
    }


    void AttendanceReports() {
        string data = attendanceFile->loadData();
        cout << "Attendance Reports:\n" << data << endl;
    }

    void LeaveReports() {
        string data = leaveFile->loadData();
        cout << "Leave Reports:\n" << data << endl;
    }


    void ELeaveReports(Employee* emp)
    {
        string data = leaveFile->loadData();
        istringstream iss(data);
        string line;

        while (getline(iss, line)) {
            istringstream lineStream(line);
            string days;
            string empId, leaveType, leaveFrom, leaveTo, reason, status;

            // Parse the line
            getline(lineStream, empId, ',');
            getline(lineStream, leaveType, ',');
            getline(lineStream, leaveFrom, ',');
            getline(lineStream, leaveTo, ',');
            getline(lineStream, days, ',');
            getline(lineStream, reason, ',');
            getline(lineStream, status, ',');

            if (empId == emp->getId())
            {
                // Output statement to display information to the user.
                cout << "Employee ID: " << empId << "\nLeave Type: " << leaveType << " For: " << days
                    << " From: " << leaveFrom << " To: " << leaveTo
                    << " Reason: " << reason << " Status: " << status << endl;
            }
        }
    }
    string RecordLeave(Employee* emp, Leave* LeaveType, string start, string end, string reason, int days) {
        string status = "Pending";

        if (LeaveType->getLeaveType() == "Casual")
        {
            if (emp->deductLeaves("Casual", days) == true)
                status = "Accepted";
            else
                status = "Rejected";
        }
        stringstream ss;
        ss << days;
        string dayz = ss.str();
        string leaveDetails = emp->getId() + "," + LeaveType->getLeaveType() + "," + start + "," + end + "," + dayz + "," + reason + "," + status;
        leaveFile->saveData(leaveDetails);
        return status;
    }

 
    void ReviewLeaves(string AgentID, int Agentcode) { //AgentID to check if they cant Approve their own leaves, Agentcode to give only the required info to Director and Supervisor
        string data = leaveFile->loadData();
        istringstream iss(data);
        string line;
        vector<string> updatedRecords;
        bool foundPending = false;

        while (getline(iss, line)) {
            istringstream lineStream(line);
            string days;
            string empId, leaveType, leaveFrom, leaveTo, reason, status;

            // Parse the line
            getline(lineStream, empId, ',');
            getline(lineStream, leaveType, ',');
            getline(lineStream, leaveFrom, ',');
            getline(lineStream, leaveTo, ',');
            getline(lineStream, days, ',');
            getline(lineStream, reason, ',');
            getline(lineStream, status, ',');

            int num;
            stringstream ss(days);
            ss >> num;
            foundPending = false;


            if (status == "Pending" && empId != AgentID && Agentcode == 0) { //for Supervisor
                foundPending = true;
                bool yess = false;

                cout << "Employee ID: " << empId << "\nLeave Type: " << leaveType << " For: " << days
                    << " From: " << leaveFrom << " To: " << leaveTo
                    << " Reason: " << reason << " Status: Pending\n";

                char decision;
                cout << "Approve this leave? (Y/N): ";
                cin >> decision;

                if (decision == 'Y' || decision == 'y') {


                    for (auto emp : employees) {
                        if (emp->getId() == empId && yess == false)
                        {
                            if (num <= 4)
                            {
                                yess = emp->deductLeaves(leaveType, num);
                            }
                            else if (num > 4)
                            {
                                yess = emp->checkLeaves(leaveType, num);
                            }
                            if (leaveType == "Unpaid" || leaveType == "Official")
                            {
                                yess = true;
                            }
                            if (yess && num <= 4)
                            {

                                markLeaveAttendance(emp, leaveType, leaveFrom, leaveTo);
                            }
                        }

                    }
                    if (yess)
                    {
                        cout << "Leave Approved.\n";
                        status = "S Approved ";
                    }

                }
                else if (decision == 'N' || decision == 'n') {
                    status = "S Unapproved";
                    cout << "Leave Unapproved.\n";
                }
                else {
                    cout << "Invalid input. Status remains Pending.\n";
                }
            }

            else if ((status == "S Approved ") && num > 4 && empId != AgentID && Agentcode == 1) { //for Director
                bool yess = false;
                foundPending = true;

                cout << "Employee ID: " << empId << "\nLeave Type: " << leaveType << " For: " << days
                    << " From: " << leaveFrom << " To: " << leaveTo
                    << " Reason: " << reason << " Status: S Approved\n";

                char decision;
                cout << "Approve this leave? (Y/N): ";
                cin >> decision;

                if (decision == 'Y' || decision == 'y') {

                    for (auto emp : employees) {
                        if (emp->getId() == empId && yess == false)
                        {
                            yess = emp->deductLeaves(leaveType, num);
                            if (leaveType == "Unpaid" || leaveType == "Official")
                            {
                                yess = true;
                            }
                            if (yess)
                            {
                                // Marks attendance for days during which leave is taken
                                markLeaveAttendance(emp, leaveType, leaveFrom, leaveTo);
                            }
                        }

                    }
                    if (yess)
                    {
                        cout << "Leave Approved.\n";
                        status = "D Approved ";
                    }
                }
                else if (decision == 'N' || decision == 'n') {
                    status = "D Unapproved";
                    cout << "Leave Unapproved.\n";
                }
                else {
                    cout << "Invalid input. Status remains Pending.\n";
                }
            }

            // Save the updated line
            updatedRecords.push_back(empId + "," + leaveType + "," + leaveFrom + "," + leaveTo + "," + days + "," + reason + "," + status);
        }

        if (!foundPending) {
            cout << "No pending leave applications to review.\n";
            return;
        }

        // Write back all leave data to the file
        ofstream file("leave_data.txt");
        for (const auto& record : updatedRecords) {
            file << record << endl;
        }
        file.close();
    }
};

void Employee::addAttendance(string month, string date, string status, int hours) { //Outstanding leaves wala kaam is happening here!!
    bool chuttiyanheinn = false;
    if (status == "A")
    {
        chuttiyanheinn = checkLeaves("Casual", 1);
        if (chuttiyanheinn)
        {
            string leaveFrom = date + "-" + month + "-" + "24";
            string leaveTo = date + "-" + month + "-" + "24";
            string reason = "Outstanding Leave";
            Leave* leave = new Casual();
            string leaveDetails = id + "," + "Casual" + "," + leaveFrom + "," + leaveTo + "," + "1" + "," + reason + "," + "Accepted";
            LeaveApplication* leaveApp = new LeaveApplication(leave, 1, leaveFrom, leaveTo, reason, id, "Accepted");
            ofstream file("leave_data.txt", ios::app); // Append mode
            if (file.is_open()) {
                file << leaveDetails << endl;
                file.close();
            }
            // Adds a leave application for the employee, with validation for leave limits
            addLeave(leaveApp);
            deductLeaves("Casual", 1);

            status = "O";
            hours = 8;
            // Output statement to display information to the user.
            cout << "Absence catered in Casual Leaves\n";
        }
    }
    attendances.push_back(new Attendance(month, date, status, hours));
}
int main() {
    Manager manager;

    // Add some sample employees
    Employee* emp1 = new Employee("E001", "Alice");
    Employee* emp2 = new Employee("E002", "Bob");
    Supervisor* supervisor = new Supervisor(true, "S001", "Charlie");
    Guard* guard = new Guard("G001", "Diana");
    Director* director = new Director(true, "D001", "Eve");

    manager.addEmployee(emp1);
    manager.addEmployee(emp2);
    manager.addEmployee(supervisor);
    manager.addEmployee(guard);
    manager.addEmployee(director);


    while (term == 0) {
        char choice = ' ';
        cout << "Enter: \n"
            << "   E for Employee \n"
            << "   S for Supervisor \n"
            << "   G for Guard \n"
            << "   D for Director \n"
            << "   A for Admin \n"
            << "   X for Exit \n";
        cin >> choice;

        if (choice == 'E' || choice == 'e') {
            // Employee operations
            string empId;
            cout << "Enter your Employee ID: ";
            cin >> empId;

            for (auto& emp : manager.getEmployees()) {
                if (emp->getId() == empId) {
                    char empChoice;
                    cout << "Enter: \n"
                        << "   A to Apply for Leave \n"
                        << "   V to View Attendance \n"
                        << "   L to check Leaves \n"
                        << "   R to check Remaining Leaves \n";
                    cin >> empChoice;

                    if (empChoice == 'A' || empChoice == 'a') {
                        string leaveType, leaveFrom, leaveTo, reason;
                        int days;
                        cout << "Enter Leave Type (Casual, Earned, Official, Unpaid): ";
                        cin >> leaveType;
                        cout << "Enter From Date: ";
                        cin >> leaveFrom;
                        cout << "Enter To Date: ";
                        cin >> leaveTo;
                        cout << "Enter Number of Days: ";
                        cin >> days;
                        cout << "Enter Reason: ";
                        cin.ignore();
                        getline(cin, reason);

                        Leave* leave;
                        if (leaveType == "Casual") leave = new Casual();
                        else if (leaveType == "Earned") leave = new Earned();
                        else if (leaveType == "Official") leave = new Official();
                        else if (leaveType == "Unpaid") leave = new Unpaid();
                        else {
                            cout << "Invalid leave type!\n";
                            break;
                        }

                        /////////////

                        string stat = manager.RecordLeave(emp, leave, leaveFrom, leaveTo, reason, days);
                        LeaveApplication* leaveApp = new LeaveApplication(leave, days, leaveFrom, leaveTo, reason, empId, stat);
                        // Adds a leave application for the employee, with validation for leave limits
                        emp->addLeave(leaveApp);

                        cout << "Leave Application Submitted!\n";
                    }
                    else if (empChoice == 'V' || empChoice == 'v') {
                        emp->showAttendance();
                    }
                    else if (empChoice == 'L' || empChoice == 'l')
                    {
                        manager.ELeaveReports(emp);
                    }
                    else if (empChoice == 'R' || empChoice == 'r')
                    {
                        emp->showRemainingLeave();
                    }
                }
            }
        }
        else if (choice == 'S' || choice == 's') {
            manager.ReviewLeaves(supervisor->getId(), 0); // 0 indicates Supervisor
        }
        else if (choice == 'G' || choice == 'g') {
            // Guard operations

            string empId, status, month, date;
            int hours;

            // Allows a guard to mark attendance for employees (but not themselves)
            cout << "Enter Employee ID to mark attendance : ";
            cin >> empId;
            cout << "\nEnter Month :  ";
            cin >> month;
            cout << "\nEnter Date : ";
            cin >> date;
            cout << "\nEnter Status (P/A) : ";
            cin >> status;
            if (status == "P")
            {
                cout << "\nEnter Overtime Hours(0 if none) : ";
                cin >> hours;
            }
            if (hours < 16)
            {
                for (auto& emp : manager.getEmployees()) {
                    if (emp->getId() == empId) {
                        guard->markAttendance(emp, month, date, status, hours);
                        cout << "Attendance Marked for Employee ID: " << empId << "\n";
                    }
                }
            }

        }
        else if (choice == 'D' || choice == 'd') {
            manager.ReviewLeaves(director->getId(), 1); // 1 indicates Director
        }
        else if (choice == 'A' || choice == 'a') {
            char cho;
            cout << "Enter: \n"
                << "   L for General Leave Reports \n"
                << "   A for General Attendance Reports \n"
                << "   S for Employee Attendence Report \n"
                << "   T for Employee Leave Report \n"
                << "   W for Employee Weekly Attendence Report \n"
                << "   M for Employee Monthly Attendance Report \n"
                << "   P for Monthly Attendance Report for Lazy Employees\n";
            cin >> cho;
            if (cho == 'L')
                manager.LeaveReports();
            else if (cho == 'A' || cho == 'a')
            {
                manager.RecordAttendance();
                manager.AttendanceReports();
            }
            else if (cho == 'S' || cho == 's')
            {
                string Eye;
                cout << "Enter the Id of Employee : ";
                cin >> Eye;

                for (auto& emp : manager.getEmployees()) {
                    if (emp->getId() == Eye) {
                        emp->showAttendance();
                    }
                }

            }
            else if (cho == 'T' || cho == 't')
            {
                string Eye;
                cout << "Enter the Id of Employee : ";
                cin >> Eye;

                for (auto& emp : manager.getEmployees()) {
                    if (emp->getId() == Eye) {
                        emp->showLeaveDetails();
                    }
                }

            }
            else if (cho == 'W' || cho == 'w')
            {
                string Eye, start, end, month;
                cout << "Enter the Id of Employee : ";
                cin >> Eye;
                cout << "Enter month : ";
                cin >> month;
                cout << "Enter start date : ";
                cin >> start;
                cout << "Enter end date : ";
                cin >> end;
                for (auto& emp : manager.getEmployees()) {
                    if (emp->getId() == Eye) {
                        emp->weeklyAttendanceReport(start, end, month);
                    }
                }

            }
            else if (cho == 'M' || cho == 'm') {
                string Eye, mon;
                cout << "Enter the Id of Employee : ";
                cin >> Eye;
                cout << "Enter month : ";
                cin >> mon;

                for (auto& emp : manager.getEmployees()) {
                    if (emp->getId() == Eye) {
                        emp->monthlyAttendanceReport(mon, 0);
                    }
                }
            }
            else if (cho == 'P' || cho == 'p') {
                string mon;
                cout << "Enter month : ";
                cin >> mon;

                for (auto& emp : manager.getEmployees()) {
                    emp->monthlyAttendanceReport(mon, 1);
                }
            }

        }
        else if (choice == 'X' || choice == 'x') {
            term++;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    cout << "Goodbye!" << endl;

    // Cleanup dynamically allocated memory
    delete emp1;
    delete emp2;
    delete supervisor;
    delete guard;
    delete director;

    return 0;
}