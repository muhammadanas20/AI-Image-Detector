#ifndef UTILS_H
#define UTILS_H

#include <string>
using namespace std;

// Utility function to print header
void printHeader(string title);

// Utility function to print section
void printSection(string title);

// Utility function to print colored status
void printStatus(string status, bool success);

// Utility function to pause execution
void pauseExecution(string message = "Press Enter to continue...");

// Utility function to format percentage
string formatPercentage(double value);

#endif
