//  Taskable is a desktop that aids you in tracking your timesheets
//  and seeing what work you have done.
//
//  Copyright(C) <2019> <Szymon Welgus>
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

#include "clientdlg.h"

#include <sqlite_modern_cpp/errors.h>
#include <wx/richtooltip.h>
#include <wx/statline.h>

#include "../common/constants.h"
#include "../common/common.h"
#include "../common/util.h"
#include "../models/employermodel.h"

namespace app::dialog
{
const wxString& ClientDialog::DateLabel = wxT("Created %s | Updated %s");

ClientDialog::ClientDialog(wxWindow* parent, std::shared_ptr<spdlog::logger> logger, const wxString& name)
    : pLogger(logger)
    , pNameTextCtrl(nullptr)
    , pEmployerChoiceCtrl(nullptr)
    , pIsActiveCtrl(nullptr)
    , pDateTextCtrl(nullptr)
    , pOkButton(nullptr)
    , pCancelButton(nullptr)
    , pClient(std::make_unique<model::ClientModel>())
    , mClientId(-1)
    , bIsEdit(false)
{
    Create(parent,
        wxID_ANY,
        wxT("Add Client"),
        wxDefaultPosition,
        wxSize(320, 240),
        wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU,
        name);
    SetMinClientSize(wxSize(320, 240));
}

ClientDialog::ClientDialog(wxWindow* parent,
    std::shared_ptr<spdlog::logger> logger,
    bool isEdit,
    int clientId,
    const wxString& name)
    : pLogger(logger)
    , pNameTextCtrl(nullptr)
    , pEmployerChoiceCtrl(nullptr)
    , pIsActiveCtrl(nullptr)
    , pDateTextCtrl(nullptr)
    , pOkButton(nullptr)
    , pCancelButton(nullptr)
    , pClient(std::make_unique<model::ClientModel>(clientId))
    , mClientId(clientId)
    , bIsEdit(isEdit)
{
    Create(parent,
        wxID_ANY,
        wxT("Edit Client"),
        wxDefaultPosition,
        wxSize(320, 320),
        wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU,
        name);
    SetMinClientSize(wxSize(320, 240));
}

bool ClientDialog::Create(wxWindow* parent,
    wxWindowID windowId,
    const wxString& title,
    const wxPoint& position,
    const wxSize& size,
    long style,
    const wxString& name)
{
    bool created = wxDialog::Create(parent, windowId, title, position, size, style, name);

    if (created) {
        CreateControls();
        ConfigureEventBindings();
        FillControls();

        if (bIsEdit) {
            DataToControls();
        }

        GetSizer()->Fit(this);
        GetSizer()->SetSizeHints(this);
        SetIcon(common::GetProgramIcon());
        Center();
    }

    return created;
}

void ClientDialog::CreateControls()
{
    /* Window Sizing */
    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    /* Task Details Box */
    auto detailsBox = new wxStaticBox(this, wxID_ANY, wxT("Client Details"));
    auto detailsBoxSizer = new wxStaticBoxSizer(detailsBox, wxVERTICAL);
    mainSizer->Add(detailsBoxSizer, common::sizers::ControlExpandProp);

    auto clientDetailsPanel = new wxPanel(this, wxID_STATIC);
    detailsBoxSizer->Add(clientDetailsPanel, common::sizers::ControlExpand);

    auto taskFlexGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
    clientDetailsPanel->SetSizer(taskFlexGridSizer);

    /* ---Controls--- */
    /* Client Name Control */
    auto clientNameText = new wxStaticText(clientDetailsPanel, wxID_STATIC, wxT("Name"));
    taskFlexGridSizer->Add(clientNameText, common::sizers::ControlCenterVertical);

    pNameTextCtrl =
        new wxTextCtrl(clientDetailsPanel, IDC_NAME, wxGetEmptyString(), wxDefaultPosition, wxSize(150, -1), wxTE_LEFT);
    pNameTextCtrl->SetHint(wxT("Client name"));
    pNameTextCtrl->SetToolTip(wxT("Enter a name for the client"));
    taskFlexGridSizer->Add(pNameTextCtrl, common::sizers::ControlDefault);

    /* Employer Selection Control */
    auto employerNameText = new wxStaticText(clientDetailsPanel, wxID_STATIC, wxT("Employer"));
    taskFlexGridSizer->Add(employerNameText, common::sizers::ControlCenterVertical);

    pEmployerChoiceCtrl = new wxChoice(clientDetailsPanel, IDC_EMPLOYER, wxDefaultPosition, wxDefaultSize);
    pEmployerChoiceCtrl->AppendString(wxT("Select a employer"));
    pEmployerChoiceCtrl->SetSelection(0);
    pEmployerChoiceCtrl->SetToolTip(wxT("Select a employer to associate the client with"));
    taskFlexGridSizer->Add(pEmployerChoiceCtrl, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    if (bIsEdit) {
        /* Is Active Checkbox Control */
        auto isActiveFiller = new wxStaticText(clientDetailsPanel, wxID_STATIC, wxT(""));
        taskFlexGridSizer->Add(isActiveFiller, common::sizers::ControlDefault);

        pIsActiveCtrl = new wxCheckBox(clientDetailsPanel, IDC_ISACTIVE, wxT("Is Active"));
        taskFlexGridSizer->Add(pIsActiveCtrl, common::sizers::ControlDefault);

        /* Date Text Control */
        pDateTextCtrl = new wxStaticText(this, wxID_STATIC, wxT(""));
        auto font = pDateTextCtrl->GetFont();
        font.SetPointSize(8);
        pDateTextCtrl->SetFont(font);
        detailsBoxSizer->Add(pDateTextCtrl, 0, wxGROW | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    }

    /* Horizontal Line*/
    auto separationLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(150, -1), wxLI_HORIZONTAL);
    mainSizer->Add(separationLine, 0, wxEXPAND | wxALL, 1);

    /* Button Panel */
    auto buttonPanel = new wxPanel(this, wxID_STATIC);
    auto buttonPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonPanel->SetSizer(buttonPanelSizer);
    mainSizer->Add(buttonPanel, wxSizerFlags(wxSizerFlags().Border(wxALL, 5)).Center());

    pOkButton = new wxButton(buttonPanel, wxID_OK, wxT("&OK"));
    pCancelButton = new wxButton(buttonPanel, wxID_CANCEL, wxT("&Cancel"));

    buttonPanelSizer->Add(pOkButton, wxSizerFlags().Border(wxALL, 5));
    buttonPanelSizer->Add(pCancelButton, wxSizerFlags().Border(wxALL, 5));
}

// clang-format off
void ClientDialog::ConfigureEventBindings()
{
    pEmployerChoiceCtrl->Bind(
        wxEVT_CHOICE,
        &ClientDialog::OnEmployerChoiceSelection,
        this
    );

    pNameTextCtrl->Bind(
        wxEVT_TEXT,
        &ClientDialog::OnNameChange,
        this
    );

    if (bIsEdit) {
        pIsActiveCtrl->Bind(
            wxEVT_CHECKBOX,
            &ClientDialog::OnIsActiveCheck,
            this
        );
    }

    pOkButton->Bind(
        wxEVT_BUTTON,
        &ClientDialog::OnOk,
        this,
        wxID_OK
    );

    pCancelButton->Bind(
        wxEVT_BUTTON,
        &ClientDialog::OnCancel,
        this,
        wxID_CANCEL
    );
}
// clang-format on

void ClientDialog::FillControls()
{
    std::vector<model::EmployerModel> employers;
    try {
        employers = model::EmployerModel::GetAll();
    } catch (const sqlite::sqlite_exception& e) {
        pLogger->error("Error occured on GetAll() - {0:d} : {1}", e.get_code(), e.what());
    }

    for (auto employer : employers) {
        pEmployerChoiceCtrl->Append(employer.GetName(), util::IntToVoidPointer(employer.GetEmployerId()));
    }
}

void ClientDialog::DataToControls()
{
    model::ClientModel client;
    try {
        client = model::ClientModel::GetById(mClientId);
    } catch (const sqlite::sqlite_exception& e) {
        pLogger->error("Error occured on GetById() - {0:d} : {1}", e.get_code(), e.what());
    }

    pNameTextCtrl->SetValue(client.GetName());

    pEmployerChoiceCtrl->SetStringSelection(client.GetEmployer()->GetName());
    pEmployerChoiceCtrl->SendSelectionChangedEvent(wxEVT_CHOICE);

    pDateTextCtrl->SetLabel(wxString::Format(ClientDialog::DateLabel,
        client.GetDateCreated().FormatISOCombined(),
        client.GetDateModified().FormatISOCombined()));

    pIsActiveCtrl->SetValue(client.IsActive());
}

bool ClientDialog::Validate()
{
    bool isValid = true;
    if (!pClient->IsNameValid()) {
        isValid = false;
        common::validations::ForRequiredText(pNameTextCtrl, wxT("client name"));
    }

    if (!pClient->IsEmployerSelected()) {
        isValid = false;
        common::validations::ForRequiredChoiceSelection(pEmployerChoiceCtrl, wxT("employer"));
    }

    return isValid;
}

bool ClientDialog::AreControlsEmpty()
{
    return pNameTextCtrl->GetValue().empty() && pEmployerChoiceCtrl->GetSelection() == 0;
}

void ClientDialog::OnNameChange(wxCommandEvent& event)
{
    wxString name = pNameTextCtrl->GetValue();
    pClient->SetName(name);
}

void ClientDialog::OnEmployerChoiceSelection(wxCommandEvent& event)
{
    int id = util::VoidPointerToInt(pEmployerChoiceCtrl->GetClientData(pEmployerChoiceCtrl->GetSelection()));
    wxString name = pEmployerChoiceCtrl->GetStringSelection();

    pClient->SetEmployerId(id);
    pClient->GetEmployer()->SetName(name);
}

void ClientDialog::OnOk(wxCommandEvent& event)
{
    if (Validate()) {
        if (!bIsEdit) {
            model::ClientModel::Create(std::move(pClient));
        }

        if (bIsEdit && pIsActiveCtrl->IsChecked()) {
            model::ClientModel::Update(std::move(pClient));
        }

        if (bIsEdit && !pIsActiveCtrl->IsChecked()) {
            model::ClientModel::Delete(std::move(pClient));
        }

        EndModal(wxID_OK);
    }
}

void ClientDialog::OnCancel(wxCommandEvent& event)
{
    bool areControlsEmpty = AreControlsEmpty();
    if (!areControlsEmpty) {
        int answer = wxMessageBox(wxT("Are you sure you want to exit?"), wxT("Confirm"), wxYES_NO | wxICON_QUESTION);
        if (answer == wxYES) {
            EndModal(wxID_CANCEL);
        }
    } else {
        EndModal(wxID_CANCEL);
    }
}

void ClientDialog::OnIsActiveCheck(wxCommandEvent& event)
{
    if (event.IsChecked()) {
        pNameTextCtrl->Enable();
        pEmployerChoiceCtrl->Enable();
    } else {
        pNameTextCtrl->Disable();
        pEmployerChoiceCtrl->Disable();
    }
}
} // namespace app::dialog
