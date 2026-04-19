#include "core/MenuSystem.h"
#include "analyzers/ImageAnalyzer.h"
#include "core/Image.h"
#include "results/FinalResult.h"
#include "utilities/Utils.h"
#include <iostream>
#include <memory>
#include <iomanip>
using namespace std;

// Global analyzer instance (declared as extern in MenuSystem to be initialized in main)
extern class ImageAnalyzer* g_imageAnalyzer;

MenuSystem::MenuSystem() : isRunning(true) {}

MenuSystem::~MenuSystem() {}

// ==================== DISPLAY FUNCTIONS ====================

void MenuSystem::displayMainMenu() {
    cout << "\n";
    printSection("MAIN MENU");
    cout << "1. Image Analysis\n";
    cout << "2. Database Management\n";
    cout << "3. Search & Filter\n";
    cout << "4. View Reports\n";
    cout << "5. System Statistics\n";
    cout << "6. Exit\n" << endl;
}

void MenuSystem::displayAnalysisMenu() {
    cout << "\n";
    printSection("IMAGE ANALYSIS");
    cout << "1. Add Image to Database\n";
    cout << "2. Analyze Image from Database\n";
    cout << "3. Run Analysis on New Image\n";
    cout << "4. Analyze All Unanalyzed Images\n";
    cout << "5. Back to Main Menu\n" << endl;
}

void MenuSystem::displayDataManagementMenu() {
    cout << "\n";
    printSection("DATABASE MANAGEMENT");
    cout << "1. View All Images\n";
    cout << "2. View Analyzed Images\n";
    cout << "3. View Unanalyzed Images\n";
    cout << "4. Update Image\n";
    cout << "5. Delete Image\n";
    cout << "6. Back to Main Menu\n" << endl;
}

void MenuSystem::displaySearchMenu() {
    cout << "\n";
    printSection("SEARCH & FILTER");
    cout << "1. Search by Filename\n";
    cout << "2. Filter by Verdict (AI Generated / Authentic)\n";
    cout << "3. Filter by Confidence Score\n";
    cout << "4. Back to Main Menu\n" << endl;
}

void MenuSystem::displayReportsMenu() {
    cout << "\n";
    printSection("REPORTS & LOGS");
    cout << "1. Display Database Statistics\n";
    cout << "2. Display Process Statistics\n";
    cout << "3. Save All Results to File\n";
    cout << "4. Display Active Analyzers\n";
    cout << "5. Back to Main Menu\n" << endl;
}

// ==================== GET MENU CHOICE ====================

int MenuSystem::getMainMenuChoice() {
    return getValidMenuChoice("\nEnter your choice (1-6): ", 1, 6);
}

int MenuSystem::getAnalysisMenuChoice() {
    return getValidMenuChoice("\nEnter your choice (1-5): ", 1, 5);
}

int MenuSystem::getSearchMenuChoice() {
    return getValidMenuChoice("\nEnter your choice (1-4): ", 1, 4);
}

int MenuSystem::getDataManagementMenuChoice() {
    return getValidMenuChoice("\nEnter your choice (1-6): ", 1, 6);
}

int MenuSystem::getReportsMenuChoice() {
    return getValidMenuChoice("\nEnter your choice (1-5): ", 1, 5);
}

// ==================== MAIN MENU LOOP ====================

void MenuSystem::run() {
    while (isRunning) {
        clearScreen();
        displayMainMenu();
        int choice = getMainMenuChoice();
        handleMainMenu(choice);
    }
}

// ==================== HANDLER FUNCTIONS ====================

void MenuSystem::handleMainMenu(int choice) {
    switch (choice) {
        case 1:
            // Image Analysis
            while (true) {
                clearScreen();
                displayAnalysisMenu();
                int subChoice = getAnalysisMenuChoice();
                handleAnalysisMenu(subChoice);
                if (subChoice == 5) break;
            }
            break;
            
        case 2:
            // Database Management
            while (true) {
                clearScreen();
                displayDataManagementMenu();
                int subChoice = getDataManagementMenuChoice();
                handleDataManagementMenu(subChoice);
                if (subChoice == 6) break;
            }
            break;
            
        case 3:
            // Search & Filter
            while (true) {
                clearScreen();
                displaySearchMenu();
                int subChoice = getSearchMenuChoice();
                handleSearchMenu(subChoice);
                if (subChoice == 4) break;
            }
            break;
            
        case 4:
            // Reports
            while (true) {
                clearScreen();
                displayReportsMenu();
                int subChoice = getReportsMenuChoice();
                handleReportsMenu(subChoice);
                if (subChoice == 5) break;
            }
            break;
            
        case 5:
            // System Statistics (shown separately)
            g_imageAnalyzer->getProcessStats();
            g_imageAnalyzer->getDatabaseStats();
            pauseExecution();
            break;
            
        case 6:
            // Exit
            cout << "\nThank you for using AI Image Detection System!" << endl;
            isRunning = false;
            break;
    }
}

void MenuSystem::handleAnalysisMenu(int choice) {
    try {
        switch (choice) {
            case 1: {
                // Add Image to Database
                printSection("ADD IMAGE TO DATABASE");
                string filePath = getValidFilePath("\nEnter image file path: ");
                string imageID = g_imageAnalyzer->addImage(filePath);
                cout << "\n[SUCCESS] Image added successfully!\n";
                cout << "Image ID: " << imageID << "\n" << endl;
                pauseExecution();
                break;
            }
            
            case 2: {
                // Analyze Image from Database
                printSection("ANALYZE IMAGE FROM DATABASE");
                g_imageAnalyzer->displayDatabaseContents();
                
                string imageID;
                cout << "\nEnter Image ID to analyze: ";
                getline(cin, imageID);
                imageID = trimString(imageID);
                
                try {
                    ImageData imageData = g_imageAnalyzer->getImage(imageID);
                    cout << "\nAnalyzing: " << imageData.image.getFilePath() << "\n" << endl;
                    
                    FinalResult result = g_imageAnalyzer->running(imageData.image);
                    result.displayFullReport();
                    
                    // Save analysis results to database
                    g_imageAnalyzer->saveAnalysisResult(imageID, result);
                    
                    cout << "\n[SUCCESS] Analysis results saved to database!\n" << endl;
                    pauseExecution();
                }
                catch (const exception& e) {
                    cout << "ERROR: " << e.what() << "\n" << endl;
                    pauseExecution();
                }
                break;
            }
            
            case 3: {
                // Run Analysis on New Image
                printSection("ANALYZE NEW IMAGE");
                string filePath = getValidFilePath("\nEnter image file path: ");
                
                try {
                    Image testImage;
                    if (!testImage.loadImage(filePath)) {
                        cout << "ERROR: Failed to load image.\n" << endl;
                        break;
                    }
                    
                    testImage.displayImageInfo();
                    FinalResult result = g_imageAnalyzer->running(testImage);
                    result.displayFullReport();
                    pauseExecution();
                }
                catch (const exception& e) {
                    cout << "ERROR: " << e.what() << "\n" << endl;
                    pauseExecution();
                }
                break;
            }
            
            case 4: {
                // Analyze All Unanalyzed Images
                printSection("ANALYZE ALL UNANALYZED IMAGES");
                vector<ImageData> unanalyzed = g_imageAnalyzer->getUnanalyzedImages();
                
                if (unanalyzed.empty()) {
                    cout << "\nNo unanalyzed images in database.\n" << endl;
                }
                else {
                    cout << "\nFound " << unanalyzed.size() << " unanalyzed image(s).\n" << endl;
                    
                    for (int i = 0; i < unanalyzed.size(); i++) {
                        cout << "Analyzing [" << i+1 << "/" << unanalyzed.size() << "]: " 
                             << unanalyzed[i].image.getFilePath() << "\n" << endl;
                        
                        Image img = unanalyzed[i].image;
                        FinalResult result = g_imageAnalyzer->running(img);
                    }
                    
                    cout << "\n[SUCCESS] Analysis complete for all unanalyzed images!\n" << endl;
                }
                
                pauseExecution();
                break;
            }
            
            case 5:
                // Back to main menu
                return;
        }
    }
    catch (const exception& e) {
        cout << "\nERROR: " << e.what() << "\n" << endl;
        pauseExecution();
    }
}

void MenuSystem::handleDataManagementMenu(int choice) {
    try {
        switch (choice) {
            case 1:
                // View All Images
                g_imageAnalyzer->displayDatabaseContents();
                pauseExecution();
                break;
                
            case 2: {
                // View Analyzed Images
                printSection("ANALYZED IMAGES");
                vector<ImageData> analyzed = g_imageAnalyzer->getAnalyzedImages();
                
                if (analyzed.empty()) {
                    cout << "\nNo analyzed images in database.\n" << endl;
                } else {
                    cout << left << setw(12) << "Image ID" 
                         << setw(30) << "File Path" 
                         << setw(12) << "Confidence"
                         << setw(12) << "Verdict" << endl;
                    cout << string(66, '-') << endl;
                    
                    for (const auto& imageData : analyzed) {
                        cout << left << setw(12) << imageData.imageID
                             << setw(30) << imageData.image.getFilePath()
                             << setw(12) << fixed << setprecision(2) << imageData.analysisResult.getConfidence()
                             << setw(12) << (imageData.analysisResult.getIsAIGenerated() ? "AI Generated" : "Authentic") << endl;
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 3: {
                // View Unanalyzed Images
                printSection("UNANALYZED IMAGES");
                vector<ImageData> unanalyzed = g_imageAnalyzer->getUnanalyzedImages();
                
                if (unanalyzed.empty()) {
                    cout << "\nNo unanalyzed images in database.\n" << endl;
                } else {
                    for (const auto& imageData : unanalyzed) {
                        cout << "ID: " << imageData.imageID 
                             << " | File: " << imageData.image.getFilePath() << endl;
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 4: {
                // Update Image
                printSection("UPDATE IMAGE");
                g_imageAnalyzer->displayDatabaseContents();
                
                string imageID;
                cout << "\nEnter Image ID to update: ";
                getline(cin, imageID);
                imageID = trimString(imageID);
                
                string newPath = getValidFilePath("\nEnter new image file path: ");
                
                Image newImage;
                if (newImage.loadImage(newPath)) {
                    if (g_imageAnalyzer->updateImage(imageID, newImage)) {
                        cout << "\n[SUCCESS] Image updated successfully!\n" << endl;
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 5: {
                // Delete Image
                printSection("DELETE IMAGE");
                g_imageAnalyzer->displayDatabaseContents();
                
                string imageID;
                cout << "\nEnter Image ID to delete: ";
                getline(cin, imageID);
                imageID = trimString(imageID);
                
                if (getConfirmation("Are you sure you want to delete this image?")) {
                    if (g_imageAnalyzer->deleteImage(imageID)) {
                        cout << "\n[SUCCESS] Image deleted successfully!\n" << endl;
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 6:
                // Back to main menu
                return;
        }
    }
    catch (const exception& e) {
        cout << "\nERROR: " << e.what() << "\n" << endl;
        pauseExecution();
    }
}

void MenuSystem::handleSearchMenu(int choice) {
    try {
        switch (choice) {
            case 1: {
                // Search by Filename
                printSection("SEARCH BY FILENAME");
                string filename;
                cout << "\nEnter filename to search (partial match OK): ";
                getline(cin, filename);
                filename = trimString(filename);
                
                vector<ImageData> results = g_imageAnalyzer->searchByFilename(filename);
                
                if (results.empty()) {
                    cout << "\nNo images found matching: " << filename << "\n" << endl;
                } else {
                    cout << "\nFound " << results.size() << " matching image(s):\n" << endl;
                    cout << left << setw(12) << "Image ID" 
                         << setw(40) << "File Path" << endl;
                    cout << string(52, '-') << endl;
                    
                    for (const auto& imageData : results) {
                        cout << left << setw(12) << imageData.imageID
                             << setw(40) << imageData.image.getFilePath() << endl;
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 2: {
                // Filter by Verdict
                printSection("FILTER BY VERDICT");
                cout << "\n1. AI Generated Images\n";
                cout << "2. Authentic Images\n";
                int verdictChoice = getValidMenuChoice("\nEnter your choice (1-2): ", 1, 2);
                
                bool isAI = (verdictChoice == 1);
                vector<ImageData> results = g_imageAnalyzer->filterByVerdict(isAI);
                
                if (results.empty()) {
                    cout << "\nNo " << (isAI ? "AI Generated" : "Authentic") << " images found.\n" << endl;
                } else {
                    cout << "\nFound " << results.size() << (isAI ? " AI Generated" : " Authentic") 
                         << " image(s):\n" << endl;
                    cout << left << setw(12) << "Image ID" 
                         << setw(30) << "File Path" 
                         << setw(12) << "Confidence" << endl;
                    cout << string(54, '-') << endl;
                    
                    for (const auto& imageData : results) {
                        cout << left << setw(12) << imageData.imageID
                             << setw(30) << imageData.image.getFilePath()
                             << setw(12) << fixed << setprecision(2) << imageData.analysisResult.getConfidence() << endl;
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 3: {
                // Filter by Confidence Score
                printSection("FILTER BY CONFIDENCE SCORE");
                cout << "\nEnter score range (0.0 to 1.0):" << endl;
                
                double minScore = getValidDouble("Minimum score (e.g., 0.0): ", 0.0, 1.0);
                double maxScore = getValidDouble("Maximum score (e.g., 1.0): ", minScore, 1.0);
                
                vector<ImageData> results = g_imageAnalyzer->filterByConfidenceRange(minScore, maxScore);
                
                if (results.empty()) {
                    cout << "\nNo images found in confidence range [" << minScore << ", " << maxScore << "]\n" << endl;
                } else {
                    cout << "\nFound " << results.size() << " image(s) in confidence range:\n" << endl;
                    cout << left << setw(12) << "Image ID" 
                         << setw(30) << "File Path" 
                         << setw(12) << "Confidence"
                         << setw(12) << "Verdict" << endl;
                    cout << string(66, '-') << endl;
                    
                    for (const auto& imageData : results) {
                        cout << left << setw(12) << imageData.imageID
                             << setw(30) << imageData.image.getFilePath()
                             << setw(12) << fixed << setprecision(2) << imageData.analysisResult.getConfidence()
                             << setw(12) << (imageData.analysisResult.getIsAIGenerated() ? "AI Gen" : "Auth") << endl;
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 4:
                // Back to main menu
                return;
        }
    }
    catch (const exception& e) {
        cout << "\nERROR: " << e.what() << "\n" << endl;
        pauseExecution();
    }
}

void MenuSystem::handleReportsMenu(int choice) {
    try {
        switch (choice) {
            case 1:
                // Database Statistics
                g_imageAnalyzer->getDatabaseStats();
                pauseExecution();
                break;
                
            case 2:
                // Process Statistics
                g_imageAnalyzer->getProcessStats();
                pauseExecution();
                break;
                
            case 3: {
                // Save All Results
                printSection("SAVE ALL RESULTS");
                string filename;
                cout << "\nEnter filename to save results (e.g., results.txt): ";
                getline(cin, filename);
                filename = trimString(filename);
                
                if (!filename.empty()) {
                    g_imageAnalyzer->saveAllResultsToFile(filename);
                    cout << "\n[SUCCESS] Results saved successfully!\n" << endl;
                }
                
                pauseExecution();
                break;
            }
                
            case 4:
                // Display Active Analyzers
                g_imageAnalyzer->displayAllAnalyzers();
                pauseExecution();
                break;
                
            case 5:
                // Back to main menu
                return;
        }
    }
    catch (const exception& e) {
        cout << "\nERROR: " << e.what() << "\n" << endl;
        pauseExecution();
    }
}
