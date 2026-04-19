#include "results/HistoryLog.h"
#include "utilities/CustomExceptions.h"
#include <fstream>
#include <algorithm>
#include <ctime>
#include <iostream>

HistoryLog::HistoryLog(int maxSize) : maxLogs(maxSize) {
}

HistoryLog::~HistoryLog() {
    logs.clear();
}

void HistoryLog::addEntry(string entry) {
    try {
        // Add timestamp to entry
        time_t now = time(0);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&now));
        
        string timestampedEntry = string(buffer) + " - " + entry;
        logs.push_back(timestampedEntry);
        
        // Keep only maxLogs entries
        if (logs.size() > static_cast<size_t>(maxLogs)) {
            logs.erase(logs.begin());
        }
    }
    catch (const exception& e) {
        throw DataException("Failed to add log entry: " + string(e.what()));
    }
}

string HistoryLog::getEntry(int index) const {
    try {
        if (index < 0 || index >= static_cast<int>(logs.size())) {
            throw InputValidationException("Log entry index out of bounds: " + to_string(index));
        }
        return logs[index];
    }
    catch (const AIDetectorException& e) {
        cerr << "ERROR: " << e.what() << endl;
        return "ERROR - Invalid index";
    }
}

void HistoryLog::sortByScore() {
    try {
        sort(logs.begin(), logs.end());
    }
    catch (const exception& e) {
        throw DataException("Failed to sort logs: " + string(e.what()));
    }
}

void HistoryLog::displayLogs() const {
    cout << "\n=== HISTORY LOG ===" << endl;
    cout << "Total entries: " << logs.size() << endl;
    cout << "==================" << endl;
    
    for (int i = 0; i < static_cast<int>(logs.size()); i++) {
        cout << "[" << i+1 << "] " << logs[i] << endl;
    }
}

void HistoryLog::clearLogs() {
    try {
        logs.clear();
        cout << "History log cleared." << endl;
    }
    catch (const exception& e) {
        throw DataException("Failed to clear logs: " + string(e.what()));
    }
}

void HistoryLog::saveLogsToFile(string filename) const {
    try {
        ofstream outFile(filename);
        
        if (!outFile.is_open()) {
            throw FileException("Could not open file for writing: " + filename);
        }
        
        outFile << "=== ANALYSIS HISTORY LOG ===" << endl;
        outFile << "Total entries: " << logs.size() << endl;
        outFile << "=============================" << endl;
        
        for (int i = 0; i < static_cast<int>(logs.size()); i++) {
            outFile << "[" << i+1 << "] " << logs[i] << endl;
        }
        
        outFile.close();
        cout << "Logs saved to: " << filename << endl;
    }
    catch (const AIDetectorException& e) {
        cerr << "ERROR saving logs: " << e.what() << endl;
        throw;
    }
    catch (const exception& e) {
        throw FileException("Unexpected error while saving logs: " + string(e.what()));
    }
}

string HistoryLog::operator[](int index) const {
    return getEntry(index);
}

int HistoryLog::countKeyword(string keyword) const {
    try {
        int count = 0;
        for (const auto& entry : logs) {
            if (entry.find(keyword) != string::npos) {
                count++;
            }
        }
        return count;
    }
    catch (const exception& e) {
        throw DataException("Failed to count keyword: " + string(e.what()));
    }
}
