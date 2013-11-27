// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_C_GUI_PLOT_H__
#define __IRR_EXT_C_GUI_PLOT_H__

#include <irrlicht.h>

#include <functional>

#include "../scene/CAutoMeshSceneNode.h"

namespace irr
{
namespace gui
{
	///@brief class CGUIPlot
	class CGUIPlot : public IGUIElement
	{
	public:
		///@brief set Parent Element Text ( i.e. the caption of a parent's window title )
		static bool setText( gui::IGUIElement* element, const core::stringw& text );

		///@brief setVisible(false) to all SceneNodes
		static bool hideAll( scene::ISceneManager* smgr );

		///@brief setVisible(true) to all SceneNodes
		static bool showAll( scene::ISceneManager* smgr );

		///@brief buildProjectionMatrixOrthoLH with 6 params, not 4 as irrlicht only does
		static core::matrix4 buildProjectionMatrixOrthoLH( f32 left, f32 right, f32 bottom, f32 top, f32 zNear = 0.1f, f32 zFar = 1000.0f );

		///@brief create a recti from position2di and dimension2du
		inline core::recti makeRect( s32 x, s32 y, u32 w, u32 h)
		{
			return core::recti( core::position2di(x,y), core::dimension2du(w,h) );
		}

		///@brief struct Shape ( holds a pointer to SceneNode and a name as UTF-8 string )
		struct Shape
		{
			///@brief pointer to ISceneNode
			scene::ISceneNode* Node;

			///@brief UTF-8 name
			core::stringc Name;

			///@brief struct constructor
			Shape() : Node(0), Name("")
			{
				// empty
			}

			///@brief struct constructor
			Shape( scene::ISceneNode* node, core::stringc name	) : Node(node), Name(name)
			{
				// if (Node) Node->grab();
			}

			///@brief struct destructor
			~Shape()
			{
				// if (Node) Node->drop();
			}
		};


		///@brief class constructor
		///@param smgr ISceneManager
		///@param env IGUIEnvironment
		///@param parent Parent element of this element
		///@param id Id of this element
		///@param rectangle Size of this element
		CGUIPlot(
			scene::ISceneManager* smgr,
			IGUIEnvironment* env,
			IGUIElement* parent,
			s32 id,
			const core::rect<s32>& rectangle );

		///@brief class destructor
		virtual ~CGUIPlot();

		///@brief called if an event happened.
		virtual bool OnEvent(const SEvent& event);

		///@brief draws the element and its children
		virtual void draw();

		///@brief quick transform from world-coords into screen coords for texts, etc.
		///@param pos Position given in world-space
		///@return Position in screen/viewport-space
		virtual core::position2di projectToScreen( const core::vector3df& pos );

		///@brief add SceneNode to draw to plot
		///@param node ISceneNode to be added to plot
		///@param name Name of the ISceneNode
		///@return true on success
		virtual bool addShape( scene::ISceneNode* node, const core::stringc& name = "unnamed" );

		///@brief set ZoomRect
		virtual void setZoomRect( const core::rectf& zoomRect )
		{
			ZoomRect = zoomRect;
		}

		///@brief get ZoomRect
		virtual core::rectf getZoomRect( ) const
		{
			return ZoomRect;
		}

		///@brief enable/disable ClearColor
		virtual void setDrawBackground( const bool& value )
		{
			IsDrawBackground = value;
		}

		///@brief set ClearColor
		virtual void setBackgroundColor( const video::SColor& color )
		{
			BackgroundColor = color;
		}

		// ///@brief Updates the absolute position, splits text if required
		// virtual void updateAbsolutePosition();

		///@brief Writes attributes of the element.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

		///@brief Reads attributes of the element
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

	protected:

		///@brief send some gui event to parent
		void sendGuiEvent(EGUI_EVENT_TYPE type);

		///@brief handle keyboard events
		bool OnKey(const SEvent& event);

		///@brief handle mouse events
		bool OnMouse(const SEvent& event);


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

		core::rect<f32> ZoomRect;
		core::rect<s32> Plotrect;

		///@brief Override color for the interface
		bool IsDrawBackground;
		video::SColor BackgroundColor;

		video::SColor TextColor;

		bool IsDrawGrid;
		video::SColor GridColor;
		video::SColor SubGridColor;

		core::array<Shape> Shapes;

		scene::ISceneManager* SceneManager;
		scene::ISceneNode* Root;
		scene::ICameraSceneNode* Camera;
	};


} // end namespace gui
} // end namespace irr

#endif // __IRR_EXT_C_GUI_PLOT_H__
