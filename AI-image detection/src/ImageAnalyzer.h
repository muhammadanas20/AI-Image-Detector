#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include "Analyzer.h"
#include "FinalResult.h"
#include "HistoryLog.h"
#include "Image.h"
#include <vector>
#include <memory>

class ImageAnalyzer : public ILoggable {
private:
    vector<Analyzer*> analyzers;            // Collection of all analyzers
    static int totalProcessed;              // Total images processed
    FinalResult currentResult;              // Current analysis result
    HistoryLog historyLog;                  // Log all activities
    Image currentImage;                     // Current image being analyzed
    
public:
    ImageAnalyzer();
    ~ImageAnalyzer();
    
    // Add analyzer to the pipeline
    void addAnalyzer(Analyzer* analyzer);
    
    // Run analysis on image
    FinalResult running(Image& img);
    
    // Clear all analyzers
    void clearAnalyzers();
    
    // Get process statistics
    void getProcessStats() const;
    
    // Get final result
    FinalResult getCurrentResult() const { return currentResult; }
    
    // Get total processed count
    static int getTotalProcessed() { return totalProcessed; }
    
    // ILoggable implementation
    void logActivity(string msg) override;
    
    // Save report
    void saveReport(string filename);
    
    // Display all analyzers
    void displayAllAnalyzers() const;
};

#endif
