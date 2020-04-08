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


#ifndef _COvdrSettingsPanel_h_
#define _COvdrSettingsPanel_h_

#include <wx/wx.h>
#include "gui.h"

#include "CSettingsPanel.h"

class ADL;

class COvdrSettingsPanel : public COvdrSettingsPanelBase
{
    public:
        COvdrSettingsPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
        virtual ~COvdrSettingsPanel();

	void SetOverdriveValues(int PerfLevel, int gpu, int mem, int volt);

	bool CommitOverdriveValues();

	void UpdateDisplayValues();

    protected:
	ADL* adl;

        CSettingsPanel* mpSettingsPanelLow;
        CSettingsPanel* mpSettingsPanelMid;
        CSettingsPanel* mpSettingsPanelHigh;

	int* mGPU;
	int* mMem;
	int* mVoltage;

	virtual void mButtonSaveDefaultClick( wxCommandEvent& event );
	virtual void mButtonResetClick( wxCommandEvent& event );
	virtual void mButtonSetClick( wxCommandEvent& event );
};

#endif
