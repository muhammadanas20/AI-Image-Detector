#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
#include <string>
using namespace std;

// Base exception class
class AIDetectorException : public exception {
protected:
    string message;
    
public:
    AIDetectorException(const string& msg = "Unknown error") : message(msg) {}
    virtual ~AIDetectorException() {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// File-related exceptions
class FileException : public AIDetectorException {
public:
    FileException(const string& msg = "File error occurred") 
        : AIDetectorException("FILE ERROR: " + msg) {}
};

class FileNotFoundException : public FileException {
public:
    FileNotFoundException(const string& filename)
        : FileException("File not found: " + filename) {}
};

class InvalidFileFormatException : public FileException {
public:
    InvalidFileFormatException(const string& format)
        : FileException("Invalid file format: " + format) {}
};

// Image-related exceptions
class ImageException : public AIDetectorException {
public:
    ImageException(const string& msg = "Image error occurred")
        : AIDetectorException("IMAGE ERROR: " + msg) {}
};

class InvalidImageException : public ImageException {
public:
    InvalidImageException(const string& msg = "Invalid image")
        : ImageException(msg) {}
};

class ImageDimensionException : public ImageException {
public:
    ImageDimensionException(int width, int height)
        : ImageException("Invalid dimensions: " + to_string(width) + "x" + to_string(height)) {}
};

// Analysis-related exceptions
class AnalysisException : public AIDetectorException {
public:
    AnalysisException(const string& msg = "Analysis failed")
        : AIDetectorException("ANALYSIS ERROR: " + msg) {}
};

class NoAnalyzersException : public AnalysisException {
public:
    NoAnalyzersException()
        : AnalysisException("No analyzers available in pipeline") {}
};

// Input validation exceptions
class InputValidationException : public AIDetectorException {
public:
    InputValidationException(const string& msg = "Invalid input")
        : AIDetectorException("INPUT ERROR: " + msg) {}
};

class InvalidChoiceException : public InputValidationException {
public:
    InvalidChoiceException(const string& choice)
        : InputValidationException("Invalid choice: " + choice) {}
};

class InvalidScoreException : public InputValidationException {
public:
    InvalidScoreException(double score)
        : InputValidationException("Score out of range (0.0-1.0): " + to_string(score)) {}
};

// Data management exceptions
class DataException : public AIDetectorException {
public:
    DataException(const string& msg = "Data error occurred")
        : AIDetectorException("DATA ERROR: " + msg) {}
};

class ImageNotFound : public DataException {
public:
    ImageNotFound(const string& id)
        : DataException("Image not found with ID: " + id) {}
};

class DuplicateImageException : public DataException {
public:
    DuplicateImageException(const string& path)
        : DataException("Image already exists: " + path) {}
};

#endif
