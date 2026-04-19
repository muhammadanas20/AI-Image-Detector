#ifndef ANALYSISRESULT_H
#define ANALYSISRESULT_H

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class AnalysisResult {
private:
    double score;           // 0.0 to 1.0 confidence score
    string reason;          // Explanation of the result
    string timestamp;       // When was it analyzed
    string analyzerName;    // Which analyzer produced this

public:
    AnalysisResult(double s = 0.0, string r = "", string name = "");
    ~AnalysisResult();
    
    // Setters
    void setScores(double s, string r);
    void setAnalyzerName(string name);
    
    // Getters
    double getScore() const { return score; }
    string getReason() const { return reason; }
    string getTimestamp() const { return timestamp; }
    string getAnalyzerName() const { return analyzerName; }
    
    // Display result
    void displayResult() const;
    
    // Operator overloading for comparison
    bool operator<(const AnalysisResult& other) const;
    bool operator==(const AnalysisResult& other) const;
    
    // Stream operators
    friend ostream& operator<<(ostream& out, const AnalysisResult& result);
    friend istream& operator>>(istream& in, AnalysisResult& result);
};

#endif
