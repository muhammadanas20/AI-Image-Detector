#include "results/AnalysisResult.h"
#include <ctime>
#include <iomanip>

AnalysisResult::AnalysisResult(double s, string r, string name) 
    : score(s), reason(r), analyzerName(name) {
    
    // Get current timestamp
    time_t now = time(0);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    timestamp = string(buffer);
}

AnalysisResult::~AnalysisResult() {
    // Cleanup if needed
}

void AnalysisResult::setScores(double s, string r) {
    score = s;
    reason = r;
}

void AnalysisResult::displayResult() const {
    cout << fixed << setprecision(2);
    cout << "\n  Analyzer: " << analyzerName << endl;
    cout << "  Score: " << score << " (0.0 = Real, 1.0 = AI)" << endl;
    cout << "  Reason: " << reason << endl;
    cout << "  Time: " << timestamp << endl;
}

bool AnalysisResult::operator<(const AnalysisResult& other) const {
    return this->score < other.score;
}

bool AnalysisResult::operator==(const AnalysisResult& other) const {
    return this->score == other.score && this->analyzerName == other.analyzerName;
}

ostream& operator<<(ostream& out, const AnalysisResult& result) {
    out << fixed << setprecision(2);
    out << "[" << result.analyzerName << "] Score: " << result.score;
    out << " - " << result.reason;
    return out;
}

istream& operator>>(istream& in, AnalysisResult& result) {
    cout << "Enter analyzer name: ";
    in >> result.analyzerName;
    cout << "Enter score (0-1): ";
    in >> result.score;
    cout << "Enter reason: ";
    in.ignore();
    getline(in, result.reason);
    return in;
}
