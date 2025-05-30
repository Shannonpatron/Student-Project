// Implements the main application window functionality,
// handling user interactions and driving the Langton's Ant simulation.
// Manages toolbar, menu commands, timer events, and status updates.

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

// IDs for toolbar buttons, timer, and menu items
enum
{
    ID_Play = 1,
    ID_Pause,
    ID_Step,
    ID_Clear,
    ID_Timer,
    ID_Settings
};

// Event table linking events to handler functions
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(ID_Play, MainWindow::OnPlay)
EVT_MENU(ID_Pause, MainWindow::OnPause)
EVT_MENU(ID_Step, MainWindow::OnStep)
EVT_MENU(ID_Clear, MainWindow::OnClear)
EVT_TIMER(ID_Timer, MainWindow::OnTimer)
EVT_MENU(ID_Settings, MainWindow::OnSettings)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Langton's Ant", wxDefaultPosition, wxSize(800, 800))
{
    // Load saved simulation settings on startup
    settings.LoadSettings();

    // Create timer for running the simulation automatically
    timer = new wxTimer(this, ID_Timer);

    // Setup toolbar with play, pause, step, and clear buttons
    toolBar = CreateToolBar();
    toolBar->AddTool(ID_Play, "Play", wxBitmap(play_xpm), "Start the simulation");
    toolBar->AddTool(ID_Pause, "Pause", wxBitmap(pause_xpm), "Pause the simulation");
    toolBar->AddTool(ID_Step, "Step", wxBitmap(next_xpm), "Advance one step");
    toolBar->AddTool(ID_Clear, "Clear", wxBitmap(trash_xpm), "Clear the grid");
    toolBar->Realize();
    toolBar->SetSize(wxSize(800, 50));

    // Create menu with settings option
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* optionsMenu = new wxMenu();
    optionsMenu->Append(ID_Settings, "Settings");
    menuBar->Append(optionsMenu, "Options");
    SetMenuBar(menuBar);

    // Create the drawing panel where the simulation runs
    drawingPanel = new DrawingPanel(this, settings);

    // Create status bar with two sections
    CreateStatusBar(2);
    SetStatusText("Generation: 0", 0);
    SetStatusText("Ready", 1);

    generationCount = 0;
}

MainWindow::~MainWindow()
{
    // Save settings before closing
    settings.SaveSettings();
    delete timer;
}

// Start the simulation timer
void MainWindow::OnPlay(wxCommandEvent& event)
{
    timer->Start(settings.intervalMs);
    SetStatusText("Simulation Running", 1);
}

// Stop the simulation timer
void MainWindow::OnPause(wxCommandEvent& event)
{
    timer->Stop();
    SetStatusText("Simulation Paused", 1);
}

// Advance simulation by one step manually
void MainWindow::OnStep(wxCommandEvent& event)
{
    drawingPanel->StepSimulation();
    generationCount++;
    SetStatusText("Generation: " + std::to_string(generationCount), 0);
}

// Clear the grid and reset generation count
void MainWindow::OnClear(wxCommandEvent& event)
{
    drawingPanel->ClearGrid();
    generationCount = 0;
    SetStatusText("Generation: 0", 0);
    SetStatusText("Ready", 1);
}

// Called on each timer tick to advance simulation automatically
void MainWindow::OnTimer(wxTimerEvent& event)
{
    drawingPanel->StepSimulation();
    generationCount++;
    SetStatusText("Generation: " + std::to_string(generationCount), 0);
}

// Open the settings dialog to adjust simulation parameters
void MainWindow::OnSettings(wxCommandEvent& WXUNUSED(event))
{
    // Reload current settings in case user canceled last time
    settings.LoadSettings();

    SettingsDialog dlg(this, wxID_ANY, "Settings", &settings);

    if (dlg.ShowModal() == wxID_OK)
    {
        // If timer is running, restart it with new interval
        if (timer->IsRunning())
        {
            timer->Start(settings.intervalMs);
        }

        // Apply settings to drawing panel and refresh display
        drawingPanel->UpdateSettings(settings);
        drawingPanel->Refresh();

        // Save updated settings
        settings.SaveSettings();
    }
}

// Update status bar with current generation count
void MainWindow::UpdateStatusBar()
{
    SetStatusText("Generation: " + std::to_string(generationCount), 0);
}