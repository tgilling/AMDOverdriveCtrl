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


#include "CSettingsPanel.h"
#include "adl.h"

CSettingsPanel::CSettingsPanel(int PerfLevel, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CSettingsPanelBase(parent, id, pos, size, style)
    , adl(NULL)
    , mPerfLevel(0)
    , mGPUStartValue(0)
    , mMemStartValue(0)
    , mVoltageStartValue(0)
{
    adl = ADL::Instance();

    mPerfLevel = PerfLevel;

    UpdateDisplayValues();

    if((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
    {
	mGPUStartValue = adl->mpODPerformanceLevels->aLevels[mPerfLevel].iEngineClock;
	mMemStartValue = adl->mpODPerformanceLevels->aLevels[mPerfLevel].iMemoryClock;
	mVoltageStartValue = adl->mpODPerformanceLevels->aLevels[mPerfLevel].iVddc;

	mGPUFreqSlider->SetRange(adl->mODParameters.sEngineClock.iMin/100, adl->mODParameters.sEngineClock.iMax/100);
	mGPUFreqSlider->SetValue(adl->mpODPerformanceLevels->aLevels[mPerfLevel].iEngineClock/100);
	mMinGPUFreq->SetValue(wxString::Format(wxT("%d"), adl->mODParameters.sEngineClock.iMin/100));
	mMaxGPUFreq->SetValue(wxString::Format(wxT("%d"), adl->mODParameters.sEngineClock.iMax/100));

	mMemFreqSlider->SetRange(adl->mODParameters.sMemoryClock.iMin/100, adl->mODParameters.sMemoryClock.iMax/100);
	mMemFreqSlider->SetValue(adl->mpODPerformanceLevels->aLevels[mPerfLevel].iMemoryClock/100);
	mMinMemFreq->SetValue(wxString::Format(wxT("%d"), adl->mODParameters.sMemoryClock.iMin/100));
	mMaxMemFreq->SetValue(wxString::Format(wxT("%d"), adl->mODParameters.sMemoryClock.iMax/100));

	mVoltageSlider->SetRange(adl->mODParameters.sVddc.iMin, adl->mODParameters.sVddc.iMax);
	mVoltageSlider->SetValue(adl->mpODPerformanceLevels->aLevels[mPerfLevel].iVddc);
	mMinVoltage->SetValue(wxString::Format(wxT("%.3f"), (float)adl->mODParameters.sVddc.iMin/1000.0));
	mMaxVoltage->SetValue(wxString::Format(wxT("%.3f"), (float)adl->mODParameters.sVddc.iMax/1000.0));
    }
}

CSettingsPanel::~CSettingsPanel()
{

}

void CSettingsPanel::UpdateDisplayValues()
{
    adl->UpdateData();

    if((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
    {
	mCurrentGPUFreq->SetValue(wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[mPerfLevel].iEngineClock/100));
	mGPUFreqSlider->SetValue(adl->mpODPerformanceLevels->aLevels[mPerfLevel].iEngineClock/100);

	mCurrentMemFreq->SetValue(wxString::Format(wxT("%d"), adl->mpODPerformanceLevels->aLevels[mPerfLevel].iMemoryClock/100));
	mMemFreqSlider->SetValue(adl->mpODPerformanceLevels->aLevels[mPerfLevel].iMemoryClock/100);

	mCurrentVoltage->SetValue(wxString::Format(wxT("%.3f"), (float)adl->mpODPerformanceLevels->aLevels[mPerfLevel].iVddc/1000.0));
	mVoltageSlider->SetValue(adl->mpODPerformanceLevels->aLevels[mPerfLevel].iVddc);
    }
}

void CSettingsPanel::mGPUFreqMinusClick(wxCommandEvent& WXUNUSED(event))
{
    int step = adl->mODParameters.sEngineClock.iStep/100;
    int current = mGPUFreqSlider->GetValue();

    if (current-step >= adl->mODParameters.sEngineClock.iMin/100)
    {
	CheckGPUFreq(current-step);
    }
}

void CSettingsPanel::mGPUFreqSliderScroll(wxScrollEvent& WXUNUSED(event))
{
    CheckGPUFreq(mGPUFreqSlider->GetValue());
}

void CSettingsPanel::CheckGPUFreq(int value)
{
    int step = adl->mODParameters.sEngineClock.iStep/100;
    int stop_pos = adl->mODParameters.sEngineClock.iMin/100;

    while(abs(stop_pos - value) >= (step/2+step%2))
    {
        stop_pos += step;
    }

    value = stop_pos;

    mGPUFreqSlider->SetValue(value);
    mCurrentGPUFreq->SetValue(wxString::Format(wxT("%d"), value));
}

void CSettingsPanel::mGPUFreqPlusClick(wxCommandEvent& WXUNUSED(event))
{
    int step = adl->mODParameters.sEngineClock.iStep/100;
    int current = mGPUFreqSlider->GetValue();

    if (current+step <= adl->mODParameters.sEngineClock.iMax/100)
    {
	CheckGPUFreq(current+step);
    }
}

void CSettingsPanel::mMemFreqMinusClick(wxCommandEvent& WXUNUSED(event))
{
    int step = adl->mODParameters.sMemoryClock.iStep/100;
    int current = mMemFreqSlider->GetValue();

    if (current-step >= adl->mODParameters.sMemoryClock.iMin/100)
    {
	CheckMemFreq(current-step);
    }
}

void CSettingsPanel::mMemFreqSliderScroll(wxScrollEvent& WXUNUSED(event))
{
    CheckMemFreq(mMemFreqSlider->GetValue());
}

void CSettingsPanel::CheckMemFreq(int value)
{
    int step = adl->mODParameters.sMemoryClock.iStep/100;
    int stop_pos = adl->mODParameters.sMemoryClock.iMin/100;

    while(abs(stop_pos - value) > (step/2+step%2))
    {
        stop_pos += step;
    }

    value = stop_pos;

    mMemFreqSlider->SetValue(value);
    mCurrentMemFreq->SetValue(wxString::Format(wxT("%d"), value));
}

void CSettingsPanel::mMemFreqPlusClick(wxCommandEvent& WXUNUSED(event))
{
    int step = adl->mODParameters.sMemoryClock.iStep/100;
    int current = mMemFreqSlider->GetValue();

    if (current+step <= adl->mODParameters.sMemoryClock.iMax/100)
    {
	CheckMemFreq(current+step);
    }
}

void CSettingsPanel::mVoltageMinusClick(wxCommandEvent& WXUNUSED(event))
{
    int step = adl->mODParameters.sVddc.iStep;
    int current = mVoltageSlider->GetValue();

    if (current-step >= adl->mODParameters.sVddc.iMin)
    {
	CheckVoltage(current-step);
    }
}

void CSettingsPanel::mVoltageSliderScroll(wxScrollEvent& WXUNUSED(event))
{
    CheckVoltage(mVoltageSlider->GetValue());
}

void CSettingsPanel::CheckVoltage(int value)
{
    int step = adl->mODParameters.sVddc.iStep;
    int stop_pos = adl->mODParameters.sVddc.iMin;

    while(abs(stop_pos - value) > (step/2+step%2))
    {
        stop_pos += step;
    }

    value = stop_pos;

    mVoltageSlider->SetValue(value);
    mCurrentVoltage->SetValue(wxString::Format(wxT("%.3f"), (float)value/1000.0));
}

void CSettingsPanel::mVoltagePlusClick(wxCommandEvent& WXUNUSED(event))
{
    int step = adl->mODParameters.sVddc.iStep;
    int current = mVoltageSlider->GetValue();

    if (current+step <= adl->mODParameters.sVddc.iMax)
    {
	CheckVoltage(current+step);
    }
}

void CSettingsPanel::GetResetValues(int& PerfLevel, int& gpu, int& mem, int& voltage)
{
    PerfLevel = mPerfLevel;
    gpu = mGPUStartValue/100;
    mem = mMemStartValue/100;
    voltage = mVoltageStartValue;
}

void CSettingsPanel::GetValues(int& PerfLevel, int& gpu, int& mem, int& voltage)
{
    PerfLevel = mPerfLevel;
    gpu = mGPUFreqSlider->GetValue();
    mem = mMemFreqSlider->GetValue();
    voltage = mVoltageSlider->GetValue();
}
