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


#include "COvdrSettingsPanel.h"
#include "adl.h"

COvdrSettingsPanel::COvdrSettingsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : COvdrSettingsPanelBase(parent, id, pos, size, style)
    , mpSettingsPanelLow(NULL)
    , mpSettingsPanelMid(NULL)
    , mpSettingsPanelHigh(NULL)
{
    adl = ADL::Instance();

    if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) ||
	!(adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
    {
	Show(false);
    }

    mpSettingsPanelLow = new CSettingsPanel(0, mOvdrNotebook);
    mpSettingsPanelMid = new CSettingsPanel(1, mOvdrNotebook);
    mpSettingsPanelHigh = new CSettingsPanel(2, mOvdrNotebook);

    if(mpSettingsPanelLow != NULL && mpSettingsPanelMid != NULL && mpSettingsPanelHigh != NULL)
    {
        mOvdrNotebook->AddPage(mpSettingsPanelLow, wxT("Low"));
        mOvdrNotebook->AddPage(mpSettingsPanelMid, wxT("Mid"));
        mOvdrNotebook->AddPage(mpSettingsPanelHigh, wxT("High"));
    }
    else
    {
        wxMessageBox(wxT("Unable to create Panels"), wxT("ERROR"), wxOK|wxCENTRE|wxICON_ERROR);
    }
}

COvdrSettingsPanel::~COvdrSettingsPanel()
{

}

void COvdrSettingsPanel::SetOverdriveValues(int PerfLevel, int gpu, int mem, int volt)
{
    if (PerfLevel >= 0 && PerfLevel < NR_OF_LEVELS)
    {
	mGPU[PerfLevel] = gpu;
	mMem[PerfLevel] = mem;
	mVoltage[PerfLevel] = volt;
    }
}

bool COvdrSettingsPanel::CommitOverdriveValues()
{
    if ((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
    {
    #ifdef FAKE_ATI_CARD
	for (int i=0; i<NR_OF_LEVELS; i++)
	{
	    printf("SetOverdriveValues: Level %d, %dMHz, %dMHz, %.3fV\n", i, mGPU[i], mMem[i], (double)mVoltage[i]/1000.0);
	}
	return true;
    #endif

	ADLODParameters para;
	ADLODPerformanceLevels* levels;

	ADL* adl = ADL::Instance();

	if(SAVE_CALL(adl->ADL_Overdrive5_ODParameters_Get)(0, &para) == ADL_OK)
	{
	    int perf_level_size = sizeof(ADLODPerformanceLevels) + sizeof(ADLODPerformanceLevel) * (para.iNumberOfPerformanceLevels - 1);
	    levels = (ADLODPerformanceLevels*)malloc(perf_level_size);
	    levels->iSize = perf_level_size;

	    if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Get)(0, 0, levels) == ADL_OK)
	    {
		for (int i=0; i<NR_OF_LEVELS; i++)
		{
		    levels->aLevels[i].iEngineClock = mGPU[i] * 100;
		    levels->aLevels[i].iMemoryClock = mMem[i] * 100;
		    levels->aLevels[i].iVddc = mVoltage[i];

		    printf("SetOverdriveValues: Level %d, %dMHz, %dMHz, %.3fV\n", i, mGPU[i], mMem[i], (double)mVoltage[i]/1000.0);
		}
	    }

	    if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Set)(0, levels) != ADL_OK)
	    {
		return false;
	    }

	    free(levels);
	    levels = NULL;

	    return true;
	}
	return false;
    }
    return true;
}

void COvdrSettingsPanel::UpdateDisplayValues()
{
    mpSettingsPanelLow->UpdateDisplayValues();
    mpSettingsPanelMid->UpdateDisplayValues();
    mpSettingsPanelHigh->UpdateDisplayValues();
}

void COvdrSettingsPanel::mButtonResetClick(wxCommandEvent& WXUNUSED(event))
{
    int level0, level1, level2;
    int gpu0, gpu1, gpu2;
    int mem0, mem1, mem2;
    int v0, v1, v2;

    mpSettingsPanelLow->GetResetValues(level0, gpu0, mem0, v0);
    mpSettingsPanelMid->GetResetValues(level1, gpu1, mem1, v1);
    mpSettingsPanelHigh->GetResetValues(level2, gpu2, mem2, v2);

    SetOverdriveValues(level0, gpu0, mem0, v0);
    SetOverdriveValues(level1, gpu1, mem1, v1);
    SetOverdriveValues(level2, gpu2, mem2, v2);

    CommitOverdriveValues();

    UpdateDisplayValues();
}

void COvdrSettingsPanel::mButtonSetClick(wxCommandEvent& WXUNUSED(event))
{
    int level0, level1, level2;
    int gpu0, gpu1, gpu2;
    int mem0, mem1, mem2;
    int v0, v1, v2;

    mpSettingsPanelLow->GetValues(level0, gpu0, mem0, v0);
    mpSettingsPanelMid->GetValues(level1, gpu1, mem1, v1);
    mpSettingsPanelHigh->GetValues(level2, gpu2, mem2, v2);

    if (mem0 != mem1 || mem1 != mem2)
    {
	if (wxMessageBox(wxT("You have choosen different memory clock settings\nfor the three performance levels.\n\n")
			 wxT("This is not recommended because you will\nencounter screen flickering at level changes.\n\n")
			 wxT("Are you sure you want to set these values?"), wxT("Are you sure?"), wxYES_NO|wxCENTRE|wxICON_WARNING) == wxNO)
	{
	    return;
	}
    }

    if (gpu0 <= gpu1 && gpu1 <= gpu2 && mem0 <= mem1 && mem1 <= mem2)
    {
	SetOverdriveValues(level0, gpu0, mem0, v0);
	SetOverdriveValues(level1, gpu1, mem1, v1);
	SetOverdriveValues(level2, gpu2, mem2, v2);

	CommitOverdriveValues();
    }
    else
    {
	wxMessageBox(wxT("\nThe choosen overdrive settings are not valid.\n\nFrequency settings must follow the rule:\n\n"
	 "low level <= mid level <= high level"), wxT("Invalid settings"), wxOK|wxCENTRE|wxICON_ERROR);
    }
}
