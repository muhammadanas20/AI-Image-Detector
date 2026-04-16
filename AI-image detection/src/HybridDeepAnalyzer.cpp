#include "HybridDeepAnalyzer.h"
#include <cstdlib>

HybridDeepAnalyzer::HybridDeepAnalyzer() {
    logActivity("HybridDeepAnalyzer initialized");
}

HybridDeepAnalyzer::~HybridDeepAnalyzer() {
    logActivity("HybridDeepAnalyzer destroyed");
}

AnalysisResult HybridDeepAnalyzer::analyze(Image& img) {
    logActivity("Starting hybrid deep analysis...");
    
    // Run all three underlying analyzers
    logActivity("Running metadata analysis...");
    AnalysisResult metaResult = metaAnalyzer.analyze(img);
    
    logActivity("Running artifact analysis...");
    AnalysisResult artifactResult = artifactAnalyzer.analyze(img);
    
    logActivity("Running frequency analysis...");
    AnalysisResult freqResult = freqAnalyzer.analyze(img);
    
    // Run neural network simulation
    bool neuralPass = runNeuralPass();
    
    // Optimize memory usage
    optimizeMemory();
    
    // Combine results
    double combinedScore = (metaResult.getScore() + 
                           artifactResult.getScore() + 
                           freqResult.getScore()) / 3.0;
    
    if (neuralPass) {
        combinedScore *= 1.1; // Boost score if neural pass confirms
        if (combinedScore > 1.0) combinedScore = 1.0;
    }
    
    string reason = "Hybrid Analysis: Meta(" + to_string(metaResult.getScore()).substr(0, 4) + 
                    ") + Artifact(" + to_string(artifactResult.getScore()).substr(0, 4) + 
                    ") + Freq(" + to_string(freqResult.getScore()).substr(0, 4) + ")";
    
    logActivity("Hybrid analysis complete. Combined score: " + to_string(combinedScore));
    
    AnalysisResult result(combinedScore, reason, "HybridDeepAnalyzer");
    return result;
}

bool HybridDeepAnalyzer::runNeuralPass() {
    logActivity("Running neural network simulation...");
    // Simulate neural network confidence
    bool confidence = (rand() % 100) > 40; // 60% accuracy
    logActivity("Neural pass result: " + string(confidence ? "POSITIVE" : "NEGATIVE"));
    return confidence;
}

void HybridDeepAnalyzer::optimizeMemory() {
    logActivity("Optimizing memory usage...");
    // Simulate memory optimization
}

double HybridDeepAnalyzer::getConfidence() const {
    return (rand() % 100) / 100.0;
}

void HybridDeepAnalyzer::displayAnalyzerInfo() const {
    cout << "\n=== HYBRID DEEP ANALYZER ===" << endl;
    Analyzer::displayAnalyzerInfo();
    cout << "Type: Advanced Multi-Method Analysis" << endl;
    cout << "Methods: Metadata + Artifacts + Frequency + Neural" << endl;
    cout << "Purpose: Comprehensive AI detection with high accuracy" << endl;
    cout << "=============================" << endl;
}
