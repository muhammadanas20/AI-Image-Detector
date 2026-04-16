#include "Analyzer.h"
#include <iostream>
using namespace std;

// Initialize static member
int Analyzer::analyzerCount = 0;

Analyzer::Analyzer() {
    analyzerID = analyzerCount++;
}

Analyzer::~Analyzer() {
    // Virtual destructor for proper cleanup in derived classes
}

void Analyzer::logActivity(string msg) {
    cout << "[Analyzer " << analyzerID << "] " << msg << endl;
}

void Analyzer::displayAnalyzerInfo() const {
    cout << "Analyzer ID: " << analyzerID << " | Total Analyzers: " << analyzerCount << endl;
}
