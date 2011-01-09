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

#include <wx/wfstream.h>

#include "CTaskBarIcon.h"
#include "CAppProfilePanel.h"
#include "CColorTempPanel.h"

enum
{
    OVDR_TB_CMD_SHOW = 10001,
    OVDR_TB_CMD_HIDE,
    OVDR_TB_CMD_EXIT,
    OVDR_TB_CMD_AUTOSTART,
    OVDR_TB_CMD_DAY_COLOR,
    OVDR_TB_CMD_NIGHT_COLOR,
    OVDR_TB_CMD_DEFAULT_COLOR,
    OVDR_TB_CMD_PROFILE_DEFAULT,
    OVDR_TB_CMD_PROFILE
};

CTaskBarIcon::CTaskBarIcon(wxWindow* dialog, CAppProfilePanel* panel, CColorTempPanel* ctpanel)
    : wxTaskBarIcon()
    , mpDialog(dialog)
    , mpAppProfilePanel(panel)
    , mpColorTempPanel(ctpanel)
{
    Connect(wxEVT_TASKBAR_LEFT_DOWN, wxTaskBarIconEventHandler(CTaskBarIcon::OnLeftDown), NULL, this);
}

CTaskBarIcon::~CTaskBarIcon()
{
    Disconnect(wxEVT_TASKBAR_LEFT_DOWN, wxTaskBarIconEventHandler(CTaskBarIcon::OnLeftDown), NULL, this);
}

wxMenu*	CTaskBarIcon::CreatePopupMenu()
{
    wxMenu* menu = new wxMenu;

    if (mpDialog->IsShown())
    {
	menu->Append(OVDR_TB_CMD_HIDE, wxT("Hide"), wxT(""), false);
    }
    else
    {
	menu->Append(OVDR_TB_CMD_SHOW, wxT("Show"), wxT(""), false);
    }
    menu->AppendSeparator();

    if (mpColorTempPanel->IsShown())
    {
	wxMenu* color_temp = new wxMenu;

	color_temp->Append(OVDR_TB_CMD_DAY_COLOR, wxT("Set day color temperatur"), wxT(""), false);
	color_temp->Append(OVDR_TB_CMD_NIGHT_COLOR, wxT("Set night color temperatur"), wxT(""), false);
	color_temp->Append(OVDR_TB_CMD_DEFAULT_COLOR, wxT("Set default color temperatur"), wxT(""), false);
	menu->AppendSubMenu(color_temp, wxT("Color temperature"));
	menu->AppendSeparator();

	color_temp->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CTaskBarIcon::OnMenuClick), NULL, this);
    }

    if (mpAppProfilePanel->IsShown())
    {
	wxMenu* app_profiles = new wxMenu;

	ProfileList AppProfiles = mpAppProfilePanel->GetProfiles();
	ProfileList::iterator it;
	int index = 0;

	for (it = AppProfiles.begin(); it != AppProfiles.end(); ++it)
	{
	    app_profiles->Append(OVDR_TB_CMD_PROFILE+index, (*it).AppName, wxT(""), true);
	    ++index;
	}

	if (index>0)
	{
	    app_profiles->AppendSeparator();
	    app_profiles->Append(OVDR_TB_CMD_PROFILE_DEFAULT, wxT("default"), wxT(""), true);
	    menu->AppendSubMenu(app_profiles, wxT("App Profiles"));
	    menu->AppendSeparator();

	    if (mpAppProfilePanel->GetActiveProfileIndex() != -1)
	    {
		wxMenuItem* item = app_profiles->FindItem(OVDR_TB_CMD_PROFILE+mpAppProfilePanel->GetActiveProfileIndex());
		item->Check(true);
	    }
	    else
	    {
		wxMenuItem* item = app_profiles->FindItem(OVDR_TB_CMD_PROFILE_DEFAULT);
		item->Check(true);
	    }

	    app_profiles->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CTaskBarIcon::OnMenuClick), NULL, this);
	}
    }

    #ifdef LINUX
    if(getenv("HOME"))
    {
	wxString filename = wxString::FromAscii(getenv("HOME"));
	filename += wxT("/.config/autostart/AMDOverdriveCtrl.desktop");

	menu->Append(OVDR_TB_CMD_AUTOSTART, wxT("AutoStart"), wxT(""), true);
	menu->AppendSeparator();

	if (wxFileExists(filename))
	{
	    wxMenuItem* item = menu->FindItem(OVDR_TB_CMD_AUTOSTART);
	    item->Check(true);
	}
    }
    #endif

    menu->Append(OVDR_TB_CMD_EXIT, wxT("Exit"), wxT(""), false);
    menu->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CTaskBarIcon::OnMenuClick), NULL, this);    

    return menu;
}

void CTaskBarIcon::OnLeftDown(wxTaskBarIconEvent& WXUNUSED(event))
{
    if (mpDialog->IsShown())
    {
	mpDialog->Show(false);
    }
    else
    {
	mpDialog->Show(true);
    }
}

void CTaskBarIcon::OnMenuClick(wxCommandEvent& event)
{
    switch(event.GetId())
    {
	case OVDR_TB_CMD_SHOW:
	{
	    mpDialog->Show(true);
	}
	break;

	case OVDR_TB_CMD_HIDE:
	{
	    mpDialog->Show(false);
	}
	break;

	case OVDR_TB_CMD_EXIT:
	{
	    mpDialog->Destroy();
	}
	break;

	case OVDR_TB_CMD_AUTOSTART:
	{
	    wxString home_path = wxString::FromAscii(getenv("HOME"));
	    wxString filename = home_path + wxT("/.config/autostart/AMDOverdriveCtrl.desktop");

	    if (wxFileExists(filename))
	    {
		remove(filename.ToUTF8());
	    }
	    else
	    {
		wxString script =
		    wxT("[Desktop Entry]\n")
		    wxT("Type=Application\n")
		    wxT("Exec=") + home_path + wxT("/.AMDOverdriveCtrl/autostart\n")
		    wxT("Hidden=false\n")
		    wxT("NoDisplay=false\n")
		    wxT("X-GNOME-Autostart-enabled=true\n")
		    wxT("Name=AMD OverdriveCtrl\n")
		    wxT("Comment=AutoStart added by AMDOverdriveCtrl Tool\n");

                wxFFileOutputStream file(filename, wxT("wt"));
		file.Write(script.ToUTF8(), script.Length());
		file.Close();

		#ifdef LINUX
			mode_t mode;
			mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			chmod(filename.ToUTF8(), mode);
		#endif
	    }
	}
	break;

	case OVDR_TB_CMD_PROFILE_DEFAULT:
	{
	    mpAppProfilePanel->EnableAppProfiles(false);
	    mpAppProfilePanel->SetManualProfile(mpAppProfilePanel->GetDefaultProfile());
	    mpAppProfilePanel->SetActiveProfile(wxT(""));
	    mpAppProfilePanel->SetActiveProfileIndex(-1);
	    mpAppProfilePanel->UpdateDisplay();
	}
	break;

	case OVDR_TB_CMD_DAY_COLOR:
	{
	    mpColorTempPanel->SetDayColorTemperature();
	}
	break;

	case OVDR_TB_CMD_NIGHT_COLOR:
	{
	    mpColorTempPanel->SetNightColorTemperature();
	}
	break;

	case OVDR_TB_CMD_DEFAULT_COLOR:
	{
	    mpColorTempPanel->SetDefaultColorTemperature();
	}
	break;

	default:
	{
	    int index = event.GetId()-OVDR_TB_CMD_PROFILE;

	    ProfileList AppProfiles = mpAppProfilePanel->GetProfiles();
	    ProfileList::iterator it = AppProfiles.begin();
	    advance(it, index);

	    printf("Profile %d %s selected\n", index, (const char*)(*it).AppName.ToUTF8());

	    mpAppProfilePanel->EnableAppProfiles(false);
	    mpAppProfilePanel->SetManualProfile((*it).ProfileName);
	    mpAppProfilePanel->SetActiveProfile((*it).AppName);
	    mpAppProfilePanel->SetActiveProfileIndex(index);
	    mpAppProfilePanel->UpdateDisplay();
	    mpAppProfilePanel->SetActiveProfileName((*it).AppName);
	}
	break;
    }
}
