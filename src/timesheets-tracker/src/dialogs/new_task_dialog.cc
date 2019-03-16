//  TimesheetsTracker is a desktop that aids you in tracking your timesheets
//  and seeing what work you have done.
//
//  Copyright(C) <2018> <Szymon Welgus>
//
//  This program is free software : you can redistribute it and /
//  or modify it under the terms of the GNU General Public License as published
//  by the Free Software Foundation
//  , either version 3 of the License
//  , or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful
//  , but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "new_task_dialog.hh"
#include <wx/timectrl.h>

namespace app::dialog
{
wxIMPLEMENT_DYNAMIC_CLASS(new_task_dialog, wxDialog);

wxBEGIN_EVENT_TABLE(new_task_dialog, wxDialog)
    EVT_BUTTON(SaveTaskId, new_task_dialog::on_save)
    EVT_BUTTON(wxID_CANCEL, new_task_dialog::on_cancel)
wxEND_EVENT_TABLE()

new_task_dialog::new_task_dialog(wxWindow* parent, const wxString& name)
{
    bool success = create(parent,
        wxID_ANY,
        wxT("Add a New Task"),
        wxDefaultPosition,
        wxSize(400, 300),
        wxCAPTION | wxCLOSE_BOX,
        name);

    SetMinClientSize(wxSize(320, 240));
}

new_task_dialog::~new_task_dialog()
{
    Destroy();
}

bool new_task_dialog::create(wxWindow* parent,
    wxWindowID windowId,
    const wxString& title,
    const wxPoint& point,
    const wxSize& size,
    long style,
    const wxString& name)
{
    bool created = wxDialog::Create(parent,
        windowId,
        title,
        point,
        size,
        style,
        name);

    if (created) {
        create_controls();

        Centre();
        ShowModal();
    }

    return created;
}

void new_task_dialog::create_controls()
{
    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxTOP | wxBOTTOM, 10);
    auto okButton = new wxButton(this, SaveTaskId, wxT("&Save"));
    buttonSizer->Add(okButton, 1);

    auto cancelButton = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
    buttonSizer->Add(cancelButton, 1);

    auto newTaskSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(newTaskSizer, 0);

    auto taskDurationBox = new wxStaticBox(this, wxID_ANY, wxT("Task Duration"));
    auto taskDurationBoxSizer = new wxStaticBoxSizer(taskDurationBox, wxVERTICAL);
    newTaskSizer->Add(taskDurationBoxSizer, 0);

    auto taskDurationPanel = new wxPanel(this, wxID_STATIC);
    taskDurationBoxSizer->Add(taskDurationPanel, 0);

    auto flexGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
    taskDurationPanel->SetSizer(flexGridSizer);

    auto startTimeText = new wxStaticText(taskDurationPanel, wxID_STATIC, wxT("Start Time"));
    flexGridSizer->Add(startTimeText, 0);

    pStartTime = new wxTimePickerCtrl();
    /*pStartTime = new wxTimePickerCtrl(taskDurationPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize(150, -1), wxTP_DEFAULT, wxDefaultValidator, "start_time_ctrl");
    pStartTime->SetToolTip(wxT("Enter the start time of the task"));
    flexGridSizer->Add(pStartTime, 0);*/
}

// void new_task_dialog::create_controls()
//{
//    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
//    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
//
//    wxPanel* panel = new wxPanel(this);
//    wxStaticBox* boundedTimesBox = new wxStaticBox(panel,
//        wxID_ANY,
//        wxT("Task Duration"),
//        wxPoint(2, 4),
//        wxSize(300, 200));
//    vbox->Add(panel, 1);
//
//    pOkButton = new wxButton(this,
//        SaveTaskId,
//        wxT("&Save"));
//    hbox->Add(pOkButton, 1);
//
//    pCancelButton = new wxButton(this,
//        wxID_CANCEL,
//        wxT("&Cancel"));
//    hbox->Add(pCancelButton, 1);
//
//    vbox->Add(hbox, 0, wxALIGN_RIGHT | wxTOP | wxBOTTOM, 10);
//    SetSizer(vbox);
//}

void new_task_dialog::on_save(wxCommandEvent& event)
{
    int i = 0;
}

void new_task_dialog::on_cancel(wxCommandEvent& event)
{
    int i = 0;
}
} // namespace app::dialog
