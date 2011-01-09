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

#ifndef _CTaskBarIcon_h_
#define _CTaskBarIcon_h_

#include <wx/wx.h>
#include <wx/taskbar.h>

class CAppProfilePanel;
class CColorTempPanel;

class CTaskBarIcon : public wxTaskBarIcon
{
    public:

        CTaskBarIcon(wxWindow* dialog, CAppProfilePanel* panel, CColorTempPanel* ctpanel);
        virtual ~CTaskBarIcon();

    protected:
        wxWindow* mpDialog;
	CAppProfilePanel* mpAppProfilePanel;
	CColorTempPanel* mpColorTempPanel;

        virtual wxMenu*	CreatePopupMenu();
        virtual void OnLeftDown(wxTaskBarIconEvent& event);
	virtual void OnMenuClick(wxCommandEvent& event);
};

#endif
