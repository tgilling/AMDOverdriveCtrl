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
#include "adl.h"

CColorTempPanel::CColorTempPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CColorTempPanelBase(parent, id, pos, size, style)
{
    adl = ADL::Instance();

    int caps, valid;
    adl->ADL_Display_ColorCaps_Get(0, 0, &caps, &valid);

    int current, def, min, max, step;
    if (adl->ADL_Display_Color_Get(0, 3, ADL_DISPLAY_COLOR_TEMPERATURE, &current, &def, &min, &max, &step) != ADL_OK)
    {
	cout << "shit" << endl;
    }

    if (adl->ADL_Display_Color_Set(0, 0, ADL_DISPLAY_COLOR_TEMPERATURE, 5000) != ADL_OK)
    {
	cout << "shit" << endl;
    }

    CalculateSunriseAndSunset();
}

CColorTempPanel::~CColorTempPanel()
{
    // nop
}

void CColorTempPanel::OnPaint(wxPaintEvent& event)
{
    DrawDiagram();
}

void CColorTempPanel::mColorTempDaySliderOnScroll(wxScrollEvent& event)
{
    int value = event.GetInt();
    mColorTempDay->SetValue(wxString::Format(wxT("%d"), value*5));
    if (value < mColorTempNightSlider->GetValue())
    {
	mColorTempNight->SetValue(wxString::Format(wxT("%d"), value*5));
	mColorTempNightSlider->SetValue(value);
    }
}

void CColorTempPanel::mColorTempNightSliderOnScroll(wxScrollEvent& event)
{
    int value = event.GetInt();
    mColorTempNight->SetValue(wxString::Format(wxT("%d"), value*5));
    if (value > mColorTempDaySlider->GetValue())
    {
	mColorTempDay->SetValue(wxString::Format(wxT("%d"), value*5));
	mColorTempDaySlider->SetValue(value);
    }
}

void CColorTempPanel::mTransitionSliderOnScroll(wxScrollEvent& event)
{
    int value = event.GetInt();

    if (value == 0)
    {
	mTransition->SetValue(wxT("30s"));
    }
    else
    {
	mTransition->SetValue(wxString::Format(wxT("%dmin"), value));
    }
}

void CColorTempPanel::mLatitudeOnText(wxCommandEvent& event)
{
    CalculateSunriseAndSunset();
}

void CColorTempPanel::mLongitudeOnText(wxCommandEvent& event)
{
    CalculateSunriseAndSunset();
}

void CColorTempPanel::SetMouseValues(wxPoint p)
{
    int is_on_day_side = MapPointFromScreen(p);

    mTransitionSlider->SetValue(p.x);
    mTransition->SetValue(wxString::Format(wxT("%dmin"), p.x));

    wxScrollEvent ev;
    ev.SetInt(p.y);

    if (is_on_day_side)
    {
	mColorTempDaySlider->SetValue(p.y);
	mColorTempDaySliderOnScroll(ev);
    }
    else
    {
	mColorTempNightSlider->SetValue(p.y);
	mColorTempNightSliderOnScroll(ev);
    }

    DrawDiagram();
}

void CColorTempPanel::mCurveOnLeftDown(wxMouseEvent& event)
{
    SetMouseValues(event.GetPosition());
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

    sunrise += longitude/15.0;
    sunset += longitude/15.0;

    double sunrise_min = fmod(sunrise, 1.0)*60.0;
    double sunset_min = fmod(sunset, 1.0)*60.0;

    mSunrise.Set(sunrise, sunrise_min);
    mSunset.Set(sunset, sunset_min);

    mSunrise = mSunrise.FromUTC();
    mSunset = mSunset.FromUTC();

    cout << "Sunrise:" << mSunrise.GetHour() << ":" << mSunrise.GetMinute() << endl;
    cout << "Sunset:" << mSunset.GetHour() << ":" << mSunset.GetMinute() << endl;

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

    for (double i=0; i<50; i++)//w/2; i+=w/100)
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

    dc.DrawLine(wxPoint(w/2, 17), wxPoint(w/2, h));

    double day_color_y = h - ((h-30) * (mColorTempDaySlider->GetValue()*5-3000) / 4000 + 15);
    double night_color_y = h - ((h-30) * (mColorTempNightSlider->GetValue()*5-3000) / 4000 + 15);

    double transition_start = (w/2) - ((w-100) * mTransitionSlider->GetValue() / 60) / 2;
    double transition_end   = (w/2) + ((w-100) * mTransitionSlider->GetValue() / 60) / 2;

    wxPoint p1(0,day_color_y);
    wxPoint p2(transition_start, day_color_y);
    wxPoint p3(transition_end, night_color_y);
    wxPoint p4(w, night_color_y);

    dc.SetPen(wxPen(Color::RED, 3));
    dc.DrawLine(p1, p2);
    dc.DrawLine(p2, p3);
    dc.DrawLine(p3, p4);

    dc.SetPen(wxPen(Color::LIGHT_RED, 1));
    dc.DrawLine(p1, p2);
    dc.DrawLine(p2, p3);
    dc.DrawLine(p3, p4);

    dc.SetBrush(Color::LIGHT_GRAY);
    dc.SetPen(wxPen(Color::BLACK));

    dc.DrawCircle(p2, 2);
    dc.DrawCircle(p3, 2);

    dc.SetTextForeground(Color::DARK_GRAY);
    dc.DrawText(wxString::Format(wxT("%d"), mColorTempDaySlider->GetValue()*5), wxPoint(2, day_color_y-16));
    dc.DrawText(wxString::Format(wxT("Sunrise: %2d:%02d"), mSunrise.GetHour(), mSunrise.GetMinute()), wxPoint(0, h-16));

    dc.SetTextForeground(Color::LIGHT_GRAY);
    dc.DrawText(wxString::Format(wxT("%d"), mColorTempNightSlider->GetValue()*5), wxPoint(w-30, night_color_y));
    dc.DrawText(wxString::Format(wxT("Sunset: %2d:%02d"), mSunset.GetHour(), mSunset.GetMinute()), wxPoint(w-84, 0));

    int t = mTransitionSlider->GetValue();
    if (t == 0)
    {
	dc.DrawText(wxT("30s"), wxPoint(w/2-10, 0));
    }
    else
    {
	dc.DrawText(wxString::Format(wxT("%2dmin"), t), wxPoint(w/2-18, 0));
    }
}

bool CColorTempPanel::MapPointFromScreen(wxPoint& p)
{
    int w, h;
    mCurve->GetSize(&w,&h);

    double diff_x = w/2-p.x;
    double t = abs(diff_x) * 60.0 / (double)(w-100.0);
    p.x = t*2;

    p.y = (h-15) - p.y;
    p.y = 3000 + p.y * 4000 / (h-30);

    if (p.x > 60)
    {
	p.x = 60;
    }

    if (p.y < 3000)
    {
	p.y = 3000;
    }

    if (p.y > 7000)
    {
	p.y = 7000;
    }

    p.y /= 5;

    return diff_x > 0 ? true : false;
}


void CColorTempPanel::GetValues(bool& enable, double& longitude, double& latitude, long& color_temp_day, long& color_temp_night, long& transition)
{
    enable = mEnable->GetValue();
    mLongitude->GetValue().ToDouble(&longitude);
    mLatitude->GetValue().ToDouble(&latitude);
    color_temp_day = mColorTempDaySlider->GetValue()*5;
    color_temp_night = mColorTempNightSlider->GetValue()*5;
    transition = mTransitionSlider->GetValue();
}

void CColorTempPanel::SetValues(bool enable, double longitude, double latitude, long color_temp_day, long color_temp_night, long transition)
{
    mEnable->SetValue(enable);
    mLongitude->SetValue(wxString::Format(wxT("%lf"), longitude));
    mLatitude->SetValue(wxString::Format(wxT("%lf"), latitude));
    mColorTempDaySlider->SetValue(color_temp_day/5);
    mColorTempDay->SetValue(wxString::Format(wxT("%d"), color_temp_day));
    mColorTempNightSlider->SetValue(color_temp_night/5);
    mColorTempNight->SetValue(wxString::Format(wxT("%d"), color_temp_night));
    mTransitionSlider->SetValue(transition);
    mTransition->SetValue(wxString::Format(wxT("%d"), transition));
    DrawDiagram();
}

void CColorTempPanel::mEnableOnCheckBox(wxCommandEvent& event)
{
    if (mLatitude->GetValue().IsEmpty() || mLongitude->GetValue().IsEmpty())
    {
	mEnable->SetValue(false);
	wxMessageBox(wxT("Please enter your geographic location."), wxT("Missing information"), wxOK|wxCENTER|wxICON_ERROR);
    }
    else
    {

    }
}

void CColorTempPanel::Notify()
{
}

