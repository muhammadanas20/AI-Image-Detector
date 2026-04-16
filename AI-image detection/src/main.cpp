#include "ImageAnalyzer.h"
#include "MetadataAnalyzer.h"
#include "ArtifactAnalyzer.h"
#include "FrequencyAnalyzer.h"
#include "WatermarkAnalyzer.h"
#include "HybridDeepAnalyzer.h"
#include <iostream>
#include <iomanip>
using namespace std;

void printHeader(string title) {
    cout << "\n" << string(70, '=') << endl;
    cout << "  " << title << endl;
    cout << string(70, '=') << endl;
}

void printSection(string title) {
    cout << "\n" << string(50, '-') << endl;
    cout << "  " << title << endl;
    cout << string(50, '-') << endl;
}

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

    // ==================== SYSTEM SUMMARY ====================
    printSection("HOW THE SYSTEM WORKS");
    
    cout << "\n1. IMAGE LOADING PHASE:" << endl;
    cout << "   • Image file is loaded and analyzed" << endl;
    cout << "   • Dimensions, format, and size are extracted" << endl;
    cout << "   • Raw pixel data is simulated for analysis" << endl;
    
    cout << "\n2. MULTI-ANALYZER PIPELINE:" << endl;
    cout << "   • MetadataAnalyzer: Checks EXIF data, source verification" << endl;
    cout << "   • ArtifactAnalyzer: Detects compression artifacts and noise" << endl;
    cout << "   • FrequencyAnalyzer: Performs FFT to analyze frequency patterns" << endl;
    cout << "   • WatermarkAnalyzer: Searches for watermark signatures" << endl;
    cout << "   • HybridDeepAnalyzer: Combines all methods + neural simulation" << endl;
    
    cout << "\n3. SCORING SYSTEM:" << endl;
    cout << "   • Each analyzer produces a score (0.0 = Real, 1.0 = AI)" << endl;
    cout << "   • Scores based on different detection methods:" << endl;
    cout << "     - Missing/invalid EXIF (+0.4)" << endl;
    cout << "     - Unverified source (+0.3)" << endl;
    cout << "     - Jagged edges and artifacts (+0.2-0.4)" << endl;
    cout << "     - Unnatural frequency patterns (+0.3)" << endl;
    
    cout << "\n4. FINAL VERDICT:" << endl;
    cout << "   • Confidence = Average of all analyzer scores" << endl;
    cout << "   • If confidence > 0.5 → AI GENERATED" << endl;
    cout << "   • If confidence ≤ 0.5 → AUTHENTIC (likely real)" << endl;
    
    cout << "\n5. LOGGING & REPORTING:" << endl;
    cout << "   • All activities logged in HistoryLog" << endl;
    cout << "   • Detailed reports saved to files" << endl;
    cout << "   • Comparative analysis across multiple images" << endl;

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
