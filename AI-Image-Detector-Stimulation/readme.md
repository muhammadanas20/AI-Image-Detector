# AI Image Detection System

A comprehensive C++ object-oriented application that detects AI-generated images using multiple analysis techniques. Features include database management, advanced search/filtering, and menu-driven interface.

---

## Group Members

| Name | Student ID |
|------|-----------|
| Muhammad Anas | 25K-0899 |

---

## Use Cases

1. **Image Authenticity Verification**: Verify whether images are authentic photographs or AI-generated before publishing.

2. **Social Media Content Moderation**: Automatically flag AI-generated images to prevent misinformation spread.

3. **Academic Integrity**: Detect AI-generated images in student submissions to ensure academic honesty.

4. **Copyright Protection**: Identify AI-generated copies of original work in digital repositories.

5. **Forensic Investigation**: Detect deepfakes and manipulated evidence in criminal investigations.

6. **E-Commerce Quality Control**: Verify product images are authentic photographs, not AI-generated mockups.

---

## How to Compile

### Prerequisites
- C++ compiler (GCC 5+,MSVC 2015+)
- C++11 or higher support
---

## How to Run

**Linux/macOS:**
```bash
g++ -std=c++11 -o bin/analyzer source/main/main.cpp source/core/Analyzer.cpp source/core/Image.cpp source/core/MenuSystem.cpp source/analyzers/*.cpp source/results/*.cpp source/utilities/*.cpp -I include/ && ./bin/analyzer
```

**Windows (MinGW):**
```bash
g++ -std=c++11 -o bin/analyzer.exe source/main/main.cpp source/core/Analyzer.cpp source/core/Image.cpp source/core/MenuSystem.cpp source/analyzers/*.cpp source/results/*.cpp source/utilities/*.cpp -I include/ ; ./bin/analyzer.exe
```

---

## How to Use

1. **Add Images**: Select "Image Analysis" → "Add Image to Database" → Enter image path
2. **Analyze Images**: Select "Image Analysis" → Choose image → System runs 5 analyzers
3. **View Results**: See individual analyzer scores and combined verdict (AI or Authentic)
4. **Search & Filter**: Find images by filename, verdict, or confidence score range
5. **Generate Reports**: Export analysis results and view statistics
6. **Manage Database**: Update or delete images from the collection

### Example Session
```
1. Start application → ./bin/analyzer (Linux/macOS) or ./bin/analyzer.exe (Windows)
2. Main Menu → Option 1 (Image Analysis)
3. Option 1 → Add Image → /path/to/image.jpg → Image added with ID: IMG_1
4. Option 2 → Analyze → IMG_1 → System analyzes with 5 methods
5. View report → Verdict displayed (confidence score shown)
6. Main Menu → Option 3 (Search & Filter) → Find images by criteria
7. Main Menu → Option 4 (Reports) → Save results to file
8. Exit
```

---

## Project Structure

```
AI-Image-Detector-Stimulation/
├── include/                          # Header files
│   ├── analyzers/
│   │   ├── ArtifactAnalyzer.h
│   │   ├── FrequencyAnalyzer.h
│   │   ├── HybridDeepAnalyzer.h
│   │   ├── ImageAnalyzer.h
│   │   ├── MetadataAnalyzer.h
│   │   └── WatermarkAnalyzer.h
│   ├── core/
│   │   ├── Analyzer.h
│   │   ├── ILoggable.h
│   │   ├── Image.h
│   │   └── MenuSystem.h
│   ├── results/
│   │   ├── AnalysisResult.h
│   │   ├── FinalResult.h
│   │   └── HistoryLog.h
│   └── utilities/
│       ├── CustomExceptions.h
│       └── Utils.h
├── source/                           # Implementation files
│   ├── analyzers/
│   │   ├── ArtifactAnalyzer.cpp
│   │   ├── FrequencyAnalyzer.cpp
│   │   ├── HybridDeepAnalyzer.cpp
│   │   ├── ImageAnalyzer.cpp
│   │   ├── MetadataAnalyzer.cpp
│   │   └── WatermarkAnalyzer.cpp
│   ├── core/
│   │   ├── Analyzer.cpp
│   │   ├── Image.cpp
│   │   └── MenuSystem.cpp
│   ├── main/
│   │   └── main.cpp
│   ├── results/
│   │   ├── AnalysisResult.cpp
│   │   ├── FinalResult.cpp
│   │   └── HistoryLog.cpp
│   └── utilities/
│       └── Utils.cpp
├── bin/                              # Compiled executables
│   └── analyzer.exe
├── assets/                           # Sample images 
├── readme.md                         # This file
```

---

##  Assumptions and Limitations

### Assumptions
1. **Image Loading is Simulated**: System uses random dimensions to avoid external image library dependencies
2. **Analysis is Heuristic-Based**: Analyzers use pattern matching, not actual deep learning models
3. **Console Environment**: Terminal supports standard I/O operations
4. **File System Access**: Read/write permissions available

### Limitations
1. **Simulated Analysis**: Demonstration system - actual analysis requires real ML models
2. **Limited Image Formats**: Recognizes common formats but doesn't load actual image data
3. **Single User**: Not designed for concurrent multi-user access
4. **In-Memory Database**: Data lost when application closes (no persistent storage)
5. **Console Interface**: Terminal/console required - no GUI
6. **Demo Scale**: Optimized for demonstrations, not production-scale analysis

---

**Version:** 1.0 (Final Submission)

