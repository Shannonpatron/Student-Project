// This file sets up the main application class and handles startup

#include "wx/wx.h"

// Main application class
class App : public wxApp
{
public:
    // Called when the program starts
    // I use this to create and show the main window
    virtual bool OnInit();
};