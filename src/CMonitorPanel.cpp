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


#include "CMonitorPanel.h"
#include "adl.h"
#include "Color.h"

CMonitorPanel::CMonitorPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CMonitorPanelBase(parent, id, pos, size, style)
    , mNrOfValidValues(0)
    , mTemperatureMin(0.0)
    , mTemperatureMax(120.0)
    , mSumTemperatureValues(0)
    , mFanSpeedMin(0)
    , mFanSpeedMax(0)
    , mSumFanSpeedValues(0)
    , mCurrentSampleIndex(0)
    , mSampleInterval(1000)
    , mDisplayValuesInChart(false)
    , mMousePositionX(0)
{
    adl = ADL::Instance();

    memset(mTemperatureValues, 0, sizeof(int)*NR_OF_SAMPLES);
    memset(mFanSpeedValues, 0, sizeof(int)*NR_OF_SAMPLES);
    memset(mPerfLevelValues, 0, sizeof(int)*NR_OF_SAMPLES);

    mFanSpeedMin = adl->mFanSpeedInfo.iMinRPM;
    mFanSpeedMax = adl->mFanSpeedInfo.iMaxRPM;

    mFanSpeedMin = adl->mFanSpeedInfo.iMinRPM;
    mFanSpeedMax = adl->mFanSpeedInfo.iMaxRPM;

    mTimerInterval->SetLabel(wxString::Format(wxT("%.1fs"), ((float)mSampleInterval/1000.0)));

    Start(mSampleInterval, false);

    if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED) ||
	!(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
    {
	mFanSpeedSlider->Disable();
    }

    if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_TEMPERATURE))
    {
	mTempSlider->Disable();
    }

    if (!(adl->GetSupportedFeatures() & ADL::FEAT_GET_ACTIVITY) &&
        !(adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED) &&
	!(adl->GetSupportedFeatures() & ADL::FEAT_GET_TEMPERATURE))
    {
	Show(false);
    }
}

CMonitorPanel::~CMonitorPanel()
{
    if (IsRunning())
    {
	Stop();
    }
}

void CMonitorPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    UpdateDisplay();
}

void CMonitorPanel::DrawGrid(wxPanel* panel)
{
    wxWindowDC dc(panel);

    wxColour background = panel->GetBackgroundColour();
    unsigned char r = background.Red();
    unsigned char g = background.Green();
    unsigned char b = background.Blue();

    dc.SetBrush(wxBrush(background));
    dc.SetPen(wxPen(Color::BLACK,0, wxTRANSPARENT));
    dc.DrawRectangle(wxPoint(0,0), wxSize(340, 95));

    for (int y=0; y<50; y++)
    {
	dc.SetBrush(wxColour(r-y*75/140, g-y*75/140, b-y*75/140));
	dc.DrawRectangle(wxPoint(11, 19+y*65/50), wxSize(299, 65/50+1));
    }

    dc.SetPen(wxPen(Color::MID_GRAY, 1));

    for(int i=1; i<5; i++)
    {
        dc.DrawLine(wxPoint(10,85-i*16), wxPoint(310,85-i*16));
    }

    for(int i=1; i<6; i++)
    {
        dc.DrawLine(wxPoint(10+i*60,21), wxPoint(10+i*60,85));
    }

    dc.SetPen(wxPen(Color::DARK_GRAY, 2));
    dc.DrawLine(wxPoint(10,21), wxPoint(10,85));
    dc.DrawLine(wxPoint(10,85), wxPoint(310,85));
    dc.DrawText(wxT("t"), wxPoint(320, 75));

    if(panel == mTemperature)
    {
        dc.SetTextForeground(Color::RED);
        dc.DrawText(wxString::Format(wxT("%.0f-%.0f °C"), fabs(mTemperatureMin), mTemperatureMax), wxPoint(5, 0));
    }
    else if(panel == mFanSpeed)
    {
        dc.SetTextForeground(Color::RED);
        dc.DrawText(wxString::Format(wxT("%.0f-%.0f rpm"), fabs(mFanSpeedMin), mFanSpeedMax), wxPoint(5, 0));
    }
    else
    {
        dc.SetTextForeground(Color::RED);

	switch(adl->mODActivity.iCurrentPerformanceLevel)
        {
            case 0:
            {
                dc.DrawText(wxT("LOW"), wxPoint(5, 0));
            }
            break;

            case 1:
            {
		if (adl->mODParameters.iNumberOfPerformanceLevels == 3)
		{
		    dc.DrawText(wxT("MID"), wxPoint(5, 0));		    
		}
		else
		{
		    dc.DrawText(wxT("HIGH"), wxPoint(5, 0));
		}
            }
            break;

            default:
            {
                dc.DrawText(wxT("HIGH"), wxPoint(5, 0));
            }
            break;
        }
    }

}

void CMonitorPanel::DrawValues(wxPanel* panel, int* values, wxColour col)
{
    wxPoint line_points[NR_OF_SAMPLES];
    int index = mCurrentSampleIndex;
    int count = 0;

    for(int i=0; i<NR_OF_SAMPLES; i++)
    {
        --index;

        if(index < 0)
        {
            index = NR_OF_SAMPLES-1;
        }

        if(values[index] != 0)
        {
            line_points[i].x = 9+300 - i;

            if(values == mTemperatureValues)
            {
                float min = mTemperatureMin;
                float max = mTemperatureMax-min;
                line_points[i].y = 85.0-((((float)values[index]-min*1000.0)*64.0/max)/1000.0);
            }
            else if(values == mFanSpeedValues)
            {
                float min = mFanSpeedMin;
                float max = mFanSpeedMax-min;
                line_points[i].y = 85.0-((((float)values[index]-min)*64.0/max));
            }
            else
            {
                float min = 0.6;
                float max = 3.75;
                line_points[i].y = 85.0-((((float)values[index]-min)*64.0/(max)));
            }

            ++count;
        }
    }

    wxWindowDC dc(panel);
    dc.SetPen(wxPen(col, 1));
    dc.DrawLines(count, line_points);

    if(mDisplayValuesInChart)
    {
        dc.SetPen(wxPen(Color::RED, 1, wxSHORT_DASH));
        dc.DrawLine(wxPoint(mMousePositionX,21), wxPoint(mMousePositionX, 85));

        int index = mCurrentSampleIndex - (310-mMousePositionX);

        if(index < 0)
        {
            index = NR_OF_SAMPLES + index;
        }

        if(values[index] != 0)
        {
            dc.SetTextForeground(col);

            if(values == mTemperatureValues)
            {
                dc.DrawText(wxString::Format(wxT("%.1f°C"), (float)values[index]/1000.0), wxPoint(mMousePositionX+4, 21));
            }
            else if(values == mFanSpeedValues)
            {
                dc.DrawText(wxString::Format(wxT("%d rpm"), values[index]), wxPoint(mMousePositionX+4, 21));
            }
            else
            {
                wxString level;

                switch(values[index])
                {
                    case 3:  { level = wxT("HIGH"); } break;
		    
                    case 2:  		    
		    { 
			if (adl->mODParameters.iNumberOfPerformanceLevels == 3)
			{
			    level = wxT("MID");  			    
			}
			else
			{
			    level = wxT("HIGH");
			}
		    } 
		    break;
		    
                    default: { level = wxT("LOW");  } break;
                }

                dc.DrawText(level, wxPoint(mMousePositionX+4, 21));
            }
        }
    }
}

void CMonitorPanel::Notify()
{
    if(adl != NULL)
    {
	adl->UpdateData();

	if(mNrOfValidValues < NR_OF_SAMPLES)
	{
	    mNrOfValidValues++;
	}

	mSumTemperatureValues -= mTemperatureValues[mCurrentSampleIndex];
	mTemperatureValues[mCurrentSampleIndex] = adl->mTemperature.iTemperature;
	mSumTemperatureValues += mTemperatureValues[mCurrentSampleIndex];

	mSumFanSpeedValues -= mFanSpeedValues[mCurrentSampleIndex];
	mFanSpeedValues[mCurrentSampleIndex] = adl->mCurrentFanSpeed.iFanSpeed;
	mSumFanSpeedValues += mFanSpeedValues[mCurrentSampleIndex];

	mPerfLevelValues[mCurrentSampleIndex] = adl->mODActivity.iCurrentPerformanceLevel+1;

	mCurrentSampleIndex++;
	mCurrentSampleIndex %= (NR_OF_SAMPLES);
    }

    UpdateDisplay();
}

void CMonitorPanel::mTemperatureSliderScroll(wxScrollEvent& WXUNUSED(event))
{
    float mean = (float)(mSumTemperatureValues/1000.0)/(float)mNrOfValidValues;
    mTemperatureMin = mean - (mean) * (float)mTempSlider->GetValue() / 100.0;
    mTemperatureMax = (120.0 - mean) * (float)mTempSlider->GetValue() / 100.0 + mean;
}

void CMonitorPanel::mFanSpeedSliderScroll(wxScrollEvent& WXUNUSED(event))
{
    float mean = (float)(mSumFanSpeedValues)/(float)mNrOfValidValues;
    mFanSpeedMin = mean - (mean) * (float)mFanSpeedSlider->GetValue() / 100.0;
    mFanSpeedMax = ((float)adl->mFanSpeedInfo.iMaxRPM - mean) * (float)mFanSpeedSlider->GetValue() / 100.0 + mean;
}

void CMonitorPanel::mTimerSliderScroll(wxScrollEvent& WXUNUSED(event))
{
    SetSampleTime(mTimerSlider->GetValue());
}

void CMonitorPanel::EnterPanel(wxMouseEvent& WXUNUSED(event))
{
    mDisplayValuesInChart = true;
}

void CMonitorPanel::LeavePanel(wxMouseEvent& WXUNUSED(event))
{
    mDisplayValuesInChart = false;
    UpdateDisplay();
}

void CMonitorPanel::MouseMotion(wxMouseEvent& event)
{
    mMousePositionX = event.GetX();

    if(mMousePositionX<10 || mMousePositionX>310)
    {
        mDisplayValuesInChart = false;
    }
    else
    {
        mDisplayValuesInChart = true;
    }

    UpdateDisplay();
}

int CMonitorPanel::GetSampleTime()
{
    return mTimerSlider->GetValue();
}

void CMonitorPanel::SetSampleTime(int time)
{
    if (time > 100)
    {
	Stop();
	mSampleInterval = 0;
	mTimerInterval->SetLabel(wxT("OFF"));
    }
    else
    {
	mSampleInterval = time * 100;
	mTimerInterval->SetLabel(wxString::Format(wxT("%.1fs"), (float)mSampleInterval/1000.0));
	Stop();
	Start(mSampleInterval, false);
    }
    mTimerSlider->SetValue(time);
}

void CMonitorPanel::UpdateDisplay()
{
    DrawGrid(mTemperature);
    DrawGrid(mFanSpeed);
    DrawGrid(mPerfLevel);

    if (adl->GetSupportedFeatures() & ADL::FEAT_GET_TEMPERATURE)
    {
	DrawValues(mTemperature, mTemperatureValues, Color::RED);
    }

    if ((adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
    {
	DrawValues(mFanSpeed, mFanSpeedValues, Color::RED);
    }

    if (adl->GetSupportedFeatures() & ADL::FEAT_GET_ACTIVITY)
    {
	DrawValues(mPerfLevel, mPerfLevelValues, Color::RED);
    }
}
