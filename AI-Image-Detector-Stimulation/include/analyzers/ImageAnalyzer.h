#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include "core/Analyzer.h"
#include "results/FinalResult.h"
#include "results/HistoryLog.h"
#include "core/Image.h"
#include <vector>
#include <memory>

// Structure to store image data with metadata
struct ImageData {
    string imageID;
    Image image;
    FinalResult analysisResult;
    bool isAnalyzed;
    string timestamp;
};

class ImageAnalyzer : public ILoggable {
private:
    vector<Analyzer*> analyzers;            // Collection of all analyzers
    vector<ImageData> imageDatabase;        // Store all images and their analysis
    static int totalProcessed;              // Total images processed
    FinalResult currentResult;              // Current analysis result
    HistoryLog historyLog;                  // Log all activities
    Image currentImage;                     // Current image being analyzed
    static int imageCounter;                // Counter for image IDs
    
    // Private helper methods
    string generateImageID();
    ImageData* findImageByID(const string& id);
    int findImageIndexByID(const string& id);
    
public:
    ImageAnalyzer();
    ~ImageAnalyzer();
    
    // Add analyzer to the pipeline
    void addAnalyzer(Analyzer* analyzer);
    
    // Run analysis on image
    FinalResult running(Image& img);
    
    // Clear all analyzers
    void clearAnalyzers();
    
    // ==================== DATA MANAGEMENT ====================
    
    // Add new image to database
    string addImage(const string& filePath);
    
    // Update existing image analysis
    bool updateImage(const string& imageID, const Image& newImage);
    
    // Save analysis result to database
    bool saveAnalysisResult(const string& imageID, const FinalResult& result);
    
    // Delete image from database
    bool deleteImage(const string& imageID);
    
    // Get all images from database
    vector<ImageData> getAllImages() const;
    
    // Get specific image
    ImageData getImage(const string& imageID) const;
    
    // Get total images in database
    int getImageCount() const { return imageDatabase.size(); }
    
    // ==================== SEARCH & FILTER ====================
    
    // Search images by filename
    vector<ImageData> searchByFilename(const string& filename) const;
    
    // Filter by analysis verdict (AI or Authentic)
    vector<ImageData> filterByVerdict(bool isAI) const;
    
    // Filter by confidence score range
    vector<ImageData> filterByConfidenceRange(double minScore, double maxScore) const;
    
    // Get analyzed vs unanalyzed images
    vector<ImageData> getAnalyzedImages() const;
    vector<ImageData> getUnanalyzedImages() const;
    
    // ==================== STATISTICS & REPORTS ====================
    
    // Get process statistics
    void getProcessStats() const;
    
    // Get database statistics
    void getDatabaseStats() const;
    
    // Get final result
    FinalResult getCurrentResult() const { return currentResult; }
    
    // Get total processed count
    static int getTotalProcessed() { return totalProcessed; }
    
    // ILoggable implementation
    void logActivity(string msg) override;
    
    // Save report
    void saveReport(string filename);
    
    // Save all results to file
    void saveAllResultsToFile(const string& filename);
    
    // Display all analyzers
    void displayAllAnalyzers() const;
    
    // Display database contents
    void displayDatabaseContents() const;
};

#endif
