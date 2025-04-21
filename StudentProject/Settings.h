// Defines the settings structure to hold grid size and timer interval
#pragma once
#include "wx/colour.h"

struct Settings
{
    int gridSize = 50; // Grid size 
    int timerInterval = 100; // Timer interval in milliseconds

    wxColour GetLivingCellColor() const { return wxColour(0, 0, 0); } // get color for living cell (black)
    wxColour GetDeadCellColor() const { return wxColour(255, 255, 255); } // get color for dead cell (white)
}; 