#pragma once
#include "wx/wx.h"
#include "Settings.h"
#include "LangtonsAnt.h"

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent, Settings& settings); // constructor
    void StepSimulation(); // advances the simulation one step
    void ClearGrid(); // clears the grid and resets the ant

private:
    void OnPaint(wxPaintEvent& event); // handles painting of the grid
    void OnMouseClick(wxMouseEvent& event); // handles mouse click on the grid

    std::vector<std::vector<bool>> grid; // 2D grid of cells (true or false)
    Settings& settings; // reference to settings (grid size, colors, etc.)
    LangtonsAnt* ant; // the langtons ant object

    wxDECLARE_EVENT_TABLE();
};