#include "analyzers/ImageAnalyzer.h"
#include "utilities/Utils.h"
#include "utilities/CustomExceptions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>

int ImageAnalyzer::totalProcessed = 0;
int ImageAnalyzer::imageCounter = 0;

ImageAnalyzer::ImageAnalyzer() : historyLog(50) {
    logActivity("ImageAnalyzer initialized");
}

ImageAnalyzer::~ImageAnalyzer() {
    clearAnalyzers();
    logActivity("ImageAnalyzer destroyed - " + to_string(imageDatabase.size()) + " images in database");
}

// ==================== ANALYZER MANAGEMENT ====================

void ImageAnalyzer::addAnalyzer(Analyzer* analyzer) {
    if (analyzer != nullptr) {
        analyzers.push_back(analyzer);
        logActivity("Analyzer added to pipeline");
    }
}

FinalResult ImageAnalyzer::running(Image& img) {
    try {
        if (analyzers.empty()) {
            throw NoAnalyzersException();
        }
        
        currentImage = img;
        totalProcessed++;
        
        logActivity("\n========== STARTING ANALYSIS ==========");
        logActivity("Image: " + img.getFilePath());
        logActivity("Dimensions: " + to_string(img.getWidth()) + "x" + to_string(img.getHeight()));
        logActivity("Number of analyzers: " + to_string(analyzers.size()));
        
        // Clear previous results
        currentResult = FinalResult();
        
        // Run each analyzer
        int analyzerNum = 0;
        for (Analyzer* analyzer : analyzers) {
            analyzerNum++;
            logActivity("\n[Analyzer " + to_string(analyzerNum) + "/" + to_string(analyzers.size()) + "]");
            
            AnalysisResult result = analyzer->analyze(img);
            currentResult.addAnalysisResult(result);
            
            historyLog.addEntry(result.getAnalyzerName() + ": " + result.getReason());
        }
        
        // Calculate final score
        currentResult.calcFinalScore();
        
        logActivity("\nAnalysis complete!");
        logActivity("Final Score: " + to_string(currentResult.getConfidence()));
        logActivity("Verdict: " + string(currentResult.getIsAIGenerated() ? "AI GENERATED" : "AUTHENTIC"));
        logActivity("========== ANALYSIS COMPLETE ==========\n");
        
        return currentResult;
    }
    catch (const AIDetectorException& e) {
        cout << "ERROR: " << e.what() << endl;
        throw;
    }
}

void ImageAnalyzer::clearAnalyzers() {
    for (Analyzer* analyzer : analyzers) {
        delete analyzer;
    }
    analyzers.clear();
    logActivity("All analyzers cleared");
}

// ==================== PRIVATE HELPER METHODS ====================

string ImageAnalyzer::generateImageID() {
    return "IMG_" + to_string(++imageCounter);
}

ImageData* ImageAnalyzer::findImageByID(const string& id) {
    for (auto& imageData : imageDatabase) {
        if (imageData.imageID == id) {
            return &imageData;
        }
    }
    return nullptr;
}

int ImageAnalyzer::findImageIndexByID(const string& id) {
    for (int i = 0; i < imageDatabase.size(); i++) {
        if (imageDatabase[i].imageID == id) {
            return i;
        }
    }
    return -1;
}

// ==================== DATA MANAGEMENT FUNCTIONS ====================

string ImageAnalyzer::addImage(const string& filePath) {
    try {
        // Check if image already exists
        for (const auto& imgData : imageDatabase) {
            if (imgData.image.getFilePath() == filePath) {
                throw DuplicateImageException(filePath);
            }
        }
        
        // Create new image
        Image newImage;
        if (!newImage.loadImage(filePath)) {
            throw InvalidImageException("Failed to load image from: " + filePath);
        }
        
        // Create ImageData entry
        ImageData imageData;
        imageData.imageID = generateImageID();
        imageData.image = newImage;
        imageData.isAnalyzed = false;
        
        // Get current timestamp
        time_t now = time(0);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        imageData.timestamp = string(buffer);
        
        // Add to database
        imageDatabase.push_back(imageData);
        
        logActivity("Image added to database: " + imageData.imageID + " (" + filePath + ")");
        return imageData.imageID;
    }
    catch (const AIDetectorException& e) {
        logActivity("ERROR adding image: " + string(e.what()));
        throw;
    }
}

bool ImageAnalyzer::updateImage(const string& imageID, const Image& newImage) {
    try {
        ImageData* imageData = findImageByID(imageID);
        if (!imageData) {
            throw ImageNotFound(imageID);
        }
        
        imageData->image = newImage;
        imageData->isAnalyzed = false;
        
        // Update timestamp
        time_t now = time(0);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        imageData->timestamp = string(buffer);
        
        logActivity("Image updated: " + imageID);
        return true;
    }
    catch (const AIDetectorException& e) {
        logActivity("ERROR updating image: " + string(e.what()));
        throw;
    }
}

bool ImageAnalyzer::saveAnalysisResult(const string& imageID, const FinalResult& result) {
    try {
        ImageData* imageData = findImageByID(imageID);
        if (!imageData) {
            throw ImageNotFound(imageID);
        }
        
        // Update analysis result
        imageData->analysisResult = result;
        imageData->isAnalyzed = true;
        
        // Update timestamp
        time_t now = time(0);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        imageData->timestamp = string(buffer);
        
        logActivity("Analysis result saved for: " + imageID + 
                   " | Verdict: " + (result.getIsAIGenerated() ? "AI GENERATED" : "AUTHENTIC") +
                   " | Confidence: " + to_string(result.getConfidence()));
        return true;
    }
    catch (const AIDetectorException& e) {
        logActivity("ERROR saving analysis result: " + string(e.what()));
        throw;
    }
}

bool ImageAnalyzer::deleteImage(const string& imageID) {
    try {
        int index = findImageIndexByID(imageID);
        if (index == -1) {
            throw ImageNotFound(imageID);
        }
        
        imageDatabase.erase(imageDatabase.begin() + index);
        logActivity("Image deleted: " + imageID);
        return true;
    }
    catch (const AIDetectorException& e) {
        logActivity("ERROR deleting image: " + string(e.what()));
        throw;
    }
}

vector<ImageData> ImageAnalyzer::getAllImages() const {
    return imageDatabase;
}

ImageData ImageAnalyzer::getImage(const string& imageID) const {
    const ImageData* imageData = const_cast<ImageAnalyzer*>(this)->findImageByID(imageID);
    if (!imageData) {
        throw ImageNotFound(imageID);
    }
    return *imageData;
}

// ==================== SEARCH & FILTER FUNCTIONS ====================

vector<ImageData> ImageAnalyzer::searchByFilename(const string& filename) const {
    vector<ImageData> results;
    string searchTerm = toLower(filename);
    
    for (const auto& imageData : imageDatabase) {
        string imagePath = toLower(imageData.image.getFilePath());
        if (imagePath.find(searchTerm) != string::npos) {
            results.push_back(imageData);
        }
    }
    
    return results;
}

vector<ImageData> ImageAnalyzer::filterByVerdict(bool isAI) const {
    vector<ImageData> results;
    
    for (const auto& imageData : imageDatabase) {
        if (imageData.isAnalyzed && imageData.analysisResult.getIsAIGenerated() == isAI) {
            results.push_back(imageData);
        }
    }
    
    return results;
}

vector<ImageData> ImageAnalyzer::filterByConfidenceRange(double minScore, double maxScore) const {
    try {
        if (!isValidScore(minScore) || !isValidScore(maxScore)) {
            throw InvalidScoreException(minScore);
        }
        
        if (minScore > maxScore) {
            throw InputValidationException("Minimum score cannot be greater than maximum score");
        }
        
        vector<ImageData> results;
        for (const auto& imageData : imageDatabase) {
            if (imageData.isAnalyzed) {
                double confidence = imageData.analysisResult.getConfidence();
                if (confidence >= minScore && confidence <= maxScore) {
                    results.push_back(imageData);
                }
            }
        }
        
        return results;
    }
    catch (const AIDetectorException& e) {
        cout << "ERROR: " << e.what() << endl;
        throw;
    }
}

vector<ImageData> ImageAnalyzer::getAnalyzedImages() const {
    vector<ImageData> results;
    for (const auto& imageData : imageDatabase) {
        if (imageData.isAnalyzed) {
            results.push_back(imageData);
        }
    }
    return results;
}

vector<ImageData> ImageAnalyzer::getUnanalyzedImages() const {
    vector<ImageData> results;
    for (const auto& imageData : imageDatabase) {
        if (!imageData.isAnalyzed) {
            results.push_back(imageData);
        }
    }
    return results;
}

// ==================== STATISTICS & REPORTS ====================

void ImageAnalyzer::getProcessStats() const {
    cout << "\n=== PROCESS STATISTICS ===" << endl;
    cout << "Total Images Processed: " << totalProcessed << endl;
    cout << "Active Analyzers: " << analyzers.size() << endl;
    cout << "Current Analysis Results: " << currentResult.getResultCount() << endl;
    cout << "History Log Entries: " << historyLog.getCount() << endl;
    cout << "=========================" << endl;
}

void ImageAnalyzer::getDatabaseStats() const {
    try {
        vector<ImageData> analyzed = getAnalyzedImages();
        vector<ImageData> unanalyzed = getUnanalyzedImages();
        vector<ImageData> aiGenerated = filterByVerdict(true);
        vector<ImageData> authentic = filterByVerdict(false);
        
        cout << "\n=== DATABASE STATISTICS ===" << endl;
        cout << "Total Images in Database: " << imageDatabase.size() << endl;
        cout << "Analyzed Images: " << analyzed.size() << endl;
        cout << "Unanalyzed Images: " << unanalyzed.size() << endl;
        cout << "AI Generated (Analyzed): " << aiGenerated.size() << endl;
        cout << "Authentic (Analyzed): " << authentic.size() << endl;
        cout << "============================" << endl;
    }
    catch (const exception& e) {
        cout << "Error retrieving statistics: " << e.what() << endl;
    }
}

void ImageAnalyzer::logActivity(string msg) {
    cout << msg << endl;
    historyLog.addEntry(msg);
}

void ImageAnalyzer::saveReport(string filename) {
    try {
        currentResult.saveToFile(filename);
        logActivity("Report saved to: " + filename);
    }
    catch (const exception& e) {
        logActivity("ERROR saving report: " + string(e.what()));
    }
}

void ImageAnalyzer::saveAllResultsToFile(const string& filename) {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            throw FileException("Cannot open file for writing: " + filename);
        }
        
        file << "=== AI IMAGE DETECTION - ANALYSIS REPORT ===\n\n";
        file << "Generated: ";
        time_t now = time(0);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        file << buffer << "\n\n";
        
        file << "DATABASE SUMMARY\n";
        file << "Total Images: " << imageDatabase.size() << "\n";
        file << "Analyzed: " << getAnalyzedImages().size() << "\n";
        file << "Unanalyzed: " << getUnanalyzedImages().size() << "\n\n";
        
        file << "DETAILED RESULTS\n";
        file << string(80, '=') << "\n";
        
        for (const auto& imageData : imageDatabase) {
            file << "Image ID: " << imageData.imageID << "\n";
            file << "File: " << imageData.image.getFilePath() << "\n";
            file << "Added: " << imageData.timestamp << "\n";
            file << "Status: " << (imageData.isAnalyzed ? "ANALYZED" : "NOT ANALYZED") << "\n";
            
            if (imageData.isAnalyzed) {
                file << "Confidence: " << fixed << setprecision(2) << imageData.analysisResult.getConfidence() << "\n";
                file << "Verdict: " << (imageData.analysisResult.getIsAIGenerated() ? "AI GENERATED" : "AUTHENTIC") << "\n";
            }
            
            file << string(80, '-') << "\n";
        }
        
        file.close();
        logActivity("All results saved to: " + filename);
    }
    catch (const AIDetectorException& e) {
        logActivity("ERROR saving results: " + string(e.what()));
        throw;
    }
}

void ImageAnalyzer::displayAllAnalyzers() const {
    cout << "\n=== ACTIVE ANALYZERS ===" << endl;
    cout << "Total: " << analyzers.size() << endl;
    cout << "========================" << endl;
    
    for (int i = 0; i < analyzers.size(); i++) {
        cout << "[" << i+1 << "] ";
        analyzers[i]->displayAnalyzerInfo();
    }
}

void ImageAnalyzer::displayDatabaseContents() const {
    try {
        if (imageDatabase.empty()) {
            cout << "\nNo images in database.\n" << endl;
            return;
        }
        
        cout << "\n=== IMAGE DATABASE CONTENTS ===" << endl;
        cout << left << setw(12) << "Image ID" 
             << setw(30) << "File Path" 
             << setw(12) << "Status"
             << setw(12) << "Confidence" << endl;
        cout << string(66, '-') << endl;
        
        for (const auto& imageData : imageDatabase) {
            cout << left << setw(12) << imageData.imageID
                 << setw(30) << imageData.image.getFilePath()
                 << setw(12) << (imageData.isAnalyzed ? "Analyzed" : "Pending")
                 << setw(12);
            
            if (imageData.isAnalyzed) {
                cout << fixed << setprecision(2) << imageData.analysisResult.getConfidence();
            } else {
                cout << "N/A";
            }
            cout << "\n";
        }
        
        cout << string(66, '=') << "\n" << endl;
    }
    catch (const exception& e) {
        cout << "Error displaying database: " << e.what() << endl;
    }
}
