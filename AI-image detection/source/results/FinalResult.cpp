#include "results/FinalResult.h"
#include <fstream>
#include <iomanip>
#include <algorithm>

FinalResult::FinalResult() : confidence(0.0), isAIGenerated(false) {
}

FinalResult::~FinalResult() {
    results.clear();
}

void FinalResult::addAnalysisResult(const AnalysisResult& result) {
    results.push_back(result);
}

void FinalResult::calcFinalScore() {
    if (results.empty()) {
        confidence = 0.0;
        return;
    }
    
    // Calculate average confidence from all analyzers
    double sum = 0.0;
    for (const auto& result : results) {
        sum += result.getScore();
    }
    confidence = sum / results.size();
    
    // Determine if AI generated based on threshold
    isAIGenerated = (confidence > 0.5);
}

void FinalResult::displayFullReport() const {
    cout << "\n" << string(50, '=') << endl;
    cout << "           FINAL ANALYSIS REPORT" << endl;
    cout << string(50, '=') << endl;
    
    cout << fixed << setprecision(2);
    cout << "\nFinal Confidence Score: " << confidence << " (0.0 = Real, 1.0 = AI)" << endl;
    cout << "Verdict: " << (isAIGenerated ? "AI GENERATED" : "LIKELY AUTHENTIC") << endl;
    
    cout << "\n" << string(50, '-') << endl;
    cout << "Individual Analyzer Results:" << endl;
    cout << string(50, '-') << endl;
    
    for (int i = 0; i < results.size(); i++) {
        cout << "\n[" << i+1 << "] ";
        results[i].displayResult();
    }
    
    cout << "\n" << string(50, '=') << endl;
}

void FinalResult::saveToFile(string filename) {
    ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    
    outFile << "=== AI IMAGE DETECTION REPORT ===" << endl;
    outFile << "Generated at: " << __DATE__ << " " << __TIME__ << endl;
    outFile << "\nFinal Verdict: " << (isAIGenerated ? "AI GENERATED" : "AUTHENTIC") << endl;
    outFile << "Confidence: " << confidence << endl;
    outFile << "\n--- Analyzer Results ---" << endl;
    
    for (const auto& result : results) {
        outFile << "\nAnalyzer: " << result.getAnalyzerName() << endl;
        outFile << "Score: " << result.getScore() << endl;
        outFile << "Reason: " << result.getReason() << endl;
        outFile << "Time: " << result.getTimestamp() << endl;
    }
    
    outFile.close();
    cout << "Report saved to: " << filename << endl;
}

AnalysisResult& FinalResult::operator[](int index) {
    return results[index];
}

const AnalysisResult& FinalResult::operator[](int index) const {
    return results[index];
}

FinalResult& FinalResult::operator++() {
    confidence += 0.01;
    if (confidence > 1.0) confidence = 1.0;
    return *this;
}

FinalResult FinalResult::operator++(int) {
    FinalResult temp = *this;
    confidence += 0.01;
    if (confidence > 1.0) confidence = 1.0;
    return temp;
}

bool FinalResult::operator>(const FinalResult& other) const {
    return this->confidence > other.confidence;
}

ostream& operator<<(ostream& out, const FinalResult& result) {
    out << fixed << setprecision(2);
    out << "[AI Detection] Confidence: " << result.confidence;
    out << " | Verdict: " << (result.isAIGenerated ? "AI" : "REAL");
    out << " | Analyzers: " << result.results.size();
    return out;
}
