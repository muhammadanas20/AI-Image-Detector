#include "Image.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

Image::Image(string path, int w, int h) 
    : filePath(path), width(w), height(h) {
    fileFormat = "Unknown";
}

Image::~Image() {
    rawData.clear();
}

void Image::setFilePath(string path) {
    filePath = path;
}

void Image::setDimensions(int w, int h) {
    width = w;
    height = h;
}

void Image::setRawData(vector<char> data) {
    rawData = data;
}

void Image::setFileFormat(string format) {
    fileFormat = format;
}

char Image::operator[](int index) const {
    if (index < 0 || index >= rawData.size()) {
        return '\0';
    }
    return rawData[index];
}

void Image::displayImageInfo() const {
    cout << "\n=== IMAGE INFORMATION ===" << endl;
    cout << "File Path: " << filePath << endl;
    cout << "Dimensions: " << width << " x " << height << " pixels" << endl;
    cout << "File Format: " << fileFormat << endl;
    cout << "File Size: " << rawData.size() << " bytes" << endl;
    cout << "=========================" << endl;
}

bool Image::loadImage(string path) {
    filePath = path;
    
    // Simulate loading image
    if (path.empty()) {
        return false;
    }
    
    // Simulate determining file format
    if (path.find(".jpg") != string::npos || path.find(".jpeg") != string::npos) {
        fileFormat = "JPEG";
    } else if (path.find(".png") != string::npos) {
        fileFormat = "PNG";
    } else if (path.find(".tiff") != string::npos || path.find(".tif") != string::npos) {
        fileFormat = "TIFF";
    } else {
        fileFormat = "Unknown";
    }
    
    // Simulate random dimensions and data
    width = 1920 + (rand() % 1080);
    height = 1080 + (rand() % 720);
    
    // Generate simulated raw data
    int dataSize = (width * height * 3) / 100; // Compressed simulation
    rawData.clear();
    for (int i = 0; i < dataSize; i++) {
        rawData.push_back((char)(rand() % 256));
    }
    
    return true;
}

ostream& operator<<(ostream& out, const Image& img) {
    out << "Image(" << img.filePath << ", " << img.width << "x" << img.height << ")";
    return out;
}
