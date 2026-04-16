#include "MetadataAnalyzer.h"
#include <cstdlib>
#include <cmath>

MetadataAnalyzer::MetadataAnalyzer() : isSourceVerified(false) {
    logActivity("MetadataAnalyzer initialized");
}

MetadataAnalyzer::~MetadataAnalyzer() {
    logActivity("MetadataAnalyzer destroyed");
}

AnalysisResult MetadataAnalyzer::analyze(Image& img) {
    logActivity("Analyzing image metadata...");
    
    bool hasExif = checkExifData(img);
    bool sourceValid = verifySource();
    
    double score = 0.0;
    string reason = "";
    
    if (!hasExif) {
        score += 0.4; // Missing EXIF = suspicious
        reason = "No valid EXIF data found | ";
    }
    
    if (!sourceValid) {
        score += 0.3; // Unverified source
        reason += "Source could not be verified | ";
    } else {
        reason += "Source verified authentic | ";
    }
    
    // Simulate checking camera model authenticity
    double cameraScore = (rand() % 100) / 100.0;
    if (cameraScore > 0.7) {
        score += 0.2; // Suspicious camera model
        reason += "Unusual camera metadata";
    }
    
    // Normalize score to 0-1 range
    score = min(score, 1.0);
    
    logActivity("Metadata analysis complete. Score: " + to_string(score));
    
    AnalysisResult result(score, reason, "MetadataAnalyzer");
    return result;
}

bool MetadataAnalyzer::checkExifData(Image& img) {
    // Simulate EXIF extraction
    if (img.getFileSize() > 100) {
        exifData = "Camera: Canon EOS 5D | Date: 2024-01-15 | GPS: Present";
        logActivity("EXIF data found: " + exifData);
        return true;
    }
    exifData = "No EXIF data";
    return false;
}

bool MetadataAnalyzer::verifySource() {
    // Simulate source verification
    isSourceVerified = (rand() % 100) > 40; // 60% chance of verification
    logActivity("Source verification: " + string(isSourceVerified ? "VERIFIED" : "FAILED"));
    return isSourceVerified;
}

void MetadataAnalyzer::displayAnalyzerInfo() const {
    cout << "\n=== METADATA ANALYZER ===" << endl;
    Analyzer::displayAnalyzerInfo();
    cout << "EXIF Data: " << exifData << endl;
    cout << "Source Verified: " << (isSourceVerified ? "Yes" : "No") << endl;
    cout << "=========================" << endl;
}
