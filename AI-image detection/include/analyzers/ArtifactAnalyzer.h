
#ifndef ARTIFACTANALYZER_H
#define ARTIFACTANALYZER_H

#include "core/Analyzer.h"

class ArtifactAnalyzer : public Analyzer {
private:
    bool detectFixedJaggies();      // Detect jagged edges from compression
    double scanAlgorithm();         // Scan for AI generation artifacts
    double getArtifactDensity();    // Calculate artifact density

public:
    ArtifactAnalyzer();
    ~ArtifactAnalyzer() override;
    
    // Analyze artifacts in image
    AnalysisResult analyze(Image& img) override;
    
    // Display analyzer info
    void displayAnalyzerInfo() const override;
};

#endif
