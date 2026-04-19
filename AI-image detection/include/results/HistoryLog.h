#ifndef HISTORYLOG_H
#define HISTORYLOG_H

#include "results/AnalysisResult.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class HistoryLog {
private:
    vector<string> logs;           // All logged activities
    int maxLogs;                   // Maximum number of logs to keep
    
public:
    HistoryLog(int maxSize = 100);
    ~HistoryLog();
    
    // Add entry to log
    void addEntry(string entry);
    
    // Get entry at index
    string getEntry(int index) const;
    
    // Get total log count
    int getCount() const { return logs.size(); }
    
    // Sort logs by score (extract numeric values and sort)
    void sortByScore();
    
    // Display all logs
    void displayLogs() const;
    
    // Clear logs
    void clearLogs();
    
    // Save logs to file
    void saveLogsToFile(string filename) const;
    
    // Operator overloading
    string operator[](int index) const;
    
    // Count occurrences of a keyword
    int countKeyword(string keyword) const;
};

#endif
