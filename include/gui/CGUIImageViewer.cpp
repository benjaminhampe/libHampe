// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUIImageViewer.h"

namespace irr
{
namespace gui
{

//! constructor
CGUIImageViewer::CGUIImageViewer(
	IGUIEnvironment* env,
	IGUIElement* parent,
	s32 id,
	const core::rect<s32>& rectangle)
	: IGUIElement( EGUIET_ELEMENT, env, parent, id, rectangle)
{
#ifdef _DEBUG
	setDebugName("CGUIImageViewer");
#endif

	// this element can be tabbed to
	setTabStop(false);
	setTabOrder(-1);

	IGUISkin *skin = 0;
	if (Environment)
		skin = Environment->getSkin();

	//FrameRect.UpperLeftCorner.X += skin->getSize(EGDS_TEXT_DISTANCE_X)+1;
	//FrameRect.UpperLeftCorner.Y += skin->getSize(EGDS_TEXT_DISTANCE_Y)+1;
	//FrameRect.LowerRightCorner.X -= skin->getSize(EGDS_TEXT_DISTANCE_X)+1;
	//FrameRect.LowerRightCorner.Y -= skin->getSize(EGDS_TEXT_DISTANCE_Y)+1;

	TextColor=skin->getColor(EGDC_HIGH_LIGHT_TEXT);

	s32 w = rectangle.getWidth(); // in pixels
	s32 h = rectangle.getHeight(); // in pixels
	s32 sb_size = 16; // in pixels

	core::recti r_canvas = makeRect(0,0, (u32)(w-sb_size-1), (u32)(h-sb_size-1) );
	core::recti r_scrollH = makeRect(1,h-sb_size, (u32)(w-sb_size-1), (u32)sb_size );
	core::recti r_scrollV = makeRect( w-sb_size, 1, (u32)sb_size, (u32)(h-sb_size-1) );
	core::recti r_reset = makeRect( w-sb_size, h-sb_size, (u32)sb_size, (u32)sb_size );

	ScrollbarH = Environment->addScrollBar(true,r_scrollH,this,-1);
	ScrollbarH->setVisible(true);
	ScrollbarH->setSubElement(false);
	ScrollbarH->setTabStop(false);
	ScrollbarH->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	ScrollbarH->setSmallStep(3);
	ScrollbarH->setMin(0);
	ScrollbarH->setMax(100);
	ScrollbarH->setPos(0);

	ScrollbarV = Environment->addScrollBar(false,r_scrollV,this,-1);
	ScrollbarV->setVisible(true);
	ScrollbarV->setSubElement(false);
	ScrollbarV->setTabStop(false);
	ScrollbarV->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	ScrollbarV->setMin(0);
	ScrollbarV->setMax(100);
	ScrollbarV->setSmallStep(3);
	ScrollbarV->setPos(0);

	Environment->addButton( r_reset, this, -1, L"R", L"Reset Zoom Button");

	BackgroundColor=skin->getColor(EGDC_WINDOW);

	// Define the defaults strings for the interface
	menustring[GID_CUT]=L"Cut";
	menustring[GID_COPY]=L"Copy";
	menustring[GID_PASTE]=L"Paste";
	menustring[GID_DELETE]=L"Delete";
	menustring[GID_UNDO]=L"Undo";
	menustring[GID_REDO]=L"Redo";
	menustring[GID_LINECOUNT]=L"Toggle linecount display";


	ContentPane = 0;

	Environment->setFocus(this);
}


//! destructor
CGUIImageViewer::~CGUIImageViewer()
{

}

//void CGUIImageViewer::updateAbsolutePosition()
//{
//	core::rect<s32> oldAbsoluteRect(AbsoluteRect);
//	IGUIElement::updateAbsolutePosition();
//	if ( oldAbsoluteRect != AbsoluteRect )
//	{
//		breakText();
//	}
//}
//
//void CGUIImageViewer::setBackgroundColor(video::SColor color)
//{
//	BackgroundColor = color;
//}


//! called if an event happened.
bool CGUIImageViewer::OnEvent(const SEvent& event)
{
	if (IsEnabled)
	{
//
//		switch(event.EventType)
//		{
//		case EET_GUI_EVENT:
//			if (event.GUIEvent.EventType == gui::EGET_MENU_ITEM_SELECTED)
//			{
//				int sel = static_cast<IGUIContextMenu*>(event.GUIEvent.Caller)->getSelectedItem();
//
//				if (sel == CM_CUT)
//					cut();
//				else if (sel == CM_COPY)
//					copy();
//				else if (sel == CM_PASTE)
//					paste();
//				else if (sel == CM_DELETE)
//					deleteText();
//				else if (sel == CM_UNDO)
//					undo();
//				else if (sel == CM_REDO)
//					redo();
//
//
//				Environment->setFocus(this);
//				InMenu = false;
//			}
//			if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
//			{
//				if (event.GUIEvent.Caller == this)
//				{
//					MouseMarking = false;
//					OldMarkBegin = MarkBegin;
//					OldMarkEnd = MarkEnd;
//					//setTextMarkers(0,0);
//					Environment->setFocus(this);
//				}
//				break;
//			}
//			if (event.GUIEvent.EventType == EGET_EDITBOX_ENTER)
//			{
//				if (event.GUIEvent.Caller == this)
//				{
//
//				}
//				break;
//			}
//
//			if (event.GUIEvent.EventType == EGET_SCROLL_BAR_CHANGED)
//			{
//
//				if (event.GUIEvent.Caller == Scrollbar)
//				{
//					if (MultiLine || (WordWrap && BrokenText.size() > 1) )
//					{
//						IGUISkin* skin = Environment->getSkin();
//						IGUIFont* font = OverrideFont;
//						if (!OverrideFont)
//							font = skin->getFont();
//						s32 scrollMove = font->getDimension(L"O").Height;
//						VScrollPos = (s32)Scrollbar->getPos()*scrollMove;
//
//
//					}
//				}
//				break;
//			}
//
//			if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
//			{
//				if (event.GUIEvent.Caller == LineToggle)
//				{
//					if (LineNumbering)
//					{
//						LineNumbering=false;
//						breakText();
//						LeftSpace=0;
//						core::rect<s32> myRect(s32 x, s32 y, s32 w, s32 h);
//						core::rect<s32> localClipRect = this->myRect(FrameRect.UpperLeftCorner.X+LeftSpace,FrameRect.UpperLeftCorner.Y,FrameRect.getWidth()-(LeftSpace/2),FrameRect.getHeight());
//						localClipRect.clipAgainst(AbsoluteClippingRect);
//					}
//
//					else
//					{
//						LineNumbering=true;
//						breakText();
//						LeftSpace=60;
//						core::rect<s32> myRect(s32 x, s32 y, s32 w, s32 h);
//						core::rect<s32> localClipRect = this->myRect(FrameRect.UpperLeftCorner.X+LeftSpace,FrameRect.UpperLeftCorner.Y,FrameRect.getWidth()-(LeftSpace/2),FrameRect.getHeight());
//						localClipRect.clipAgainst(AbsoluteClippingRect);
//					}
//				}
//
//			}
//			break;
//
//		case EET_KEY_INPUT_EVENT:
//			if (processKey(event))
//				return true;
//			break;
//
//		case EET_MOUSE_INPUT_EVENT:
//			if (processMouse(event))
//				return true;
//			break;
//
//		default:
//			break;
//		}
	}

	return IGUIElement::OnEvent(event);
}

//! draws the element and its children
void CGUIImageViewer::draw()
{

	//calculateScrollPos();

	if (!IsVisible)
		return;

	const bool focus = Environment->hasFocus(this);

	IGUISkin* skin = Environment->getSkin();
	if (!skin)
		return;

//	core::list<IGUIElement*> children = getChildren();
//	for (core::list<IGUIElement*>::ConstIterator i = children.begin(); i != children.end(); i++) {
//		if ((*i)->getType() == gui::EGUIET_CONTEXT_MENU)
//			menuOpen = true;
//	}
	// draw children
	IGUIElement::draw();
}




bool CGUIImageViewer::OnMouse(const SEvent& event)
{
//	s32 value = 0;
//	switch(event.MouseInput.Event)
//	{
//	case EMIE_MOUSE_WHEEL:
//		value = (s32)-event.MouseInput.Wheel;
//
//		if (MultiLine || (WordWrap && BrokenText.size() > 1) )
//		{
//
//			int realVal = value;
//			if (Scrollbar->getPos()+value < Scrollbar->getMin())
//				realVal = (Scrollbar->getMin()-Scrollbar->getPos());
//			if (Scrollbar->getPos()+value > Scrollbar->getMax())
//				realVal = (Scrollbar->getMax()-Scrollbar->getPos());
//			Scrollbar->setPos(Scrollbar->getPos() + realVal);
//			IGUISkin* skin = Environment->getSkin();
//			IGUIFont* font = OverrideFont ? OverrideFont : skin->getFont();
//			int height = (s32)font->getDimension(L"O").Height;
//			VScrollPos=VScrollPos+height*(realVal);
//			/*s32 lineNo = getLineFromPos(CursorPos);
//			if (lineNo > 0)
//			{
//				s32 cp = CursorPos - BrokenTextPositions[lineNo];
//
//				if ((lineNo+value)>=lineCount-1)
//					value=0;
//
//				if ((lineNo+value)<0)
//					value=0;
//
//				if (value!=0)
//				{
//					if ((s32)BrokenText[lineNo-1].size() < cp)
//						CursorPos = BrokenTextPositions[lineNo+value] + (s32)BrokenText[lineNo+value].size()+value;
//					else
//						CursorPos = BrokenTextPositions[lineNo+value] + cp;
//				}
//			}
//			if (value!=0)
//				// Update the scrollbar
//				//Scrollbar->setPos(getLineFromPos(CursorPos));
//			calculateScrollPos();*/
//			return true;
//
//		}
//
//
//		break;
//	case EMIE_LMOUSE_LEFT_UP:
//		if (Environment->hasFocus(this))
//		{
//			if (!InMenu) {
//				if (!DoubleClicked) {
//					CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//					if (MouseMarking)
//					{
//						setTextMarkers( MarkBegin, CursorPos );
//					}
//
//					//Scrollbar->setPos(getLineFromPos(CursorPos));
//					calculateScrollPos();
//
//				}
//				MouseMarking = false;
//				DoubleClicked = false;
//			}
//			return true;
//		}
//		break;
//	case EMIE_MOUSE_MOVED:
//		{
//			if (MouseMarking)
//			{
//				CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//				setTextMarkers( MarkBegin, CursorPos );
//				//TODO: calculateScrollPos seem to have bugs
//				if (MarkBegin!=CursorPos)
//					calculateScrollPos();
//				/*IGUISkin* skin = Environment->getSkin();
//				IGUIFont* font = OverrideFont ? OverrideFont : skin->getFont();
//				int height = (s32)font->getDimension(L"O").Height;
//				s32 lineCount = isMultiLineEnabled() ? BrokenText.size() : 1;
//				float linesOnScreen = FrameRect.getHeight()/(float)height;
//				Scrollbar->setPos(std::max(0,getLineFromPos(CursorPos-linesOnScreen)));*/
//				return true;
//			}
//		}
//		break;
//	case EMIE_RMOUSE_LEFT_UP:
//		{
//			if (!InMenu) {
//				if (Environment->hasFocus(this))
//				{
//					if (!DoubleClicked) {
//						CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//						if (MouseMarking)
//						{
//							setTextMarkers( MarkBegin, CursorPos );
//						}
//
//						//Scrollbar->setPos(getLineFromPos(CursorPos));
//						calculateScrollPos();
//
//					}
//					MouseMarking = false;
//					DoubleClicked = false;
//				}
//			}
//			// Let's create a context menu if right mouse was clicked
//			core::recti rect(event.MouseInput.X,event.MouseInput.Y,event.MouseInput.X+1,event.MouseInput.Y);
//			rect.UpperLeftCorner -= AbsoluteRect.UpperLeftCorner;
//			rect.LowerRightCorner -= AbsoluteRect.UpperLeftCorner;
//			menu = Environment->addContextMenu(rect,this);
//			OldMarkBegin = MarkBegin;
//			OldMarkEnd = MarkEnd;
//
//			menu->addItem(menustring[CM_CUT].c_str());
//			menu->addItem(menustring[CM_COPY].c_str());
//			menu->addItem(menustring[CM_PASTE].c_str());
//			menu->addItem(menustring[CM_DELETE].c_str());
//			menu->addSeparator();
//			menu->addItem(menustring[CM_UNDO].c_str());
//			menu->addItem(menustring[CM_REDO].c_str());
//
//			InMenu = true;
//			return true;
//			break;
//		}
//	case EMIE_LMOUSE_DOUBLE_CLICK:
//		{
//			// Select the entire word
//			// Words are only alpha numerical characters, so something like != would not be selected in its entirety (Maybe add an option for the user to say what limits the word?)
//			CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//
//			// Now let's process the word
//			// First, find the beginning
//			int start, end;
//			start = end = 0;
//
//			for (int i = CursorPos; i > 0; i--) {
//				char character;
//				wcstombs(&character,&Text.c_str()[i],1);
//				if (!isalnum(character)) {
//
//					start = i+1;
//					break;
//				}
//			}
//			for (u32 i = CursorPos; i < Text.size(); i++) {
//				char character;
//				wcstombs(&character,&Text.c_str()[i],1);
//				if (!isalnum(character)) {
//
//					end = i;
//					break;
//				}
//				if (i == Text.size()-1)
//					end = i+1;
//			}
//			setTextMarkers(start,end);
//			DoubleClicked = true;
//			return true;
//			break;
//		}
//	case EMIE_LMOUSE_TRIPLE_CLICK:
//		{
//			// Select the entire line
//			// Go from \n to \n
//			CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//
//			// Now let's process the word
//			// First, find the beginning
//			int start, end;
//			start = end = 0;
//
//			for (int i = CursorPos; i > 0; i--) {
//				if (Text.c_str()[i] == L'\n' || Text.c_str()[i] == L'\r') {
//					start = i+1;
//					break;
//				}
//			}
//			for (u32 i = CursorPos; i < Text.size(); i++) {
//				if (Text.c_str()[i] == L'\n' || Text.c_str()[i] == L'\r') {
//					end = i;
//					break;
//				}
//				if (i == Text.size()-1)
//					end = i+1;
//			}
//			setTextMarkers(start,end);
//			DoubleClicked = true;
//			return true;
//			break;
//		}
//	case EMIE_LMOUSE_PRESSED_DOWN:
//		if (!InMenu) {
//			if (!Environment->hasFocus(this))
//			{
//				BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//				MouseMarking = true;
//				CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//				setTextMarkers(CursorPos, CursorPos );
//				calculateScrollPos();
//				return true;
//			}
//			else
//			{
//				if (!AbsoluteClippingRect.isPointInside(
//					core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
//				{
//					return false;
//				}
//				else
//				{
//					// move cursor
//					CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//
//					s32 newMarkBegin = MarkBegin;
//					if (!MouseMarking)
//						newMarkBegin = CursorPos;
//
//					MouseMarking = true;
//					setTextMarkers( newMarkBegin, CursorPos);
//					calculateScrollPos();
//
//				}
//			}
//		}
//
//		return true;
//	case EMIE_RMOUSE_PRESSED_DOWN:
//		if (!InMenu && !isPointInSelection(core::position2di(event.MouseInput.X,event.MouseInput.Y))) {
//			if (!Environment->hasFocus(this))
//			{
//				BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//				MouseMarking = true;
//				CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//				setTextMarkers(CursorPos, CursorPos );
//				calculateScrollPos();
//				return true;
//			}
//			else
//			{
//				if (!AbsoluteClippingRect.isPointInside(
//					core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
//				{
//					return false;
//				}
//				else
//				{
//					// move cursor
//					CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
//
//					s32 newMarkBegin = MarkBegin;
//					if (!MouseMarking)
//						newMarkBegin = CursorPos;
//
//					MouseMarking = true;
//					setTextMarkers( newMarkBegin, CursorPos);
//					calculateScrollPos();
//
//				}
//			}
//		}
//		return true;
//	default:
//		break;
//	}
//
	return false;
}

bool CGUIImageViewer::OnKey(const SEvent& event)
{
	if (!event.KeyInput.PressedDown)
		return false;

//	bool textChanged = false;
//	s32 newMarkBegin = MarkBegin;
//	s32 newMarkEnd = MarkEnd;
//
//	// control shortcut handling
//
//	if (event.KeyInput.Control)
//	{
//		// german backlash '\' entered with control + '?'
//		if ( event.KeyInput.Char == '\\' )
//		{
//			inputChar(event.KeyInput.Char);
//			return true;
//		}
//
//		switch(event.KeyInput.Key)
//		{
//
//		case KEY_KEY_Z:
//			undo();
//			break;
//		case KEY_KEY_Y:
//			redo();
//			break;
//		case KEY_KEY_A:
//			// select all
//			newMarkBegin = 0;
//			newMarkEnd = Text.size();
//			break;
//		case KEY_KEY_C:
//			// copy to clipboard
//			copy();
//			break;
//		case KEY_KEY_X:
//			// cut to the clipboard
//			cut();
//			return true;
//		case KEY_KEY_V:
//			paste();
//			return true;
//		case KEY_HOME:
//			// move/highlight to start of text
//			if (event.KeyInput.Shift)
//			{
//				newMarkEnd = CursorPos;
//				newMarkBegin = 0;
//				CursorPos = 0;
//			}
//			else
//			{
//				CursorPos = 0;
//				newMarkBegin = 0;
//				newMarkEnd = 0;
//			}
//			break;
//		case KEY_END:
//			// move/highlight to end of text
//			if (event.KeyInput.Shift)
//			{
//				newMarkBegin = CursorPos;
//				newMarkEnd = Text.size();
//				CursorPos = 0;
//			}
//			else
//			{
//				CursorPos = Text.size();
//				newMarkBegin = 0;
//				newMarkEnd = 0;
//			}
//			break;
//		default:
//			return false;
//		}
//	}
//	// default keyboard handling
//	else
//		switch(event.KeyInput.Key)
//	{
//		case KEY_END:
//			{
//				s32 p = Text.size();
//				if (WordWrap || MultiLine)
//				{
//					p = getLineFromPos(CursorPos);
//					p = BrokenTextPositions[p] + (s32)BrokenText[p].size();
//					if (p > 0 && (Text[p-1] == L'\r' || Text[p-1] == L'\n' ))
//						p-=1;
//				}
//
//				if (event.KeyInput.Shift)
//				{
//					if (MarkBegin == MarkEnd)
//						newMarkBegin = CursorPos;
//
//					newMarkEnd = p;
//				}
//				else
//				{
//					newMarkBegin = 0;
//					newMarkEnd = 0;
//				}
//				CursorPos = p;
//				BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//			}
//			break;
//		case KEY_HOME:
//			{
//
//				s32 p = 0;
//				if (WordWrap || MultiLine)
//				{
//					p = getLineFromPos(CursorPos);
//					p = BrokenTextPositions[p];
//				}
//
//				if (event.KeyInput.Shift)
//				{
//					if (MarkBegin == MarkEnd)
//						newMarkBegin = CursorPos;
//					newMarkEnd = p;
//				}
//				else
//				{
//					newMarkBegin = 0;
//					newMarkEnd = 0;
//				}
//				CursorPos = p;
//				BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//
//			}
//			break;
//		case KEY_RETURN:
//			if (MultiLine)
//			{
//				sendGuiEvent( EGET_EDITBOX_ENTER );
//				s32 lineStart = getLineFromPos(CursorPos);
//				lineStart = BrokenTextPositions[lineStart];
//
//				s32 lineEnd = CursorPos;
//
//				inputChar(L'\n');
//
//				for (int i=lineStart ; i<=lineEnd ; i++)
//				{
//					if( Text.subString(i,1) == core::stringw(" ") )
//					{
//						inputChar(L' ');
//					}
//					else
//						break;
//				}
//
//				return true;
//			}
//			else
//			{
//				sendGuiEvent( EGET_EDITBOX_ENTER );
//			}
//			break;
//		case KEY_LEFT:
//
//			if (event.KeyInput.Shift)
//			{
//				if (CursorPos > 0)
//				{
//					if (MarkBegin == MarkEnd)
//						newMarkBegin = CursorPos;
//
//					newMarkEnd = CursorPos-1;
//				}
//			}
//			else
//			{
//				newMarkBegin = 0;
//				newMarkEnd = 0;
//			}
//
//			if (CursorPos > 0)
//				CursorPos--;
//			BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//			break;
//
//		case KEY_RIGHT:
//			if (event.KeyInput.Shift)
//			{
//				if (Text.size() > (u32)CursorPos)
//				{
//					if (MarkBegin == MarkEnd)
//						newMarkBegin = CursorPos;
//
//					newMarkEnd = CursorPos+1;
//				}
//			}
//			else
//			{
//				newMarkBegin = 0;
//				newMarkEnd = 0;
//			}
//
//			if (Text.size() > (u32)CursorPos)
//				CursorPos++;
//			BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//			break;
//
//		case KEY_UP:
//			if (MultiLine || (WordWrap && BrokenText.size() > 1) )
//			{
//				s32 lineNo = getLineFromPos(CursorPos);
//				s32 mb = (MarkBegin == MarkEnd) ? CursorPos : (MarkBegin > MarkEnd ? MarkBegin : MarkEnd);
//				if (lineNo > 0)
//				{
//					s32 cp = CursorPos - BrokenTextPositions[lineNo];
//					if ((s32)BrokenText[lineNo-1].size() < cp)
//						CursorPos = BrokenTextPositions[lineNo-1] + (s32)BrokenText[lineNo-1].size()-1;
//					else
//						CursorPos = BrokenTextPositions[lineNo-1] + cp;
//				}
//
//				if (event.KeyInput.Shift)
//				{
//					newMarkBegin = mb;
//					newMarkEnd = CursorPos;
//				}
//				else
//				{
//					newMarkBegin = 0;
//					newMarkEnd = 0;
//				}
//				//Scrollbar->setPos(getLineFromPos(CursorPos));
//			}
//			else
//			{
//				return false;
//			}
//			break;
//
//		case KEY_DOWN:
//			if (MultiLine || (WordWrap && BrokenText.size() > 1) )
//			{
//				s32 lineNo = getLineFromPos(CursorPos);
//				s32 mb = (MarkBegin == MarkEnd) ? CursorPos : (MarkBegin < MarkEnd ? MarkBegin : MarkEnd);
//				if (lineNo < (s32)BrokenText.size()-1)
//				{
//					s32 cp = CursorPos - BrokenTextPositions[lineNo];
//					if ((s32)BrokenText[lineNo+1].size() < cp)
//						CursorPos = BrokenTextPositions[lineNo+1] + BrokenText[lineNo+1].size()-1;
//					else
//						CursorPos = BrokenTextPositions[lineNo+1] + cp;
//				}
//
//				if (event.KeyInput.Shift)
//				{
//					newMarkBegin = mb;
//					newMarkEnd = CursorPos;
//				}
//				else
//				{
//					newMarkBegin = 0;
//					newMarkEnd = 0;
//				}
//				//Scrollbar->setPos(getLineFromPos(CursorPos));
//
//			}
//			else
//			{
//				return false;
//			}
//			break;
//
//		case KEY_BACK:
//			if ( !this->IsEnabled )
//				break;
//
//			if (Text.size())
//			{
//				core::stringw s;
//
//				if (MarkBegin != MarkEnd)
//				{
//					// delete marked text
//					const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
//					const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;
//
//					replaceText(realmbgn,realmend,L"");
//
//					CursorPos = realmbgn;
//				}
//				else
//				{
//					// delete text behind cursor
//					if (CursorPos>0)
//						replaceText(CursorPos-1,CursorPos,L"");
//					else
//						replaceText(0,CursorPos,L"");
//					--CursorPos;
//				}
//
//				if (CursorPos < 0)
//					CursorPos = 0;
//
//				BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//				newMarkBegin = 0;
//				newMarkEnd = 0;
//				textChanged = true;
//			}
//			break;
//
//		case KEY_DELETE:
//			if ( !this->IsEnabled )
//				break;
//
//			if (Text.size() != 0)
//			{
//				core::stringw s;
//
//				if (MarkBegin != MarkEnd)
//				{
//					// delete marked text
//					const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
//					const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;
//
//					replaceText(realmbgn,realmend,L"");
//
//					CursorPos = realmbgn;
//				}
//				else
//				{
//					// delete text before cursor
//					replaceText(CursorPos,CursorPos+1,L"");
//				}
//
//				if (CursorPos > (s32)Text.size())
//					CursorPos = (s32)Text.size();
//
//				BlinkStartTime = IRRdevice->getTimer()->getRealTime();
//				newMarkBegin = 0;
//				newMarkEnd = 0;
//				textChanged = true;
//			}
//			break;
//
//		case KEY_TAB:
//			Environment->setFocus(this);
//			inputChar(L' ');
//			//inputChar(L' ');
//			break;
//		case KEY_INSERT:
//			Inserting = !Inserting;
//			break;
//		case KEY_ESCAPE:
//		case KEY_SHIFT:
//		case KEY_F1:
//		case KEY_F2:
//		case KEY_F3:
//		case KEY_F4:
//		case KEY_F5:
//		case KEY_F6:
//		case KEY_F7:
//		case KEY_F8:
//		case KEY_F9:
//		case KEY_F10:
//		case KEY_F11:
//		case KEY_F12:
//		case KEY_F13:
//		case KEY_F14:
//		case KEY_F15:
//		case KEY_F16:
//		case KEY_F17:
//		case KEY_F18:
//		case KEY_F19:
//		case KEY_F20:
//		case KEY_F21:
//		case KEY_F22:
//		case KEY_F23:
//		case KEY_F24:
//			// ignore these keys
//			return false;
//
//		default:
//			// ` ' and " must be replaced to ' (lua interpreter does not recognize wrong chars)
//			/*if(event.KeyInput.Char == 96 || event.KeyInput.Char == 180 || event.KeyInput.Char == 168)
//				inputChar(L'"');
//			else*/
//				inputChar(event.KeyInput.Char);
//			//printf("%s",(core::stringc)event.KeyInput.Char);
//			return true;
//	}

//	// Set new text markers
//	setTextMarkers( newMarkBegin, newMarkEnd );
//
//	// break the text if it has changed
//	if (textChanged)
//	{
//		breakText();
//		sendGuiEvent(EGET_EDITBOX_CHANGED);
//	}

//	calculateScrollPos();

	return true;
}


//! send some gui event to parent
void CGUIImageViewer::sendGuiEvent(EGUI_EVENT_TYPE type)
{
	if ( Parent )
	{
		SEvent e;
		e.EventType = EET_GUI_EVENT;
		e.GUIEvent.Caller = this;
		e.GUIEvent.Element = 0;
		e.GUIEvent.EventType = type;

		Parent->OnEvent(e);
	}
}

//! Writes attributes of the element.
void CGUIImageViewer::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
{
	// IGUIEditBox::serializeAttributes(out,options);
//	out->addBool  ("OverrideColorEnabled",OverrideColorEnabled );
//	out->addColor ("OverrideColor",       OverrideColor);
//	// out->addFont("OverrideFont",OverrideFont);
//	out->addInt   ("MaxChars",            Max);
//	out->addBool  ("WordWrap",            WordWrap);
//	out->addBool  ("MultiLine",           MultiLine);
//	out->addBool  ("AutoScroll",          AutoScroll);
//	out->addBool  ("PasswordBox",         PasswordBox);
//	core::stringw ch = L" ";
//	ch[0] = PasswordChar;
//	out->addString("PasswordChar",        ch.c_str());
//	out->addEnum  ("HTextAlign",          HAlign, GUIAlignmentNames);
//	out->addEnum  ("VTextAlign",          VAlign, GUIAlignmentNames);
//
	IGUIElement::serializeAttributes(out,options);
}


//! Reads attributes of the element
void CGUIImageViewer::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
{
	IGUIElement::deserializeAttributes(in,options);

//	setOverrideColor(in->getAttributeAsColor("OverrideColor"));
//	enableOverrideColor(in->getAttributeAsBool("OverrideColorEnabled"));
//	setMax(in->getAttributeAsInt("MaxChars"));
//	setWordWrap(in->getAttributeAsBool("WordWrap"));
//	setMultiLine(in->getAttributeAsBool("MultiLine"));
//	setAutoScroll(in->getAttributeAsBool("AutoScroll"));
//	core::stringw ch = in->getAttributeAsStringW("PasswordChar");
//
//	if (!ch.size())
//		setPasswordBox(in->getAttributeAsBool("PasswordBox"));
//	else
//		setPasswordBox(in->getAttributeAsBool("PasswordBox"), ch[0]);
//
//	setTextAlignment( (EGUI_ALIGNMENT) in->getAttributeAsEnumeration("HTextAlign", GUIAlignmentNames),
//		(EGUI_ALIGNMENT) in->getAttributeAsEnumeration("VTextAlign", GUIAlignmentNames));

	// setOverrideFont(in->getAttributeAsFont("OverrideFont"));
}

} // end namespace gui
} // end namespace irr
