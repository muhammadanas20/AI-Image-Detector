#ifndef FREQUENCYANALYZER_H
#define FREQUENCYANALYZER_H

#include "core/Analyzer.h"
#include <vector>
using namespace std;

class FrequencyAnalyzer : public Analyzer {
private:
    vector<double> frequencyMap;    // FFT frequency components
    
    void performFFTTransform();     // Perform FFT on image
    bool checkNoiseBands();         // Check for noise patterns
    double calculateVariance();     // Calculate frequency variance

public:
    FrequencyAnalyzer();
    ~FrequencyAnalyzer() override;
    
    // Analyze frequency patterns
    AnalysisResult analyze(Image& img) override;
    
    // Get frequency map
    vector<double> getFrequencyMap() const { return frequencyMap; }
    
    // Display analyzer info
    void displayAnalyzerInfo() const override;
};

#endif
