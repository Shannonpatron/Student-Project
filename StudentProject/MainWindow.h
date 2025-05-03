#pragma once

#include "wx/wx.h"
#include "DrawingPanel.h"
#include "Settings.h"

class MainWindow : public wxFrame
{
public:
    MainWindow(); // constructor
    ~MainWindow(); // destructor

private:
    void OnPlay(wxCommandEvent& event); // Play button action
    void OnPause(wxCommandEvent& event); // Pause button action
    void OnStep(wxCommandEvent& event); // Step button action
    void OnClear(wxCommandEvent& event); // Clear grid action
    void OnTimer(wxTimerEvent& event); // Timer event
    void UpdateStatusBar(); // Update the status bar with info

    wxTimer* timer; // Timer for simulations steps
    DrawingPanel* drawingPanel; // Drawing panel that displays the grid
    Settings settings; // settings for grid size, color, etc
    wxToolBar* toolBar; // Toolbar for controls like play, pause
    int generationCount = 0; // Tracks the number of generations

    wxDECLARE_EVENT_TABLE();
};