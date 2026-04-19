#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <string>
#include <vector>
using namespace std;

class MenuSystem {
private:
    bool isRunning;
    
    // Menu display functions
    void displayMainMenu();
    void displayAnalysisMenu();
    void displaySearchMenu();
    void displayDataManagementMenu();
    void displayReportsMenu();
    
public:
    MenuSystem();
    ~MenuSystem();
    
    // Main menu loop
    void run();
    
    // Get menu options
    int getMainMenuChoice();
    int getAnalysisMenuChoice();
    int getSearchMenuChoice();
    int getDataManagementMenuChoice();
    int getReportsMenuChoice();
    
    // Menu handlers
    void handleMainMenu(int choice);
    void handleAnalysisMenu(int choice);
    void handleSearchMenu(int choice);
    void handleDataManagementMenu(int choice);
    void handleReportsMenu(int choice);
    
    // Setter
    void setRunning(bool running) { isRunning = running; }
    bool getRunning() const { return isRunning; }
};

#endif
