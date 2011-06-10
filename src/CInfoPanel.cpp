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


#include "CInfoPanel.h"
#include "adl.h"
#include "Color.h"

const int TIMER_INTERVAL = 500;

CInfoPanel::CInfoPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CInfoPanelBase(parent, id, pos, size, style)
{
    if((adl = ADL::Instance()) != NULL)
    {
	UpdateDisplayValues();

	mDefaultGPUMHz->SetLabel(wxString::Format(wxT("GPU (%d)"), adl->mODClockInfo.sEngineClock.iDefaultClock/100));
	mDefaultMemMHz->SetLabel(wxString::Format(wxT("Mem (%d)"), adl->mODClockInfo.sMemoryClock.iDefaultClock/100));

	mInfoActivity->SetRange(100);

	mInactiveTextColor = mInfoLevelLow->GetForegroundColour();
	mActiveTextColor = Color::RED;

	if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) || !(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
	{
	    mInfoMinFanSpeed->Disable();
	    mInfoMaxFanSpeed->Disable();
	    mInfoCurrentFanSpeed->Disable();
	}

	if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_TEMPERATURE))
	{
	    mInfoTemperature->Disable();
	}

	if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS) ||
	    !(adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) ||
	    !(adl->GetSupportedFeatures() & ADL::FEAT_GET_ACTIVITY))
	{
	    mInfoOVGPULow->Disable();
	    mInfoOVGPUMid->Disable();
	    mInfoOVGPUHigh->Disable();

	    mInfoOVMemLow->Disable();
	    mInfoOVMemMid->Disable();
	    mInfoOVMemHigh->Disable();

	    mInfoOVVoltLow->Disable();
	    mInfoOVVoltMid->Disable();
	    mInfoOVVoltHigh->Disable();

	    mInfoLevelLow->Disable();
	    mInfoLevelMid->Disable();
	    mInfoLevelHigh->Disable();
	}
	
	if (adl->mODParameters.iNumberOfPerformanceLevels == 2)
	{
	    mInfoOVGPUMid->Disable();
	    mInfoOVMemMid->Disable();
	    mInfoOVVoltMid->Disable();
	    mInfoLevelMid->Disable();	    
	}
    }
    else
    {
        wxMessageBox(wxT("Unable to initialize AMD ADL Library.\nThis program needs the proprietary Catalyst drivers."), wxT("ERROR"));
    }
}

CInfoPanel::~CInfoPanel()
{
    StopTimer();
}

void CInfoPanel::StartTimer()
{
    Start(TIMER_INTERVAL, false);
}

void CInfoPanel::StopTimer()
{
    if(IsRunning())
    {
        Stop();
    }
}

void CInfoPanel::UpdateDisplayValues()
{
    if(adl != NULL)
    {
        adl->UpdateData();

        mInfoCardID->SetValue(wxString(adl->mpAdapterInfo[adl->GetGPUIndex()].strAdapterName, wxConvUTF8));

	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_TEMPERATURE)
	{
	    mInfoTemperature->SetValue(wxString::Format(wxT("%.2f °C"), (float)adl->mTemperature.iTemperature/1000.0));
	}
	else
	{
	    mInfoTemperature->SetValue(wxT("---"));
	}

        mInfoCurrentGPU->SetValue(wxString::Format(wxT("%d MHz"), adl->mODActivity.iEngineClock/100));
        mInfoCurrentMemory->SetValue(wxString::Format(wxT("%d MHz"), adl->mODActivity.iMemoryClock/100));

	if (adl->mODActivity.iVddc != 0.0)
	{
	    mInfoCurrentVoltage->SetValue(wxString::Format(wxT("%.3f V"), (float)adl->mODActivity.iVddc/1000.0));
	}
	else
	{
	    mInfoCurrentVoltage->SetValue(wxT("---"));
	}

	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO)
	{
	    mInfoMinFanSpeed->SetValue(wxString::Format(wxT("%d rpm"), adl->mFanSpeedInfo.iMinRPM));
	    mInfoMaxFanSpeed->SetValue(wxString::Format(wxT("%d rpm"), adl->mFanSpeedInfo.iMaxRPM));
	    mInfoCurrentFanSpeed->SetValue(wxString::Format(wxT("%d rpm"), adl->mCurrentFanSpeed.iFanSpeed));
	}
	else
	{
	    mInfoMinFanSpeed->SetValue(wxT("---"));
	    mInfoMaxFanSpeed->SetValue(wxT("---"));
	    mInfoCurrentFanSpeed->SetValue(wxT("---"));
	}

	if((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))	    
	{
	    mInfoOVGPULow->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[0].iEngineClock/100));
	    mInfoOVMemLow->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[0].iMemoryClock/100));
	    mInfoOVVoltLow->SetValue(wxString::Format(wxT("%.3f V"), (float)adl->mpODPerformanceLevels->aLevels[0].iVddc/1000.0));
	    
	    if (adl->mODParameters.iNumberOfPerformanceLevels == 2)
	    {
		mInfoOVGPUMid->SetValue(wxT("---"));
		mInfoOVMemMid->SetValue(wxT("---"));
		mInfoOVVoltMid->SetValue(wxT("---"));
		mInfoLevelMid->SetLabel(wxT("---"));

		mInfoOVGPUHigh->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[1].iEngineClock/100));
		mInfoOVMemHigh->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[1].iMemoryClock/100));
		mInfoOVVoltHigh->SetValue(wxString::Format(wxT("%.3f V"), (float)adl->mpODPerformanceLevels->aLevels[1].iVddc/1000.0));
	    }
	    else
	    {		
		mInfoOVGPUMid->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[1].iEngineClock/100));
		mInfoOVMemMid->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[1].iMemoryClock/100));
		mInfoOVVoltMid->SetValue(wxString::Format(wxT("%.3f V"), (float)adl->mpODPerformanceLevels->aLevels[1].iVddc/1000.0));

		mInfoOVGPUHigh->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[2].iEngineClock/100));
		mInfoOVMemHigh->SetValue(wxString::Format(wxT("%d MHz"), adl->mpODPerformanceLevels->aLevels[2].iMemoryClock/100));
		mInfoOVVoltHigh->SetValue(wxString::Format(wxT("%.3f V"), (float)adl->mpODPerformanceLevels->aLevels[2].iVddc/1000.0));		
	    }
	}
	else
	{
	    mInfoOVGPULow->SetValue(wxT("---"));
	    mInfoOVGPUMid->SetValue(wxT("---"));
	    mInfoOVGPUHigh->SetValue(wxT("---"));

	    mInfoOVMemLow->SetValue(wxT("---"));
	    mInfoOVMemMid->SetValue(wxT("---"));
	    mInfoOVMemHigh->SetValue(wxT("---"));

	    mInfoOVVoltLow->SetValue(wxT("---"));
	    mInfoOVVoltMid->SetValue(wxT("---"));
	    mInfoOVVoltHigh->SetValue(wxT("---"));
	}
	
        mInfoActivity->SetValue(adl->mODActivity.iActivityPercent);

	if (adl->mODActivity.iCurrentBusLanes != 0 && adl->mODActivity.iMaximumBusLanes != 0)
	{
	    mPCILanes->SetLabel(wxString::Format(wxT("(%d/%d, %d)"), adl->mODActivity.iCurrentBusLanes,
                                             adl->mODActivity.iMaximumBusLanes, adl->mODActivity.iCurrentBusSpeed/50));
	}

        switch(adl->mODActivity.iCurrentPerformanceLevel)
        {
            case 0:
            {
                mInfoLevelLow->SetForegroundColour(mActiveTextColor);
                mInfoLevelMid->SetForegroundColour(mInactiveTextColor);
                mInfoLevelHigh->SetForegroundColour(mInactiveTextColor);
            }
            break;

            case 1:
            {
		
		if (adl->mODParameters.iNumberOfPerformanceLevels == 2)
		{
		    mInfoLevelLow->SetForegroundColour(mInactiveTextColor);
		    mInfoLevelMid->SetForegroundColour(mInactiveTextColor);
		    mInfoLevelHigh->SetForegroundColour(mActiveTextColor);				    
		}
		else
		{
		    mInfoLevelLow->SetForegroundColour(mInactiveTextColor);
		    mInfoLevelMid->SetForegroundColour(mActiveTextColor);
		    mInfoLevelHigh->SetForegroundColour(mInactiveTextColor);		
		}
            }
            break;

            case 2:
            default:
            {
                mInfoLevelLow->SetForegroundColour(mInactiveTextColor);
                mInfoLevelMid->SetForegroundColour(mInactiveTextColor);
                mInfoLevelHigh->SetForegroundColour(mActiveTextColor);
            }
            break;
        }
    }
}

void CInfoPanel::Notify()
{
    UpdateDisplayValues();
}
