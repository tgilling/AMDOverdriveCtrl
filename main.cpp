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
#include <wx/mstream.h>
#include <wx/wfstream.h>

#include "main.h"
#include "adl/adl.h"
#include "icon.png.h"

const int TIMER_INTERVAL = 1000;

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// application class implementation
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit()
{
    ADL* adl = ADL::Instance();

    if(!adl->IsATICardAndCatalystPresent())
    {
        wxMessageBox(wxT("Unable to initialize AMD ADL Library.\n\nThis program depends on the proprietary Catalyst drivers.\n"\
                         "Please check the driver installation."), wxT("Initialization problem"), wxOK|wxCENTRE|wxICON_ERROR);
        return false;
    }
    else
    {
        MainDialog* main_dialog = new MainDialog(NULL);

        if(getenv("HOME"))
        {
            wxString file_path = wxString::FromAscii(getenv("HOME"));
            file_path += wxT("/.AMDOverdriveCtrl");
            mkdir(file_path.ToUTF8(), 700);

            // each start
            wxString filename = file_path + wxT("/Current_Startup.ovdr");
            main_dialog->SaveXML(filename);
	    main_dialog->SetStartupProfileName(filename);

            // only very first start
            filename = file_path +wxT("/VeryFirstStart.ovdr");
            if(!wxFileExists(filename))
            {
                main_dialog->SaveXML(filename);
            }

            // only create if not existing
            filename = file_path +wxT("/autostart");
            if(!wxFileExists(filename))
            {
		wxString script =
		    wxT("#!/bin/bash\n")
		    wxT("# Autostart script for AMD/ATI OverdriveCtrl\n")
		    wxT("sleep 20\n")
		    wxT("AMDOverdriveCtrl --enable-app-profiles\n");

                wxFFileOutputStream file(filename, wxT("wt"));
		file.Write(script.ToUTF8(), script.Length());
		file.Close();

		mode_t mode;
		mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
		chmod(filename.ToUTF8(), mode);
            }

	    // see if we have  a default profile
            filename = file_path +wxT("/default.ovdr");
            if(wxFileExists(filename))
	    {
		if (main_dialog->LoadXML(filename))
		{
		    printf("Default profile found and loaded.\n");
		}
	    }
	}

        wxString tmp = wxString::Format(wxT("Usage: %s [overdrive_profile_filename [--batch-mode]] | [--enable-app-profiles]\n"), argv[0]);
        printf("%s\n", (const char*)tmp.ToUTF8());

        if(argc >= 2)
        {
            wxString tmp = wxT("--enable-app-profiles");
            if(tmp.CompareTo(argv[2], wxString::ignoreCase) == 0 ||
	       tmp.CompareTo(argv[1], wxString::ignoreCase) == 0)
            {
                main_dialog->EnableAppProfiles();
            }
	    else
	    {
		if (!main_dialog->LoadXML(argv[1]))
		{
		    wxString profile = argv[1];
		    wxMessageBox(wxT("\nThe specified startup profile '") + profile + wxT("' is missing."), wxT("AMD/ATI OverdriveCtrl warning"), wxOK|wxCENTRE|wxICON_WARNING);
		}
	    }

            tmp = wxT("--batch-mode");
            if(tmp.CompareTo(argv[2], wxString::ignoreCase) == 0)
            {
		main_dialog->SetStartupProfileName(wxT(""));
                delete main_dialog;
                return false;
            }
        }

        SetTopWindow(main_dialog);

	if (argc == 1)
	{
	    GetTopWindow()->Show();
	}

        return true;
    }
}

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation
////////////////////////////////////////////////////////////////////////////////

MainDialog::MainDialog(wxWindow *parent)
    : MainDialogBase(parent)
    , mStartupProfileName(wxT(""))
    , mMustAddPages(true)
    , mpInfoPanel(NULL)
    , mpFanSpeedPanel(NULL)
    , mpAuthorPanel(NULL)
    , mpMonitorPanel(NULL)
    , mpFanControlPanel(NULL)
    , mpAppProfilePanel(NULL)
{
    wxImage::AddHandler(new wxPNGHandler);

    wxMemoryInputStream istream(IconPng, sizeof(IconPng));
    wxImage tmp(istream, wxBITMAP_TYPE_PNG);
    wxIcon icon;
    icon.CopyFromBitmap(tmp);

    SetIcon(icon);

    mpInfoPanel = new CInfoPanel(mNotebook);
    mpAuthorPanel = new CAuthorPanel(mNotebook);
    mpMonitorPanel = new CMonitorPanel(mNotebook);
    mpFanSpeedPanel = new CFanSpeedPanel(mNotebook);
    mpFanControlPanel = new CFanControlPanel(mpFanSpeedPanel, mNotebook);
    mpFanSpeedPanel->SetFanControlPanel(mpFanControlPanel);
    mpAppProfilePanel = new CAppProfilePanel(mNotebook);
    mpOvdrSettingsPanel = new COvdrSettingsPanel(mNotebook);

    tmp.Rescale(20,20, wxIMAGE_QUALITY_HIGH);
    icon.CopyFromBitmap(tmp);

    mpTaskBarIcon = new CTaskBarIcon(this, mpAppProfilePanel);
    mpTaskBarIcon->SetIcon(icon, wxT("AMD OverdriveCtrl"));

    Start(TIMER_INTERVAL);
}

MainDialog::~MainDialog()
{
    if (!mStartupProfileName.IsEmpty())
    {
	LoadXML(mStartupProfileName);
    }
    delete mpTaskBarIcon;
}

void MainDialog::OnInit(wxInitDialogEvent& WXUNUSED(event))
{
    if (mMustAddPages)
    {
	mMustAddPages = false;

	if (mpInfoPanel != NULL && mpFanSpeedPanel != NULL && mpAuthorPanel != NULL
	    && mpMonitorPanel != NULL && mpFanControlPanel != NULL && mpAppProfilePanel != NULL
	    && mpOvdrSettingsPanel != NULL)
	{
	    mNotebook->AddPage(mpAuthorPanel, wxT("?"));
	    mNotebook->AddPage(mpInfoPanel, wxT("Info"));
	    mNotebook->AddPage(mpOvdrSettingsPanel, wxT("Overdrive"));
	    mNotebook->AddPage(mpFanSpeedPanel, wxT("FanSpeed"));
	    mNotebook->AddPage(mpFanControlPanel, wxT("FanCtrl"));
	    mNotebook->AddPage(mpAppProfilePanel, wxT("AppProfile"));
	    mNotebook->AddPage(mpMonitorPanel, wxT("Monitor"));
	}
	else
	{
	    wxMessageBox(wxT("Unable to create Panels"), wxT("ERROR"));
	}
    }
}

void MainDialog::OnCloseDialog(wxCloseEvent& WXUNUSED(event))
{
    Destroy();
}

void MainDialog::OnOKClick(wxCommandEvent& WXUNUSED(event))
{
    Show(false);
}

void MainDialog::mExitButtonClick(wxCommandEvent& WXUNUSED(event))
{
    Destroy();
}

void MainDialog::OnNotebookPageChanged(wxNotebookEvent& WXUNUSED(event))
{
    if(mNotebook->GetCurrentPage() == mpInfoPanel)
    {
        mpInfoPanel->StartTimer();
        mpFanSpeedPanel->StopTimer();

        mpInfoPanel->UpdateDisplayValues();
    }
    else if(mNotebook->GetCurrentPage() == mpFanSpeedPanel)
    {
        mpInfoPanel->StopTimer();
        mpFanSpeedPanel->StartTimer();

        mpFanSpeedPanel->UpdateDisplayValues();
    }
    else
    {
        mpInfoPanel->StopTimer();
        mpFanSpeedPanel->StopTimer();
    }
}

void MainDialog::mLoadButtonClick(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog OpenFileDialog(this, wxT("Open AMD/ATI Overdrive profile"), wxT(""), wxT(""),
                                wxT("ovdr files (*.ovdr)|*.ovdr"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(OpenFileDialog.ShowModal() == wxID_OK)
    {
        LoadXML(OpenFileDialog.GetPath());
    }
}

void MainDialog::mSaveButtonClick(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog SaveFileDialog(this, wxT("Save AMD/ATI Overdrive profile"), wxT(""), wxT(""),
                                wxT("ovdr files (*.ovdr)|*.ovdr"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(SaveFileDialog.ShowModal() == wxID_OK)
    {
        SaveXML(SaveFileDialog.GetPath());
    }
}

void MainDialog::EnableAppProfiles()
{
    if (mpAppProfilePanel->EnableAppProfiles())
    {
	LoadXML(mpAppProfilePanel->GetDefaultProfile());
    }
}

bool MainDialog::LoadXML(wxString filename)
{
    CTRL_POINTS ctrl_points;
    bool enable_fan_ctrl = false;
    wxXmlDocument doc;

    if(wxFileExists(filename))
    {
	if(doc.Load(filename))
	{
	    if(doc.GetRoot()->GetName() == wxT("OVERDRIVE_PROFILE"))
	    {
		wxXmlNode* child = doc.GetRoot()->GetChildren();

		while(child)
		{
		    if(child->GetName() == wxT("PERFORMANCE_LEVEL"))
		    {
			long llevel, lgpu, lmem, lvoltage;

			wxString level = child->GetAttribute(wxT("level"), wxT("2"));
			wxString gpu = child->GetAttribute(wxT("gpu"), wxT("0"));
			wxString mem = child->GetAttribute(wxT("mem"), wxT("0"));
			wxString voltage = child->GetAttribute(wxT("voltage"), wxT("0"));

			level.ToLong(&llevel);
			gpu.ToLong(&lgpu);
			mem.ToLong(&lmem);
			voltage.ToLong(&lvoltage);

			if(lgpu != 0 && lmem != 0 && lvoltage != 0)
			{
			    mpOvdrSettingsPanel->SetOverdriveValues(llevel, lgpu/100, lmem/100, lvoltage);
			}
		    }
		    else if(child->GetName() == wxT("FAN_SETTING"))
		    {
			long percentage;
			wxString fanspeed = child->GetAttribute(wxT("percentage"), wxT("AUTO"));
			fanspeed.ToLong(&percentage);

			if(percentage != 0)
			{
			    if(!mpFanSpeedPanel->SetFanSpeed(percentage))
			    {
				wxMessageBox(wxString::Format(wxT("Could not apply setting:\nFanSpeed: %ld"), percentage), wxT("Failed to set FanSpeed"), wxOK|wxCENTRE|wxICON_ERROR);
			    }
			}
			else
			{
			    mpFanSpeedPanel->SetDefaultFanSpeed();
			}
		    }
		    else if (child->GetName() == wxT("FAN_CTRL"))
		    {
			wxString enable = child->GetAttribute(wxT("enabled"), wxT("no"));
			if (enable == wxT("yes"))
			{
			    enable_fan_ctrl = true;
			}
			else
			{
			    enable_fan_ctrl = false;
			}
		    }
		    else if (child->GetName() == wxT("FAN_CTRL_CURVE"))
		    {
			long type;
			wxString curve_type = child->GetAttribute(wxT("type"), wxT("0"));
			curve_type.ToLong(&type);

			mpFanControlPanel->SetCurveType(type);

		    }
		    else if (child->GetName() == wxT("FAN_CTRL_POINT"))
		    {
			long nr, temperature, percentage;

			wxString s_nr = child->GetAttribute(wxT("nr"), wxT("0"));
			wxString s_temperature = child->GetAttribute(wxT("temperature"), wxT("0"));
			wxString s_percentage = child->GetAttribute(wxT("percentage"), wxT("100"));

			s_nr.ToLong(&nr);
			s_temperature.ToLong(&temperature);
			s_percentage.ToLong(&percentage);

			ctrl_points[nr].x = (double)temperature / 100.0;
			ctrl_points[nr].y = (double)percentage / 100.0;

			if (nr == NR_OF_CTRL_POINTS-1)
			{
			    mpFanControlPanel->SetCtrlPoints(ctrl_points);
			    mpFanControlPanel->EnableFanControllerMode(enable_fan_ctrl);
			}
		    }
		    else if (child->GetName() == wxT("MONITOR_SAMPLE_TIME"))
		    {
			long time;

			wxString s_time = child->GetAttribute(wxT("interval"), wxT("10"));

			s_time.ToLong(&time);

			mpMonitorPanel->SetSampleTime(time);
		    }

		    child = child->GetNext();
		}

		if(!mpOvdrSettingsPanel->CommitOverdriveValues())
		{
		    wxMessageBox(wxT("Could not apply overdrive settings.\n"), wxT("Overdrive ERROR"), wxOK|wxCENTRE|wxICON_ERROR);
		}
		else
		{
		    mpOvdrSettingsPanel->UpdateDisplayValues();
		}

		return true;
	    }
	}
    }
    return false;
}

bool MainDialog::SaveXML(wxString filename)
{
    ADL* adl = ADL::Instance();
    adl->UpdateData();

    wxXmlDocument doc;

    wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("OVERDRIVE_PROFILE"));

    doc.SetRoot(root);

    wxXmlNode* node;

    for(int i=adl->mODParameters.iNumberOfPerformanceLevels-1; i>=0; i--)
    {
        node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("PERFORMANCE_LEVEL"));
        node->AddProperty(wxT("level"), wxString::Format(wxT("%d"), i));
        node->AddProperty(wxT("gpu"), wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[i].iEngineClock));
        node->AddProperty(wxT("mem"), wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[i].iMemoryClock));
        node->AddProperty(wxT("voltage"), wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[i].iVddc));
        root->AddChild(node);
    }

    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("FAN_SETTING"));
    if(mpFanSpeedPanel->HasFanSpeedFixedLevel())
    {
        node->AddProperty(wxT("percentage"), wxString::Format(wxT("%d"), mpFanSpeedPanel->GetFanSpeedSetting()));
    }
    else
    {
        node->AddProperty(wxT("percentage"), wxT("AUTO"));
    }
    root->AddChild(node);

    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("FAN_CTRL"));
    node->AddProperty(wxT("enabled"), mpFanControlPanel->IsFanControllerEnabled() ? wxT("yes") : wxT("no"));
    root->AddChild(node);

    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("FAN_CTRL_CURVE"));
    node->AddProperty(wxT("type"), wxString::Format(wxT("%d"), mpFanControlPanel->GetCurveType()));
    root->AddChild(node);

    CTRL_POINTS ctrl_points;
    mpFanControlPanel->GetCtrlPoints(ctrl_points);

    for(int i=0; i<NR_OF_CTRL_POINTS; i++)
    {
        node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("FAN_CTRL_POINT"));
        node->AddProperty(wxT("nr"), wxString::Format(wxT("%d"), i));
	node->AddProperty(wxT("temperature"), wxString::Format(wxT("%.0f"), ctrl_points[i].x*100));
        node->AddProperty(wxT("percentage"), wxString::Format(wxT("%.0f"), ctrl_points[i].y*100));
        root->AddChild(node);
    }

    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("MONITOR_SAMPLE_TIME"));
    node->AddProperty(wxT("interval"), wxString::Format(wxT("%d"), mpMonitorPanel->GetSampleTime()));
    root->AddChild(node);

    if(filename.Find(wxT(".ovdr")) == wxNOT_FOUND)
    {
        filename += wxT(".ovdr");
    }

    return doc.Save(filename);
}

void MainDialog::Notify()
{
    if (mpAppProfilePanel->GetEnabled())
    {
	if (mpAppProfilePanel->GetActiveProfile().IsEmpty())
	{
	    ProfileList AppProfiles = mpAppProfilePanel->GetProfiles();
	    ProfileList::iterator it;
	    int index = 0;

	    for (it = AppProfiles.begin(); it !=  AppProfiles.end(); ++it)
	    {		
		if (IsAppRunning((*it).AppName))
		{
		    if (LoadXML((*it).ProfileName))
		    {
			printf("Profile: %s, %s activated\n", (const char*)(*it).AppName.ToUTF8(), (const char*)(*it).ProfileName.ToUTF8());
			mpAppProfilePanel->SetActiveProfile((*it).AppName);
			mpAppProfilePanel->SetActiveProfileIndex(index);
			mpAppProfilePanel->UpdateDisplay();
			Stop();
			Start(5*TIMER_INTERVAL);
		    }
		    else
		    {
			printf("Failed to load profile %s\n", (const char*)(*it).AppName.ToUTF8());			
		    }
		}

		++index;
	    }
	}
	else
	{
	    if (!IsAppRunning(mpAppProfilePanel->GetActiveProfile()))
	    {
		printf("%s closed.\n", (const char*)mpAppProfilePanel->GetActiveProfile().ToUTF8());
		if (mpAppProfilePanel->GetDefaultProfile().IsEmpty())
		{
		    mpFanSpeedPanel->SetDefaultFanSpeed();
		    mpAppProfilePanel->SetActiveProfile(wxT(""));
		    mpAppProfilePanel->SetActiveProfileIndex(-1);
		    mpAppProfilePanel->UpdateDisplay();
		}
		else
		{
		    printf("Default Profile activated\n");
		    if (LoadXML(mpAppProfilePanel->GetDefaultProfile()))
		    {
			mpAppProfilePanel->SetActiveProfile(wxT(""));
			mpAppProfilePanel->SetActiveProfileIndex(-1);
			mpAppProfilePanel->UpdateDisplay();
		    }
		    else
		    {
			printf("Failed to load default profile %s\n", (const char*)mpAppProfilePanel->GetDefaultProfile().ToUTF8());
		    }
		}
		mpAppProfilePanel->SetActiveProfile(wxT(""));
		Stop();
		Start(TIMER_INTERVAL);
	    }
	}
    }
    else if (!mpAppProfilePanel->GetManualProfile().IsEmpty())
    {
	printf("Profile: %s activated\n", (const char*)mpAppProfilePanel->GetManualProfile().ToUTF8());
	if (LoadXML(mpAppProfilePanel->GetManualProfile()))
	{
	    mpAppProfilePanel->SetManualProfile(wxT(""));
	}
	else
	{
	    printf("Failed to load manual profile %s\n", (const char*)mpAppProfilePanel->GetManualProfile().ToUTF8());
	}
	Stop();
	Start(TIMER_INTERVAL);
    }
}

bool MainDialog::IsAppRunning(wxString app)
{
    FILE *fp;
    char path[PATH_MAX];
    char cmd[PATH_MAX];
    bool running = false;

    sprintf(cmd, "ps -C %s | grep %s", (const char*)app.ToUTF8(), (const char*)app.ToUTF8());

    fp = popen(cmd, "r");

    if (fgets(path, PATH_MAX, fp) == NULL)
    {
	running = false;
    }
    else
    {
	wxString result = wxString::FromUTF8(path);

	if (result.Find(app) == wxNOT_FOUND)
	{
	    running = false;
	}
	else
	{
	    running = true;
	}
    }

    pclose(fp);

    return running;
}
