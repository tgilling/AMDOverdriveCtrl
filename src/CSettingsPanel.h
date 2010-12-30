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


#ifndef _CSettingsPanel_h_
#define _CSettingsPanel_h_

#include <wx/wx.h>
#include "gui.h"

class ADL;

class CSettingsPanel : public CSettingsPanelBase
{
    public:
        CSettingsPanel(int PerfLevel, wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
        virtual ~CSettingsPanel();

        void UpdateDisplayValues();

        void GetResetValues(int& PerfLevel, int& gpu, int& mem, int& voltage);

	void GetValues(int& PerfLevel, int& gpu, int& mem, int& voltage);

    protected:
        ADL* adl;

        int mPerfLevel;
        int mGPUStartValue;
        int mMemStartValue;
        int mVoltageStartValue;

        virtual void mGPUFreqMinusClick(wxCommandEvent& event);
        virtual void mGPUFreqSliderScroll(wxScrollEvent& event);
        virtual void mGPUFreqPlusClick(wxCommandEvent& event);
        virtual void mMemFreqMinusClick(wxCommandEvent& event);
        virtual void mMemFreqSliderScroll(wxScrollEvent& event);
        virtual void mMemFreqPlusClick(wxCommandEvent& event);
        virtual void mVoltageMinusClick(wxCommandEvent& event);
        virtual void mVoltageSliderScroll(wxScrollEvent& event);
        virtual void mVoltagePlusClick(wxCommandEvent& event);

        void CheckGPUFreq(int value);
        void CheckMemFreq(int value);
        void CheckVoltage(int value);
};

#endif
