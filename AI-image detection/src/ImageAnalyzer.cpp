#include "ImageAnalyzer.h"
#include <iostream>
#include <iomanip>

int ImageAnalyzer::totalProcessed = 0;

ImageAnalyzer::ImageAnalyzer() : historyLog(50) {
    logActivity("ImageAnalyzer initialized");
}

ImageAnalyzer::~ImageAnalyzer() {
    clearAnalyzers();
    logActivity("ImageAnalyzer destroyed");
}

void ImageAnalyzer::addAnalyzer(Analyzer* analyzer) {
    if (analyzer != nullptr) {
        analyzers.push_back(analyzer);
        logActivity("Analyzer added to pipeline");
    }
}

FinalResult ImageAnalyzer::running(Image& img) {
    currentImage = img;
    totalProcessed++;
    
    logActivity("\n========== STARTING ANALYSIS ==========");
    logActivity("Image: " + img.getFilePath());
    logActivity("Dimensions: " + to_string(img.getWidth()) + "x" + to_string(img.getHeight()));
    logActivity("Number of analyzers: " + to_string(analyzers.size()));
    
    // Clear previous results
    currentResult = FinalResult();
    
    // Run each analyzer
    for (Analyzer* analyzer : analyzers) {
        logActivity("\nRunning: " + string(typeid(*analyzer).name()));
        
        AnalysisResult result = analyzer->analyze(img);
        currentResult.addAnalysisResult(result);
        
        historyLog.addEntry(result.getAnalyzerName() + ": " + result.getReason());
    }
    
    // Calculate final score
    currentResult.calcFinalScore();
    
    logActivity("\nAnalysis complete!");
    logActivity("Final Score: " + to_string(currentResult.getConfidence()));
    logActivity("Verdict: " + string(currentResult.getIsAIGenerated() ? "AI GENERATED" : "AUTHENTIC"));
    logActivity("========== ANALYSIS COMPLETE ==========\n");
    
    return currentResult;
}

void ImageAnalyzer::clearAnalyzers() {
    for (Analyzer* analyzer : analyzers) {
        delete analyzer;
    }
    analyzers.clear();
    logActivity("All analyzers cleared");
}

void ImageAnalyzer::getProcessStats() const {
    cout << "\n=== PROCESS STATISTICS ===" << endl;
    cout << "Total Images Processed: " << totalProcessed << endl;
    cout << "Active Analyzers: " << analyzers.size() << endl;
    cout << "Current Analysis Results: " << currentResult.getResultCount() << endl;
    cout << "History Log Entries: " << historyLog.getCount() << endl;
    cout << "=========================" << endl;
}

void ImageAnalyzer::logActivity(string msg) {
    cout << msg << endl;
    historyLog.addEntry(msg);
}

void ImageAnalyzer::saveReport(string filename) {
    currentResult.saveToFile(filename);
}

void ImageAnalyzer::displayAllAnalyzers() const {
    cout << "\n=== ACTIVE ANALYZERS ===" << endl;
    cout << "Total: " << analyzers.size() << endl;
    cout << "========================" << endl;
    
    for (int i = 0; i < analyzers.size(); i++) {
        cout << "[" << i+1 << "] ";
        analyzers[i]->displayAnalyzerInfo();
    }
}
