#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
using namespace std;

class Image {
private:
    string filePath;            // Path to image file
    int width;                  // Image width in pixels
    int height;                 // Image height in pixels
    vector<char> rawData;       // Raw image data (simulated)
    string fileFormat;          // PNG, JPG, TIFF, etc.

public:
    Image(string path = "", int w = 0, int h = 0);
    ~Image();
    
    // Setters
    void setFilePath(string path);
    void setDimensions(int w, int h);
    void setRawData(vector<char> data);
    void setFileFormat(string format);
    
    // Getters
    string getFilePath() const { return filePath; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    vector<char> getRawData() const { return rawData; }
    string getFileFormat() const { return fileFormat; }
    int getFileSize() const { return rawData.size(); }
    
    // Get pixel data at index (simulated)
    char operator[](int index) const;
    
    // Display image info
    void displayImageInfo() const;
    
    // Load image (simulated)
    bool loadImage(string path);
    
    // Stream operators
    friend ostream& operator<<(ostream& out, const Image& img);
};

#endif
