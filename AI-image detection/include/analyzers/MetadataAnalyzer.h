#ifndef METADATAANALYZER_H
#define METADATAANALYZER_H

#include "core/Analyzer.h"
#include <string>
using namespace std;

class MetadataAnalyzer : public Analyzer {
private:
    string exifData;           // EXIF metadata from image
    bool isSourceVerified;     // Is source metadata legitimate?

public:
    MetadataAnalyzer();
    ~MetadataAnalyzer() override;
    
    // Analyze image metadata
    AnalysisResult analyze(Image& img) override;
    
    // Check EXIF data
    bool checkExifData(Image& img);
    
    // Verify source authenticity
    bool verifySource();
    
    // Getters
    string getExifData() const { return exifData; }
    bool isSourceValid() const { return isSourceVerified; }
    
    // Display metadata info
    void displayAnalyzerInfo() const override;
};

#endif
