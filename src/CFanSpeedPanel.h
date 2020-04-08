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


#ifndef _CFanSpeedPanel_h_
#define _CFanSpeedPanel_h_

#include <wx/wx.h>
#include "gui.h"

class ADL;
class CFanControlPanel;

class CFanSpeedPanel : public CFanSpeedPanelBase, wxTimer
{
        static const int NR_OF_FAN_PROFILE_SAMPLES = 20;

    public:
        CFanSpeedPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
        virtual ~CFanSpeedPanel();

        void StartTimer();
        void StopTimer();

        void UpdateDisplayValues();

        bool SetFanSpeed(int percent, bool controller_mode = false);
        bool SetDefaultFanSpeed();

        bool HasFanSpeedFixedLevel();

        int GetFanSpeedSetting();
	
	void SetFanControlPanel(CFanControlPanel* FanControlPanel);

    protected:
        ADL* adl;
	
	CFanControlPanel* mpFanControlPanel;

        bool mFanSpeedLevelFixed;

        long mFanProfileData[NR_OF_FAN_PROFILE_SAMPLES][2];
        long mFanProfileDataValid;
        bool mFanProfilingActive;

        wxString mFanProfileDataFilePath;

        bool mDisplayValuesInChart;

        int mMousePositionX;
	int mMousePositionY;
	
        void DrawFanProfile();

        void Notify();	// timer callback

        virtual void mFanSpeedMinusClick(wxCommandEvent& event);
        virtual void mFanSpeedSliderOnScroll(wxScrollEvent& event);
        virtual void mFanSpeedPlusClick(wxCommandEvent& event);
        virtual void mButtonProfileClick(wxCommandEvent& event);
        virtual void mButtonSetClick(wxCommandEvent& event);
        virtual void mButtonDefaultClick(wxCommandEvent& event);
        virtual void OnPaint(wxPaintEvent& event);
        virtual void EnterPanel(wxMouseEvent& event);
        virtual void LeavePanel(wxMouseEvent& event);
        virtual void MouseMotion(wxMouseEvent& event);
	virtual void LeftDblClick(wxMouseEvent& event);
};

#endif
