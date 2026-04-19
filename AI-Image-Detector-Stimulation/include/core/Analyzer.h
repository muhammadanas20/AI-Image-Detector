#ifndef ANALYZER_H
#define ANALYZER_H

#include "core/Image.h"
#include "results/AnalysisResult.h"
#include "core/ILoggable.h"
#include <iostream>
#include <string>
using namespace std;

// Abstract base class for all analyzers
class Analyzer : public ILoggable {
protected:
    int analyzerID;                    // Unique ID for this analyzer
    static int analyzerCount;          // Total analyzers created
    
public:
    Analyzer();
    virtual ~Analyzer();
    
    // Pure virtual function 
    virtual AnalysisResult analyze(Image& img) = 0;
    
    // Getters
    int getID() const { return analyzerID; }
    static int getCount() { return analyzerCount; }
    
    // ILoggable implementation
    void logActivity(string msg) override;
    
    // Display analyzer info
    virtual void displayAnalyzerInfo() const;
};

#endif
