# 🏗️ System Architecture & Image Processing - Quick Reference

## File Structure
```
src/
├── Main Components
│   ├── main.cpp (Entry point, demonstrates full workflow)
│   ├── Image.h/.cpp (Image representation)
│   └── ILoggable.h (Logging interface)
│
├── Analyzer Framework
│   ├── Analyzer.h/.cpp (Abstract base class)
│   ├── MetadataAnalyzer.h/.cpp
│   ├── ArtifactAnalyzer.h/.cpp
│   ├── FrequencyAnalyzer.h/.cpp
│   ├── WatermarkAnalyzer.h/.cpp
│   └── HybridDeepAnalyzer.h/.cpp
│
├── Result Management
│   ├── AnalysisResult.h/.cpp (Single analyzer result)
│   ├── FinalResult.h/.cpp (Aggregated results)
│   └── HistoryLog.h/.cpp (Activity logging)
│
├── Orchestration
│   ├── ImageAnalyzer.h/.cpp (Main controller)
│   └── Utils.cpp (Helper functions)
│
└── Documentation
    ├── readme.md (Full documentation)
    └── WORKFLOW_EXPLANATION.md (Detailed workflow)
```

---

## 🔵 Class Relationships

```
┌──────────────┐
│  ILoggable   │ (Interface)
└──────┬───────┘
       △ implements
       │
┌──────┴──────────┬─────────────┐
│                 │             │
┌─▼────────┐  ┌──▼─────┐   ┌──▼──────┐
│ Analyzer │  │ImageAna│   │HistoryLog
│(abstract)│  │lyzer   │   └──────────┘
└────┬─────┘  └────────┘
     △
     │ extends
┌────┴──────────┬──────────┬──────────┬─────────┐
│               │          │          │         │
Meta        Artifact    Frequency   Watermark Hybrid
Analyzer    Analyzer    Analyzer    Analyzer  Deep
```

### Key Relationships
- **Inheritance:** All Analyzers inherit from abstract `Analyzer`
- **Composition:** `ImageAnalyzer` owns collection of `Analyzer*`
- **Aggregation:** `FinalResult` contains vector<`AnalysisResult`>
- **Interface:** `ILoggable` contract implemented by both

---

## 📊 Image Processing Sequence

### Input → Processing → Output

```
User Image File
    ↓
Image::loadImage()
    ├─ Extract format (JPG/PNG/TIFF)
    ├─ Get dimensions (width×height)
    ├─ Generate simulated rawData
    └─ Ready for analysis
    ↓
ImageAnalyzer::running()
    ├─ For each registered Analyzer:
    │  ├─ Call analyzer.analyze(image)
    │  ├─ Get AnalysisResult
    │  ├─ Add to FinalResult
    │  └─ Log activity
    ↓
FinalResult::calcFinalScore()
    ├─ Sum all scores
    ├─ Divide by count
    ├─ Determine verdict (>0.5 = AI)
    └─ Store in confidence field
    ↓
Result Display
    ├─ displayFullReport() → Console
    ├─ saveToFile() → Text file
    └─ getProcessStats() → Summary
    ↓
Output: FinalResult Object
```

---

## 🎯 Analyzer Scoring Breakdown

### MetadataAnalyzer
| Factor | Score Increase |
|--------|-----------------|
| No EXIF Data | +0.40 |
| Unverified Source | +0.30 |
| Suspicious Camera | +0.20 |
| **Max Score** | **0.70** |
| **Typical Range** | 0.0 - 0.35 |

**Real Image Indicators:**
- ✓ Complete EXIF metadata
- ✓ Known camera model
- ✓ Verified source

---

### ArtifactAnalyzer
| Factor | Score Increase |
|--------|-----------------|
| Jagged Edges Detected | +0.30 |
| AI Artifacts Found | +0.45 |
| High Artifact Density | Proportional |
| **Max Score** | **0.80** |
| **Typical Range** | 0.0 - 0.50 |

**Real Image Indicators:**
- ✓ Natural edge variation
- ✓ No consistent artifacts
- ✓ Random noise patterns

---

### FrequencyAnalyzer
| Factor | Score Increase |
|--------|-----------------|
| Suspicious Noise Bands | +0.40 |
| Low Frequency Variance | +0.30 |
| Unnatural Frequency Distribution | Variable |
| **Max Score** | **0.80** |
| **Typical Range** | 0.2 - 0.6 |

**Technical Details:**
- FFT breaks image into frequency components
- AI images often have lower variance
- Real photos show random frequency distribution

---

### WatermarkAnalyzer
| Factor | Score Change |
|--------|-----------------|
| Copyright Watermark | -0.10 |
| Visible Watermark | +0.20 |
| No Watermark | 0.0 |
| **Max Score** | **0.30** |
| **Typical Range** | 0.0 - 0.20 |

**Why Watermarks Matter:**
- Copyright marks indicate authentic source
- Absence doesn't prove AI generation

---

### HybridDeepAnalyzer
```
Score = (MetaScore + ArtifactScore + FreqScore) / 3
if (NeuralPassPositive)
    Score = Score × 1.1  (max 1.0)
```

**Multi-Method Validation:**
Combines 3 independent analyzers + simulated neural network

---

## 📋 Final Verdict Logic

```
confidence = Average(all 5 analyzers)

if (confidence > 0.5) {
    isAIGenerated = true;
    verdict = "⚠️ AI GENERATED - HIGH CONFIDENCE";
} else if (confidence > 0.4) {
    isAIGenerated = false;
    verdict = "⚠️ SUSPICIOUS - FURTHER REVIEW RECOMMENDED";
} else {
    isAIGenerated = false;
    verdict = "✓ LIKELY AUTHENTIC";
}
```

### Example Scenarios

**Scenario 1: Authentic Photo**
```
Meta: 0.10 (Good EXIF) ✓
Artifact: 0.15 (Natural) ✓
Frequency: 0.20 (Good variance) ✓
Watermark: -0.05 (Copyright) ✓
Hybrid: 0.15 (Confirms)
────────────────────────
Average: 0.11 = AUTHENTIC ✓
```

**Scenario 2: AI-Generated**
```
Meta: 0.40 (No EXIF) ✗
Artifact: 0.65 (Many artifacts) ✗
Frequency: 0.70 (Low variance) ✗
Watermark: 0.10 (None/Unknown) ✗
Hybrid: 0.61 (Confirms AI) ✗
────────────────────────
Average: 0.49 = AI GENERATED ⚠️
```

**Scenario 3: Mixed Signals**
```
Meta: 0.25 (Partial EXIF)
Artifact: 0.35 (Some noise)
Frequency: 0.45 (Medium variance)
Watermark: 0.15 (Generic)
Hybrid: 0.38 (Inconclusive)
────────────────────────
Average: 0.32 = LIKELY AUTHENTIC ✓
           (but review recommended)
```

---

## 🔐 Data Flow Through System

```
┌──────────────┐
│   Image      │ Contains: path, width, height, rawData
└──────┬───────┘
       │
       │ Passed to each analyzer
       │
   ┌───▼──────────────────────────────┐
   │ Analyzer::analyze(Image& img)    │
   │ ↓                                │
   │ Examines image characteristics  │
   │ ↓                                │
   │ Generates score (0.0-1.0)        │
   │ ↓                                │
   │ Returns AnalysisResult           │
   └───┬──────────────────────────────┘
       │
   ┌───▼──────────────────────────────┐
   │  AnalysisResult                  │
   │  Contains:                       │
   │  • score (0.0-1.0)              │
   │  • reason (string)              │
   │  • timestamp (when analyzed)    │
   │  • analyzerName (which analyzer)│
   └───┬──────────────────────────────┘
       │
       │ All 5 results collected
       │
   ┌───▼──────────────────────────────┐
   │  FinalResult                     │
   │  Contains:                       │
   │  • vector<AnalysisResult>       │
   │  • confidence (average)         │
   │  • isAIGenerated (bool)         │
   │  • verdict (string)             │
   └───┬──────────────────────────────┘
       │
   ┌───▼──────────────────────────────┐
   │  Output & Storage                │
   │  • Console display              │
   │  • File export                  │
   │  • History log                  │
   │  • Statistics tracking          │
   └──────────────────────────────────┘
```

---

## 💻 Code Usage Pattern

### Basic Usage
```cpp
// 1. Create controller
ImageAnalyzer analyzer;

// 2. Register analyzers
analyzer.addAnalyzer(new MetadataAnalyzer());      // 20% weight
analyzer.addAnalyzer(new ArtifactAnalyzer());      // 20% weight
analyzer.addAnalyzer(new FrequencyAnalyzer());     // 20% weight
analyzer.addAnalyzer(new WatermarkAnalyzer());     // 20% weight
analyzer.addAnalyzer(new HybridDeepAnalyzer());    // 20% weight

// 3. Load and analyze image
Image image;
image.loadImage("photo.jpg");
FinalResult result = analyzer.running(image);

// 4. Display results
result.displayFullReport();

// 5. Get statistics
analyzer.getProcessStats();
```

### Advanced Usage
```cpp
// Access individual results
for (int i = 0; i < result.getResultCount(); i++) {
    cout << result[i];  // Uses operator[]
}

// Compare multiple images
vector<FinalResult> results;
// ... process multiple images ...
sort(results.begin(), results.end(), 
     [](const FinalResult& a, const FinalResult& b) {
         return a > b;  // Uses operator>
     });

// Modify confidence
FinalResult r;
++r;  // Increment confidence by 0.01 (uses operator++)

// Save results
result.saveToFile("analysis_report.txt");
```

---

## 🎓 OOP Concepts Demonstrated

✅ **Inheritance:** Analyzer hierarchy
✅ **Polymorphism:** Virtual analyze() method
✅ **Encapsulation:** Private/public members
✅ **Abstraction:** Pure virtual functions
✅ **Operator Overloading:** 6+ operators
✅ **Interfaces:** ILoggable contract
✅ **Composition:** ImageAnalyzer → Analyzers
✅ **Aggregation:** FinalResult → AnalysisResults
✅ **Static Members:** analyzerCount
✅ **Friend Functions:** Stream operators

---

## 📊 Performance Characteristics

| Component | Time Complexity | Space |
|-----------|-----------------|-------|
| Image Load | O(n) | O(n) |
| Meta Analysis | O(1) | O(1) |
| Artifact Analysis | O(n) | O(1) |
| Frequency Analysis | O(n log n) | O(n) |
| Watermark Analysis | O(n) | O(1) |
| Hybrid Analysis | O(n log n) | O(n) |
| Score Calculation | O(m) | O(1) |
| **Total** | **O(n log n)** | **O(n)** |

*Where n = image size in pixels, m = number of analyzers*

---

## 🚀 Compilation & Build

### Requirements
- C++17 or later
- G++ compiler (or MSVC/Clang)
- Standard library

### Build Command
```bash
g++ -std=c++17 -O2 -o ai_detector \
    main.cpp Image.cpp Analyzer.cpp \
    AnalysisResult.cpp MetadataAnalyzer.cpp \
    ArtifactAnalyzer.cpp FrequencyAnalyzer.cpp \
    WatermarkAnalyzer.cpp HybridDeepAnalyzer.cpp \
    ImageAnalyzer.cpp HistoryLog.cpp \
    FinalResult.cpp Utils.cpp
```

### Run
```bash
./ai_detector
```

---

## 📈 System Statistics

After processing 3 test images:
```
Total Images Processed: 3
Total Analyzers: 5
Total Analysis Results: 15
Average Confidence: 0.38
Total Log Entries: 50+

Verdict Distribution:
├─ Authentic: 2 images
├─ AI Generated: 0 images
└─ Suspicious: 1 image
```

---

## 🎯 Summary

**What It Does:**
- Analyzes images from 5 different technical perspectives
- Combines results into single confidence score
- Determines if image is AI-generated or authentic

**How It Works:**
- Each analyzer examines different image characteristics
- Independent scoring prevents bias
- Averaging provides robust final verdict

**Why It's Good:**
- Modular: Easy to add new analyzers
- Accurate: Multiple perspectives
- Transparent: Each analyzer explains findings
- Extensible: Built on OOP principles

**Real-World Applications:**
- News media verification
- Social media content authentication
- Copyright detection
- Deepfake identification
- Forensic analysis
