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

#include <wx/mstream.h>

#include "CAuthorPanel.h"
#include "icon.png.h"
#include "Color.h"
#include "Revision.h"


CAuthorPanel::CAuthorPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : CAuthorPanelBase(parent, id, pos, size, style)
{
    wxString text1 =
        wxString::Format(wxT("\n\nAMDOverdriveCtrl\n\nV%d.%d.%d\n"), VERSION, REVISION, BUILD);

    wxString text2 = wxT("Copyright(c) Thorsten Gilling\n<tgilling@web.de>\n"
			 "\n\nThis program is free software\nYou can redistribute it "
			 "and/or modify it\nunder the terms of the GNU GPL2"
                     );

    wxString text3 = wxT("\n!!! USE AT YOUR OWN RISK !!!\n\nExperimental 'Powertune' feature\nwill only work on HD6xxx cards.");

    mText1->SetLabel(text1);
    mText2->SetLabel(text2);
    mText3->SetLabel(text3);
    mText3->SetForegroundColour(Color::RED);

    wxMemoryInputStream istream(IconPng, sizeof(IconPng));
    wxImage tmp(istream, wxBITMAP_TYPE_PNG);

    mBitmap->SetBitmap(tmp);
    mBitmap->SetSize(wxRect(0,0,100,100));
}

CAuthorPanel::~CAuthorPanel()
{

}

