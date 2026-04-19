#include "analyzers/ImageAnalyzer.h"
#include "analyzers/MetadataAnalyzer.h"
#include "analyzers/ArtifactAnalyzer.h"
#include "analyzers/FrequencyAnalyzer.h"
#include "analyzers/WatermarkAnalyzer.h"
#include "analyzers/HybridDeepAnalyzer.h"
#include "core/MenuSystem.h"
#include "utilities/Utils.h"
#include "utilities/CustomExceptions.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Global analyzer instance accessible to MenuSystem
ImageAnalyzer* g_imageAnalyzer = nullptr;

void initializeSystem() {
    try {
        printHeader("AI IMAGE DETECTION SYSTEM - INITIALIZATION");
        
        // Create main analyzer controller
        g_imageAnalyzer = new ImageAnalyzer();
        cout << "ImageAnalyzer controller created\n" << endl;
        
        // Add individual analyzers
        cout << "Loading analyzers...\n" << endl;
        
        g_imageAnalyzer->addAnalyzer(new MetadataAnalyzer());
        cout << "MetadataAnalyzer loaded\n";
        
        g_imageAnalyzer->addAnalyzer(new ArtifactAnalyzer());
        cout << "ArtifactAnalyzer loaded\n";
        
        g_imageAnalyzer->addAnalyzer(new FrequencyAnalyzer());
        cout << "FrequencyAnalyzer loaded\n";
        
        g_imageAnalyzer->addAnalyzer(new WatermarkAnalyzer());
        cout << "WatermarkAnalyzer loaded\n";
        
        g_imageAnalyzer->addAnalyzer(new HybridDeepAnalyzer());
        cout << "HybridDeepAnalyzer loaded\n" << endl;
        
        cout << "System initialized successfully with " << Analyzer::getCount() << " analyzers\n" << endl;
        pauseExecution("Press Enter to continue to main menu...");
    }
    catch (const AIDetectorException& e) {
        cout << "\nCRITICAL ERROR during initialization: " << e.what() << endl;
        cout << "System cannot continue. Please check your configuration.\n" << endl;
        throw;
    }
    catch (const exception& e) {
        cout << "\nUnexpected error during initialization: " << e.what() << endl;
        cout << "System cannot continue.\n" << endl;
        throw;
    }
}

void cleanupSystem() {
    try {
        if (g_imageAnalyzer != nullptr) {
            delete g_imageAnalyzer;
            g_imageAnalyzer = nullptr;
            cout << "\nSystem cleanup complete\n" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Error during cleanup: " << e.what() << endl;
    }
}

int main() {
    try {
        // Initialize system
        initializeSystem();
        
        MenuSystem menu;
        menu.run();
        
        // Cleanup
        cleanupSystem();
        
        cout << "Thank you for using AI Image Detection System!" << endl;
        cout << "Program terminated successfully.\n" << endl;
        
        return 0;
    }
    catch (const AIDetectorException& e) {
        cout << "\n" << string(60, '=') << endl;
        cout << "CRITICAL ERROR: " << e.what() << endl;
        cout << string(60, '=') << "\n" << endl;
        
        cleanupSystem();
        return 1;
    }
    catch (const exception& e) {
        cout << "\n" << string(60, '=') << endl;
        cout << "UNEXPECTED ERROR: " << e.what() << endl;
        cout << string(60, '=') << "\n" << endl;
        
        cleanupSystem();
        return 1;
    }
}
