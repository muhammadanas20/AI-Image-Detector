#include "WatermarkAnalyzer.h"
#include <cstdlib>

WatermarkAnalyzer::WatermarkAnalyzer() : hasWatermark(false), watermarkType("None") {
    logActivity("WatermarkAnalyzer initialized");
}

WatermarkAnalyzer::~WatermarkAnalyzer() {
    logActivity("WatermarkAnalyzer destroyed");
}

AnalysisResult WatermarkAnalyzer::analyze(Image& img) {
    logActivity("Analyzing watermarks...");
    
    // Simulate watermark detection
    hasWatermark = (rand() % 100) > 50;
    
    double score = 0.0;
    string reason = "";
    
    if (hasWatermark) {
        int type = rand() % 3;
        switch(type) {
            case 0:
                watermarkType = "Copyright";
                score = 0.1; // Less suspicious
                reason = "Copyright watermark found - likely authentic";
                break;
            case 1:
                watermarkType = "Visible";
                score = 0.2;
                reason = "Visible watermark present";
                break;
            case 2:
                watermarkType = "Invisible";
                score = 0.15;
                reason = "Invisible watermark detected";
                break;
        }
    } else {
        reason = "No watermark found";
    }
    
    logActivity("Watermark analysis complete. Score: " + to_string(score));
    
    AnalysisResult result(score, reason, "WatermarkAnalyzer");
    return result;
}

void WatermarkAnalyzer::displayAnalyzerInfo() const {
    cout << "\n=== WATERMARK ANALYZER ===" << endl;
    Analyzer::displayAnalyzerInfo();
    cout << "Watermark Detected: " << (hasWatermark ? "Yes - " + watermarkType : "No") << endl;
    cout << "=========================" << endl;
}
