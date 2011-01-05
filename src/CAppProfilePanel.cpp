/*******************************************************************************

 * This program reads HW information from your ATI Radeon card and displays them
 * You can also change frequencies and voltages.

 * THIS PROGRAM MAY DAMAGE YOUR VIDEO CARD, IF YOU APPLY NONSENSIAL VALUES.
 * e.g. INCREASING THE VOLTAGES AND FREQUENCIES IN CONJUNCTION WITH LOWERING THE
 *      FAN SPEED IS NOT ADVISABLE!

 * Copyright(C) Thorsten Gilling (tgilling@web.de)

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*******************************************************************************/

#include <wx/xml/xml.h>

#include "CAppProfilePanel.h"
#include "Color.h"
#include "adl.h"

CAppProfilePanel::CAppProfilePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CAppProfilePanelBase(parent, id, pos, size, style)
    , mDefaultProfile(wxT(""))
    , mActiveProfile(wxT(""))
    , mManualProfile(wxT(""))
    , mActiveProfileIndex(-1)
    , mEnabled(false)
    , mAppProfileDataFilePath(wxT(""))
{
    mProfileList->InsertColumn(0, wxT("Application"));
    mProfileList->InsertColumn(1, wxT("Profile"));

    mProfileList->SetColumnWidth(0, 120);
    mProfileList->SetColumnWidth(1, 250);

    if (getenv("HOME"))
    {
	mAppProfileDataFilePath = wxString::FromAscii(getenv("HOME"));
	mAppProfileDataFilePath += wxT("/.AMDOverdriveCtrl");
	#ifdef LINUX
	    mkdir(mAppProfileDataFilePath.ToAscii(), 0750);
	#else
	    mkdir(mAppProfileDataFilePath.ToAscii());
	#endif

	mAppProfileDataFilePath += wxT("/AppProfiles.xml");

	if (wxFileExists(mAppProfileDataFilePath))
	{
	    wxXmlDocument doc;

	    if (doc.Load(mAppProfileDataFilePath))
	    {
		if (doc.GetRoot()->GetName() == wxT("APP_PROFILES"))
		{
		    wxXmlNode* child = doc.GetRoot()->GetChildren();

		    while (child)
		    {
			if (child->GetName() == wxT("APP_PROFILE_DEFAULT"))
			{
			    wxString profile = child->GetPropVal(wxT("profile"), wxT(""));
			    mDefaultProfile = profile;
			    mAppProfiles.clear();
			}
			else if (child->GetName() == wxT("APP_PROFILE"))
			{
			    wxString nr = child->GetPropVal(wxT("nr"), wxT("0"));
			    wxString app = child->GetPropVal(wxT("app"), wxT(""));
			    wxString profile = child->GetPropVal(wxT("profile"), wxT(""));

			    mAppProfiles.push_back(AppProfile(app, profile));
			    UpdateDisplay();
			}
			child = child->GetNext();
		    }
		}
	    }
	}
    }

    ADL* adl = ADL::Instance();

    if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS) &&
        !(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
    {
	Show(false);
    }
}

CAppProfilePanel::~CAppProfilePanel()
{
}

void CAppProfilePanel::SaveXML()
{
    wxXmlDocument doc;

    wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("APP_PROFILES"));

    doc.SetRoot(root);

    wxXmlNode* node;

    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("APP_PROFILE_DEFAULT"));
    node->AddProperty(wxT("profile"), mDefaultProfile);
    root->AddChild(node);

    ProfileList::iterator it;
    int i = 0;

    for (it = mAppProfiles.begin(); it != mAppProfiles.end(); ++it)
    {
        node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("APP_PROFILE"));
        node->AddProperty(wxT("nr"), wxString::Format(wxT("%d"), i));
	node->AddProperty(wxT("app"), (*it).AppName);
        node->AddProperty(wxT("profile"), (*it).ProfileName);
        root->AddChild(node);
	++i;
    }

    doc.Save(mAppProfileDataFilePath);
}

void CAppProfilePanel::mButtonChooseDefaultClick(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog OpenFileDialog(this, wxT("Open AMD/ATI Overdrive profile"), wxT(""), wxT(""),
                                wxT("ovdr files (*.ovdr)|*.ovdr"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(OpenFileDialog.ShowModal() == wxID_OK)
    {
	mDefaultProfile = OpenFileDialog.GetPath();
        mDefaultProfileName->SetValue(mDefaultProfile.AfterLast('/'));

	SaveXML();
    }
}

void CAppProfilePanel::mButtonAddProfileClick(wxCommandEvent& WXUNUSED(event))
{
    wxString app, prof, path;
    CProfileAddDialog dialog(this);

    dialog.ShowModal();

    if (dialog.GetResult(app, prof, path))
    {
	mAppProfiles.push_back(AppProfile(app,path));

	UpdateDisplay();

	SaveXML();
    }
}

void CAppProfilePanel::mButtonDeleteProfileClick(wxCommandEvent& WXUNUSED(event))
{
    long itemIndex = -1;

    itemIndex = mProfileList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex != -1)
    {
	ProfileList::iterator it = mAppProfiles.begin();
	advance(it, itemIndex);
	mAppProfiles.erase(it);

	mProfileList->DeleteItem(itemIndex);

	if (itemIndex == mActiveProfileIndex)
	{
	    mActiveProfileIndex = -1;
	    mActiveProfile = wxT("___GOTO___DEFAULT___PROFILE___");
	}
    }

    UpdateDisplay();

    SaveXML();
}

void CAppProfilePanel::mButtonEditProfileClick(wxCommandEvent& WXUNUSED(event))
{
    CProfileAddDialog dialog(this);

    long itemIndex = -1;

    itemIndex = mProfileList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex != -1)
    {
	ProfileList::iterator it = mAppProfiles.begin();
	advance(it, itemIndex);

	wxString app, prof, path;

	dialog.SetValues((*it).AppName, (*it).ProfileName);

	dialog.ShowModal();

	if (dialog.GetResult(app, prof, path))
	{
	    mAppProfiles.erase(it);
	    mProfileList->DeleteItem(itemIndex);

	    mAppProfiles.push_back(AppProfile(app,path));
	}

	if (itemIndex == mActiveProfileIndex)
	{
	    mActiveProfileIndex = -1;
	    mActiveProfile = wxT("___GOTO___DEFAULT___PROFILE___");
	}
    }

    UpdateDisplay();

    SaveXML();
}

bool CAppProfilePanel::EnableAppProfiles(bool enable)
{
    if (!mDefaultProfileName->GetValue().IsEmpty() && enable)
    {
	mEnable->SetValue(true);
	mEnabled = true;
	mActiveProfileName->SetValue(mDefaultProfile.AfterLast('/'));
	return true;
    }
    else
    {
	mEnable->SetValue(false);
	mEnabled = false;
	mActiveProfileName->SetValue(mDefaultProfile.AfterLast('/'));
	return false;
    }
}

void CAppProfilePanel::mEnableOnCheckBox(wxCommandEvent& WXUNUSED(event))
{
    if (mDefaultProfileName->GetValue().IsEmpty())
    {
	wxMessageBox(wxT("Please choose a default profile."), wxT("Problem!"), wxOK|wxCENTRE|wxICON_ERROR);
	mEnable->SetValue(false);
    }
    else
    {
	mEnabled = mEnable->GetValue();
	if (mEnabled)
	{
	    mActiveProfile = wxT(" ");
	}
	else
	{
	    mManualProfile = mDefaultProfile;
	    mActiveProfileIndex = -1;
	}
	UpdateDisplay();
    }
}

void CAppProfilePanel::UpdateDisplay()
{
    mProfileList->DeleteAllItems();

    ProfileList::iterator it;
    int index = 0;

    for (it = mAppProfiles.begin(); it !=  mAppProfiles.end(); ++it)
    {
	mProfileList->InsertItem(index, (*it).AppName);
	mProfileList->SetItem(index, 1, (*it).ProfileName.AfterLast('/'));

	if (index == mActiveProfileIndex)
	{
	    mProfileList->SetItemBackgroundColour(index, Color::ORANGE);
	}
	else
	{
	    if (!wxFileExists((*it).ProfileName))
	    {
		mProfileList->SetItemBackgroundColour(index, Color::RED);
		mProfileList->SetItem(index, 1, (*it).ProfileName.AfterLast('/') + wxT("   (file not found)"));
	    }
	    else
	    {
		if (index%2)
		{
		    mProfileList->SetItemBackgroundColour(index, Color::LIGHT_GRAY);
		}
		else
		{
		    mProfileList->SetItemBackgroundColour(index, Color::WHITE);
		}
	    }
	}

	++index;
    }

    mDefaultProfileName->SetValue(mDefaultProfile.AfterLast('/'));

    if (mEnabled)
    {
	if (mActiveProfile.IsEmpty())
	{
	    mActiveProfileName->SetValue(wxT("default"));
	}
	else
	{
	    mActiveProfileName->SetValue(mActiveProfile);
	}
    }
    else
    {
	mActiveProfileName->SetValue(wxT(""));
    }
}

void CAppProfilePanel::OnLeftDClick(wxMouseEvent& WXUNUSED(event))
{
    long itemIndex = -1;

    itemIndex = mProfileList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex != -1)
    {
	if (mActiveProfileIndex == itemIndex)
	{
	    EnableAppProfiles(false);
	    mActiveProfile = wxT("");
	    mManualProfile = mDefaultProfile;
	    mActiveProfileIndex = -1;
	    UpdateDisplay();
	}
	else
	{
	    wxListItem item;

	    item.SetColumn(0);
	    item.SetId(itemIndex);
	    item.SetMask(wxLIST_MASK_TEXT);

	    mProfileList->GetItem(item);

	    ProfileList::iterator it = mAppProfiles.begin();
	    advance(it, itemIndex);

	    EnableAppProfiles(false);
	    mActiveProfile = (*it).AppName;
	    mManualProfile = (*it).ProfileName;
	    mActiveProfileIndex = itemIndex;
	    UpdateDisplay();
	    mActiveProfileName->SetValue(mActiveProfile);
	}
    }
}

//*************************************************************************************//

CProfileAddDialog::CProfileAddDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : CProfileAddDialogBase(parent, id, title, pos, size, style), mOK(false)
{

}

CProfileAddDialog::~CProfileAddDialog()
{

}

void CProfileAddDialog::mButtonChooseProfileClick(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog OpenFileDialog(this, wxT("Open AMD/ATI Overdrive profile"), wxT(""), wxT(""),
                                wxT("ovdr files (*.ovdr)|*.ovdr"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(OpenFileDialog.ShowModal() == wxID_OK)
    {
	mPath = OpenFileDialog.GetPath();
        mProfileName->SetValue(mPath.AfterLast('/'));
    }
}

void CProfileAddDialog::CancelButtonClick(wxCommandEvent& WXUNUSED(event))
{
    Destroy();
}

void CProfileAddDialog::OKButtonClick(wxCommandEvent& WXUNUSED(event))
{
    Destroy();
    mOK = true;
}

bool CProfileAddDialog::GetResult(wxString& app, wxString& profile, wxString& path)
{
    app = mAppName->GetValue();
    profile = mProfileName->GetValue();
    if (!mPath.IsEmpty())
    {
	path = mPath;
    }
    else
    {
	path = mProfileName->GetValue();
    }
    return (mOK && !app.IsEmpty() && !profile.IsEmpty() && !path.IsEmpty());
}

void CProfileAddDialog::SetValues(wxString& app, wxString& profile)
{
    mAppName->SetValue(app);
    mProfileName->SetValue(profile.AfterLast('/'));
    mPath = profile;
}
