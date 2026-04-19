#ifndef ILOGGABLE_H
#define ILOGGABLE_H

#include <string>
using namespace std;

// Interface for logging activities
class ILoggable {
public:
    virtual ~ILoggable() {}
    
    // Log an activity with a message
    virtual void logActivity(string msg) = 0;
};

#endif
