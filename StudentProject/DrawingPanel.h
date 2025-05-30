// This file defines the custom panel where the grid and ant are drawn.
// It handles drawing, simulation steps, and mouse interaction.

#pragma once

#include "wx/wx.h"
#include "Settings.h"
#include <vector>

class LangtonsAnt;  // Forward declaration for the ant logic

class DrawingPanel : public wxPanel
{
public:
    // Constructor – takes in settings and stores a copy
    DrawingPanel(wxWindow* parent, const Settings& settings);

    ~DrawingPanel();  // Cleans up the dynamically created ant

    // Moves the simulation forward by one step
    void StepSimulation();

    // Clears the grid and resets the simulation
    void ClearGrid();

    // Updates the settings when user changes them
    void UpdateSettings(const Settings& newSettings);

    // Updates the neighbor count for each cell
    void UpdateNeighborCounts();

    // Turns on/off the display of neighbor numbers
    void SetShowNeighborCount(bool show);

private:
    Settings settings;  // Local copy of the settings

    std::vector<std::vector<bool>> grid;  // Stores the grid state (on/off cells)
    std::vector<std::vector<int>> neighborCounts;  // Stores neighbor counts per cell

    LangtonsAnt* ant = nullptr;  // Pointer to the ant object

    bool showNeighborCount = false;  // Controls whether neighbor numbers are drawn

    // Handles drawing the panel when refreshed
    void OnPaint(wxPaintEvent& event);

    // Handles mouse clicks to toggle cells manually
    void OnMouseClick(wxMouseEvent& event);

    wxDECLARE_EVENT_TABLE();  // Required for custom event handling
};