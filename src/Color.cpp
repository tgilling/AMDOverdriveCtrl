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

#include <wx/wx.h>

#include "Color.h"

wxColour Color::BLACK = wxColour(0,0,0);
wxColour Color::WHITE = wxColour(255,255,255);
wxColour Color::RED = wxColour(240,50,50);
wxColour Color::LIGHT_RED = wxColour(240,110,110);
wxColour Color::ORANGE = wxColour(250,190,50);
wxColour Color::BLUE = wxColour(100,100,240);
wxColour Color::LIGHT_BLUE = wxColour(130,180,250);
wxColour Color::CYAN = wxColour(0,155,200);
wxColour Color::MID_GRAY = wxColour(175,175,175);
wxColour Color::DARK_GRAY = wxColour(100,100,100);
wxColour Color::LIGHT_GRAY = wxColour(240,240,240);
wxColour Color::GREEN = wxColour(50,240,50);
