// Defines the main application window.
// Handles user interface elements like toolbar and simulation controls,
// contains the drawing panel for the Langton's Ant simulation,
// and manages the timer for automatic simulation steps.

#pragma once

#include "wx/wx.h"
#include "DrawingPanel.h"
#include "Settings.h"   // Settings struct for simulation parameters
#include "Utilities.h"

class MainWindow : public wxFrame
{
public:
    MainWindow();  // Constructor to set up UI and initialize components
    ~MainWindow(); // Destructor to clean up resources

private:
    void OnPlay(wxCommandEvent& event);   // Starts the simulation timer
    void OnPause(wxCommandEvent& event);  // Stops the simulation timer
    void OnStep(wxCommandEvent& event);   // Advances simulation by one step
    void OnClear(wxCommandEvent& event);  // Clears the simulation grid
    void OnTimer(wxTimerEvent& event);    // Called on each timer tick to update simulation

    void OnSettings(wxCommandEvent& event); // Opens settings dialog to adjust parameters

    void UpdateStatusBar();  // Updates the status bar with current generation count

    wxToolBar* toolBar = nullptr;       // Toolbar with control buttons
    DrawingPanel* drawingPanel = nullptr; // Panel where the grid and ant are drawn
    wxTimer* timer = nullptr;            // Timer to run simulation steps automatically

    int generationCount = 0;             // Tracks number of simulation steps taken

    Settings settings;  // Holds current simulation settings

    wxDECLARE_EVENT_TABLE();
};