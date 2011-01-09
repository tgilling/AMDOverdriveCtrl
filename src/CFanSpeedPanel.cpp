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

#include "CFanSpeedPanel.h"
#include "CFanControlPanel.h"
#include "adl.h"
#include "Color.h"

const int TIMER_INTERVAL_PROFILE = 2000;
const int TIMER_INTERVAL = 1000;

CFanSpeedPanel::CFanSpeedPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CFanSpeedPanelBase(parent, id, pos, size, style)
    , adl(NULL)
    , mpFanControlPanel(NULL) 
    , mFanSpeedLevelFixed(false)
    , mFanProfileDataValid(0)
    , mFanProfilingActive(false)
    , mDisplayValuesInChart(false)
    , mMousePositionX(0)
    , mMousePositionY(0)
{
    adl = ADL::Instance();

    memset(mFanProfileData, 0, sizeof(mFanProfileData));

    if (getenv("HOME"))
    {
	mFanProfileDataFilePath = wxString::FromAscii(getenv("HOME"));
	mFanProfileDataFilePath += wxT("/.AMDOverdriveCtrl");
	
	#ifdef LINUX
		mkdir(mFanProfileDataFilePath.ToAscii(), 0750);
	#else
		mkdir(mFanProfileDataFilePath.ToAscii());
	#endif

	mFanProfileDataFilePath += wxT("/FanProfile.xml");

	if (wxFileExists(mFanProfileDataFilePath))
	{
	    wxXmlDocument doc;

	    if (doc.Load(mFanProfileDataFilePath))
	    {
		if (doc.GetRoot()->GetName() == wxT("FAN_PROFILE"))
		{
		    int index = 0;

		    wxXmlNode* child = doc.GetRoot()->GetChildren();

		    while (child && index < NR_OF_FAN_PROFILE_SAMPLES)
		    {
			if (child->GetName() == wxT("ACTIVE_DATA_SAMPLES"))
			{
			    wxString nr_of_samples = child->GetPropVal(wxT("samples"), wxT("0"));
			    nr_of_samples.ToLong(&mFanProfileDataValid);
			}
			else if (child->GetName() == wxT("SAMPLE"))
			{
			    wxString percentage = child->GetPropVal(wxT("percentage"), wxT("0"));
			    wxString fanspeed = child->GetPropVal(wxT("fanspeed"), wxT("0"));
			    percentage.ToLong(&mFanProfileData[index][0]);
			    fanspeed.ToLong(&mFanProfileData[index][1]);
			    ++index;
			}
			child = child->GetNext();
		    }
		}
	    }
	}
    }

    if ((adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
    {
	UpdateDisplayValues();
	mFanSpeedSlider->SetRange(adl->mFanSpeedInfo.iMinPercent, adl->mFanSpeedInfo.iMaxPercent);
	mFanSpeedSlider->SetValue(adl->mCurrentFanSpeed.iFanSpeed * 100 / adl->mFanSpeedInfo.iMaxRPM);
	mMinFanSpeed->SetValue(wxString::Format(wxT("%d %%"), adl->mFanSpeedInfo.iMinPercent));
	mMaxFanSpeed->SetValue(wxString::Format(wxT("%d %%"), adl->mFanSpeedInfo.iMaxPercent));
	mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), adl->mCurrentFanSpeed.iFanSpeed * 100 / adl->mFanSpeedInfo.iMaxRPM));
	mMinRPM->SetLabel(wxString::Format(wxT("%d"), adl->mFanSpeedInfo.iMinRPM));
	mMaxRPM->SetLabel(wxString::Format(wxT("%d"), adl->mFanSpeedInfo.iMaxRPM));
	SetDefaultFanSpeed();
    }
    else
    {
	Show(false);
    }
}

CFanSpeedPanel::~CFanSpeedPanel()
{
    if(IsRunning())
    {
        StopTimer();
    }
}

void CFanSpeedPanel::mFanSpeedMinusClick(wxCommandEvent& WXUNUSED(event))
{
    int current = mFanSpeedSlider->GetValue() - 1;

    if(current < adl->mFanSpeedInfo.iMinPercent)
    {
        current = adl->mFanSpeedInfo.iMinPercent;
    }

    mFanSpeedSlider->SetValue(current);
    mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), current));
}

void CFanSpeedPanel::mFanSpeedPlusClick(wxCommandEvent& WXUNUSED(event))
{
    int current = mFanSpeedSlider->GetValue() + 1;

    if(current > adl->mFanSpeedInfo.iMaxPercent)
    {
        current = adl->mFanSpeedInfo.iMaxPercent;
    }

    mFanSpeedSlider->SetValue(current);
    mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), current));
}

void CFanSpeedPanel::mFanSpeedSliderOnScroll(wxScrollEvent& WXUNUSED(event))
{
    int current = mFanSpeedSlider->GetValue();

    mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), current));
}

void CFanSpeedPanel::mButtonProfileClick(wxCommandEvent& WXUNUSED(event))
{
    mFanProfilingActive = true;
    mFanProfileDataValid = 0;

    DrawFanProfile();

    SetFanSpeed(adl->mFanSpeedInfo.iMinPercent);
    mFanProfileData[mFanProfileDataValid][0] = adl->mFanSpeedInfo.iMinPercent;

    mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), adl->mFanSpeedInfo.iMinPercent));
    mFanSpeedSlider->SetValue(adl->mFanSpeedInfo.iMinPercent);

    if(IsRunning())
    {
        Stop();
    }

    Start(TIMER_INTERVAL_PROFILE, false);
}

void CFanSpeedPanel::mButtonSetClick(wxCommandEvent& WXUNUSED(event))
{
    mpFanControlPanel->EnableFanControllerMode(false, false);
    SetFanSpeed(mFanSpeedSlider->GetValue());
    mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), mFanSpeedSlider->GetValue()));
    mFanSpeedLevelFixed = true;
}

void CFanSpeedPanel::mButtonDefaultClick(wxCommandEvent& WXUNUSED(event))
{
    SetDefaultFanSpeed();
}

bool CFanSpeedPanel::SetDefaultFanSpeed()
{
    if(SAVE_CALL(adl->ADL_Overdrive5_FanSpeedToDefault_Set)(0, 0) != ADL_OK)
    {
        return false;
    }
    else
    {
	ACT_LOG("Set fan speed to default");
	mTargetFanSpeed->SetValue(wxT("auto"));
	mFanSpeedSlider->SetValue((adl->mFanSpeedInfo.iMaxPercent - adl->mFanSpeedInfo.iMinPercent)/2+adl->mFanSpeedInfo.iMinPercent);
	mFanSpeedLevelFixed = false;
	return true;
    }
}

bool CFanSpeedPanel::SetFanSpeed(int percent, bool controller_mode)
{
    ADLFanSpeedValue speed_value;

    speed_value.iSize = sizeof(ADLFanSpeedValue);
    speed_value.iFlags = ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED;
    speed_value.iFanSpeed = percent;
    speed_value.iSpeedType = ADL_DL_FANCTRL_SPEED_TYPE_PERCENT;

    if(SAVE_CALL(adl->ADL_Overdrive5_FanSpeed_Set)(0, 0, &speed_value) != ADL_OK)
    {
	return false;
    }
    else
    {
	ACT_LOG("Fan speed set to " << percent << "%");
    }
    
    if (controller_mode)
    {
	mTargetFanSpeed->SetValue(wxT("ctrl on"));
    }
    return true;
}

void CFanSpeedPanel::UpdateDisplayValues()
{
    if(adl != NULL)
    {
        adl->UpdateData();
        mCurrentFanSpeed->SetLabel(wxString::Format(wxT("%d"), adl->mCurrentFanSpeed.iFanSpeed));
    }
}

void CFanSpeedPanel::StartTimer()
{
    Start(TIMER_INTERVAL, false);
}

void CFanSpeedPanel::StopTimer()
{
    Stop();

    if(mFanProfilingActive)
    {
        mFanProfilingActive = false;
    }
}

void CFanSpeedPanel::Notify()
{
    UpdateDisplayValues();

    if(mFanProfilingActive)
    {
        mFanProfileData[mFanProfileDataValid][1] = adl->mCurrentFanSpeed.iFanSpeed;
        ++mFanProfileDataValid;

        int step = (adl->mFanSpeedInfo.iMaxPercent - adl->mFanSpeedInfo.iMinPercent) / NR_OF_FAN_PROFILE_SAMPLES + 1;
        int new_percentage = adl->mFanSpeedInfo.iMinPercent + mFanProfileDataValid * step;

	mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), adl->mFanSpeedInfo.iMinPercent + (mFanProfileDataValid-1) * step));

        if(mFanProfileDataValid >= NR_OF_FAN_PROFILE_SAMPLES || new_percentage > (adl->mFanSpeedInfo.iMaxPercent+step))
        {
            mFanProfilingActive = false;
            Stop();
            Start(TIMER_INTERVAL, false);

	    wxXmlDocument doc;

	    wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("FAN_PROFILE"));

	    doc.SetRoot(root);

	    wxXmlNode* node;

	    node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("ACTIVE_DATA_SAMPLES"));
	    node->AddProperty(wxT("samples"), wxString::Format(wxT("%d"), mFanProfileDataValid));
	    root->AddChild(node);

	    for (int i=0; i<NR_OF_FAN_PROFILE_SAMPLES; i++)
	    {
		node = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("SAMPLE"));
		node->AddProperty(wxT("percentage"), wxString::Format(wxT("%d"), mFanProfileData[i][0]));
		node->AddProperty(wxT("fanspeed"), wxString::Format(wxT("%d"), mFanProfileData[i][1]));
		root->AddChild(node);
	    }

	    doc.Save(mFanProfileDataFilePath);

            wxCommandEvent dummy;
            mButtonDefaultClick(dummy);
        }
        else
        {
            if(new_percentage > adl->mFanSpeedInfo.iMaxPercent)
            {
                new_percentage = adl->mFanSpeedInfo.iMaxPercent;
            }

            mFanProfileData[mFanProfileDataValid][0] = new_percentage;
            SetFanSpeed(new_percentage);

            mFanSpeedSlider->SetValue(new_percentage);
        }

        DrawFanProfile();
    }
}

void CFanSpeedPanel::DrawFanProfile()
{
    if ((adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
    {
	wxWindowDC dc(mFanProfile);

	wxColour background = mFanProfile->GetBackgroundColour();
	unsigned char r = background.Red();
	unsigned char g = background.Green();
	unsigned char b = background.Blue();

	dc.SetBrush(wxBrush(background));
	dc.SetPen(wxPen(Color::BLACK,0, wxTRANSPARENT));
	dc.DrawRectangle(wxPoint(0,0), wxSize(370, 170));

	for (int y=0; y<50; y++)
	{
	    dc.SetBrush(wxColour(r-y*75/140, g-y*75/140, b-y*75/140));
	    dc.DrawRectangle(wxPoint(12, 19+y*140/50), wxSize(330, 140/50+1));
	}

	dc.SetPen(wxPen(Color::MID_GRAY, 1));

	for(int i=1; i<5; i++)
	{
	    dc.DrawLine(wxPoint(10+i*80,20), wxPoint(10+i*80,160));
	    dc.DrawLine(wxPoint(10,160-i*32), wxPoint(340,160-i*32));
	}

	dc.DrawText(wxT("%"), wxPoint(350, 152));
	dc.DrawText(wxT("rpm"), wxPoint(0, 0));

	dc.SetPen(wxPen(Color::DARK_GRAY, 3));
	dc.DrawLine(wxPoint(10,20), wxPoint(10,160));
	dc.DrawLine(wxPoint(10,160), wxPoint(340,160));

	if(mFanProfileDataValid > 0)
	{
	    dc.SetPen(wxPen(Color::RED, 3));

	    dc.DrawPoint(wxPoint((mFanProfileData[0][0]-adl->mFanSpeedInfo.iMinPercent) * 320 / (adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent) + 10, 160 - (mFanProfileData[0][1] * 132 / adl->mFanSpeedInfo.iMaxRPM)));

	    for(int i=1; i<mFanProfileDataValid; i++)
	    {
		wxPoint p1((mFanProfileData[i-1][0]-adl->mFanSpeedInfo.iMinPercent) * 320 / (adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent) + 10, 160 - (mFanProfileData[i-1][1] * 132 / adl->mFanSpeedInfo.iMaxRPM));
		wxPoint p2((mFanProfileData[i][0]-adl->mFanSpeedInfo.iMinPercent)   * 320 / (adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent) + 10, 160 - (mFanProfileData[i][1]   * 132 / adl->mFanSpeedInfo.iMaxRPM));

		dc.SetPen(wxPen(Color::RED, 3));
		dc.DrawLine(p1, p2);

		dc.SetPen(wxPen(Color::LIGHT_RED, 1));
		dc.DrawLine(p1, p2);
	    }

	    if(mDisplayValuesInChart)
	    {
		dc.SetPen(wxPen(Color::RED, 1, wxSHORT_DASH));
		dc.DrawLine(wxPoint(mMousePositionX,20), wxPoint(mMousePositionX, 160));

		int percentage = adl->mFanSpeedInfo.iMinPercent + (mMousePositionX-10)*(adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent)/320;

		if (percentage > adl->mFanSpeedInfo.iMaxPercent)
		{
		    percentage = adl->mFanSpeedInfo.iMaxPercent;
		}

		if (percentage < adl->mFanSpeedInfo.iMinPercent)
		{
		    percentage = adl->mFanSpeedInfo.iMinPercent;
		}

		dc.SetTextForeground(Color::RED);
		dc.DrawText(wxString::Format(wxT("%d%%"), percentage), wxPoint(mMousePositionX+4, mMousePositionY-34));

		int rpm = 0;
		int index = 0;
		while (index < mFanProfileDataValid && percentage >= mFanProfileData[index][0])
		{
		    index++;
		}

		if (index < mFanProfileDataValid)
		{
		    if (percentage == mFanProfileData[index-1][0])
		    {
			// sample point hit
			rpm = mFanProfileData[index-1][1];
		    }
		    else
		    {
			// between 2 points -> interpolate
			float m = (mFanProfileData[index][1]-mFanProfileData[index-1][1]) / (mFanProfileData[index][0]-mFanProfileData[index-1][0]);
			rpm = (percentage-mFanProfileData[index-1][0]) * m + mFanProfileData[index-1][1];
		    }
		}
		else if (index <= mFanProfileDataValid)
		{
		    // last sample point and beyond
		    rpm = mFanProfileData[mFanProfileDataValid-1][1];
		}

		if (rpm != 0)
		{
		    dc.DrawText(wxString::Format(wxT("%d rpm"), rpm), wxPoint(mMousePositionX+4, mMousePositionY-18));
		}
	    }
	}
    }
}

void CFanSpeedPanel::EnterPanel(wxMouseEvent& WXUNUSED(event))
{
    if(!mFanProfilingActive)
    {
	mDisplayValuesInChart = true;
    }
}

void CFanSpeedPanel::LeavePanel(wxMouseEvent& WXUNUSED(event))
{
    mDisplayValuesInChart = false;
}

void CFanSpeedPanel::MouseMotion(wxMouseEvent& event)
{
    if(!mFanProfilingActive)
    {
	mMousePositionX = event.GetX();
	mMousePositionY = event.GetY();

	if(mMousePositionX<10 || mMousePositionX>330)
	{
	    mDisplayValuesInChart = false;
	}
	else
	{
	    mDisplayValuesInChart = true;
	}

	DrawFanProfile();
    }
}

void CFanSpeedPanel::LeftDblClick(wxMouseEvent& event)
{
    mMousePositionX = event.GetX();
    mMousePositionY = event.GetY();
    int percentage = adl->mFanSpeedInfo.iMinPercent + (mMousePositionX-10)*(adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent)/320;

    mpFanControlPanel->EnableFanControllerMode(false, false);
    SetFanSpeed(percentage);
    mTargetFanSpeed->SetValue(wxString::Format(wxT("%d %%"), percentage));
    mFanSpeedLevelFixed = true;
}


void CFanSpeedPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    DrawFanProfile();
}

bool CFanSpeedPanel::HasFanSpeedFixedLevel()
{
    return mFanSpeedLevelFixed;
}

int CFanSpeedPanel::GetFanSpeedSetting()
{
    return mFanSpeedSlider->GetValue();
}

void CFanSpeedPanel::SetFanControlPanel(CFanControlPanel* FanControlPanel)
{
    mpFanControlPanel = FanControlPanel;
}
