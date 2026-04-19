#include "analyzers/ArtifactAnalyzer.h"
#include <cstdlib>
#include <cmath>

ArtifactAnalyzer::ArtifactAnalyzer() {
    logActivity("ArtifactAnalyzer initialized");
}

ArtifactAnalyzer::~ArtifactAnalyzer() {
    logActivity("ArtifactAnalyzer destroyed");
}

AnalysisResult ArtifactAnalyzer::analyze(Image& img) {
    logActivity("Scanning for artifacts...");
    
    double jaggieScore = detectFixedJaggies() ? 0.3 : 0.0;
    double algorithmScore = scanAlgorithm();
    double densityScore = getArtifactDensity();
    
    double score = (jaggieScore + algorithmScore + densityScore) / 3.0;
    
    string reason = "";
    if (jaggieScore > 0.2) reason += "Fixed jaggies detected | ";
    if (algorithmScore > 0.4) reason += "AI artifacts found | ";
    if (densityScore > 0.5) reason += "High artifact density | ";
    
    if (reason.empty()) reason = "No significant artifacts detected";
    
    logActivity("Artifact analysis complete. Score: " + to_string(score));
    
    AnalysisResult result(score, reason, "ArtifactAnalyzer");
    return result;
}

bool ArtifactAnalyzer::detectFixedJaggies() {
    // Simulate jagged edge detection
    logActivity("Checking for fixed jaggies...");
    return (rand() % 100) > 60; // 40% chance of detection
}

double ArtifactAnalyzer::scanAlgorithm() {
    // Simulate AI artifact scanning algorithm
    logActivity("Running scan algorithm...");
    double result = (rand() % 100) / 100.0 * 0.8; // Max 0.8
    return result;
}

double ArtifactAnalyzer::getArtifactDensity() {
    // Simulate calculating artifact density
    logActivity("Calculating artifact density...");
    double density = (rand() % 100) / 100.0;
    return density;
}

void ArtifactAnalyzer::displayAnalyzerInfo() const {
    cout << "\n=== ARTIFACT ANALYZER ===" << endl;
    Analyzer::displayAnalyzerInfo();
    cout << "Purpose: Detect compression and generation artifacts" << endl;
    cout << "Methods: Edge detection, noise scanning, density calculation" << endl;
    cout << "=========================" << endl;
}
