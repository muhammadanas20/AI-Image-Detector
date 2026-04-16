#include "HistoryLog.h"
#include <fstream>
#include <algorithm>
#include <ctime>

HistoryLog::HistoryLog(int maxSize) : maxLogs(maxSize) {
}

HistoryLog::~HistoryLog() {
    logs.clear();
}

void HistoryLog::addEntry(string entry) {
    // Add timestamp to entry
    time_t now = time(0);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&now));
    
    string timestampedEntry = string(buffer) + " - " + entry;
    logs.push_back(timestampedEntry);
    
    // Keep only maxLogs entries
    if (logs.size() > maxLogs) {
        logs.erase(logs.begin());
    }
}

string HistoryLog::getEntry(int index) const {
    if (index < 0 || index >= logs.size()) {
        return "Invalid index";
    }
    return logs[index];
}

void HistoryLog::sortByScore() {
    sort(logs.begin(), logs.end());
}

void HistoryLog::displayLogs() const {
    cout << "\n=== HISTORY LOG ===" << endl;
    cout << "Total entries: " << logs.size() << endl;
    cout << "==================" << endl;
    
    for (int i = 0; i < logs.size(); i++) {
        cout << "[" << i+1 << "] " << logs[i] << endl;
    }
}

void HistoryLog::clearLogs() {
    logs.clear();
    cout << "History log cleared." << endl;
}

void HistoryLog::saveLogsToFile(string filename) const {
    ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    
    outFile << "=== ANALYSIS HISTORY LOG ===" << endl;
    outFile << "Total entries: " << logs.size() << endl;
    outFile << "=============================" << endl;
    
    for (int i = 0; i < logs.size(); i++) {
        outFile << "[" << i+1 << "] " << logs[i] << endl;
    }
    
    outFile.close();
    cout << "Logs saved to: " << filename << endl;
}

string HistoryLog::operator[](int index) const {
    return getEntry(index);
}

int HistoryLog::countKeyword(string keyword) const {
    int count = 0;
    for (const auto& entry : logs) {
        if (entry.find(keyword) != string::npos) {
            count++;
        }
    }
    return count;
}
