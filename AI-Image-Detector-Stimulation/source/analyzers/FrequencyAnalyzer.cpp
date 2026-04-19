#include "analyzers/FrequencyAnalyzer.h"
#include <cstdlib>
#include <cmath>

FrequencyAnalyzer::FrequencyAnalyzer() {
    logActivity("FrequencyAnalyzer initialized");
}

FrequencyAnalyzer::~FrequencyAnalyzer() {
    logActivity("FrequencyAnalyzer destroyed");
    frequencyMap.clear();
}

AnalysisResult FrequencyAnalyzer::analyze(Image& img) {
    logActivity("Analyzing frequency patterns...");
    
    performFFTTransform();
    bool noisyBands = checkNoiseBands();
    double variance = calculateVariance();
    
    double score = 0.0;
    string reason = "";
    
    if (noisyBands) {
        score += 0.4;
        reason = "Suspicious noise bands detected | ";
    }
    
    // Analyze variance (AI images often have lower natural variance)
    if (variance < 0.3) {
        score += 0.3;
        reason += "Low frequency variance (typical of AI) | ";
    } else if (variance > 0.7) {
        reason += "High natural frequency distribution | ";
    }
    
    // Normalize score
    score = min(score, 1.0);
    
    logActivity("Frequency analysis complete. Score: " + to_string(score));
    
    AnalysisResult result(score, reason, "FrequencyAnalyzer");
    return result;
}

void FrequencyAnalyzer::performFFTTransform() {
    logActivity("Performing FFT transform...");
    
    // Simulate FFT by generating frequency components
    frequencyMap.clear();
    for (int i = 0; i < 16; i++) {
        frequencyMap.push_back((rand() % 100) / 100.0);
    }
    
    logActivity("FFT transform completed");
}

bool FrequencyAnalyzer::checkNoiseBands() {
    logActivity("Checking noise bands...");
    
    // Simulate noise band detection
    double avgNoise = 0.0;
    for (double freq : frequencyMap) {
        avgNoise += freq;
    }
    avgNoise /= frequencyMap.size();
    
    // If average noise is above threshold, consider it suspicious
    bool suspicious = avgNoise > 0.6;
    logActivity("Noise detection: " + string(suspicious ? "SUSPICIOUS" : "NORMAL"));
    return suspicious;
}

double FrequencyAnalyzer::calculateVariance() {
    logActivity("Calculating variance...");
    
    if (frequencyMap.empty()) return 0.0;
    
    // Calculate mean
    double mean = 0.0;
    for (double freq : frequencyMap) {
        mean += freq;
    }
    mean /= frequencyMap.size();
    
    // Calculate variance
    double variance = 0.0;
    for (double freq : frequencyMap) {
        variance += (freq - mean) * (freq - mean);
    }
    variance /= frequencyMap.size();
    
    logActivity("Variance calculated: " + to_string(variance));
    return variance;
}

void FrequencyAnalyzer::displayAnalyzerInfo() const {
    cout << "\n=== FREQUENCY ANALYZER ===" << endl;
    Analyzer::displayAnalyzerInfo();
    cout << "Method: Fast Fourier Transform (FFT)" << endl;
    cout << "Frequency components analyzed: " << frequencyMap.size() << endl;
    cout << "Purpose: Detect unnatural frequency patterns" << endl;
    cout << "=========================" << endl;
}
