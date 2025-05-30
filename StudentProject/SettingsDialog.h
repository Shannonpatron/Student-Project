// Defines a dialog window to edit and update simulation settings,
// including cell colors, grid size, and timer interval.
// Updates the Settings struct through user interaction.

#pragma once
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include "Settings.h"  // Include your Settings struct header


class SettingsDialog : public wxDialog
{
public:
    // Constructor takes parent window, ID, title, and pointer to Settings struct
    SettingsDialog(wxWindow* parent, wxWindowID id, const wxString& title, Settings* settingsPtr);

private:
    Settings* settings;  // Pointer to Settings object to modify

    // UI Controls for editing settings
    wxColourPickerCtrl* livingCellColorPicker; // Living cell color selector
    wxColourPickerCtrl* deadCellColorPicker;   // Dead cell color selector
    wxSpinCtrl* gridSizeSpinCtrl;               // Grid size input
    wxSpinCtrl* intervalSpinCtrl;               // Timer interval input

    // Event handlers for dialog buttons
    void OnOkButtonClick(wxCommandEvent& event);
    void OnCancelButtonClick(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // SETTINGSDIALOG_H
