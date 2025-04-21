// Implements the MainWindow class and event handling
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
EVT_MENU(ID_Step, MainWindow::OnStep) // Bing Step button to OnStep
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

    drawingPanel = new DrawingPanel(this, settings); // create drawing panel
}

MainWindow::~MainWindow()
{
    delete timer; // clean up timer
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
    timer->Start(settings.timerInterval); // start the timer to begin simulation
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    timer->Stop(); // stop the timer to pause simulations
}

void MainWindow::OnStep(wxCommandEvent& event)
{
    drawingPanel->StepSimulation(); // advance the simulation one step
}

void MainWindow::OnClear(wxCommandEvent& event)
{
    drawingPanel->ClearGrid(); // clear the grid and reset the ant
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    drawingPanel->StepSimulation(); // advance the simulation on timer event
}