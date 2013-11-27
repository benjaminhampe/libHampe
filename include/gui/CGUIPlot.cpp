// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUIPlot.h"

//#include "../core/CMath.h"

#include <GL/gl.h>
#include <GL/glu.h>


namespace irr
{
namespace gui
{

//! set Parent Element Text ( i.e. the caption of a parent's window title )
bool CGUIPlot::setText( gui::IGUIElement* element, const core::stringw& text )
{
	if (!element)
		return false;

	element->setText( text.c_str() );

	return true;
}

/// setVisible(false) to all SceneNodes
bool CGUIPlot::hideAll( scene::ISceneManager* smgr )
{
	_IRR_DEBUG_BREAK_IF( !smgr )
//	if (!smgr)
//	{
//		printf("CGUIPlot::hideAll()::Invalid pointer to ISceneManager\n");
//		return false;
//	}

	scene::ISceneNode* root = smgr->getRootSceneNode();

	_IRR_DEBUG_BREAK_IF( !root )
//	if (!root)
//	{
//		printf("CGUIPlot::hideAll()::Invalid pointer to root ISceneNode\n");
//		return false;
//	}

	const core::list<scene::ISceneNode*>& Nodes = root->getChildren();

	core::list<scene::ISceneNode*>::ConstIterator it = Nodes.begin();

	while( it != Nodes.end() )
	{
		if ((*it))
		{
			(*it)->setVisible( false );
		}

		it++;
	}

	return true;
}

/// setVisible(true) to all SceneNodes
bool CGUIPlot::showAll( scene::ISceneManager* smgr )
{
	_IRR_DEBUG_BREAK_IF( !smgr )

	if (!smgr)
		return false;

	scene::ISceneNode* root = smgr->getRootSceneNode();

	_IRR_DEBUG_BREAK_IF( !root )

	if (!root)
		return false;

	const core::list<scene::ISceneNode*>& Nodes = root->getChildren();

	core::list<scene::ISceneNode*>::ConstIterator it = Nodes.begin();

	while( it != Nodes.end() )
	{
		if (*it)
		{
			(*it)->setVisible( true );
		}

		it++;
	}

	return true;
}

core::matrix4 CGUIPlot::buildProjectionMatrixOrthoLH( f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar )
{
	core::matrix4 M;
	_IRR_DEBUG_BREAK_IF( core::equals(left,right) ); //divide by zero
	_IRR_DEBUG_BREAK_IF( core::equals(top,bottom) ); //divide by zero
	_IRR_DEBUG_BREAK_IF( core::equals(zNear,zFar) ); //divide by zero

	//	2/(r-l)      0            0           0
	//	0            2/(t-b)      0           0
	//	0            0            1/(zf-zn)   0
	//	(l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

	M[0] = 2.f/(left-right);
	M[1] = 0.f;
	M[2] = 0.f;
	M[3] = 0.f;

	M[4] = 0.f;
	M[5] = 2.f/(top-bottom);
	M[6] = 0.f;
	M[7] = 0.f;

	M[8] = 0.f;
	M[9] = 0.f;
	M[10] = 1.f/(zFar-zNear);
	M[11] = 0.f;

	M[12] = (left+right)/(left-right);
	M[13] = (top+bottom)/(bottom-top);
	M[14] = zNear/(zNear-zFar);
	M[15] = 1.f;

	return M;
}


//! constructor
CGUIPlot::CGUIPlot(
	scene::ISceneManager* smgr,
	IGUIEnvironment* env,
	IGUIElement* parent,
	s32 id,
	const core::rect<s32>& rectangle)
: IGUIElement( EGUIET_ELEMENT, env, parent, id, rectangle)
//, Viewport(0,0,0,0)
, ZoomRect(-1,-4,10,5)
, Plotrect(0,0,0,0)
, IsDrawBackground(false)
, BackgroundColor(video::SColor(255,255,255,255))
, TextColor(video::SColor(255,0,0,0))
, IsDrawGrid(true)
, GridColor(video::SColor(255,200,200,200))
, SubGridColor(video::SColor(255,235,235,235))
, SceneManager(smgr)
, Root(0)
, Camera(0)
{
#ifdef _DEBUG
	setDebugName("CGUIPlot");
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

	// TextColor=skin->getColor(EGDC_HIGH_LIGHT_TEXT);

	s32 w = rectangle.getWidth(); // in pixels
	s32 h = rectangle.getHeight(); // in pixels
	s32 sb_size = 16; // in pixels

	core::recti r_canvas = makeRect(0,0, (u32)(w-sb_size-1), (u32)(h-sb_size-1) );
	core::recti r_scrollH = makeRect(1,h-sb_size, (u32)(w-sb_size-1), (u32)sb_size );
	core::recti r_scrollV = makeRect( w-sb_size, 1, (u32)sb_size, (u32)(h-sb_size-1) );
	core::recti r_reset = makeRect( w-sb_size, h-sb_size, (u32)sb_size, (u32)sb_size );

	Plotrect = r_canvas; //! visible ContentRect, Viewport is projected to this rect

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

	ContentPane = 0;

	Environment->setFocus(this);
//
//	SceneManager = new scene::CSceneManager(
//		Environment->getVideoDriver(), Environment->getFileSystem(), 0, 0, Environment);

	_IRR_DEBUG_BREAK_IF( !SceneManager )
//	if (!SceneManager)
//	{
//		printf("CGUIPlot::Could not create SceneManager\n");
//		return;
//	}

	Root = SceneManager->addEmptySceneNode( SceneManager->getRootSceneNode(), -1);

	_IRR_DEBUG_BREAK_IF( !Root )

	Camera = SceneManager->addCameraSceneNode( Root, core::vector3df(0,0,-100), core::vector3df(0,0,100), -1, false);

	_IRR_DEBUG_BREAK_IF( !Camera )

	Root->setVisible( false );

	/// Prepare some SceneNodes for x,y Axis and Grid

	//scene::ISceneManager* SceneManager = SceneManager;

	gui::IGUIFont* font = Environment->getBuiltInFont();

	scene::ITextSceneNode* textNode00 = SceneManager->addTextSceneNode(
		font, L"(0,0)", TextColor, SceneManager->getRootSceneNode(), core::vector3df(0,0,0) );

	scene::ITextSceneNode* textNodeX = SceneManager->addTextSceneNode(
		font, L"X", TextColor, SceneManager->getRootSceneNode(), core::vector3df(ZoomRect.LowerRightCorner.X,0,0) );

	scene::ITextSceneNode* textNodeY = SceneManager->addTextSceneNode(
		font, L"Y", TextColor, SceneManager->getRootSceneNode(), core::vector3df(0, ZoomRect.UpperLeftCorner.Y,0) );

	addShape( textNode00, L"Ursprung" );

	addShape( textNodeX, L"X-Axis" );

	addShape( textNodeY, L"Y-Axis" );


}



//! destructor
CGUIPlot::~CGUIPlot()
{
	if (Root)
	{
		Root->setVisible( false );
		Root->drop();
	}

}

///@brief get the screen-coords of vector2df given in world-coords
core::position2di CGUIPlot::projectToScreen( const core::vector3df& pos )
{
	_IRR_DEBUG_BREAK_IF( !SceneManager )

	return SceneManager->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition( pos, Camera, true );
}

//! addShape
bool CGUIPlot::addShape( scene::ISceneNode* node, const core::stringc& name )
{
	if (!node)
	{
		printf("CGUIPlot::addShape()::Invalid pointer to ISceneNode\n");
		return false;
	}

	_IRR_DEBUG_BREAK_IF( !SceneManager )
	_IRR_DEBUG_BREAK_IF( !Root )

	Shape shape;
	shape.Name = name;
	shape.Node = node;
	Shapes.push_back( shape );

	node->setParent( Root );

	node->setPosition( core::vector3df(0,0,1000.f - (f32)Shapes.size()) );

	node->setScale( core::vector3df(-1,1,1) ); /// This is a correction to a bug?

	printf("CGUIPlot::addShape()::OK\n");
	return true;
}

//! draws the element and its children
void CGUIPlot::draw()
{
	if (!IsVisible)
		return;

	if (!SceneManager)
	{
		printf("CGUIPlot::Has no SceneManager\n");
		return;
	}

//	const bool focus = Environment->hasFocus(this);

//	IGUISkin* skin = Environment->getSkin();
//	if (!skin)
//		return;

	video::IVideoDriver* driver = Environment->getVideoDriver();
	if (!driver)
		return;

	/// create caption text
	core::stringw t = L"CGUIPlot | Shape-Count = "; t += Shapes.size();
	t += L" | AbsoluteRect = { x="; t += AbsoluteRect.UpperLeftCorner.X;
	t += L", y="; t += AbsoluteRect.UpperLeftCorner.Y;
	t += L", w="; t += AbsoluteRect.getWidth();
	t += L", h="; t += AbsoluteRect.getHeight();
	t += L"}";

	/// deactivate all other SceneNodes than my own Root

	_IRR_DEBUG_BREAK_IF( !SceneManager )
	_IRR_DEBUG_BREAK_IF( !Root )

	hideAll( SceneManager );

	if (Root)
		Root->setVisible( true );

	/// Viewport
	const core::recti old_Viewport = driver->getViewPort();

	const core::recti new_Viewport( AbsoluteRect.UpperLeftCorner, core::dimension2du( (u32)Plotrect.getWidth(), (u32)Plotrect.getHeight() ) );

	driver->setViewPort( new_Viewport );

	// driver->setTransform( video::ETS_WORLD, core::IdentityMatrix );
	// driver->setTransform( video::ETS_VIEW, core::IdentityMatrix );
	// driver->setTransform( video::ETS_PROJECTION, core::IdentityMatrix );

	/// ProjectionMatrix ( Ortho2D )
	//glMatrixMode( GL_PROJECTION );
	//glLoadIdentity();
	//glFrustum( fovy, aspect, znear, zfar );
	//gluOrtho2D( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
	//gluOrtho2D( ZoomRect.UpperLeftCorner.X, ZoomRect.LowerRightCorner.X,
	//			ZoomRect.UpperLeftCorner.Y, ZoomRect.LowerRightCorner.Y);

	scene::ICameraSceneNode* old_Camera = SceneManager->getActiveCamera();

	if (Camera)
	{
		core::matrix4 ortho = buildProjectionMatrixOrthoLH( ZoomRect.UpperLeftCorner.X, ZoomRect.LowerRightCorner.X,
			ZoomRect.UpperLeftCorner.Y, ZoomRect.LowerRightCorner.Y, .1f, 1000.0f );

//		core::matrix4 ortho;
//		ortho.buildProjectionMatrixOrthoLH( ZoomRect.getWidth(), ZoomRect.getHeight(), 1.0f, 1000.0f );

		Camera->setProjectionMatrix( ortho );
		Camera->setPosition( core::vector3df(0,0,0) );
		Camera->setTarget( core::vector3df(0,0,100) );

		SceneManager->setActiveCamera( Camera );
	}


	/// WorldViewMatrix ( World * Camera )
//	glMatrixMode( GL_MODELVIEW );
//	glLoadIdentity();

	// set up camera position and orientation
//	glTranslatef( 0,0,100 );

	SceneManager->drawAll();

//	for (u32 i=0; i<Shapes.size(); i++)
//	{
//		scene::ISceneNode* node = Shapes[i].Node;
//		if (node)
//		{
////			glPushMatrix();
//
////			const core::matrix4 m = node->getAbsoluteTransformation();
////			const core::vector3df pos = m.getTranslation();
////			const core::vector3df rot = m.getRotationDegrees();
////			const core::vector3df scl = m.getScale();
//
////			glTranslatef( pos.X, pos.Y, pos.Z );
////			glRotatef( 1, 0, 0, rot.X );
////			glRotatef( 0, 1, 0, rot.Y );
////			glRotatef( 0, 0, 1, rot.Z );
////			glScalef( scl.X, scl.Y, scl.Z );
////
//			node->render();
//
////			glPopMatrix();
//		}
//	}

//	driver->endScene();

	IGUIFont* font = Environment->getBuiltInFont();

	core::vector3df p3f(0,0,0);
	core::position2di p2i = projectToScreen( p3f );
	t += L" | project = { ";
	t += p2i.X; t += L", ";
	t += p2i.Y; t += L"}";

	core::stringw txt = L"(0,0)";
	core::dimension2du txt_size = font->getDimension( txt.c_str() );

	driver->setViewPort( old_Viewport );

	font->draw( txt, core::recti(getAbsolutePosition().UpperLeftCorner+p2i, txt_size), TextColor, false, false );

	/// set all SceneNodes visible again
	showAll( SceneManager );

	if (Root)
		Root->setVisible( false );

//	if (Camera)
//		Camera->setVisible( false );

	if (old_Camera)
		SceneManager->setActiveCamera( old_Camera );

	/// set Text of Parent ( WindowCaption )

	t += L" | ZoomRect = { ";
	t += ZoomRect.UpperLeftCorner.X; t += L", ";
	t += ZoomRect.UpperLeftCorner.Y; t += L", ";
	t += ZoomRect.LowerRightCorner.X; t += L", ";
	t += ZoomRect.LowerRightCorner.Y; t += L" }";
	setText( Parent, t );



//	if (IsDrawBackground)
//		driver->draw2DRectangle( BackgroundColor, AbsoluteClippingRect );


//	if (IsDrawGrid)
//	{
//		core::vector2df u2f(0,0);
//		core::vector2di u2i = core::transformPoint2d<s32>( u2f, ZoomRect, AbsoluteRect );
//
//		driver->draw2DRectangle( TextColor, core::recti(u2i.X-2, u2i.Y-2, u2i.X+2, u2i.Y+2) );
//
//		if (font)
//		{
//			const core::stringw txt = L"Ursprung";
//			const core::dimension2du txt_size = font->getDimension( txt.c_str() );
//			font->draw( txt, core::recti(u2i+core::position2di(5,5), txt_size), TextColor, false,false, &AbsoluteClippingRect);
//		}
//
//	}


	// draw children
	IGUIElement::draw();
}

//! called if an event happened.
bool CGUIPlot::OnEvent(const SEvent& event)
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




bool CGUIPlot::OnMouse(const SEvent& event)
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

bool CGUIPlot::OnKey(const SEvent& event)
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
void CGUIPlot::sendGuiEvent(EGUI_EVENT_TYPE type)
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


//void CGUIPlot::updateAbsolutePosition()
//{
//	core::rect<s32> oldAbsoluteRect(AbsoluteRect);
//	IGUIElement::updateAbsolutePosition();
//	if ( oldAbsoluteRect != AbsoluteRect )
//	{
//		breakText();
//	}
//}
//
//void CGUIPlot::setBackgroundColor(video::SColor color)
//{
//	BackgroundColor = color;
//}


//! Writes attributes of the element.
void CGUIPlot::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
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
void CGUIPlot::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
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
