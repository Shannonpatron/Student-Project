// Implements the DrawingPanel class to manage the visual grid and simulation
#include "DrawingPanel.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint) // Bind paint event to OnPaint method
EVT_LEFT_DOWN(DrawingPanel::OnMouseClick) // Bind mouse click to OnMouseClick method
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, Settings& settingsRef)
    : wxPanel(parent), settings(settingsRef)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT); // Set painting style

    grid.resize(settings.gridSize, std::vector<bool>(settings.gridSize, false)); // Initialized grid with false values
    ant = new LangtonsAnt(settings.gridSize / 2, settings.gridSize / 2); // Place ant in the center of the grid
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear(); // clear the canvas before repainting

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc); // create graphics context from drawing
    if (!gc) return;

    wxSize size = GetSize(); // get the size of the window
    float cellWidth = size.GetWidth() / settings.gridSize; // calculate cell width based on grid size
    float cellHeight = size.GetHeight() / settings.gridSize; // calculate cell height based on grid size

    for (int row = 0; row < settings.gridSize; ++row) // loop over each row
    {
        for (int col = 0; col < settings.gridSize; ++col) // loop over each column
        {
            wxBrush brush = grid[row][col] // set brush color based on cell state
                ? wxBrush(settings.GetLivingCellColor()) // living cell color (black)
                : wxBrush(settings.GetDeadCellColor()); // dead cell color (white)
            gc->SetBrush(brush);
            gc->DrawRectangle(col * cellWidth, row * cellHeight, cellWidth, cellHeight); // draw the cell
        }
    }

    delete gc; // clean up graphics context
}

void DrawingPanel::StepSimulation()
{
    ant->Step(grid); // update the ant's position and grid state
    Refresh(); // refresh the panel to update the drawing
}

void DrawingPanel::ClearGrid()
{
    for (auto& row : grid) // Clear the grid (set all cells to false)
        std::fill(row.begin(), row.end(), false);
    delete ant; // delete the old ant
    ant = new LangtonsAnt(settings.gridSize / 2, settings.gridSize / 2); // reset the ant's position to the center
    Refresh(); // refresh the panel
}

void DrawingPanel::OnMouseClick(wxMouseEvent& event)
{
    wxSize size = GetSize(); // get the size of the window
    int cellWidth = size.GetWidth() / settings.gridSize; // caluclate cell width
    int cellHeight = size.GetHeight() / settings.gridSize; // calculate cell height

    int col = event.GetX() / cellWidth; // get the clicked column
    int row = event.GetY() / cellHeight; // get the clicked row

    if (row >= 0 && row < settings.gridSize && col >= 0 && col < settings.gridSize) // check if click is within grid bounds
    {
        grid[row][col] = !grid[row][col]; // toggle cell state (true/false)
        Refresh(); // refresh the panel to update the drawing
    }
}