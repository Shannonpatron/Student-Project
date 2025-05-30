// App.cpp – This is the starting point of the app. It creates and shows the main window.

#include "App.h"
#include "MainWindow.h"
#include "Utilities.h"  // Used for memory leak detection

wxIMPLEMENT_APP(App); // This macro starts the wxWidgets app using the App class

bool App::OnInit()
{
    ENABLE_LEAK_DETECTION();  // Turns on memory leak checking when the app starts

    // Create the main window
    MainWindow* mainWin = new MainWindow();

    // Show the main window on the screen
    mainWin->Show(true);

    return true; // Returning true tells wxWidgets to continue running
}