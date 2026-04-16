#ifndef WATERMARKANALYZER_H
#define WATERMARKANALYZER_H

#include "Analyzer.h"

class WatermarkAnalyzer : public Analyzer {
private:
    bool hasWatermark;
    string watermarkType;

public:
    WatermarkAnalyzer();
    ~WatermarkAnalyzer() override;
    
    // Analyze watermarks
    AnalysisResult analyze(Image& img) override;
    
    // Getters
    bool getHasWatermark() const { return hasWatermark; }
    string getWatermarkType() const { return watermarkType; }
    
    // Display analyzer info
    void displayAnalyzerInfo() const override;
};

#endif
