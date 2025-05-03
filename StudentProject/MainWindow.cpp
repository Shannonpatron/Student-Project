#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

enum
{
    ID_Play = 1,
    ID_Pause,
    ID_Step,
    ID_Clear,
    ID_Timer
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(ID_Play, MainWindow::OnPlay) // Bind play button to OnPlay
EVT_MENU(ID_Pause, MainWindow::OnPause) // Bind Pause button OnPause
EVT_MENU(ID_Step, MainWindow::OnStep) // Bind Step button to OnStep
EVT_MENU(ID_Clear, MainWindow::OnClear) // Bind Clear button to OnClear
EVT_TIMER(ID_Timer, MainWindow::OnTimer) // Bind Timer event to OnTimer
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Langton's Ant", wxDefaultPosition, wxSize(800, 800))
{
    timer = new wxTimer(this, ID_Timer); // Create timer for simulation

    // Create and set up the toolbar
    toolBar = CreateToolBar();
    toolBar->AddTool(ID_Play, "Play", wxBitmap(play_xpm), "Start the simulation");
    toolBar->AddTool(ID_Pause, "Pause", wxBitmap(pause_xpm), "Pause the simulation");
    toolBar->AddTool(ID_Step, "Step", wxBitmap(next_xpm), "Advance one step");
    toolBar->AddTool(ID_Clear, "Clear", wxBitmap(trash_xpm), "Clear the grid");

    // Finalize toolbar setup
    toolBar->Realize();

    // Set the size of the toolbar 
    toolBar->SetSize(wxSize(800, 50)); // Example size: 800px width, 50px height

    drawingPanel = new DrawingPanel(this, settings); // create drawing panel and pass settings

    // Initialize status bar
    CreateStatusBar(2); // Create a status bar with two fields
    SetStatusText("Generation: 0", 0); // Set initial text in the first field
    SetStatusText("Ready", 1); // Set initial status in the second field
}

MainWindow::~MainWindow()
{
    delete timer; // clean up timer
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
    timer->Start(settings.timerInterval); // start the timer to begin simulation
    SetStatusText("Simulation Running", 1); // Update status bar to show simulation status
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    timer->Stop(); // stop the timer to pause simulations
    SetStatusText("Simulation Paused", 1); // Update status bar to show paused status
}

void MainWindow::OnStep(wxCommandEvent& event)
{
    drawingPanel->StepSimulation(); // advance the simulation one step
    generationCount++; // Increment the generation count
    SetStatusText("Generation: " + std::to_string(generationCount), 0); // Update generation count on status bar
}

void MainWindow::OnClear(wxCommandEvent& event)
{
    drawingPanel->ClearGrid(); // clear the grid and reset the ant
    generationCount = 0; // Reset generation count
    SetStatusText("Generation: 0", 0); // Reset generation count on status bar
    SetStatusText("Ready", 1); // Reset status to "Ready"
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    drawingPanel->StepSimulation(); // advance the simulation on timer event
    generationCount++; // Increment generation count
    SetStatusText("Generation: " + std::to_string(generationCount), 0); // Update generation count on status bar
}

void MainWindow::UpdateStatusBar()
{
    SetStatusText("Generation: " + std::to_string(generationCount), 0); // Update generation number
}