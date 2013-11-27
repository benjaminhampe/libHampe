// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_C_GUI_IMAGE_VIEWER_H__
#define __IRR_EXT_C_GUI_IMAGE_VIEWER_H__

#include <irrlicht.h>

namespace irr
{
namespace gui
{
	/// @class CGUIImageViewer

	class CGUIImageViewer : public IGUIElement
	{
	public:
		inline core::recti makeRect( s32 x, s32 y, u32 w, u32 h)
		{
			return core::recti( core::position2di(x,y), core::dimension2du(w,h) );
		}

		// Enums for the elements that compose the code editor
		enum GUI_ID
		{
			GID_CUT = 0,
			GID_COPY,
			GID_PASTE,
			GID_DELETE,
			GID_UNDO,
			GID_REDO,
			GID_LINECOUNT,
			GID_COUNT
		};

		// Enums for the elements that compose the code editor
//		enum DATA_SET_TYPE
//		{
//			DST_LINESTRIP = 0,
//			DST_COUNT
//		};

		struct SDataSet // SPathShape/
		{
			core::stringc Name;
			scene::E_PRIMITIVE_TYPE Type; //DATA_SET_TYPE Type;
			video::SColor Color;
			f32 LineWidth;
			u16 LineStipple;
			core::array<core::vector2df> Data;
		};

	private:
		IGUIElement* ContentPane;
		IGUIScrollBar* ScrollbarV;
		IGUIScrollBar* ScrollbarH;
		IGUIButton* ButtonZoomReset;
		IGUIButton* ButtonZoomWindow;
		IGUIStaticText* LabelZoomRectXMin;
		IGUIStaticText* LabelZoomRectYMin;
		IGUIStaticText* LabelZoomRectXMax;
		IGUIStaticText* LabelZoomRectYMax;
		IGUIEditBox* EditZoomRectXMin;
		IGUIEditBox* EditZoomRectYMin;
		IGUIEditBox* EditZoomRectXMax;
		IGUIEditBox* EditZoomRectYMax;


		//! Override color for the interface
		video::SColor TextColor;
		video::SColor BackgroundColor;
		video::SColor GridColor;
		video::SColor SubGridColor;


		//! Store the text information for the menus
		core::stringw menustring[GID_COUNT];

		//! Arrays for the keywords informations
		core::array<SDataSet> Data;
	public:




		//! constructor
		CGUIImageViewer( IGUIEnvironment* env, IGUIElement* parent, s32 id, const core::rect<s32>& rectangle );

		//! destructor
		virtual ~CGUIImageViewer();

		//! called if an event happened.
		virtual bool OnEvent(const SEvent& event);

		//! draws the element and its children
		virtual void draw();

		//! get content pane
		virtual IGUIElement* getContentPane()
		{
			return ContentPane;
		}


//		//! Updates the absolute position, splits text if required
//		virtual void updateAbsolutePosition();
//
		//! Writes attributes of the element.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

		//! Reads attributes of the element
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

	protected:

		//! send some gui event to parent
		void sendGuiEvent(EGUI_EVENT_TYPE type);

		//! handle keyboard events
		bool OnKey(const SEvent& event);

		//! handle mouse events
		bool OnMouse(const SEvent& event);


//		template <class T>
//		class TPathShape2d : public scene::ISceneNode
//		{
//			scene::E_PRIMITIVE_TYPE Type;
//			core::stringc Name;
//			video::SColor Color;
//			u16 LineStipple;
//
//			core::array<core::vector2df> Data;
//		};
//
//		template <class T>
//		class TPathShape3d : public scene::ISceneNode
//		{
//			scene::E_PRIMITIVE_TYPE Type;
//			core::stringc Name;
//			video::SColor Color;
//			u16 LineStipple;
//
//			core::array<core::vector3d<T>> Data;
//
//			public:
//			TPathShape3d
//			render()
//		};
//
//		typedef TPathShape2d<f32> SPathShape2df;
//		typedef TPathShape3d<f32> SPathShape3df;


//		class Canvas : public IGUIElement
//		{
//
//			core::array<SPathShape> PathData;
//
//		public:
//			//! constructor
//			Canvas( IGUIEnvironment* env, IGUIElement* parent,
//				s32 id, const core::rect<s32>& rectangle )
//			: IGUIElement( EGUIET_ELEMENT, env, parent, id, rectangle)
//			{
//				// #ifdef _DEBUG
//				setDebugName("Canvas::ctr()");
//				// #endif
//
//				setTabStop(true);
//				setTabOrder(-1);
//
//				IGUISkin *skin = 0;
//
//				if (Environment)
//				{
//					skin = Environment->getSkin();
//
//					// create Element
//
//
//					Environment->setFocus(this);
//				}
//			}
//
//			//! destructor
//			virtual ~Canvas()
//			{
//
//			}
//
//			//! called if an event happened.
//			virtual bool OnEvent(const SEvent& event)
//			{
//				if (IsEnabled)
//				{
//
//				}
//
//				return IGUIElement::OnEvent(event);
//			}
//
//			//! draws the element and its children
//			virtual void draw()
//			{
//				IGUIElement::draw(event);
//
//				if (IsVisible)
//				{
//					// drawGraph
//				}
//
//			}
//		};


	};


} // end namespace gui
} // end namespace irr

#endif // __IRR_EXT_C_GUI_IMAGE_VIEWER_H__
