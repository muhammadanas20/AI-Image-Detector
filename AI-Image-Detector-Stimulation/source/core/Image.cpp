#include "core/Image.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constructor
Image::Image(string path, int w, int h) 
    : filePath(path), width(w), height(h), fileFormat("") {
    // Initialize with simulated data
    if (w > 0 && h > 0) {
        rawData.resize(w * h, 0);
    }
}

// Destructor
Image::~Image() {
    rawData.clear();
}

// Setters
void Image::setFilePath(string path) {
    filePath = path;
}

void Image::setDimensions(int w, int h) {
    width = w;
    height = h;
    if (w > 0 && h > 0) {
        rawData.resize(w * h, 0);
    }
}

void Image::setRawData(vector<char> data) {
    rawData = data;
}

void Image::setFileFormat(string format) {
    fileFormat = format;
}

// Pixel access operator
char Image::operator[](int index) const {
    if (index >= 0 && index < static_cast<int>(rawData.size())) {
        return rawData[index];
    }
    return 0;
}

// Display image info
void Image::displayImageInfo() const {
    cout << "\n>>> IMAGE INFORMATION <<<" << endl;
    cout << "File Path: " << filePath << endl;
    cout << "File Format: " << (fileFormat.empty() ? "Unknown" : fileFormat) << endl;
    cout << "Dimensions: " << width << " x " << height << " pixels" << endl;
    cout << "File Size: " << rawData.size() << " bytes" << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>" << endl;
}

// Load image (simulated)
bool Image::loadImage(string path) {
    filePath = path;
    
    // Extract format from path
    size_t dotPos = path.find_last_of('.');
    if (dotPos != string::npos) {
        fileFormat = path.substr(dotPos + 1);
    }
    
    // Simulate loading image
    width = 1920 + (rand() % 1000);    // Random width between 1920-2920
    height = 1080 + (rand() % 1000);   // Random height between 1080-2080
    
    // Create simulated raw data
    int fileSize = width * height;
    rawData.resize(fileSize);
    
    // Fill with simulated pixel data
    for (int i = 0; i < fileSize; i++) {
        rawData[i] = static_cast<char>(rand() % 256);
    }
    
    return true;
}

// Stream output operator
ostream& operator<<(ostream& out, const Image& img) {
    out << "Image(path=" << img.filePath 
        << ", format=" << img.fileFormat 
        << ", size=" << img.width << "x" << img.height 
        << ", dataSize=" << img.rawData.size() << " bytes)";
    return out;
}
