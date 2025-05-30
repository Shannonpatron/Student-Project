// This file handles how the panel looks and reacts. 
// It draws the grid, handles mouse clicks, and runs the simulation steps.

#include "DrawingPanel.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"
#include "LangtonsAnt.h"  // Includes the ant simulation logic
#include <fstream>
#include <sstream>


// Paint, mouse click, and import pattern events to the corresponding functions
wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_DOWN(DrawingPanel::OnMouseClick)
EVT_MENU(ID_IMPORT_PATTERN, DrawingPanel::OnImportPattern)   // Added import pattern event
EVT_MENU(ID_SAVE_UNIVERSE, DrawingPanel::OnSaveUniverse)    // Save universe event
wxEND_EVENT_TABLE()

// Constructor – sets up grid, neighbor counts, and places the ant in the center
DrawingPanel::DrawingPanel(wxWindow* parent, const Settings& settingsRef)
    : wxPanel(parent), settings(settingsRef), showNeighborCount(false)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT); // Enables smoother drawing

    grid.resize(settings.gridSize, std::vector<bool>(settings.gridSize, false)); // All cells start off
    neighborCounts.resize(settings.gridSize, std::vector<int>(settings.gridSize, 0)); // All counts zero

    ant = new LangtonsAnt(settings.gridSize / 2, settings.gridSize / 2); // Ant starts in the center
}

// Destructor – clean up memory
DrawingPanel::~DrawingPanel()
{
    delete ant;
}

// Paint event – handles all the drawing on the screen
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);  // Prevents flickering
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc); // Use graphics context for smooth shapes
    if (!gc) return;

    wxSize size = GetSize();
    float cellWidth = static_cast<float>(size.GetWidth()) / settings.gridSize;
    float cellHeight = static_cast<float>(size.GetHeight()) / settings.gridSize;

    // Loop through the grid and draw each cell
    for (int row = 0; row < settings.gridSize; ++row)
    {
        for (int col = 0; col < settings.gridSize; ++col)
        {
            // Pick color based on if the cell is alive or dead
            wxBrush brush = grid[row][col]
                ? wxBrush(settings.GetLivingCellColor())
                : wxBrush(settings.GetDeadCellColor());

            gc->SetBrush(brush);
            gc->DrawRectangle(col * cellWidth, row * cellHeight, cellWidth, cellHeight);

            // If neighbor counts are shown, draw them in red
            if (showNeighborCount && neighborCounts[row][col] > 0)
            {
                wxString text = wxString::Format("%d", neighborCounts[row][col]);
                dc.SetFont(wxFontInfo(16));
                dc.SetTextForeground(*wxRED);

                int textWidth, textHeight;
                dc.GetTextExtent(text, &textWidth, &textHeight);

                int x = static_cast<int>(col * cellWidth + (cellWidth - textWidth) / 2);
                int y = static_cast<int>(row * cellHeight + (cellHeight - textHeight) / 2);

                dc.DrawText(text, x, y);
            }
        }
    }

    // HUD Drawing
    if (settings.ShowHUD)  // ShowHUD controls if HUD is displayed
    {
        // Set font size, bold, color 
        dc.SetFont(wxFontInfo(16).Bold());
        dc.SetTextForeground(*wxRED);

        wxString hudText;
        // Add universe size info (grid size)
        hudText << "Universe Size: " << settings.gridSize;

        int textWidth, textHeight;
        dc.GetTextExtent(hudText, &textWidth, &textHeight);

        // Position at lower left corner, with a small margin
        int margin = 10;
        int x = margin;
        int y = size.GetHeight() - textHeight - margin;

        dc.DrawText(hudText, x, y);
    }

    delete gc;
}

// Steps the simulation forward and redraws
void DrawingPanel::StepSimulation()
{
    ant->Step(grid);           // Move the ant and update the grid
    UpdateNeighborCounts();    // Update neighbor numbers
    Refresh();                 // Trigger a redraw
}

// Clears everything and resets the ant
void DrawingPanel::ClearGrid()
{
    for (auto& row : grid)
        std::fill(row.begin(), row.end(), false); // Turn off all cells

    delete ant;
    ant = new LangtonsAnt(settings.gridSize / 2, settings.gridSize / 2); // Reset ant to center

    for (auto& row : neighborCounts)
        std::fill(row.begin(), row.end(), 0); // Clear neighbor counts

    Refresh();
}

// Handles mouse click – toggles cell state
void DrawingPanel::OnMouseClick(wxMouseEvent& event)
{
    wxSize size = GetSize();
    int cellWidth = size.GetWidth() / settings.gridSize;
    int cellHeight = size.GetHeight() / settings.gridSize;

    int col = event.GetX() / cellWidth;
    int row = event.GetY() / cellHeight;

    if (row >= 0 && row < settings.gridSize && col >= 0 && col < settings.gridSize)
    {
        grid[row][col] = !grid[row][col]; // Flip the cell state
        UpdateNeighborCounts();           // Update neighbors accordingly
        Refresh();
    }
}

// Updates settings when changed and resets the grid and ant
void DrawingPanel::UpdateSettings(const Settings& newSettings)
{
    settings = newSettings;
    grid.resize(settings.gridSize, std::vector<bool>(settings.gridSize, false));
    neighborCounts.resize(settings.gridSize, std::vector<int>(settings.gridSize, 0));

    delete ant;
    ant = new LangtonsAnt(settings.gridSize / 2, settings.gridSize / 2);

    Refresh();
}

// Loops through each cell and counts how many living neighbors it has
void DrawingPanel::UpdateNeighborCounts()
{
    int n = settings.gridSize;

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            int count = 0;
            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    if (dr == 0 && dc == 0)
                        continue;

                    int r = row + dr;
                    int c = col + dc;

                    if (r >= 0 && r < n && c >= 0 && c < n && grid[r][c])
                        count++;
                }
            }
            neighborCounts[row][col] = count;
        }
    }
}

// Enables or disables the neighbor count display
void DrawingPanel::SetShowNeighborCount(bool show)
{
    showNeighborCount = show;
    Refresh(); // Redraw to reflect change
}

// Import a pattern from file and place it centered on the existing grid without resizing
bool DrawingPanel::ImportPatternFromFile(const wxString& filename)
{
    std::ifstream file(filename.ToStdString());
    if (!file.is_open())
        return false;

    std::vector<std::vector<bool>> pattern;
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<bool> rowPattern;
        for (char ch : line)
        {
            if (ch == '1' || ch == 'X' || ch == '*')
                rowPattern.push_back(true);
            else if (ch == '0' || ch == '.' || ch == ' ')
                rowPattern.push_back(false);
            // Ignore other characters
        }
        if (!rowPattern.empty())
            pattern.push_back(rowPattern);
    }
    file.close();

    if (pattern.empty())
        return false;

    int patternRows = static_cast<int>(pattern.size());
    int patternCols = static_cast<int>(pattern[0].size());

    int gridSize = settings.gridSize;

    // Calculate top-left corner to center the pattern in the grid
    int startRow = (gridSize - patternRows) / 2;
    int startCol = (gridSize - patternCols) / 2;

    // Clear current grid cells that will be overwritten
    for (int r = 0; r < gridSize; ++r)
    {
        for (int c = 0; c < gridSize; ++c)
        {
            if (r >= startRow && r < startRow + patternRows &&
                c >= startCol && c < startCol + patternCols)
            {
                grid[r][c] = false; // reset before importing
            }
        }
    }

    // Copy pattern into grid without resizing grid
    for (int r = 0; r < patternRows; ++r)
    {
        for (int c = 0; c < patternCols; ++c)
        {
            int gridR = startRow + r;
            int gridC = startCol + c;
            if (gridR >= 0 && gridR < gridSize && gridC >= 0 && gridC < gridSize)
            {
                grid[gridR][gridC] = pattern[r][c];
            }
        }
    }

    UpdateNeighborCounts();
    Refresh();

    return true;
}

// Handles menu command to import a pattern
void DrawingPanel::OnImportPattern(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open Pattern file"), "", "",
        "Pattern files (*.txt;*.pattern)|*.txt;*.pattern|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    ImportPatternFromFile(openFileDialog.GetPath());
}

// Handles menu command to save the current universe state to a file
void DrawingPanel::OnSaveUniverse(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save Universe file"), "", "",
        "Universe files (*.uni)|*.uni|All files (*.*)|*.*",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // User cancelled save

    SaveUniverse(saveFileDialog.GetPath());
}

// Saves the current grid to the specified file path
bool DrawingPanel::SaveUniverse(const wxString& filePath)
{
    std::ofstream file(filePath.ToStdString(), std::ios::binary);
    if (!file.is_open())
        return false;

    int n = settings.gridSize;
    file.write(reinterpret_cast<const char*>(&n), sizeof(n));

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            char cell = grid[row][col] ? 1 : 0;
            file.write(&cell, sizeof(cell));
        }
    }
    file.close();
    return true;
}


   
