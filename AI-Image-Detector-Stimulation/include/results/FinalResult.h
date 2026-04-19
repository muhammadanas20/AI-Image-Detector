#ifndef FINALRESULT_H
#define FINALRESULT_H

#include "results/AnalysisResult.h"
#include <vector>
#include <iostream>
using namespace std;

class FinalResult {
private:
    double confidence;                          // Final confidence score 0-1
    bool isAIGenerated;                         // Final verdict
    vector<AnalysisResult> results;             // All individual analyzer results
    
public:
    FinalResult();
    ~FinalResult();
    
    // Add analysis result
    void addAnalysisResult(const AnalysisResult& result);
    
    // Calculate final score from all results
    void calcFinalScore();
    
    // Setters
    void setConfidence(double conf) { confidence = conf; }
    void setIsAIGenerated(bool val) { isAIGenerated = val; }
    
    // Getters
    double getConfidence() const { return confidence; }
    bool getIsAIGenerated() const { return isAIGenerated; }
    vector<AnalysisResult> getResults() const { return results; }
    int getResultCount() const { return results.size(); }
    
    // Display full report
    void displayFullReport() const;
    
    // Save results to file
    void saveToFile(string filename);
    
    // Operator overloading
    AnalysisResult& operator[](int index);
    const AnalysisResult& operator[](int index) const;
    
    // Increment confidence by small amount
    FinalResult& operator++();
    FinalResult operator++(int);
    
    // Compare with another result
    bool operator>(const FinalResult& other) const;
    
    // Stream operators
    friend ostream& operator<<(ostream& out, const FinalResult& result);
};

#endif
