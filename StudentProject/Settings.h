// Defines the Settings struct that holds configuration options for the Langton's Ant simulation, 
// including cell colors, grid size, and simulation speed. Provides methods to load and save
// these settings from/to a binary file.


#ifndef SETTINGS_H
#define SETTINGS_H

#include <wx/colour.h>
#include <fstream>

struct Settings
{
    // RGBA color components for living cells (default gray)
    unsigned int livingCellRed = 128;
    unsigned int livingCellGreen = 128;
    unsigned int livingCellBlue = 128;
    unsigned int livingCellAlpha = 255;

    // RGBA color components for dead cells (default white)
    unsigned int deadCellRed = 255;
    unsigned int deadCellGreen = 255;
    unsigned int deadCellBlue = 255;
    unsigned int deadCellAlpha = 255;

    // Grid size (number of cells per row/column)
    int gridSize = 15;

    // Timer interval in milliseconds between simulation steps
    int intervalMs = 50;

    // Return wxColour for living cells from RGBA components
    wxColour GetLivingCellColor() const
    {
        return wxColour(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
    }

    // Return wxColour for dead cells from RGBA components
    wxColour GetDeadCellColor() const
    {
        return wxColour(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
    }

    // Set living cell color from wxColour object
    void SetLivingCellColor(const wxColour& c)
    {
        livingCellRed = c.Red();
        livingCellGreen = c.Green();
        livingCellBlue = c.Blue();
        livingCellAlpha = c.Alpha();
    }

    // Set dead cell color from wxColour object
    void SetDeadCellColor(const wxColour& c)
    {
        deadCellRed = c.Red();
        deadCellGreen = c.Green();
        deadCellBlue = c.Blue();
        deadCellAlpha = c.Alpha();
    }

    // Load settings from binary file "settings.bin"
    void LoadSettings()
    {
        std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
        if (file.is_open())
        {
            file.read((char*)this, sizeof(Settings));
            file.close();
        }
    }

    // Save settings to binary file "settings.bin"
    void SaveSettings() const
    {
        std::ofstream file("settings.bin", std::ios::binary | std::ios::out);
        if (file.is_open())
        {
            file.write((char*)this, sizeof(Settings));
            file.close();
        }
    }
};

#endif // SETTINGS_H