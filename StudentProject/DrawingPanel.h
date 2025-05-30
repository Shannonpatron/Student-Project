// This header defines the DrawingPanel class, which handles rendering 
// and interaction logic for the cellular automaton grid, including 
// simulation steps, mouse input, neighbor counting, and HUD display. 
// It also manages file import/export for universe and pattern data.

#pragma once

#include <wx/wx.h>
#include <vector>
#include "Settings.h"
#include "LangtonsAnt.h"
#include <wx/filedlg.h>
#include <fstream>


const int ID_SAVE_UNIVERSE = wxID_HIGHEST + 1;
const int ID_IMPORT_PATTERN = wxID_HIGHEST + 2;

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent, const Settings& settingsRef);
    ~DrawingPanel();

    void StepSimulation();
    void ClearGrid();
    void UpdateSettings(const Settings& newSettings);
    void SetShowNeighborCount(bool show);

    bool ImportPatternFromFile(const wxString& filename);

private:
    void OnPaint(wxPaintEvent& event);
    void OnMouseClick(wxMouseEvent& event);
    void OnImportPattern(wxCommandEvent& event);

    void UpdateNeighborCounts();

    void OnSaveUniverse(wxCommandEvent& event);
    void OnLoadUniverse(wxCommandEvent& event);

    bool SaveUniverse(const wxString& filename);
    bool LoadUniverse(const wxString& filename);

    // New helper to draw the HUD
    void DrawHUD(wxPaintDC& dc);

    Settings settings;
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<int>> neighborCounts;
    LangtonsAnt* ant;
    bool showNeighborCount;

    wxDECLARE_EVENT_TABLE();

    // Optional: prevent copying
    DrawingPanel(const DrawingPanel&) = delete;
    DrawingPanel& operator=(const DrawingPanel&) = delete;


};