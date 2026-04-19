#include "results/FinalResult.h"
#include "utilities/CustomExceptions.h"
#include "utilities/Utils.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

FinalResult::FinalResult() : confidence(0.0), isAIGenerated(false) {
}

FinalResult::~FinalResult() {
    results.clear();
}

void FinalResult::addAnalysisResult(const AnalysisResult& result) {
    try {
        results.push_back(result);
    }
    catch (const exception& e) {
        throw AnalysisException("Failed to add analysis result: " + string(e.what()));
    }
}

void FinalResult::calcFinalScore() {
    try {
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
        
        // Validate confidence score
        if (!isValidScore(confidence)) {
            throw InvalidScoreException(confidence);
        }
        
        // Determine if AI generated based on threshold
        isAIGenerated = (confidence > 0.5);
    }
    catch (const AIDetectorException& e) {
        cerr << "ERROR calculating final score: " << e.what() << endl;
        throw;
    }
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
    try {
        ofstream outFile(filename);
        
        if (!outFile.is_open()) {
            throw FileException("Could not open file for writing: " + filename);
        }
        
        outFile << "=== AI IMAGE DETECTION REPORT ===" << endl;
        outFile << "Generated at: " << __DATE__ << " " << __TIME__ << endl;
        outFile << "\nFinal Verdict: " << (isAIGenerated ? "AI GENERATED" : "AUTHENTIC") << endl;
        outFile << "Confidence: " << fixed << setprecision(2) << confidence << endl;
        outFile << "\n--- Analyzer Results ---" << endl;
        
        for (const auto& result : results) {
            outFile << "\nAnalyzer: " << result.getAnalyzerName() << endl;
            outFile << "Score: " << fixed << setprecision(2) << result.getScore() << endl;
            outFile << "Reason: " << result.getReason() << endl;
            outFile << "Time: " << result.getTimestamp() << endl;
        }
        
        outFile.close();
        cout << "Report saved to: " << filename << endl;
    }
    catch (const AIDetectorException& e) {
        cerr << "ERROR saving report: " << e.what() << endl;
        throw;
    }
    catch (const exception& e) {
        throw FileException("Unexpected error while saving file: " + string(e.what()));
    }
}

AnalysisResult& FinalResult::operator[](int index) {
    try {
        if (index < 0 || index >= static_cast<int>(results.size())) {
            throw InputValidationException("Analysis result index out of bounds: " + to_string(index));
        }
        return results[index];
    }
    catch (const AIDetectorException& e) {
        cerr << "ERROR accessing result: " << e.what() << endl;
        throw;
    }
}

const AnalysisResult& FinalResult::operator[](int index) const {
    try {
        if (index < 0 || index >= static_cast<int>(results.size())) {
            throw InputValidationException("Analysis result index out of bounds: " + to_string(index));
        }
        return results[index];
    }
    catch (const AIDetectorException& e) {
        cerr << "ERROR accessing result: " << e.what() << endl;
        throw;
    }
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
