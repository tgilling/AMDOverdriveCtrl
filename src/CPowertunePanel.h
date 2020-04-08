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


#ifndef _CPowertunePanel_h_
#define _CPowertunePanel_h_

#include <wx/wx.h>
#include "gui.h"

class ADL;

class CPowertunePanel : public CPowertunePanelBase
{
    public:
        CPowertunePanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxPoint(-1,15), const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
        virtual ~CPowertunePanel();
	
	long GetPowertuneSetting();
	void SetPowertuneSetting(long value);

    protected:
	ADL* adl;
	
        virtual void mPowertuneMinusOnButtonClick( wxCommandEvent& event );
        virtual void mPowertuneSliderOnScroll( wxScrollEvent& event );
        virtual void mPowertunePlusOnButtonClick( wxCommandEvent& event );
        virtual void mButtonSetOnButtonClick( wxCommandEvent& event );

};

#endif
