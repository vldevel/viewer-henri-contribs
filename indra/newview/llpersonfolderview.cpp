/** 
* @file llpersonfolderview.cpp
* @brief Implementation of llpersonfolderview
* @author Gilbert@lindenlab.com
*
* $LicenseInfo:firstyear=2013&license=viewerlgpl$
* Second Life Viewer Source Code
* Copyright (C) 2013, Linden Research, Inc.
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation;
* version 2.1 of the License only.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*
* Linden Research, Inc., 945 Battery Street, San Francisco, CA  94111  USA
* $/LicenseInfo$
*/

#include "llviewerprecompiledheaders.h"

#include "llpersonfolderview.h"

static LLDefaultChildRegistry::Register<LLPersonFolderView> r_person_folder_view("person_folder_view");

const LLColor4U DEFAULT_WHITE(255, 255, 255);

LLPersonFolderView::Params::Params()
{}

LLPersonFolderView::LLPersonFolderView(const LLPersonFolderView::Params& p) :
LLFolderViewFolder(p)
{

}

S32 LLPersonFolderView::getLabelXPos()
{ 
	return getIndentation() + mArrowSize + 15;//Should be a .xml variable but causes crash;
}

LLPersonFolderView::~LLPersonFolderView()
{

}

void LLPersonFolderView::draw()
{
	static LLUIColor sFgColor = LLUIColorTable::instance().getColor("MenuItemEnabledColor", DEFAULT_WHITE);
	static const LLFolderViewItem::Params& default_params = LLUICtrlFactory::getDefaultParams<LLPersonFolderView>();

	static LLUIColor sHighlightBgColor = LLUIColorTable::instance().getColor("MenuItemHighlightBgColor", DEFAULT_WHITE);
	static LLUIColor sFlashBgColor = LLUIColorTable::instance().getColor("MenuItemFlashBgColor", DEFAULT_WHITE);
	static LLUIColor sFocusOutlineColor = LLUIColorTable::instance().getColor("MenuItemHighlightBgColor", DEFAULT_WHITE);
	static LLUIColor sMouseOverColor = LLUIColorTable::instance().getColor("DkGray", DEFAULT_WHITE);

	const LLFontGL * font = LLFontGL::getFontSansSerif();
	F32 text_left = (F32)getLabelXPos();
	F32 y = (F32)getRect().getHeight() - font->getLineHeight() - (F32)mTextPad;
	LLColor4 color = sFgColor;
	F32 right_x  = 0;

	drawHighlight(false, mIsSelected, sHighlightBgColor, sFlashBgColor, sFocusOutlineColor, sMouseOverColor);
	
	updateLabelRotation();
	drawOpenFolderArrow(default_params, sFgColor);

	drawLabel(font, text_left, y, color, right_x);

	LLView::draw();
}

//
// LLPersonFolderModel
// 


LLPersonView::Params::Params()
{}

LLPersonView::LLPersonView(const LLPersonView::Params& p) :
LLFolderViewItem(p)
{

}

S32 LLPersonView::getLabelXPos()
{
	return getIndentation();
}

void LLPersonView::addToFolder(LLFolderViewFolder * person_folder_view)
{
	LLFolderViewItem::addToFolder(person_folder_view);
	//Added item to folder, could change folder's mHasVisibleChildren flag so call arrange
	person_folder_view->requestArrange();
}

LLPersonView::~LLPersonView()
{

}

void LLPersonView::draw()
{
	static LLUIColor sFgColor = LLUIColorTable::instance().getColor("MenuItemEnabledColor", DEFAULT_WHITE);
	static LLUIColor sHighlightFgColor = LLUIColorTable::instance().getColor("MenuItemHighlightFgColor", DEFAULT_WHITE);

	const LLFontGL * font = LLFontGL::getFontSansSerifSmall();
	F32 text_left = (F32)getLabelXPos();
	F32 y = (F32)getRect().getHeight() - font->getLineHeight() - (F32)mTextPad;
	LLColor4 color = color = mIsSelected ? sHighlightFgColor : sFgColor;
	F32 right_x  = 0;

	drawLabel(font, text_left, y, color, right_x);

	LLView::draw();
}
