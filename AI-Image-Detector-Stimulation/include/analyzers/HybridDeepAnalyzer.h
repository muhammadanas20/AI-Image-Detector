#ifndef HYBRIDDEEPANALYZER_H
#define HYBRIDDEEPANALYZER_H

#include "core/Analyzer.h"
#include "analyzers/MetadataAnalyzer.h"
#include "analyzers/ArtifactAnalyzer.h"
#include "analyzers/FrequencyAnalyzer.h"

class HybridDeepAnalyzer : public Analyzer {
private:
    MetadataAnalyzer metaAnalyzer;
    ArtifactAnalyzer artifactAnalyzer;
    FrequencyAnalyzer freqAnalyzer;
    
    bool runNeuralPass();
    void optimizeMemory();
    double getConfidence() const;

public:
    HybridDeepAnalyzer();
    ~HybridDeepAnalyzer() override;
    
    // Combined analysis using multiple techniques
    AnalysisResult analyze(Image& img) override;
    
    // Display analyzer info
    void displayAnalyzerInfo() const override;
};

#endif
