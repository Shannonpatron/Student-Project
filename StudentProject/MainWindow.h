// Defines the main application window.
// Handles UI elements like toolbar and simulation controls,
// contains the drawing panel for Langton's Ant simulation,
// and manages the timer for automatic simulation steps.

#pragma once

#include <wx/wx.h>
#include <wx/timer.h>
#include "DrawingPanel.h"
#include "Settings.h"   // Settings struct for simulation parameters
#include "Utilities.h"

class MainWindow : public wxFrame
{
public:
    MainWindow();   // Constructor: set up UI and initialize components
    ~MainWindow();  // Destructor: clean up resources

private:
    // Simulation control event handlers
    void OnPlay(wxCommandEvent& event);    // Start the simulation timer
    void OnPause(wxCommandEvent& event);   // Stop the simulation timer
    void OnStep(wxCommandEvent& event);    // Advance simulation by one step
    void OnClear(wxCommandEvent& event);   // Clear the simulation grid
    void OnTimer(wxTimerEvent& event);     // Timer event: update simulation step

    void OnImportPattern(wxCommandEvent& event);

    // Settings dialog handlers
    void OnSettings(wxCommandEvent& event);       // Open settings dialog
    void OnResetSettings(wxCommandEvent& event);  // Reset settings to default

    // HUD related handler
    void OnToggleHUD(wxCommandEvent& event);      // Toggle HUD visibility

    void UpdateStatusBar();  // Update status bar with current generation count

    // UI components
    wxToolBar* toolBar = nullptr;          // Toolbar with control buttons
    DrawingPanel* drawingPanel = nullptr;  // Panel where grid and ant are drawn
    wxTimer* timer = nullptr;              // Timer for automatic simulation steps

    // Simulation state
    int generationCount = 0;  // Tracks number of simulation steps taken

    // Configuration
    Settings settings;  // Holds current simulation settings

    wxDECLARE_EVENT_TABLE();
};