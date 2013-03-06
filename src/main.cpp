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
#include "adl.h"
#include "icon.png.h"

const int TIMER_INTERVAL = 1000;

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// application class implementation
////////////////////////////////////////////////////////////////////////////////

static int MissingFeatures = 0;

void MainApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc (g_cmdLineDesc);
    parser.SetSwitchChars (wxT("-/"));
}

bool MainApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    mStartHidden = false;

    mBatchMode = parser.Found(wxT("b"));

    mEnableAppProfiles = parser.Found(wxT("a"));

    mNoWarnings = parser.Found(wxT("n"));

    if (mBatchMode || mEnableAppProfiles)
    {
	mStartHidden = true;
    }

    if (!parser.Found(wxT("c"), &mColorTemp))
    {
	mColorTemp = 0;	
    }
    else
    {
	mStartHidden = true;
    }

    if (!parser.Found(wxT("i"), &mGPUIndex))
    {
	mGPUIndex = 0;
    }

    if (parser.GetParamCount() > 0)
    {
        mProfileName = parser.GetParam(0);
	mStartHidden = true;
    }

    return true;
}

bool MainApp::OnInit()
{
    ADL* adl = ADL::Instance();
    
    if (!wxApp::OnInit())
    {
        return false;
    }

    if (adl == NULL)
    {
        wxMessageBox(wxT("Unable to initialize AMD ADL Library.\n\nThis program depends on the proprietary Catalyst drivers.\n"\
                         "Please check the driver installation."), wxT("Initialization problem"), wxOK|wxCENTRE|wxICON_ERROR);
        return false;
    }

    adl->SetGPUIndex(&mGPUIndex);

    if(!adl->IsATICardAndCatalystPresent())
    {
        wxMessageBox(wxT("Unable to initialize AMD ADL Library.\n\nThis program depends on the proprietary Catalyst drivers.\n"\
                         "Please check the driver installation."), wxT("Initialization problem"), wxOK|wxCENTRE|wxICON_ERROR);
        return false;
    }
    else
    {
	wxString line;
	wxString problem = wxT("Some functions are not supported by either\n"
			       "your hardware, the Catalyst driver or the ADL.\n\n"
			       "Here is a list of problems:\n");

	MissingFeatures = ~adl->UpdateData();

	if (MissingFeatures != 0)
	{
	    if (MissingFeatures & ADL::ERR_GET_TEMPERATURE_FAILED)
	    {
		line = wxT("failed to read the GPU temperature.");
		WRN_LOG(line.ToUTF8());
		problem += wxT("\n - ") + line;
	    }

	    if (MissingFeatures & ADL::ERR_GET_FANSPEED_INFO_FAILED)
	    {
		line = wxT("failed to get fan speed information.");
		WRN_LOG(line.ToUTF8());
		problem += wxT("\n - ") + line;
	    }

	    if (MissingFeatures & ADL::ERR_GET_CURRENT_FANSPEED_FAILED)
	    {
		line = wxT("failed to read current fan speed.");
		WRN_LOG(line.ToUTF8());
		problem += wxT("\n - ") + line;
	    }

	    if (MissingFeatures & ADL::ERR_GET_OD_PARAMETERS_FAILED)
	    {
		line = wxT("failed to get Overdrive parameters.");
		WRN_LOG(line.ToUTF8());
		problem += wxT("\n - ") + line;
	    }

	    if (MissingFeatures & ADL::ERR_GET_OD_PERF_LEVELS_FAILED)
	    {
		line = wxT("failed to get Overdrive performance levels.");
		WRN_LOG(line.ToUTF8());
		problem += wxT("\n - ") + line;
	    }	    

	    if (MissingFeatures & ADL::ERR_GET_ACTIVITY_FAILED)
	    {
		line = wxT("failed to read current GPU activity.");
		WRN_LOG(line.ToUTF8());
		problem += wxT("\n - ") + line;
	    }

	    if (MissingFeatures & ADL::ERR_GET_DEFAULTCLOCKINFO_FAILED)
	    {
		line = wxT("failed to read default GPU/Memory clocks.");
		WRN_LOG(line.ToUTF8());
		problem += wxT("\n - ") + line;
	    }
	}

	if (MissingFeatures != 0 && !mNoWarnings && argc == 1)
	{
	    problem += wxT("\n\nSome parts of the program will be disabled.");
	    wxMessageBox(problem, wxT("Problems occured!"), wxOK|wxCENTRE|wxICON_ERROR);

	    wxString tmp = wxString::FromAscii(adl->mpAdapterInfo[adl->GetGPUIndex()].strAdapterName);
	    if (tmp.Find(wxT("Mobility")) != wxNOT_FOUND)
	    {
		INF_LOG("Mobility Radeon chip detected.");
		wxMessageBox(wxT("Your hardware seems to be a Mobility Radeon chip.\nThe overdrive settings will probably only work, if your\nNotebook is connected to power line."), wxT("Information"), wxOK|wxCENTRE|wxICON_INFORMATION);
	    }
	}

	MainDialog* main_dialog = new MainDialog(NULL);

	if(getenv("HOME"))
	{
	    wxString file_path = wxString::FromAscii(getenv("HOME"));
	    file_path += wxT("/.AMDOverdriveCtrl");

	    #ifdef LINUX
		mkdir(file_path.ToUTF8(), 0700);
	    #else
		mkdir(file_path.ToUTF8());
	    #endif

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

	    #ifdef LINUX
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
	    #endif

	    // see if we have a default profile
	    filename = file_path +wxT("/default.ovdr");
	    if(mProfileName.IsEmpty() && wxFileExists(filename))
	    {
		if (main_dialog->LoadXML(filename))
		{
		    INF_LOG("Default profile found and loaded.");
		}
	    }
	}

	if (!mProfileName.IsEmpty())
	{
	    if (!main_dialog->LoadXML(mProfileName))
	    {
		wxMessageBox(wxT("\nThe specified startup profile '") + mProfileName + wxT("' is missing."), wxT("AMD/ATI OverdriveCtrl warning"), wxOK|wxCENTRE|wxICON_WARNING);
	    }
	    else
	    {
		INF_LOG("Profile '" << mProfileName.ToUTF8() << "' applied successfully.\n");
	    }
	}

	if (mColorTemp != 0)
	{
	    main_dialog->SetColorTemperature(mColorTemp);
	}

	if (mBatchMode)
	{
	    main_dialog->SetStartupProfileName(wxT(""));
	    delete main_dialog;
	    return false;
	}
	else if (mEnableAppProfiles)
	{
	    main_dialog->EnableAppProfiles();
	}

	if (mGPUIndex != 0)
	{
	    main_dialog->SetTitle(wxString::Format(wxT("AMDOverdriveCtrl  (Index %i)"),mGPUIndex));
	}

	SetTopWindow(main_dialog);

	if (!mStartHidden)
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
    , mpColorTempPanel(NULL)
    , mpPowertunePanel(NULL)
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
    mpAppProfilePanel = new CAppProfilePanel(mNotebook);
    mpOvdrSettingsPanel = new COvdrSettingsPanel(mNotebook);
    mpColorTempPanel = new CColorTempPanel(mNotebook);
    mpPowertunePanel = new CPowertunePanel(mNotebook);

    mpFanSpeedPanel->SetFanControlPanel(mpFanControlPanel);

    tmp.Rescale(20,20, wxIMAGE_QUALITY_HIGH);
    icon.CopyFromBitmap(tmp);

    mpTaskBarIcon = new CTaskBarIcon(this, mpAppProfilePanel, mpColorTempPanel);
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
	    && mpOvdrSettingsPanel != NULL && mpColorTempPanel != NULL && mpPowertunePanel != NULL)
	{
	    mNotebook->AddPage(mpAuthorPanel, wxT("?"));
	    mNotebook->AddPage(mpInfoPanel, wxT("Info"));
	    mNotebook->AddPage(mpOvdrSettingsPanel, wxT("Overdrive"));
	    //mNotebook->AddPage(mpPowertunePanel, wxT("Powertune"));
	    mNotebook->AddPage(mpFanSpeedPanel, wxT("FanSpeed"));
	    mNotebook->AddPage(mpFanControlPanel, wxT("FanCtrl"));
	    mNotebook->AddPage(mpAppProfilePanel, wxT("AppProfile"));
	    mNotebook->AddPage(mpColorTempPanel, wxT("Color"));
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
        if (mpFanSpeedPanel != NULL)
	{
	    mpFanSpeedPanel->StopTimer();
	}

        mpInfoPanel->UpdateDisplayValues();
    }
    else if(mNotebook->GetCurrentPage() == mpFanSpeedPanel)
    {
        mpInfoPanel->StopTimer();
        if (mpFanSpeedPanel != NULL)
	{
	    mpFanSpeedPanel->StartTimer();
	    mpFanSpeedPanel->UpdateDisplayValues();
	}
    }
    else
    {
        mpInfoPanel->StopTimer();
        if (mpFanSpeedPanel != NULL)
	{
	    mpFanSpeedPanel->StopTimer();
	}
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

void MainDialog::SetColorTemperature(int color_temp)
{
    mpColorTempPanel->SetColorTemperature(color_temp, true);
}

bool MainDialog::LoadXML(wxString filename)
{
    CTRL_POINTS ctrl_points;
    bool enable_fan_ctrl = false;

    if(wxFileExists(filename))
    {
	wxXmlDocument doc;

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

			wxString level = child->GetPropVal(wxT("level"), wxT("2"));
			wxString gpu = child->GetPropVal(wxT("gpu"), wxT("0"));
			wxString mem = child->GetPropVal(wxT("mem"), wxT("0"));
			wxString voltage = child->GetPropVal(wxT("voltage"), wxT("0"));

			level.ToLong(&llevel);
			gpu.ToLong(&lgpu);
			mem.ToLong(&lmem);
			voltage.ToLong(&lvoltage);

			mpOvdrSettingsPanel->SetOverdriveValues(llevel, lgpu/100, lmem/100, lvoltage);			
		    }
		    else if(child->GetName() == wxT("FAN_SETTING"))
		    {
			long percentage;
			wxString fanspeed = child->GetPropVal(wxT("percentage"), wxT("AUTO"));
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
			wxString enable = child->GetPropVal(wxT("enabled"), wxT("no"));
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
			wxString curve_type = child->GetPropVal(wxT("type"), wxT("0"));
			curve_type.ToLong(&type);

			mpFanControlPanel->SetCurveType(type);

		    }
		    else if (child->GetName() == wxT("FAN_CTRL_POINT"))
		    {
			long nr, temperature, percentage;

			wxString s_nr = child->GetPropVal(wxT("nr"), wxT("0"));
			wxString s_temperature = child->GetPropVal(wxT("temperature"), wxT("0"));
			wxString s_percentage = child->GetPropVal(wxT("percentage"), wxT("100"));

			s_nr.ToLong(&nr);
			s_temperature.ToLong(&temperature);
			s_percentage.ToLong(&percentage);

			ctrl_points[nr].x = (double)temperature / 100.0;
			ctrl_points[nr].y = (double)percentage / 100.0;

			if (nr == NR_OF_CTRL_POINTS-1)
			{
			    mpFanControlPanel->SetCtrlPoints(ctrl_points);
			    mpFanControlPanel->EnableFanControllerMode(enable_fan_ctrl, false);
			}
		    }
		    else if (child->GetName() == wxT("MONITOR_SAMPLE_TIME"))
		    {
			long time;

			wxString s_time = child->GetPropVal(wxT("interval"), wxT("10"));

			s_time.ToLong(&time);

			mpMonitorPanel->SetSampleTime(time);
		    }
		    else if (child->GetName() == wxT("COLOR_PROFILE"))
		    {
			bool enable;
			double longitude;
			double latitude;
			long color_temp_day;
			long color_temp_night;
			long transition;

			wxString tmp;

			tmp = child->GetPropVal(wxT("enabled"), wxT("no"));
			enable = tmp == wxT("yes") ? true : false;

			tmp = child->GetPropVal(wxT("longitude"), wxT("-13,5"));
			tmp.ToDouble(&longitude);

			tmp = child->GetPropVal(wxT("latitude"), wxT("52,5"));
			tmp.ToDouble(&latitude);

			tmp = child->GetPropVal(wxT("color_temp_day"), wxT("6500"));
			tmp.ToLong(&color_temp_day);

			tmp = child->GetPropVal(wxT("color_temp_night"), wxT("3400"));
			tmp.ToLong(&color_temp_night);

			tmp = child->GetPropVal(wxT("transition"), wxT("30"));
			tmp.ToLong(&transition);

			mpColorTempPanel->SetValues(enable, longitude, latitude, color_temp_day, color_temp_night, transition);
		    }
		    else if (child->GetName() == wxT("POWERTUNE"))
		    {
			wxString tmp;
			long percentage;
			
			tmp = child->GetPropVal(wxT("percentage"), wxT("0"));
			tmp.ToLong(&percentage);
			
			mpPowertunePanel->SetPowertuneSetting(percentage);			
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

    if((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
    {
	for(int i=adl->mODParameters.iNumberOfPerformanceLevels-1; i>=0; i--)
	{
	    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("PERFORMANCE_LEVEL"));
	    node->AddProperty(wxT("level"), wxString::Format(wxT("%d"), i));
	    node->AddProperty(wxT("gpu"), wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[i].iEngineClock));
	    node->AddProperty(wxT("mem"), wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[i].iMemoryClock));
	    node->AddProperty(wxT("voltage"), wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[i].iVddc));
	    root->AddChild(node);
	}
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

    bool enable;
    double longitude;
    double latitude;
    long color_temp_day;
    long color_temp_night;
    long transition;

    mpColorTempPanel->GetValues(enable, longitude, latitude, color_temp_day, color_temp_night, transition);

    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("COLOR_PROFILE"));
    node->AddProperty(wxT("enabled"), enable ? wxT("yes") : wxT("no"));
    node->AddProperty(wxT("longitude"), wxString::Format(wxT("%lf"), longitude));
    node->AddProperty(wxT("latitude"), wxString::Format(wxT("%lf"), latitude));
    node->AddProperty(wxT("color_temp_day"), wxString::Format(wxT("%d"), color_temp_day));
    node->AddProperty(wxT("color_temp_night"), wxString::Format(wxT("%d"), color_temp_night));
    node->AddProperty(wxT("transition"), wxString::Format(wxT("%d"), transition));
    root->AddChild(node);

    int percentage = mpPowertunePanel->GetPowertuneSetting();
    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("POWERTUNE"));
    node->AddProperty(wxT("percentage"), wxString::Format(wxT("%d"), percentage));
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
			ACT_LOG("Profile: " << (*it).AppName.ToUTF8() << ", " << (*it).ProfileName.ToUTF8() << " activated");
			mpAppProfilePanel->SetActiveProfile((*it).AppName);
			mpAppProfilePanel->SetActiveProfileIndex(index);
			mpAppProfilePanel->UpdateDisplay();
			Stop();
			Start(5*TIMER_INTERVAL);
		    }
		    else
		    {
			ERR_LOG("Failed to load profile " << (*it).AppName.ToUTF8());
		    }
		}

		++index;
	    }
	}
	else
	{
	    if (!IsAppRunning(mpAppProfilePanel->GetActiveProfile()))
	    {
		ACT_LOG(mpAppProfilePanel->GetActiveProfile().ToUTF8() << " closed.");
		if (mpAppProfilePanel->GetDefaultProfile().IsEmpty())
		{
		    mpFanSpeedPanel->SetDefaultFanSpeed();
		    mpAppProfilePanel->SetActiveProfile(wxT(""));
		    mpAppProfilePanel->SetActiveProfileIndex(-1);
		    mpAppProfilePanel->UpdateDisplay();
		}
		else
		{
		    ACT_LOG("Default Profile activated");
		    if (LoadXML(mpAppProfilePanel->GetDefaultProfile()))
		    {
			mpAppProfilePanel->SetActiveProfile(wxT(""));
			mpAppProfilePanel->SetActiveProfileIndex(-1);
			mpAppProfilePanel->UpdateDisplay();
		    }
		    else
		    {
			ERR_LOG("Failed to load default profile " << mpAppProfilePanel->GetDefaultProfile().ToUTF8());
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
	ACT_LOG("Profile: " << mpAppProfilePanel->GetManualProfile().ToUTF8() << " activated.");
	if (LoadXML(mpAppProfilePanel->GetManualProfile()))
	{
	    mpAppProfilePanel->SetManualProfile(wxT(""));
	}
	else
	{
	    ERR_LOG("Failed to load manual selected profile " << mpAppProfilePanel->GetManualProfile().ToUTF8());
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
