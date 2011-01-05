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


#ifndef _CFanControlPanel_h_
#define _CFanControlPanel_h_

#include <wx/wx.h>
#include "gui.h"
#include "adl.h"

class CFanSpeedPanel;

const int NR_OF_CTRL_POINTS = 5;
const int NR_OF_BEZIER_POINTS = 15;

typedef struct
{
    double x;
    double y;
} _POINT;

typedef _POINT CTRL_POINTS[NR_OF_CTRL_POINTS];
typedef _POINT BEZIER_POINTS[NR_OF_BEZIER_POINTS];

class CFanControlPanel : public CFanControlPanelBase, wxTimer
{
    public:

        CFanControlPanel(CFanSpeedPanel* FanSpeedPanel, wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxPoint(-1,15), const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
        virtual ~CFanControlPanel();

        void GetCtrlPoints(CTRL_POINTS& ctrl_points);
        void SetCtrlPoints(CTRL_POINTS& ctrl_points);

        int GetCurveType();
        void SetCurveType(int type);

	void EnableFanControllerMode(bool enable, bool reset_to_default=true);
	bool IsFanControllerEnabled();

    protected:

        ADL* adl;
	CFanSpeedPanel* mpFanSpeedPanel;

        CTRL_POINTS mCtrlPoints;
        BEZIER_POINTS mBezierPoints;

        int mTrackingPoint;
	bool mDisplayValues;

	wxPoint mMousePosition;
	wxPoint mMousePositionScreen;
	bool mForceFanSpeedSetting;

	double mLastPercentage;
	double mLastTemperature;

	virtual void OnPaint( wxPaintEvent& event );
        virtual void mButtonClearClick(wxCommandEvent& event);
        virtual void mCurveOnLeftDown(wxMouseEvent& event);
        virtual void mCurveOnLeftUp(wxMouseEvent& event);
        virtual void mCurveOnMotion(wxMouseEvent& event);
        virtual void mCurveTypeOnChoice(wxCommandEvent& event);
        virtual void mCurveOnEnterWindow(wxMouseEvent& event);
        virtual void mCurveOnLeaveWindow(wxMouseEvent& event);
	virtual void mEnableOnCheckBox(wxCommandEvent& event);

        void DrawGrid();

        void DrawBezier(wxWindowDC& dc);
        void DrawSteps(wxWindowDC& dc);
        void DrawLinear(wxWindowDC& dc);
        void CheckAndDrawEndPoints(wxWindowDC& dc);

        void InitCtrlPoints();

        void MapPointToScreen(wxPoint& p);
        void MapPointFromScreen(wxPoint& p);

        int FindNearestCtrlPoint(wxPoint p);

        void CalculateBezierPoints();

	int CalcFanPercentage(int temperature);

        void Notify();
};

#endif
