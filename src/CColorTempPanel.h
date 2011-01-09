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


#ifndef _CColorTempPanel_h_
#define _CColorTempPanel_h_

#include <wx/datetime.h>
#include <wx/wx.h>
#include "gui.h"
#include "adl.h"

class CColorTempPanel : public CColorTempPanelBase, public wxTimer
{
        enum STATES
        {
            INACTIVE,
            DAY,
            NIGHT,
            TRANSITION_FROM_DAY_TO_NIGHT,
            TRANSITION_FROM_NIGHT_TO_DAY,
	    TRANSITION_TO_DAY,
	    TRANSITION_TO_NIGHT
        };

    public:
        CColorTempPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxPoint(-1,15), const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
        virtual ~CColorTempPanel();

        void GetValues(bool& enable, double& longitude, double& latitude, long& color_temp_day, long& color_temp_night, long& transition);
        void SetValues(bool enable, double longitude, double latitude, long color_temp_day, long color_temp_night, long transition);

	void SetDefaultColorTemperature();
	void SetDayColorTemperature();
	void SetNightColorTemperature();
	void SetColorTemperature(int color_temp, bool manual_setting, unsigned char display = 255);

    protected:
        virtual void OnPaint(wxPaintEvent& event);
        virtual void mEnableOnCheckBox(wxCommandEvent& event);
        virtual void mLongitudeOnText(wxCommandEvent& event);
        virtual void mLatitudeOnText(wxCommandEvent& event);
        virtual void mColorTempDaySliderOnScroll(wxScrollEvent& event);
        virtual void mColorTempNightSliderOnScroll(wxScrollEvent& event);
        virtual void mTransitionSliderOnScroll(wxScrollEvent& event);
        virtual void mCurveOnLeftDown(wxMouseEvent& event);
	virtual void mCurveOnLeftUp(wxMouseEvent& event);
        virtual void mCurveOnMotion(wxMouseEvent& event);
        virtual void ButtonTestDayColorClick(wxCommandEvent& event);
        virtual void ButtonTestNightColorClick(wxCommandEvent& event);
	virtual void ButtonSetDayColorClick(wxCommandEvent& event);
	virtual void ButtonSetNightColorClick(wxCommandEvent& event);

        virtual void Notify();

        void CalculateSunriseAndSunset();

        void DrawDiagram();

        bool MapPointFromScreen(wxPoint& p, bool& only_color);
	double Distance(wxPoint p1, wxPoint p2);

        void SetMouseValues(wxPoint p);

	void TestColorTemperature(int color_temp);
	int GetColorTemperature(unsigned char display = 255);
	void EnableColorTemperatureCtrl(bool enable = true);

	ADL* adl;
	int mNrOfDisplays;
	LPADLDisplayInfo mpDisplayInfo;
	unsigned long mValidDisplays;

	int* mpColorTempAtStartup;
	int* mpColorTempDefault;
	int mMinColorTemp;
	int mMaxColorTemp;
	int mColorTempStep;

	int mColorTempScratch;

        wxDateTime mSunrise;
        wxDateTime mSunset;

        STATES mState;

	wxPoint mTrDayNight;
	wxPoint mTrNightDay;
	wxPoint mDragDayColor;
	wxPoint mDragNightColor;

	bool mManualColorSet;

};

#endif
