// SettingsDialog.cpp
// Implements the settings dialog for Langton's Ant simulation.
// Allows users to customize cell colors, grid size, and timer interval.
// Updates the Settings struct when confirmed.

#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOkButtonClick)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancelButtonClick)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, wxWindowID id, const wxString& title, Settings* settingsPtr)
    : wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize),
    settings(settingsPtr)
{
    // Main vertical sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Living Cell Color picker row
    {
        wxBoxSizer* livingColorSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* label = new wxStaticText(this, wxID_ANY, "Living Cell Color:");
        livingColorSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

        // Initialize color picker with current setting
        wxColour initialColor(settings->livingCellRed, settings->livingCellGreen,
            settings->livingCellBlue, settings->livingCellAlpha);
        livingCellColorPicker = new wxColourPickerCtrl(this, wxID_ANY, initialColor);
        livingColorSizer->Add(livingCellColorPicker, 1, wxEXPAND);

        mainSizer->Add(livingColorSizer, 0, wxEXPAND | wxALL, 5);
    }

    // Dead Cell Color picker row
    {
        wxBoxSizer* deadColorSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* label = new wxStaticText(this, wxID_ANY, "Dead Cell Color:");
        deadColorSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

        wxColour initialColor(settings->deadCellRed, settings->deadCellGreen,
            settings->deadCellBlue, settings->deadCellAlpha);
        deadCellColorPicker = new wxColourPickerCtrl(this, wxID_ANY, initialColor);
        deadColorSizer->Add(deadCellColorPicker, 1, wxEXPAND);

        mainSizer->Add(deadColorSizer, 0, wxEXPAND | wxALL, 5);
    }

    // Grid Size input row
    {
        wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* label = new wxStaticText(this, wxID_ANY, "Grid Size:");
        gridSizeSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

        gridSizeSpinCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1));
        gridSizeSpinCtrl->SetRange(1, 100); // Acceptable grid size range
        gridSizeSpinCtrl->SetValue(settings->gridSize);
        gridSizeSizer->Add(gridSizeSpinCtrl, 0);

        mainSizer->Add(gridSizeSizer, 0, wxEXPAND | wxALL, 5);
    }

    // Timer Interval input row (in milliseconds)
    {
        wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* label = new wxStaticText(this, wxID_ANY, "Interval (ms):");
        intervalSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

        intervalSpinCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1));
        intervalSpinCtrl->SetRange(10, 1000); // Reasonable interval range
        intervalSpinCtrl->SetValue(settings->intervalMs);
        intervalSizer->Add(intervalSpinCtrl, 0);

        mainSizer->Add(intervalSizer, 0, wxEXPAND | wxALL, 5);
    }

    // Add standard OK and Cancel buttons
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);

    SetSizerAndFit(mainSizer);
}

// When OK clicked: save changes back to settings and close dialog
void SettingsDialog::OnOkButtonClick(wxCommandEvent& WXUNUSED(event))
{
    wxColour livingColor = livingCellColorPicker->GetColour();
    settings->livingCellRed = livingColor.Red();
    settings->livingCellGreen = livingColor.Green();
    settings->livingCellBlue = livingColor.Blue();
    settings->livingCellAlpha = livingColor.Alpha();

    wxColour deadColor = deadCellColorPicker->GetColour();
    settings->deadCellRed = deadColor.Red();
    settings->deadCellGreen = deadColor.Green();
    settings->deadCellBlue = deadColor.Blue();
    settings->deadCellAlpha = deadColor.Alpha();

    settings->gridSize = gridSizeSpinCtrl->GetValue();
    settings->intervalMs = intervalSpinCtrl->GetValue();

    EndModal(wxID_OK);
}

// When Cancel clicked: discard changes and close dialog
void SettingsDialog::OnCancelButtonClick(wxCommandEvent& WXUNUSED(event))
{
    EndModal(wxID_CANCEL);
}