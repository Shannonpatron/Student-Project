// Implements main application window functionality for Langton's Ant.

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

// IDs for controls and events
enum
{
    ID_Play = 1,
    ID_Pause,
    ID_Step,
    ID_Clear,
    ID_Timer,
    ID_Settings,
    ID_ResetSettings,
    ID_ImportPattern,  // new ID for Import Pattern
    ID_ToggleHUD,      // new ID for Show HUD menu item
    ID_SaveUniverse = wxID_HIGHEST + 1,
    ID_LoadUniverse
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(ID_Play, MainWindow::OnPlay)
EVT_MENU(ID_Pause, MainWindow::OnPause)
EVT_MENU(ID_Step, MainWindow::OnStep)
EVT_MENU(ID_Clear, MainWindow::OnClear)
EVT_TIMER(ID_Timer, MainWindow::OnTimer)
EVT_MENU(ID_Settings, MainWindow::OnSettings)
EVT_MENU(ID_ResetSettings, MainWindow::OnResetSettings)
EVT_MENU(ID_ImportPattern, MainWindow::OnImportPattern)  // new event
EVT_MENU(ID_ToggleHUD, MainWindow::OnToggleHUD)     
// new event
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Langton's Ant", wxDefaultPosition, wxSize(800, 800)),
    generationCount(0)
{
    settings.LoadSettings();

    timer = new wxTimer(this, ID_Timer);

    // Setup toolbar
    toolBar = CreateToolBar();
    toolBar->AddTool(ID_Play, "Play", wxBitmap(play_xpm), "Start Simulation");
    toolBar->AddTool(ID_Pause, "Pause", wxBitmap(pause_xpm), "Pause Simulation");
    toolBar->AddTool(ID_Step, "Step", wxBitmap(next_xpm), "Advance One Step");
    toolBar->AddTool(ID_Clear, "Clear", wxBitmap(trash_xpm), "Clear Grid");
    toolBar->Realize();
    toolBar->SetSize(wxSize(800, 50));

    // Setup menu
    wxMenuBar* menuBar = new wxMenuBar();

    // File menu with Import Pattern
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(ID_ImportPattern, "Import Pattern...\tCtrl+I", "Import a pattern file");
    menuBar->Append(fileMenu, "File");

    // Options menu with Settings and Reset Settings
    wxMenu* optionsMenu = new wxMenu();
    optionsMenu->Append(ID_Settings, "Settings");
    optionsMenu->Append(ID_ResetSettings, "Reset Settings");
    menuBar->Append(optionsMenu, "Options");

    // View menu with Show HUD option (checkable)
    wxMenu* viewMenu = new wxMenu();
    viewMenu->AppendCheckItem(ID_ToggleHUD, "Show HUD");
    menuBar->Append(viewMenu, "View");

    SetMenuBar(menuBar);

    fileMenu->Append(ID_SaveUniverse, "Save Universe...\tCtrl+S");
    fileMenu->Append(ID_LoadUniverse, "Load Universe...\tCtrl+O");

    // Set initial check state for Show HUD menu item
    menuBar->Check(ID_ToggleHUD, settings.ShowHUD);

    // Create drawing panel for simulation
    drawingPanel = new DrawingPanel(this, settings);

    // Status bar
    CreateStatusBar(2);
    UpdateStatusBar();
    SetStatusText("Ready", 1);
}

MainWindow::~MainWindow()
{
    settings.SaveSettings();
    delete timer;
}

void MainWindow::OnPlay(wxCommandEvent& /*event*/)
{
    timer->Start(settings.intervalMs);
    SetStatusText("Simulation Running", 1);
}

void MainWindow::OnPause(wxCommandEvent& /*event*/)
{
    timer->Stop();
    SetStatusText("Simulation Paused", 1);
}

void MainWindow::OnStep(wxCommandEvent& /*event*/)
{
    drawingPanel->StepSimulation();
    ++generationCount;
    UpdateStatusBar();
}

void MainWindow::OnClear(wxCommandEvent& /*event*/)
{
    drawingPanel->ClearGrid();
    generationCount = 0;
    UpdateStatusBar();
    SetStatusText("Ready", 1);
}

void MainWindow::OnTimer(wxTimerEvent& /*event*/)
{
    drawingPanel->StepSimulation();
    ++generationCount;
    UpdateStatusBar();
}

void MainWindow::OnSettings(wxCommandEvent& /*event*/)
{
    settings.LoadSettings();

    SettingsDialog dlg(this, wxID_ANY, "Settings", &settings);
    if (dlg.ShowModal() == wxID_OK)
    {
        if (timer->IsRunning())
            timer->Start(settings.intervalMs);

        drawingPanel->UpdateSettings(settings);
        drawingPanel->Refresh();

        settings.SaveSettings();

        // Update status bar in case ShowHUD changed
        UpdateStatusBar();

        // Update HUD menu check state
        GetMenuBar()->Check(ID_ToggleHUD, settings.ShowHUD);
    }
}

void MainWindow::OnResetSettings(wxCommandEvent& /*event*/)
{
    timer->Stop();
    settings.ResetToDefaults();
    settings.SaveSettings();

    drawingPanel->UpdateSettings(settings);
    drawingPanel->ClearGrid();

    generationCount = 0;
    UpdateStatusBar();
    drawingPanel->Refresh();

    // Update HUD menu check state
    GetMenuBar()->Check(ID_ToggleHUD, settings.ShowHUD);

    SetStatusText("Settings reset to default", 1);
}

void MainWindow::OnImportPattern(wxCommandEvent& /*event*/)
{
    wxFileDialog openFileDialog(this, _("Open pattern file"), "", "",
        "Pattern files (*.txt;*.pat)|*.txt;*.pat|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // user cancelled

    wxString path = openFileDialog.GetPath();

    if (!drawingPanel->ImportPatternFromFile(path))
    {
        wxMessageBox("Failed to load pattern from file.", "Error", wxOK | wxICON_ERROR);
    }
}

void MainWindow::OnToggleHUD(wxCommandEvent& /*event*/)
{
    // Toggle ShowHUD setting and save
    settings.ShowHUD = !settings.ShowHUD;
    settings.SaveSettings();

    // Update menu check state to reflect new value
    GetMenuBar()->Check(ID_ToggleHUD, settings.ShowHUD);

    // Refresh drawing panel to show/hide HUD
    drawingPanel->Refresh();

    // Update status bar display
    UpdateStatusBar();
}

void MainWindow::UpdateStatusBar()
{
    if (settings.ShowHUD)
    {
        SetStatusText("Generation: " + std::to_string(generationCount), 0);
    }
    else
    {
        SetStatusText("", 0);
    }
}