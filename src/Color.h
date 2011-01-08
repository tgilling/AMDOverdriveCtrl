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

#ifndef _COLORS_H_
#define _COLORS_H_

#include <wx/wx.h>

class Color
{
    public:
	static wxColour BLACK;
	static wxColour WHITE;
	static wxColour RED;
	static wxColour LIGHT_RED;
	static wxColour ORANGE;
	static wxColour BLUE;
	static wxColour LIGHT_BLUE;
	static wxColour CYAN;
	static wxColour MID_GRAY;
	static wxColour DARK_GRAY;
	static wxColour LIGHT_GRAY;
	static wxColour GREEN;
};

#endif

