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


#ifndef _CAppProfilePanel_h_
#define _CAppProfilePanel_h_

#include <wx/wx.h>
#include "gui.h"

#include <list>

using namespace std;

struct AppProfile
{
    AppProfile(wxString app, wxString prof) { AppName = app; ProfileName = prof; }

    wxString AppName;
    wxString ProfileName;
};

typedef list<AppProfile> ProfileList;

class CAppProfilePanel : public CAppProfilePanelBase
{
    public:
        CAppProfilePanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
        virtual ~CAppProfilePanel();

        void UpdateDisplay();

        bool EnableAppProfiles(bool enable = true);

        const ProfileList& GetProfiles() const {return mAppProfiles;}

        void SetActiveProfile(const wxString& mActiveProfile) {this->mActiveProfile = mActiveProfile;}
        const wxString& GetActiveProfile() const {return mActiveProfile;}

	void SetActiveProfileName(wxString name) { mActiveProfileName->SetValue(name); }

	void SetActiveProfileIndex(int mActiveProfileIndex) {this->mActiveProfileIndex = mActiveProfileIndex;}
        int GetActiveProfileIndex() const {return mActiveProfileIndex;}

	void SetDefaultProfile(const wxString& mDefaultProfile) {this->mDefaultProfile = mDefaultProfile;}
        const wxString& GetDefaultProfile() const {return mDefaultProfile;}

	void SetEnabled(bool mEnabled) {this->mEnabled = mEnabled;}
        bool GetEnabled() const {return mEnabled;}

	void SetManualProfile(const wxString& mManualProfile) {this->mManualProfile = mManualProfile;}
        const wxString& GetManualProfile() const {return mManualProfile;}

    protected:
        ProfileList mAppProfiles;

        wxString mDefaultProfile;
        wxString mActiveProfile;
        wxString mManualProfile;
        int mActiveProfileIndex;
        bool mEnabled;

        virtual void mButtonChooseDefaultClick(wxCommandEvent& event);
        virtual void mButtonAddProfileClick(wxCommandEvent& event);
        virtual void mButtonEditProfileClick(wxCommandEvent& event);
        virtual void mButtonDeleteProfileClick(wxCommandEvent& event);
        virtual void mEnableOnCheckBox(wxCommandEvent& event);
        virtual void OnLeftDClick(wxMouseEvent& event);

        wxString mAppProfileDataFilePath;

        void SaveXML();
};

class CProfileAddDialog : public CProfileAddDialogBase
{
    public:
        CProfileAddDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        ~CProfileAddDialog();

        bool GetResult(wxString& app, wxString& profile, wxString& path);
	void SetValues(wxString& app, wxString& profile);

    protected:
        virtual void mButtonChooseProfileClick(wxCommandEvent& event);
        virtual void CancelButtonClick(wxCommandEvent& event);
        virtual void OKButtonClick(wxCommandEvent& event);

        bool mOK;
        wxString mPath;
};

#endif
