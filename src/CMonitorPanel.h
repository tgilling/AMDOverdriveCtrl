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


#ifndef _CMonitorPanel_h_
#define _CMonitorPanel_h_

#include <wx/wx.h>
#include "gui.h"

class ADL;

class CMonitorPanel : public CMonitorPanelBase, wxTimer
{
    public:
        CMonitorPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxPoint(-1,15), const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
        virtual ~CMonitorPanel();

	int GetSampleTime();
	void SetSampleTime(int time);

    protected:
        ADL* adl;

        static const int NR_OF_SAMPLES = 300;

        int mNrOfValidValues;

        int mTemperatureValues[NR_OF_SAMPLES];
        float mTemperatureMin;
        float mTemperatureMax;
        int mSumTemperatureValues;

        int mFanSpeedValues[NR_OF_SAMPLES];
        float mFanSpeedMin;
        float mFanSpeedMax;
        int mSumFanSpeedValues;

	int mPerfLevelValues[NR_OF_SAMPLES];

        int mCurrentSampleIndex;

        int mSampleInterval;

        bool mDisplayValuesInChart;

        int mMousePositionX;

        void DrawGrid(wxPanel* panel);
        void DrawValues(wxPanel* panel, int* values, wxColour col);

        virtual void OnPaint(wxPaintEvent& event);
	virtual void mTimerSliderScroll(wxScrollEvent& event);
        virtual void mTemperatureSliderScroll(wxScrollEvent& event);
	virtual void mFanSpeedSliderScroll(wxScrollEvent& event);
	virtual void EnterPanel( wxMouseEvent& event );
	virtual void LeavePanel( wxMouseEvent& event );
	virtual void MouseMotion( wxMouseEvent& event );

        void Notify();

	void UpdateDisplay();
};

#endif
