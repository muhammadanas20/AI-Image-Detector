#include "utilities/Utils.h"
#include "utilities/CustomExceptions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
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
void pauseExecution(string message) {
    cout << "\n" << message << endl;
    cin.ignore();
    cin.get();
}

// Utility function to clear screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Mac
    #endif
}

// Utility function to format percentage
string formatPercentage(double value) {
    return to_string((int)(value * 100)) + "%";
}

// ==================== INPUT VALIDATION IMPLEMENTATIONS ====================

int getValidInteger(string prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        try {
            cout << prompt;
            cin >> value;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw InputValidationException("Invalid input. Please enter a valid integer.");
            }
            
            if (value < minValue || value > maxValue) {
                throw InputValidationException("Value must be between " + to_string(minValue) + 
                                              " and " + to_string(maxValue));
            }
            
            cin.ignore(10000, '\n');
            return value;
        }
        catch (const InputValidationException& e) {
            cout << "ERROR: " << e.what() << "\n" << endl;
        }
    }
}

double getValidDouble(string prompt, double minValue, double maxValue) {
    double value;
    while (true) {
        try {
            cout << prompt;
            cin >> value;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw InputValidationException("Invalid input. Please enter a valid number.");
            }
            
            if (value < minValue || value > maxValue) {
                throw InputValidationException("Value must be between " + to_string(minValue) + 
                                              " and " + to_string(maxValue));
            }
            
            cin.ignore(10000, '\n');
            return value;
        }
        catch (const InputValidationException& e) {
            cout << "ERROR: " << e.what() << "\n" << endl;
        }
    }
}

string getValidFilePath(string prompt) {
    string path;
    while (true) {
        try {
            cout << prompt;
            getline(cin, path);
            path = trimString(path);
            
            if (path.empty()) {
                throw InputValidationException("File path cannot be empty.");
            }
            
            if (!isValidFilePath(path)) {
                throw FileNotFoundException(path);
            }
            
            return path;
        }
        catch (const AIDetectorException& e) {
            cout << "ERROR: " << e.what() << "\n" << endl;
        }
    }
}

int getValidMenuChoice(string prompt, int minChoice, int maxChoice) {
    int choice;
    while (true) {
        try {
            cout << prompt;
            cin >> choice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw InputValidationException("Invalid input. Please enter a valid number.");
            }
            
            if (choice < minChoice || choice > maxChoice) {
                throw InvalidChoiceException(to_string(choice));
            }
            
            cin.ignore(10000, '\n');
            return choice;
        }
        catch (const AIDetectorException& e) {
            cout << "ERROR: " << e.what() << "\n" << endl;
        }
    }
}

bool getConfirmation(string prompt) {
    string response;
    while (true) {
        cout << prompt << " (y/n): ";
        getline(cin, response);
        response = trimString(toLower(response));
        
        if (response == "y" || response == "yes") {
            return true;
        }
        else if (response == "n" || response == "no") {
            return false;
        }
        else {
            cout << "ERROR: Please enter 'y' or 'n'.\n" << endl;
        }
    }
}

bool isValidFilePath(const string& path) {
    ifstream file(path);
    return file.good();
}

bool isValidImageFormat(const string& extension) {
    string ext = toLower(extension);
    return ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "tiff" || 
           ext == "bmp" || ext == "gif" || ext == "webp";
}

bool isValidScore(double score) {
    return score >= 0.0 && score <= 1.0;
}

string trimString(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
