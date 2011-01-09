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

#include <iostream>
using namespace std;

#include "CColorTempPanel.h"
#include "Color.h"

const int MAX_TRANSITION_TIME = 60;

CColorTempPanel::CColorTempPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CColorTempPanelBase(parent, id, pos, size, style)
    , adl(NULL)
    , mNrOfDisplays(0)
    , mpDisplayInfo(NULL)
    , mValidDisplays(0)
    , mpColorTempAtStartup(NULL)
    , mpColorTempDefault(NULL)
    , mMinColorTemp(0)
    , mMaxColorTemp(100000)
    , mColorTempStep(0)
    , mSunrise()
    , mSunset()
    , mState(INACTIVE)
    , mTrDayNight(0,0)
    , mTrNightDay(0,0)
    , mDragDayColor(0,0)
    , mDragNightColor(0,0)
    , mManualColorSet(true)
{
    adl = ADL::Instance();

#ifdef FAKE_ATI_CARD
    mValidDisplays = 0;
#else
    if (SAVE_CALL(adl->ADL_Display_DisplayInfo_Get)(0, &mNrOfDisplays, &mpDisplayInfo, 0) != ADL_OK)
    {
	Show(false);
	mEnable->SetValue(false);
    }
    else
    {
	mpColorTempAtStartup = new int[mNrOfDisplays];
	mpColorTempDefault = new int[mNrOfDisplays];

	if (mpColorTempAtStartup == NULL || mpColorTempDefault == NULL)
	{
	    wxMessageBox(wxT("Out of memory!"), wxT("error"), wxOK|wxCENTER|wxICON_ERROR);
	    Show(false);
	    mEnable->SetValue(false);
	    return;
	}

	memset(mpColorTempAtStartup, 0, sizeof(int)*mNrOfDisplays);
	memset(mpColorTempDefault, 0, sizeof(int)*mNrOfDisplays);

	for (int i=0; i<mNrOfDisplays; i++)
	{
	    if ((mpDisplayInfo[i].iDisplayInfoValue & (ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED | ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED)) ==
		(ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED | ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED))
	    {
		int caps = 0;
		int valid = 0;
		if (SAVE_CALL(adl->ADL_Display_ColorCaps_Get)(0, i, &caps, &valid) == ADL_OK)
		{
		    if (caps & valid & ADL_DISPLAY_COLOR_TEMPERATURE)
		    {
			mValidDisplays |= (1<<i);
		    }
		}

	        int current, def, min, max, step;

	        if (SAVE_CALL(adl->ADL_Display_Color_Get)(0, i, ADL_DISPLAY_COLOR_TEMPERATURE, &current, &def, &min, &max, &step) == ADL_OK)
	        {
		    INF_LOG("Color temp disp(" << i << ") : ");
		    INF_LOG("current " << current << "K default " << def << "K");
		    INF_LOG("min " << min << "K max " << max << "K step " << step << "K");

		    mpColorTempAtStartup[i] = current;
		    mpColorTempDefault[i] = def;

		    if (mMinColorTemp < min)
		    {
			mMinColorTemp = min;
		    }

		    if (mMaxColorTemp > max)
		    {
			mMaxColorTemp = max;
		    }

		    if (mColorTempStep < step)
		    {
			mColorTempStep = step;
		    }
	        }
	    }
	}
    }
#endif

    if (mValidDisplays == 0)
    {
	Show(false);
    }
    else
    {
	mColorTempDaySlider->SetRange(mMinColorTemp/mColorTempStep, mMaxColorTemp/mColorTempStep);
	if (6500 > mMinColorTemp && 6500 < mMaxColorTemp)
	{
	    mColorTempDaySlider->SetValue(6500/mColorTempStep);
	    mColorTempDay->SetValue(wxT("6500"));
	}
	else
	{
	    mColorTempDaySlider->SetValue(mMaxColorTemp/mColorTempStep);
	    mColorTempDay->SetValue(wxString::Format(wxT("%d"), mMaxColorTemp));
	}

	mColorTempNightSlider->SetRange(mMinColorTemp/mColorTempStep, mMaxColorTemp/mColorTempStep);
	mColorTempNightSlider->SetValue(mMinColorTemp/mColorTempStep);
	mColorTempNight->SetValue(wxString::Format(wxT("%d"), mMinColorTemp));

	CalculateSunriseAndSunset();
    }
}

CColorTempPanel::~CColorTempPanel()
{
    if (!mManualColorSet)
    {
	for (int i=0; i<mNrOfDisplays; i++)
	{
	    SetColorTemperature(mpColorTempAtStartup[i], true, i);
	}
	Stop();
    }

    delete[] mpColorTempAtStartup;
    delete[] mpColorTempDefault;
}

void CColorTempPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    DrawDiagram();
}

void CColorTempPanel::mColorTempDaySliderOnScroll(wxScrollEvent& event)
{
    int value = event.GetInt();

    mColorTempDaySlider->SetValue(value);
    mColorTempDay->SetValue(wxString::Format(wxT("%d"), value*mColorTempStep));
    if (value < mColorTempNightSlider->GetValue())
    {
	mColorTempNight->SetValue(wxString::Format(wxT("%d"), value*mColorTempStep));
	mColorTempNightSlider->SetValue(value);
    }

    Stop();
    mEnable->SetValue(false);
}

void CColorTempPanel::mColorTempNightSliderOnScroll(wxScrollEvent& event)
{
    int value = event.GetInt();

    mColorTempNightSlider->SetValue(value);
    mColorTempNight->SetValue(wxString::Format(wxT("%d"), value*mColorTempStep));
    if (value > mColorTempDaySlider->GetValue())
    {
	mColorTempDay->SetValue(wxString::Format(wxT("%d"), value*mColorTempStep));
	mColorTempDaySlider->SetValue(value);
    }

    Stop();
    mEnable->SetValue(false);
}

void CColorTempPanel::mTransitionSliderOnScroll(wxScrollEvent& event)
{
    int value = event.GetInt();
    mTransition->SetValue(wxString::Format(wxT("%dmin"), value));    
}

void CColorTempPanel::mLatitudeOnText(wxCommandEvent& WXUNUSED(event))
{
    CalculateSunriseAndSunset();
}

void CColorTempPanel::mLongitudeOnText(wxCommandEvent& WXUNUSED(event))
{
    CalculateSunriseAndSunset();
}

void CColorTempPanel::SetMouseValues(wxPoint p)
{
    bool only_color = false;
    int is_on_day_side = MapPointFromScreen(p, only_color);

    if (!only_color)
    {
	mTransitionSlider->SetValue(p.x);
	mTransition->SetValue(wxString::Format(wxT("%dmin"), p.x));
    }

    wxScrollEvent ev;
    ev.SetInt(p.y);

    if (is_on_day_side)
    {
	mColorTempDaySlider->SetValue(p.y);
	mColorTempDaySliderOnScroll(ev);
	SetColorTemperature(mColorTempDaySlider->GetValue()*mColorTempStep, false);
    }
    else
    {
	mColorTempNightSlider->SetValue(p.y);
	mColorTempNightSliderOnScroll(ev);
	SetColorTemperature(mColorTempNightSlider->GetValue()*mColorTempStep, false);
    }

    DrawDiagram();
}

void CColorTempPanel::mCurveOnLeftDown(wxMouseEvent& event)
{
    mEnable->SetValue(false);
    mState = INACTIVE;
    Stop();
    mColorTempScratch = GetColorTemperature();
    SetMouseValues(event.GetPosition());
}

void CColorTempPanel::mCurveOnLeftUp(wxMouseEvent& WXUNUSED(event))
{
    SetColorTemperature(mColorTempScratch, false);
    DrawDiagram();
}

void CColorTempPanel::mCurveOnMotion(wxMouseEvent& event)
{
    if (event.m_leftDown)
    {
	SetMouseValues(event.GetPosition());
    }
}

void CColorTempPanel::CalculateSunriseAndSunset()
{
    // Algorithm based on ideas from "http://lexikon.astronomie.info/zeitgleichung/"

    const double RAD = M_PI/180.0;
    const double h = -(50.0/60.0)*RAD;
    double latitude, longitude;

    wxDateTime t = wxDateTime::Now();

    int day = t.GetDayOfYear();

    mLatitude->GetValue().ToDouble(&latitude);
    mLongitude->GetValue().ToDouble(&longitude);

    double B = M_PI * latitude / 180;

    double declination = 0.409526325277017*sin(0.0169060504029192*(day-80.0856919827619));

    double timediff = 12*acos((sin(h) - sin(B)*sin(declination)) / (cos(B)*cos(declination)))/M_PI;

    double timedeviation = -0.170869921174742*sin(0.0336997028793971*day + 0.465419984181394) - 0.129890681040717*sin(0.0178674832556871*day - 0.167936777524864);

    double sunrise = 12 - timediff - timedeviation;
    double sunset  = 12 + timediff - timedeviation;

    longitude = fmod(longitude, 15.0);

    sunrise -= longitude/15.0;
    sunset -= longitude/15.0;

    double sunrise_min = fmod(sunrise, 1.0)*60.0;
    double sunset_min = fmod(sunset, 1.0)*60.0;

    mSunrise.Set(sunrise, sunrise_min);
    mSunset.Set(sunset, sunset_min);

    mSunrise = mSunrise.FromUTC();
    mSunset = mSunset.FromUTC();

    DrawDiagram();
}

void CColorTempPanel::DrawDiagram()
{
    int iw, ih;
    double w, h;
    wxWindowDC dc(mCurve);

    mCurve->GetSize(&iw,&ih);
    w = iw;
    h = ih;

    unsigned char dr = 200;
    unsigned char dg = 230;
    unsigned char db = 250;

    unsigned char nr = 120;
    unsigned char ng = 135;
    unsigned char nb = 170;

    for (double i=0; i<50; i++)
    {
	wxColour dcol = wxColour(dr-i*1.7, dg-i*1.7, db-i*1.3);
	dc.SetBrush(dcol);
	dc.SetPen(wxPen(wxColour(dcol)));
	dc.DrawRectangle(wxPoint(i*(w/100.0), 0), wxSize(w/100.0+1, h));

	wxColour ncol = wxColour(nr-i*1.7, ng-i*1.7, nb-i*1.3);
	dc.SetBrush(ncol);
	dc.SetPen(wxPen(wxColour(ncol)));
	dc.DrawRectangle(wxPoint(w/2.0+i*(w/100.0), 0), wxSize(w/100.0+1, h));
    }

    dc.SetPen(wxPen(Color::DARK_GRAY));

    dc.DrawLine(wxPoint(w/2, 17), wxPoint(w/2, h-17));

    int day_color_y = h - ((h-30) * (mColorTempDaySlider->GetValue()*mColorTempStep-mMinColorTemp) / (mMaxColorTemp-mMinColorTemp) + 15);
    int night_color_y = h - ((h-30) * (mColorTempNightSlider->GetValue()*mColorTempStep-mMinColorTemp) / (mMaxColorTemp-mMinColorTemp) + 15);

    int transition_start = (w/2) - ((w-100) * mTransitionSlider->GetValue() / MAX_TRANSITION_TIME) / 2;
    int transition_end   = (w/2) + ((w-100) * mTransitionSlider->GetValue() / MAX_TRANSITION_TIME) / 2;

    wxPoint Start(0, day_color_y);
    mTrDayNight = wxPoint(transition_start, day_color_y);
    mTrNightDay = wxPoint(transition_end, night_color_y);
    wxPoint End(w, night_color_y);

    mDragDayColor = wxPoint(38, day_color_y-2);
    mDragNightColor = wxPoint(w-43, night_color_y-2);

    dc.SetPen(wxPen(Color::RED, 3));
    dc.DrawLine(Start, mTrDayNight);
    dc.DrawLine(mTrDayNight, mTrNightDay);
    dc.DrawLine(mTrNightDay, End);

    dc.SetPen(wxPen(Color::LIGHT_RED, 1));
    dc.DrawLine(Start, mTrDayNight);
    dc.DrawLine(mTrDayNight, mTrNightDay);
    dc.DrawLine(mTrNightDay, End);

    dc.SetBrush(Color::LIGHT_GRAY);
    dc.SetPen(wxPen(Color::BLACK));

    dc.DrawCircle(mTrDayNight, 2);
    dc.DrawCircle(mTrNightDay, 2);

    dc.DrawRectangle(mDragDayColor, wxSize(5,5));
    dc.DrawRectangle(mDragNightColor, wxSize(5,5));

    dc.SetTextForeground(Color::DARK_GRAY);
    dc.DrawText(wxString::Format(wxT("%d"), mColorTempDaySlider->GetValue()*mColorTempStep), wxPoint(2, day_color_y-16));
    dc.DrawText(wxString::Format(wxT("Sunrise: %2d:%02d"), mSunrise.GetHour(), mSunrise.GetMinute()), wxPoint(2, h-16));

    dc.SetTextForeground(Color::LIGHT_GRAY);
    dc.DrawText(wxString::Format(wxT("%d"), mColorTempNightSlider->GetValue()*mColorTempStep), wxPoint(w-30, night_color_y));
    dc.DrawText(wxString::Format(wxT("Sunset: %2d:%02d"), mSunset.GetHour(), mSunset.GetMinute()), wxPoint(w-84, 0));

    dc.DrawText(wxString::Format(wxT("%2dmin"), mTransitionSlider->GetValue()), wxPoint(w/2-18, 0));

    dc.DrawText(wxString::Format(wxT("%4dK"), GetColorTemperature()), wxPoint(w/2-17, h-16));
}

double CColorTempPanel::Distance(wxPoint p1, wxPoint p2)
{
    double a = fabs(p1.x-p2.x);
    double b = fabs(p1.y-p2.y);
    double c = sqrt(a*a+b*b);
    return c;
}

bool CColorTempPanel::MapPointFromScreen(wxPoint& p, bool& only_color)
{
    int w, h;
    mCurve->GetSize(&w,&h);

    only_color = false;

    if (p.x <= w/2)
    {
	if (Distance(mDragDayColor, p) <= Distance(mTrDayNight, p))
	{
	    only_color = true;
	}
    }
    else
    {
	if (Distance(mDragNightColor, p) <= Distance(mTrNightDay, p))
	{
	    only_color = true;
	}
    }

    double diff_x = w/2-p.x;
    double t = abs(diff_x) * MAX_TRANSITION_TIME / (double)(w-100.0);
    p.x = t*2;

    p.y = (h-15) - p.y;
    p.y = mMinColorTemp + p.y * (mMaxColorTemp-mMinColorTemp) / (h-30);

    if (p.x > MAX_TRANSITION_TIME)
    {
	p.x = MAX_TRANSITION_TIME;
    }

    if (p.x == 0)
    {
	p.x = 1;
    }

    if (p.y < mMinColorTemp)
    {
	p.y = mMinColorTemp;
    }

    if (p.y > mMaxColorTemp)
    {
	p.y = mMaxColorTemp;
    }

    p.y /= mColorTempStep;

    return diff_x > 0 ? true : false;
}


void CColorTempPanel::GetValues(bool& enable, double& longitude, double& latitude, long& color_temp_day, long& color_temp_night, long& transition)
{
    enable = mEnable->GetValue();
    mLongitude->GetValue().ToDouble(&longitude);
    mLatitude->GetValue().ToDouble(&latitude);
    color_temp_day = mColorTempDaySlider->GetValue()*mColorTempStep;
    color_temp_night = mColorTempNightSlider->GetValue()*mColorTempStep;
    transition = mTransitionSlider->GetValue();
}

void CColorTempPanel::SetValues(bool enable, double longitude, double latitude, long color_temp_day, long color_temp_night, long transition)
{
    if (mValidDisplays != 0)
    {
	mEnable->SetValue(enable);
	mLongitude->SetValue(wxString::Format(wxT("%.2lf"), longitude));
	mLatitude->SetValue(wxString::Format(wxT("%.2lf"), latitude));
	mColorTempDaySlider->SetValue(color_temp_day/mColorTempStep);
	mColorTempDay->SetValue(wxString::Format(wxT("%d"), color_temp_day));
	mColorTempNightSlider->SetValue(color_temp_night/mColorTempStep);
	mColorTempNight->SetValue(wxString::Format(wxT("%d"), color_temp_night));
	mTransitionSlider->SetValue(transition);
	mTransition->SetValue(wxString::Format(wxT("%dmin"), transition));
	EnableColorTemperatureCtrl(enable);
	INF_LOG("Sunrise:" << mSunrise.GetHour() << ":" << mSunrise.GetMinute());
	INF_LOG("Sunset:" << mSunset.GetHour() << ":" << mSunset.GetMinute());
    }
}

void CColorTempPanel::ButtonTestDayColorClick(wxCommandEvent& WXUNUSED(event))
{
    TestColorTemperature(mColorTempDaySlider->GetValue()*mColorTempStep);
}

void CColorTempPanel::ButtonTestNightColorClick(wxCommandEvent& WXUNUSED(event))
{
    TestColorTemperature(mColorTempNightSlider->GetValue()*mColorTempStep);
}

void CColorTempPanel::TestColorTemperature(int color_temp)
{
    int temp = GetColorTemperature();
    SetColorTemperature(color_temp, false);
    wxMessageBox(wxString::Format(wxT("\nColor temperature value: %dK"), color_temp), wxT("Test color temperature"));
    SetColorTemperature(temp, false);
}

int CColorTempPanel::GetColorTemperature(unsigned char display)
{
    if (display == 255)
    {
	for (int i=0; i<mNrOfDisplays; i++)
	{
	    if (mValidDisplays & (1<<i))
	    {
		int current, def, min, max, step;

		if (SAVE_CALL(adl->ADL_Display_Color_Get)(0, i, ADL_DISPLAY_COLOR_TEMPERATURE, &current, &def, &min, &max, &step) == ADL_OK)
		{
		    return current;
		}
	    }
	}
    }
    else
    {
	if (mValidDisplays & (1<<display))
	{
	    int current, def, min, max, step;

	    if (SAVE_CALL(adl->ADL_Display_Color_Get)(0, display, ADL_DISPLAY_COLOR_TEMPERATURE, &current, &def, &min, &max, &step) == ADL_OK)
	    {
		return current;
	    }
	}
    }
    return 6500;
}

void CColorTempPanel::SetColorTemperature(int color_temp, bool manual_setting, unsigned char display)
{
    if (display == 255)
    {
	for (int i=0; i<mNrOfDisplays; i++)
	{
	    if (mValidDisplays & (1<<i))
	    {
		if (SAVE_CALL(adl->ADL_Display_Color_Set)(0, i, ADL_DISPLAY_COLOR_TEMPERATURE, color_temp) != ADL_OK)
		{
		    ERR_LOG("Could not set color temperature value : " << color_temp << " for display " << (int) i);
		}
		else
		{
		    ACT_LOG("Color temperature: " << color_temp << "K set for display " << (int)i);
		}
	    }
	}
    }
    else
    {
	if (mValidDisplays & (1<<display))
	{
	    if (SAVE_CALL(adl->ADL_Display_Color_Set)(0, display, ADL_DISPLAY_COLOR_TEMPERATURE, color_temp) != ADL_OK)
	    {
		ERR_LOG("Could not set color temperature value : " << color_temp << " for display " << (int) display);
	    }
	    else
	    {
		ACT_LOG("Color temperature: " << color_temp << "K set for display " << (int)display);
	    }
	}
    }
    mManualColorSet = manual_setting;    
}

void CColorTempPanel::mEnableOnCheckBox(wxCommandEvent& WXUNUSED(event))
{
    if (mLatitude->GetValue().IsEmpty() || mLongitude->GetValue().IsEmpty())
    {
	mEnable->SetValue(false);
	wxMessageBox(wxT("Please enter your geographic location."), wxT("Missing information"), wxOK|wxCENTER|wxICON_ERROR);
    }
    else
    {
	EnableColorTemperatureCtrl(mEnable->GetValue());
    }
}

void CColorTempPanel::EnableColorTemperatureCtrl(bool enable)
{
    if (enable)
    {
	wxDateTime t = wxDateTime::Now();
	if (t >= mSunrise && t <= mSunset)
	{
	    mState = TRANSITION_TO_DAY;
	}
	else
	{
	    mState = TRANSITION_TO_NIGHT;
	}

	Start(100);

	mManualColorSet = false;
    }
    else
    {
	Stop();
	DrawDiagram();
    }
}

void CColorTempPanel::Notify()
{
    switch (mState)
    {
	case INACTIVE:
	{
	    Stop();
	}
	break;

	case DAY:
	{
	    double min = mTransitionSlider->GetValue() / 2;
	    wxTimeSpan ts(0, min);

	    if (wxDateTime::Now() + ts >= mSunset)
	    {
		Stop();
		mState = TRANSITION_FROM_DAY_TO_NIGHT;

		int time_left = (mSunset + ts - wxDateTime::Now()).GetSeconds().GetLo();

		if (time_left <= 0)
		{
		    time_left = 60;
		}

		int diff = abs(GetColorTemperature()-mColorTempNightSlider->GetValue()*mColorTempStep);
		double steps = diff / mColorTempStep;		

		Start(time_left /steps*1000);
	    }
	}
	break;

	case NIGHT:
	{
	    static bool new_day = false;

	    wxDateTime t = wxDateTime::Now();
	    double min = mTransitionSlider->GetValue() / 2;
	    wxTimeSpan ts(0, min);

	    if (t.GetHour() == 0 && t.GetMinute() == 0)
	    {
		new_day = true;
	    }

	    if (new_day && t + ts >= mSunrise)
	    {
		new_day = false;

		Stop();
		mState = TRANSITION_FROM_NIGHT_TO_DAY;

		int time_left = (mSunrise + ts - wxDateTime::Now()).GetSeconds().GetLo();

		if (time_left <= 0)
		{
		    time_left = 60;
		}

		int diff = abs(GetColorTemperature()-mColorTempDaySlider->GetValue()*mColorTempStep);
		double steps = diff / mColorTempStep;

		Start(time_left/steps*1000);
	    }
	}
	break;

	case TRANSITION_FROM_NIGHT_TO_DAY:
	case TRANSITION_TO_DAY:
	case TRANSITION_FROM_DAY_TO_NIGHT:
	case TRANSITION_TO_NIGHT:
	{
	    int target = 0;

	    if (mState == TRANSITION_FROM_NIGHT_TO_DAY || mState == TRANSITION_TO_DAY)
	    {
		target = mColorTempDaySlider->GetValue()*mColorTempStep;
	    }
	    else
	    {
		target = mColorTempNightSlider->GetValue()*mColorTempStep;
	    }

	    int current = GetColorTemperature();
	    if (current > target)
	    {
		current -= mColorTempStep;
	    }
	    else if (current < target)
	    {
		current += mColorTempStep;
	    }
	    else
	    {
		if (mState == TRANSITION_FROM_NIGHT_TO_DAY || mState == TRANSITION_TO_DAY)
		{
		    mState = DAY;
		}
		else
		{
		    mState = NIGHT;
		}
		Stop();
		Start(30*1000);
	    }
	    SetColorTemperature(current, false);
	    DrawDiagram();
	}
	break;

	default:
	{
	    mState = INACTIVE;
	}
	break;
    }
}

void CColorTempPanel::ButtonSetDayColorClick(wxCommandEvent& WXUNUSED(event))
{
    SetDayColorTemperature();
}

void CColorTempPanel::ButtonSetNightColorClick(wxCommandEvent& WXUNUSED(event))
{
    SetNightColorTemperature();
}

void CColorTempPanel::SetDayColorTemperature()
{
    SetColorTemperature(mColorTempDaySlider->GetValue()*mColorTempStep, true);
    Stop();
    mEnable->SetValue(false);
    DrawDiagram();    
}

void CColorTempPanel::SetDefaultColorTemperature()
{
    for (int i=0; i<mNrOfDisplays; i++)
    {
	SetColorTemperature(mpColorTempDefault[i], true, i);
    }
    Stop();
    mEnable->SetValue(false);
    DrawDiagram();
}

void CColorTempPanel::SetNightColorTemperature()
{
    SetColorTemperature(mColorTempNightSlider->GetValue()*mColorTempStep, true);
    Stop();
    mEnable->SetValue(false);
    DrawDiagram();    
}

