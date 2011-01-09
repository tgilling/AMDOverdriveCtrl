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

#include "CFanControlPanel.h"
#include "CFanSpeedPanel.h"
#include "BezierMath.h"
#include "Color.h"

const double MIN_TEMP = 20;
const double MAX_TEMP = 100;

const int LINEAR_CURVE_TYPE = 0;
const int STEPS_CURVE_TYPE = 1;
const int BEZIER_CURVE_TYPE = 2;

const int TIMER_INTERVAL = 200;

CFanControlPanel::CFanControlPanel(CFanSpeedPanel* FanSpeedPanel, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CFanControlPanelBase(parent, id, pos, size, style)
    , adl(NULL)
    , mpFanSpeedPanel(FanSpeedPanel)
    , mTrackingPoint(-1)
    , mDisplayValues(false)
    , mMousePosition(0, 0)
    , mMousePositionScreen(0, 0)
    , mForceFanSpeedSetting(false)
    , mLastPercentage(0.0)
    , mLastTemperature(0.0)
{
    adl = ADL::Instance();

    if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) ||
	!(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED) ||
	!(adl->GetSupportedFeatures() & ADL::FEAT_GET_TEMPERATURE))
    {
	Show(false);
	EnableFanControllerMode(false);
    }

    mCurveType->AppendString(wxT("Linear"));
    mCurveType->AppendString(wxT("Steps"));
    mCurveType->AppendString(wxT("Bezier"));
    mCurveType->Select(0);

    mCurrentTemperature->SetLabel(wxT(""));
    mCurrentFanSpeed->SetLabel(wxT(""));

    memset (mCtrlPoints, 0, sizeof(CTRL_POINTS));
    memset (mBezierPoints, 0, sizeof(BEZIER_POINTS));

    InitCtrlPoints();
}

CFanControlPanel::~CFanControlPanel()
{

}

void CFanControlPanel::GetCtrlPoints(CTRL_POINTS& ctrl_points)
{
    memcpy(ctrl_points, mCtrlPoints, sizeof(CTRL_POINTS));
}

void CFanControlPanel::SetCtrlPoints(CTRL_POINTS& ctrl_points)
{
    memcpy(mCtrlPoints, ctrl_points, sizeof(CTRL_POINTS));
    CalculateBezierPoints();
}

int CFanControlPanel::GetCurveType()
{
    return mCurveType->GetSelection();
}

void CFanControlPanel::SetCurveType(int type)
{
    mCurveType->SetSelection(type);
    DrawGrid();
}

void CFanControlPanel::OnPaint( wxPaintEvent& WXUNUSED(event))
{
    DrawGrid();
}

void CFanControlPanel::mButtonClearClick(wxCommandEvent& WXUNUSED(event))
{
    InitCtrlPoints();
    DrawGrid();
}

void CFanControlPanel::mCurveOnEnterWindow(wxMouseEvent& event)
{
    if (mMousePosition.x > 30 && mMousePosition.x < 336 && mMousePosition.y > 24 && mMousePosition.y < 300)
    {
	mDisplayValues = true;

	mMousePosition = event.GetPosition();
	mMousePositionScreen = event.GetPosition();
    }
}

void CFanControlPanel::mCurveOnLeaveWindow(wxMouseEvent& WXUNUSED(event))
{
    mDisplayValues = false;
    DrawGrid();
}

void CFanControlPanel::mCurveOnLeftDown(wxMouseEvent& event)
{
    mTrackingPoint = FindNearestCtrlPoint(event.GetPosition());
    mCurveOnMotion(event);
}

void CFanControlPanel::mCurveOnLeftUp(wxMouseEvent& event)
{
    mTrackingPoint = -1;
    mCurveOnMotion(event);
    if (mEnable->GetValue())
    {
	mForceFanSpeedSetting = true;
    }
}

void CFanControlPanel::mCurveOnMotion(wxMouseEvent& event)
{
    mMousePosition = event.GetPosition();

    if (mMousePosition.x > 30 && mMousePosition.x < 336 && mMousePosition.y > 24 && mMousePosition.y < 290)
    {
	mDisplayValues = true;

	mMousePosition = event.GetPosition();
	mMousePositionScreen = event.GetPosition();

	MapPointFromScreen(mMousePosition);

	if (mTrackingPoint != -1)
	{
	    if (mCurveType->GetSelection() != BEZIER_CURVE_TYPE)
	    {
		if (mTrackingPoint == 0)
		{
		    if (mMousePosition.x <= mCtrlPoints[mTrackingPoint+1].x)
		    {
			mCtrlPoints[mTrackingPoint].x = mMousePosition.x;
			mCtrlPoints[mTrackingPoint].y = mMousePosition.y;
		    }
		}
		else if (mTrackingPoint == NR_OF_CTRL_POINTS-1)
		{
		    if (mMousePosition.x >= mCtrlPoints[mTrackingPoint-1].x)
		    {
			mCtrlPoints[mTrackingPoint].x = mMousePosition.x;
			mCtrlPoints[mTrackingPoint].y = mMousePosition.y;
		    }
		}
		else
		{
		    if (mMousePosition.x >= mCtrlPoints[mTrackingPoint-1].x &&
			mMousePosition.x <= mCtrlPoints[mTrackingPoint+1].x)
		    {
			mCtrlPoints[mTrackingPoint].x = mMousePosition.x;
			mCtrlPoints[mTrackingPoint].y = mMousePosition.y;
		    }
		}
	    }
	    else
	    {
		mCtrlPoints[mTrackingPoint].x = mMousePosition.x;
		mCtrlPoints[mTrackingPoint].y = mMousePosition.y;

		CalculateBezierPoints();
	    }
	}	
    }
    else
    {
	mDisplayValues = false;
    }

    DrawGrid();
}

void CFanControlPanel::mCurveTypeOnChoice(wxCommandEvent& WXUNUSED(event))
{
    InitCtrlPoints();
    DrawGrid();
    if (mEnable->GetValue())
    {
	mForceFanSpeedSetting = true;
    }
}

void CFanControlPanel::DrawGrid()
{
    if ((adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
    {
	int temperature = mMousePosition.x;
	int percentage = CalcFanPercentage(temperature);

	wxWindowDC dc(mCurve);

	wxColour background = mCurve->GetBackgroundColour();
	unsigned char r = background.Red();
	unsigned char g = background.Green();
	unsigned char b = background.Blue();

	dc.SetBrush(wxBrush(background));
	dc.SetPen(wxPen(Color::BLACK, 0, wxTRANSPARENT));
	dc.DrawRectangle(wxPoint(0,0), wxSize(370, 310));

	for (int y=0; y<50; y++)
	{
	    dc.SetBrush(wxColour(r-y*75/140, g-y*75/140, b-y*75/140));
	    dc.DrawRectangle(wxPoint(32, 19+y*272/50), wxSize(302, 272/50+1));
	}

	dc.SetBrush(wxBrush(Color::LIGHT_GRAY));
	dc.SetPen(wxPen(Color::MID_GRAY, 1));
	dc.SetTextForeground(Color::RED);

	for(int i=0; i<5; i++)
	{
	    dc.DrawLine(wxPoint(30+i*76,19), wxPoint(30+i*76,295));
	    dc.DrawLine(wxPoint(25,290-i*68), wxPoint(340,290-i*68));

	    dc.DrawText(wxString::Format(wxT("%.0f"), MIN_TEMP+((MAX_TEMP-MIN_TEMP)/4.0)*i), wxPoint(30+i*76-11, 293));
	    dc.DrawText(wxString::Format(wxT("%.0f"), adl->mFanSpeedInfo.iMinPercent+((double)adl->mFanSpeedInfo.iMaxPercent-(double)adl->mFanSpeedInfo.iMinPercent)/4.0*i), wxPoint(5, 290-i*68-8));
	}

	dc.DrawText(wxT("°C"), wxPoint(348, 282));
	dc.DrawText(wxT("%"), wxPoint(25, 0));

	dc.SetPen(wxPen(Color::DARK_GRAY, 3));
	dc.DrawLine(wxPoint(30,20), wxPoint(30,290));
	dc.DrawLine(wxPoint(30,290), wxPoint(340,290));

	switch (mCurveType->GetSelection())
	{
	    case LINEAR_CURVE_TYPE:
	    {
		DrawLinear(dc);

	    }
	    break;

	    case STEPS_CURVE_TYPE:
	    {
		DrawSteps(dc);
	    }
	    break;

	    case BEZIER_CURVE_TYPE:
	    {
		DrawBezier(dc);
	    }
	    break;
	}

	if (mDisplayValues)
	{
	    if (mTrackingPoint == -1)
	    {
		dc.SetPen(wxPen(Color::RED, 1, wxSHORT_DASH));
		dc.DrawLine(wxPoint(mMousePositionScreen.x,20), wxPoint(mMousePositionScreen.x, 290));
	    }

	    if (mCurveType->GetSelection() != BEZIER_CURVE_TYPE ||
		mTrackingPoint == -1 || mTrackingPoint == 0 || mTrackingPoint == NR_OF_CTRL_POINTS-1)
	    {
		dc.DrawText(wxString::Format(wxT("%d°C"), temperature), wxPoint(mMousePositionScreen.x+17, mMousePositionScreen.y+10));
		dc.DrawText(wxString::Format(wxT("%d%%"), percentage), wxPoint(mMousePositionScreen.x+17, mMousePositionScreen.y+22));
	    }
	}

	if (mEnable->GetValue())
	{
	    if (mLastPercentage != 0.0 && mLastTemperature != 0.0)
	    {
		double screen_temp = 30.0 + (mLastTemperature-MIN_TEMP) * 304.0 / (MAX_TEMP-MIN_TEMP);
		double screen_percentage = 290.0 - (mLastPercentage - adl->mFanSpeedInfo.iMinPercent) * 262.0 / (adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent);

		wxPoint p1(screen_temp, 20);
		wxPoint p2(screen_temp, 290);
		wxPoint p3(30, screen_percentage);
		wxPoint p4(336, screen_percentage);

		dc.SetPen(wxPen(Color::BLUE, 2, wxSHORT_DASH));
		dc.DrawLine(p1, p2);
		dc.DrawLine(p3, p4);

		dc.SetTextForeground(Color::BLUE);
		dc.DrawText(wxString::Format(wxT("%.1f°C"), mLastTemperature), wxPoint(screen_temp-14,0));
		dc.DrawText(wxString::Format(wxT("%.0f%%"), mLastPercentage), wxPoint(340, screen_percentage-8));
	    }
	}
    }
}

void CFanControlPanel::DrawBezier(wxWindowDC& dc)
{
    CheckAndDrawEndPoints(dc);

    for (int i=0; i<NR_OF_BEZIER_POINTS-1; i++)
    {
	wxPoint p1(mBezierPoints[i].x, mBezierPoints[i].y);
	wxPoint p2(mBezierPoints[i+1].x, mBezierPoints[i+1].y);

	MapPointToScreen(p1);
	MapPointToScreen(p2);

	dc.SetPen(wxPen(Color::RED, 3));
	dc.DrawLine(p1, p2);

	dc.SetPen(wxPen(Color::LIGHT_RED, 1));
	dc.DrawLine(p1, p2);

	dc.SetPen(wxPen(Color::DARK_GRAY, 1));
	dc.DrawCircle(p1, 1);
	dc.DrawCircle(p2, 1);
    }

    for (int i=0; i<NR_OF_CTRL_POINTS; i++)
    {
	wxPoint p1(mCtrlPoints[i].x, mCtrlPoints[i].y);

	MapPointToScreen(p1);

	dc.SetPen(wxPen(Color::BLACK, 1));
	dc.DrawCircle(p1, 2);
    }
}

void CFanControlPanel::DrawSteps(wxWindowDC& dc)
{
    CheckAndDrawEndPoints(dc);

    for (int i=0; i<NR_OF_CTRL_POINTS-1; i++)
    {
	wxPoint p1(mCtrlPoints[i].x, mCtrlPoints[i].y);
	wxPoint p2(mCtrlPoints[i+1].x, mCtrlPoints[i].y);
	wxPoint p3(mCtrlPoints[i+1].x, mCtrlPoints[i+1].y);

	MapPointToScreen(p1);
	MapPointToScreen(p2);
	MapPointToScreen(p3);

	dc.SetPen(wxPen(Color::RED, 3));
	dc.DrawLine(p1, p2);
	dc.DrawLine(p2, p3);

	dc.SetPen(wxPen(Color::LIGHT_RED, 1));
	dc.DrawLine(p1, p2);
	dc.DrawLine(p2, p3);

	dc.SetPen(wxPen(Color::BLACK, 1));
	dc.DrawCircle(p1, 2);
	dc.DrawCircle(p3, 2);
    }
}

void CFanControlPanel::DrawLinear(wxWindowDC& dc)
{
    CheckAndDrawEndPoints(dc);

    for (int i=0; i<NR_OF_CTRL_POINTS-1; i++)
    {
	wxPoint p1(mCtrlPoints[i].x, mCtrlPoints[i].y);
	wxPoint p2(mCtrlPoints[i+1].x, mCtrlPoints[i+1].y);

	MapPointToScreen(p1);
	MapPointToScreen(p2);

	dc.SetPen(wxPen(Color::RED, 3));
	dc.DrawLine(p1, p2);

	dc.SetPen(wxPen(Color::LIGHT_RED, 1));
	dc.DrawLine(p1, p2);

	dc.SetPen(wxPen(Color::BLACK, 1));
	dc.DrawCircle(p1, 2);
	dc.DrawCircle(p2, 2);
    }
}

void CFanControlPanel::CheckAndDrawEndPoints(wxWindowDC& dc)
{
    if (mCtrlPoints[0].x != MIN_TEMP)
    {
	wxPoint p1(MIN_TEMP, mCtrlPoints[0].y);
	wxPoint p2(mCtrlPoints[0].x, mCtrlPoints[0].y);

	MapPointToScreen(p1);
	MapPointToScreen(p2);

	dc.SetPen(wxPen(Color::RED, 3));
	dc.DrawLine(p1, p2);

	dc.SetPen(wxPen(Color::LIGHT_RED, 1));
	dc.DrawLine(p1, p2);
    }

    if (mCtrlPoints[NR_OF_CTRL_POINTS-1].x != MAX_TEMP)
    {
	wxPoint p1(mCtrlPoints[NR_OF_CTRL_POINTS-1].x, mCtrlPoints[NR_OF_CTRL_POINTS-1].y);
	wxPoint p2(MAX_TEMP, mCtrlPoints[NR_OF_CTRL_POINTS-1].y);

	MapPointToScreen(p1);
	MapPointToScreen(p2);

	dc.SetPen(wxPen(Color::RED, 3));
	dc.DrawLine(p1, p2);

	dc.SetPen(wxPen(Color::LIGHT_RED, 1));
	dc.DrawLine(p1, p2);
    }
}

void CFanControlPanel::InitCtrlPoints()
{
    double m = ((double)adl->mFanSpeedInfo.iMaxPercent-(double)adl->mFanSpeedInfo.iMinPercent) / (MAX_TEMP-MIN_TEMP);

    for (int i=0; i<NR_OF_CTRL_POINTS; i++)
    {
	mCtrlPoints[i].x = MIN_TEMP + (MAX_TEMP-MIN_TEMP)/(NR_OF_CTRL_POINTS-1) * i;
	mCtrlPoints[i].y = m * (mCtrlPoints[i].x-MIN_TEMP) + adl->mFanSpeedInfo.iMinPercent;

	if (mCurveType->GetSelection() == STEPS_CURVE_TYPE)
	{
	    if (i!=0)
	    {
		mCtrlPoints[i].x -= (MAX_TEMP-MIN_TEMP)/(NR_OF_CTRL_POINTS-1)/2;
	    }
	}
    }

    CalculateBezierPoints();
}

void CFanControlPanel::MapPointToScreen(wxPoint& p)
{
    p.x = (p.x - MIN_TEMP) * 304 / (MAX_TEMP-MIN_TEMP);
    p.y = (p.y - adl->mFanSpeedInfo.iMinPercent) * 262.0 / (adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent);

    p.x = 30 + p.x;
    p.y = 290 - p.y;
}

void CFanControlPanel::MapPointFromScreen(wxPoint& p)
{
    p.x = p.x - 30;
    p.y = 290 - p.y;

    p.x = p.x * (MAX_TEMP-MIN_TEMP) / 304 + MIN_TEMP;
    p.y = adl->mFanSpeedInfo.iMinPercent + p.y * (adl->mFanSpeedInfo.iMaxPercent-adl->mFanSpeedInfo.iMinPercent) / 262 ;
}

int CFanControlPanel::FindNearestCtrlPoint(wxPoint p)
{
    int nearest = 0;
    double distance = 10000000000.0;

    MapPointFromScreen(p);

    for (int i=0; i<NR_OF_CTRL_POINTS; i++)
    {
	double a = fabs(p.x - mCtrlPoints[i].x);
	double b = fabs(p.y - mCtrlPoints[i].y);
	double c = sqrt(a*a+b*b);

	if (c < distance)
	{
	    distance = c;
	    nearest = i;
	}
    }

    return nearest;
}

void CFanControlPanel::CalculateBezierPoints()
{
    double step= (double)1.0 / (NR_OF_BEZIER_POINTS - 1);
    double t = 0.0;

    for (int bcnt = 0; bcnt < NR_OF_BEZIER_POINTS; bcnt++)
    {
	if ((1.0 - t) < 5e-6)
	{
	    t = 1.0;
	}

	mBezierPoints[bcnt].x = 0.0;
	mBezierPoints[bcnt].y = 0.0;

	for (int i = 0; i < NR_OF_CTRL_POINTS; i++)
	{
	    double basis = Bernstein(NR_OF_CTRL_POINTS - 1, i, t);
	    mBezierPoints[bcnt].x += basis * mCtrlPoints[i].x;
	    mBezierPoints[bcnt].y += basis * mCtrlPoints[i].y;
	}

	t += step;
    }
}

int CFanControlPanel::CalcFanPercentage(int temperature)
{
    if (temperature > MAX_TEMP)
    {
	return adl->mFanSpeedInfo.iMaxPercent;
    }

    if (temperature < MIN_TEMP)
    {
	return adl->mFanSpeedInfo.iMinPercent;
    }

    int curve_type = mCurveType->GetSelection();

    if (curve_type == BEZIER_CURVE_TYPE)
    {
	for (int i=0; i<NR_OF_BEZIER_POINTS; i++)
	{
	    if (temperature < mBezierPoints[i].x)
	    {
		if (i==0)
		{
		    return mCtrlPoints[i].y;
		}
		else
		{
		    double m = (mBezierPoints[i].y - mBezierPoints[i-1].y) / (mBezierPoints[i].x - mBezierPoints[i-1].x);
		    return m * (temperature - mBezierPoints[i-1].x) + mBezierPoints[i-1].y;
		}
	    }
	}
    }
    else
    {
	for (int i=0; i<NR_OF_CTRL_POINTS; i++)
	{
	    if (temperature < mCtrlPoints[i].x)
	    {
		if (i==0)
		{
		    return mCtrlPoints[i].y;
		}
		else
		{
		    if (curve_type == LINEAR_CURVE_TYPE)
		    {
			double m = (mCtrlPoints[i].y - mCtrlPoints[i-1].y) / (mCtrlPoints[i].x - mCtrlPoints[i-1].x);
			return m * (temperature - mCtrlPoints[i-1].x) + mCtrlPoints[i-1].y;
		    }
		    else
		    {
			return mCtrlPoints[i-1].y;
		    }
		}
	    }
	}
    }
    return mCtrlPoints[NR_OF_CTRL_POINTS-1].y;
}

void CFanControlPanel::EnableFanControllerMode(bool enable, bool reset_to_default)
{
    mEnable->SetValue(enable);

    if (!enable)
    {
	if (reset_to_default)
	{
	    mpFanSpeedPanel->SetDefaultFanSpeed();
	}
	Stop();
	mCurrentTemperature->SetLabel(wxT(""));
	mCurrentFanSpeed->SetLabel(wxT(""));

	INF_LOG("FanCtrl mode off");
    }
    else
    {
	if (!IsRunning())
	{
	    Start(TIMER_INTERVAL);

	    adl->UpdateData();

	    mCurrentTemperature->SetLabel(wxString::Format(wxT("%.1f °C"), adl->mTemperature.iTemperature / 1000.0));
	    mCurrentFanSpeed->SetLabel(wxString::Format(wxT("%d rpm"), adl->mCurrentFanSpeed.iFanSpeed));
	    mForceFanSpeedSetting = true;

	    INF_LOG("FanCtrl mode on");
	}
    }
}

bool CFanControlPanel::IsFanControllerEnabled()
{
    return mEnable->GetValue();
}

void CFanControlPanel::mEnableOnCheckBox(wxCommandEvent& WXUNUSED(event))
{
    EnableFanControllerMode(mEnable->GetValue());
}

void CFanControlPanel::Notify()
{
    const double HYSTERESIS = mCurveType->GetSelection() == STEPS_CURVE_TYPE ? 2.0 : 1.0;
    int percentage = 0;
    double temperature = 0.0;
    static int cnt = 0;
    static int min_time = 0;

    const int TIME_INTERVAL_NEW_SAMPLE = 1000;		// 1s
    const int MIN_TIME_SINCE_LAST_CHANGE = 10000;	// 10s

    adl->UpdateData();

    temperature = adl->mTemperature.iTemperature / 1000.0;
    percentage = CalcFanPercentage(temperature);

    if (++cnt * TIMER_INTERVAL >= TIME_INTERVAL_NEW_SAMPLE)
    {
	cnt = 0;
	mCurrentTemperature->SetLabel(wxString::Format(wxT("%.1f °C"), adl->mTemperature.iTemperature / 1000.0));
	mCurrentFanSpeed->SetLabel(wxString::Format(wxT("%d rpm"), adl->mCurrentFanSpeed.iFanSpeed));
    }

    if (mEnable->GetValue())
    {
	if ((++min_time*TIMER_INTERVAL >= (temperature > mLastTemperature ? MIN_TIME_SINCE_LAST_CHANGE / 2 : MIN_TIME_SINCE_LAST_CHANGE)
	    && fabs(temperature - mLastTemperature) >= HYSTERESIS) || mForceFanSpeedSetting)
	{
	    mLastPercentage = percentage;
	    mLastTemperature = temperature;
	    mpFanSpeedPanel->SetFanSpeed(percentage, true);
	    DrawGrid();
	    min_time = 0;
	}

	mForceFanSpeedSetting = false;
    }
}
