#include "analyzers/ImageAnalyzer.h"
#include "analyzers/MetadataAnalyzer.h"
#include "analyzers/ArtifactAnalyzer.h"
#include "analyzers/FrequencyAnalyzer.h"
#include "analyzers/WatermarkAnalyzer.h"
#include "analyzers/HybridDeepAnalyzer.h"
#include "utilities/Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    printHeader("AI IMAGE DETECTION SYSTEM");
    cout << "Advanced multi-analyzer approach for image authenticity detection\n" << endl;

    // ==================== SYSTEM INITIALIZATION ====================
    printSection("SYSTEM INITIALIZATION");
    
    // Create main analyzer controller
    ImageAnalyzer imageAnalyzer;
    cout << "✓ ImageAnalyzer controller created" << endl;
    
    // Add individual analyzers
    imageAnalyzer.addAnalyzer(new MetadataAnalyzer());
    cout << "✓ MetadataAnalyzer added to pipeline" << endl;
    
    imageAnalyzer.addAnalyzer(new ArtifactAnalyzer());
    cout << "✓ ArtifactAnalyzer added to pipeline" << endl;
    
    imageAnalyzer.addAnalyzer(new FrequencyAnalyzer());
    cout << "✓ FrequencyAnalyzer added to pipeline" << endl;
    
    imageAnalyzer.addAnalyzer(new WatermarkAnalyzer());
    cout << "✓ WatermarkAnalyzer added to pipeline" << endl;
    
    imageAnalyzer.addAnalyzer(new HybridDeepAnalyzer());
    cout << "✓ HybridDeepAnalyzer added to pipeline" << endl;
    
    cout << "\nTotal analyzers in pipeline: " << Analyzer::getCount() << endl;

    // ==================== IMAGE PROCESSING WORKFLOW ====================
    printSection("IMAGE PROCESSING WORKFLOW");
    
    // Create test images
    vector<string> testImages = {
        "assets/sample_images/photo1.jpg",
        "assets/sample_images/generated_image.png",
        "assets/sample_images/authentic_photo.tiff"
    };
    
    vector<FinalResult> allResults;
    
    for (int i = 0; i < testImages.size(); i++) {
        cout << "\n[" << i+1 << "/" << testImages.size() << "] Processing: " << testImages[i] << endl;
        
        // Create and load image
        Image testImage;
        bool loaded = testImage.loadImage(testImages[i]);
        
        if (loaded) {
            testImage.displayImageInfo();
            
            // Run analysis
            cout << "\nStarting analysis pipeline..." << endl;
            FinalResult result = imageAnalyzer.running(testImage);
            
            // Display results
            result.displayFullReport();
            
            // Store result
            allResults.push_back(result);
            
            // Save individual report
            string reportName = "report_" + to_string(i+1) + ".txt";
            imageAnalyzer.saveReport(reportName);
        } else {
            cout << "✗ Failed to load image" << endl;
        }
        
        if (i < testImages.size() - 1) {
            cout << "\n" << string(70, '~') << endl;
        }
    }

    // ==================== COMPARATIVE ANALYSIS ====================
    printSection("COMPARATIVE ANALYSIS");
    
    if (allResults.size() > 1) {
        cout << left << setw(35) << "Image" 
             << setw(15) << "Confidence" 
             << setw(20) << "Verdict" << endl;
        cout << string(70, '-') << endl;
        
        for (int i = 0; i < allResults.size(); i++) {
            cout << left << setw(35) << testImages[i]
                 << setw(15) << fixed << setprecision(2) << allResults[i].getConfidence()
                 << setw(20) << (allResults[i].getIsAIGenerated() ? "AI GENERATED" : "AUTHENTIC")
                 << endl;
        }
    }

    // ==================== SYSTEM STATISTICS ====================
    printSection("SYSTEM STATISTICS");
    imageAnalyzer.getProcessStats();
    
    imageAnalyzer.displayAllAnalyzers();


    // ==================== DEMONSTRATION COMPLETE ====================
    printHeader("ANALYSIS COMPLETE");
    cout << "Total images processed: " << ImageAnalyzer::getTotalProcessed() << endl;
    cout << "Reports saved: " << testImages.size() << endl;
    cout << "Average confidence: " << fixed << setprecision(2);
    
    double avgConfidence = 0.0;
    for (const auto& result : allResults) {
        avgConfidence += result.getConfidence();
    }
    avgConfidence /= allResults.size();
    cout << avgConfidence << endl;
    
    cout << "\n✓ System shutdown complete." << endl;
    cout << string(70, '=') << endl << endl;

    return 0;
}
