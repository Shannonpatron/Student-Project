// Implementing the application entry point and initializing the main window
#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainWindow* mainWin = new MainWindow(); // Created the main window
    mainWin->Show(true); // Show the window
    return true;
}