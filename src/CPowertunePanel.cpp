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

#include "adl.h"
#include "CPowertunePanel.h"

CPowertunePanel::CPowertunePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CPowertunePanelBase(parent, id, pos, size, style)
    , adl(NULL)
{
    adl = ADL::Instance();

    mExperimental->SetForegroundColour(wxColour(250, 50, 50));

    if (adl->ADL_Overdrive5_PowerControl_Get == NULL || adl->ADL_Overdrive5_PowerControl_Set == NULL)
    {
        Show(false);
    }
    else
    {
        int percentage, dummy;
        SAVE_CALL(adl->ADL_Overdrive5_PowerControl_Get)(adl->GetGPUIndex(), &percentage, &dummy);
        mCurrentPowertune->SetLabel(wxString::Format(wxT("%d%%"), percentage));
    }
}

CPowertunePanel::~CPowertunePanel()
{

}

void CPowertunePanel::mPowertuneMinusOnButtonClick( wxCommandEvent& WXUNUSED(event) )
{
    int tmp = mPowertuneSlider->GetValue();

    if (tmp > -20)
    {
        --tmp;
        mPowertuneSlider->SetValue(tmp);
        mTargetPowertune->SetValue(wxString::Format(wxT("%d%%"), tmp));
    }
}

void CPowertunePanel::mPowertuneSliderOnScroll( wxScrollEvent& WXUNUSED(event) )
{
    int tmp = mPowertuneSlider->GetValue();
    mTargetPowertune->SetValue(wxString::Format(wxT("%d%%"), tmp));
}

void CPowertunePanel::mPowertunePlusOnButtonClick( wxCommandEvent& WXUNUSED(event))
{
    int tmp = mPowertuneSlider->GetValue();

    if (tmp < 20)
    {
        ++tmp;
        mPowertuneSlider->SetValue(tmp);
        mTargetPowertune->SetValue(wxString::Format(wxT("%d%%"), tmp));
    }
}

void CPowertunePanel::mButtonSetOnButtonClick( wxCommandEvent& WXUNUSED(event ))
{
    if (SAVE_CALL(adl->ADL_Overdrive5_PowerControl_Set)(adl->GetGPUIndex(), mPowertuneSlider->GetValue()) == ADL_OK)
    {
        int percentage, dummy;
        SAVE_CALL(adl->ADL_Overdrive5_PowerControl_Get)(adl->GetGPUIndex(), &percentage, &dummy);
        mCurrentPowertune->SetLabel(wxString::Format(wxT("%d%%"), percentage));
    }
    else
    {
        wxMessageBox(wxT("Failed to set Powertune value."), wxT("Problem!"), wxOK|wxCENTRE|wxICON_ERROR);
    }
}

long CPowertunePanel::GetPowertuneSetting()
{
    int percentage, dummy;
    SAVE_CALL(adl->ADL_Overdrive5_PowerControl_Get)(adl->GetGPUIndex(), &percentage, &dummy);
    return percentage;
}

void CPowertunePanel::SetPowertuneSetting(long value)
{
    if (SAVE_CALL(adl->ADL_Overdrive5_PowerControl_Set)(adl->GetGPUIndex(), value) == ADL_OK)
    {
        int percentage, dummy;
        SAVE_CALL(adl->ADL_Overdrive5_PowerControl_Get)(adl->GetGPUIndex(), &percentage, &dummy);
        mCurrentPowertune->SetLabel(wxString::Format(wxT("%d%%"), percentage));
    }
}
