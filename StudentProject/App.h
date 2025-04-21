// Defining the main application class from wxWidgets
// Inherits from wxApp and overrides OnInit to initialize the application
#pragma once
#include "wx/wx.h"

class App : public wxApp
{
public:
    virtual bool OnInit(); // Initialized the main window
};