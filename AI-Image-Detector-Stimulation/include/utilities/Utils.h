#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <climits>
using namespace std;

// Utility function to print header
void printHeader(string title);

// Utility function to print section
void printSection(string title);

// Utility function to print colored status
void printStatus(string status, bool success);

// Utility function to pause execution
void pauseExecution(string message = "Press Enter to continue...");

// Utility function to clear screen
void clearScreen();

// Utility function to format percentage
string formatPercentage(double value);

// ==================== INPUT VALIDATION FUNCTIONS ====================

// Get valid integer from user
int getValidInteger(string prompt, int minValue = INT_MIN, int maxValue = INT_MAX);

// Get valid double from user
double getValidDouble(string prompt, double minValue = 0.0, double maxValue = 1.0);

// Get valid file path from user
string getValidFilePath(string prompt);

// Get valid menu choice from user
int getValidMenuChoice(string prompt, int minChoice, int maxChoice);

// Get yes/no confirmation from user
bool getConfirmation(string prompt);

// Validate file path exists
bool isValidFilePath(const string& path);

// Validate image format
bool isValidImageFormat(const string& extension);

// Validate score range (0.0 to 1.0)
bool isValidScore(double score);

// Trim whitespace from string
string trimString(const string& str);

// Convert string to lowercase
string toLower(const string& str);

#endif
