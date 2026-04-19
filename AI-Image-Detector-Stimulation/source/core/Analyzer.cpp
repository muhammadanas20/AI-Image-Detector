#include "core/Analyzer.h"
#include "utilities/CustomExceptions.h"
#include <iostream>
using namespace std;

// Initialize static member
int Analyzer::analyzerCount = 0;

Analyzer::Analyzer() {
    try {
        analyzerID = analyzerCount++;
    }
    catch (const exception& e) {
        throw AnalysisException("Failed to initialize analyzer: " + string(e.what()));
    }
}

Analyzer::~Analyzer() {
    // Virtual destructor for proper cleanup in derived classes
}

void Analyzer::logActivity(string msg) {
    try {
        cout << "[Analyzer " << analyzerID << "] " << msg << endl;
    }
    catch (const exception& e) {
        cerr << "ERROR logging activity: " << e.what() << endl;
    }
}

void Analyzer::displayAnalyzerInfo() const {
    try {
        cout << "Analyzer ID: " << analyzerID << " | Total Analyzers: " << analyzerCount << endl;
    }
    catch (const exception& e) {
        cerr << "ERROR displaying analyzer info: " << e.what() << endl;
    }
}
