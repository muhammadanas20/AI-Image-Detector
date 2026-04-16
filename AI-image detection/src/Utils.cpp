#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Utility function to print header
void printHeader(string title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "    " << title << endl;
    cout << string(60, '=') << endl;
}

// Utility function to print section
void printSection(string title) {
    cout << "\n" << string(40, '-') << endl;
    cout << title << endl;
    cout << string(40, '-') << endl;
}

// Utility function to print colored status
void printStatus(string status, bool success) {
    cout << "[" << (success ? "SUCCESS" : "ERROR") << "] " << status << endl;
}

// Utility function to pause execution
void pauseExecution(string message = "Press Enter to continue...") {
    cout << "\n" << message << endl;
    cin.ignore();
    cin.get();
}

// Utility function to format percentage
string formatPercentage(double value) {
    return to_string((int)(value * 100)) + "%";
}
