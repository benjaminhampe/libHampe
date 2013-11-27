#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <irrlicht.h>

namespace irr
{

///@brief class MyEventReceiver
class MyEventReceiver : public IEventReceiver
{
public:
	///@brief class constructor
	MyEventReceiver( IrrlichtDevice* device )
	{
		Device = device;
		IsEnabled = false;
		ToggleButtonWireframe = 0;

		if ( Device )
		{
			Device->setEventReceiver( this );

			if (this == Device->getEventReceiver())
			{
				IsEnabled = true;
			}
		}

		if (!IsEnabled)
		{
			printf("SolarCAD_EventReceiver() :: Could not set EventReceiver\n");
		}

		gui::IGUIEnvironment* env = device->getGUIEnvironment();
		gui::IGUIElement* envRoot = env->getRootGUIElement();
		video::IVideoDriver* driver = device->getVideoDriver();

		if (env && envRoot && driver)
		{
			s32 x = 0;
			s32 y = 0;
//			s32 k = 0;
			s32 padd = 5;
			s32 btn_w = 48;
			s32 btn_h = 48;
			s32 line_height = 24;

			const core::dimension2du screen = driver->getScreenSize();

			ToggleButtonWireframe = env->addButton(	core::recti( x+padd,y+padd, x+padd+btn_w,y+padd+btn_h),
				envRoot, -1, L"Wireframe", L"toggle wireframe");

			y += btn_h + 2*padd;

			ToggleButtonHelpWindow = env->addButton(
				core::recti( x+padd,y+padd, x+padd+btn_w,y+padd+btn_h),
				envRoot, -1, L"Help", L"toggle visibility of help window");

			HelpWindow = env->addWindow(
				core::recti( screen.Width/2+padd, padd, screen.Width-padd, screen.Height/2-padd ),
				false, L"Documentation Help Window", envRoot, -1);

			const core::recti r_client = HelpWindow->getClientRect();
			const s32 w = r_client.getWidth();
//			const s32 h = r_client.getHeight();

			x = r_client.UpperLeftCorner.X+padd;
			y = r_client.UpperLeftCorner.Y+padd;
//			k = 0;

			gui::IGUIStaticText* gui_text = env->addStaticText( L"Key Bindings:",
				core::recti(x,y,w-padd,y+line_height-1),
				false, false, HelpWindow, -1, true ); y += line_height;

			gui_text->setAlignment( gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT );

			env->addStaticText( L"Key Bindings:",
				core::recti(x,y,w-padd,y+line_height-1),
				false, false, HelpWindow, -1, true ); y += line_height;

			env->addStaticText( L"Key Bindings:",
				core::recti(x,y,w-padd,y+line_height-1),
				false, false, HelpWindow, -1, true ); y += line_height;

			env->addStaticText( L"Key Bindings:",
				core::recti(x,y,w-padd,y+line_height-1),
				false, false, HelpWindow, -1, true ); y += line_height;

	//		y += btn_h + 2*padd;
	//
	//		ToggleButtonParamWindow = myGUI->addButton(
	//			core::recti( x+padd,y+padd, x+padd+btn_w,y+padd+btn_h),
	//			myGUI->getRootGUIElement(), -1, L"Parameters", L"toggle visibility of param window");
	//
	//		y += btn_h + 2*padd;

		}

	}

	///@brief class destructor
	virtual ~MyEventReceiver()
	{

	}

	///@brief handles GUI events
	///@param event Given event to be handled
	///@return false, if event was not processed
	virtual bool OnGUIEvent (const SEvent &event)
	{
		if (!Device)
			return false;

		if (event.EventType != EET_GUI_EVENT)
			return false;

		/// light toggle button

		/// frontface-culling toggle button

		/// backface-culling toggle button

		/// show-help toggle button

		gui::IGUIEnvironment* env = Device->getGUIEnvironment();

		gui::IGUIElement* caller = event.GUIEvent.Caller;

		/// window close event

		if (event.GUIEvent.EventType==gui::EGET_ELEMENT_CLOSED)
		{
			/// prevent help-window from destroying itself
			if (caller==HelpWindow)
			{
				caller->setVisible(false);

				return true; // catch event by returning true
			}
			return false; // else return false
		}

		/// button click event

		if (event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED)
		{
			/// toggle button - HelpWindow
			if (caller == ToggleButtonHelpWindow)
			{
				if (HelpWindow && !HelpWindow->isVisible())
				{
					HelpWindow->setVisible(true);
					env->setFocus( HelpWindow );
					return true;
				}
				return true;
			}

			/// toggle button - wireframe
			if (caller == ToggleButtonWireframe)
			{
				const core::list<scene::ISceneNode*>& children = Device->getSceneManager()->getRootSceneNode()->getChildren();
				core::list<scene::ISceneNode*>::ConstIterator it = children.begin();
				while ( it != children.end() )
				{
					scene::ISceneNode* node = *it;
					if (node)
					{
						u32 matCount = node->getMaterialCount();
						for (u32 i=0; i<matCount; i++)
						{
							video::SMaterial& matRef = node->getMaterial(i);
							matRef.Wireframe = !matRef.Wireframe;
						}
					}
					it++;
				}
				return true;
			}
			return false;
		}
		return false;
	}

	///@brief handles all events
	///@param event Given event to be handled
	///@return false, if event was not processed
	virtual bool OnEvent (const SEvent &event) _IRR_OVERRIDE_
	{
		if (!Device)
			return false;

		if (!IsEnabled)
			return false;

		ITimer* timer = Device->getTimer();

//		u32 time = timer->getRealTime();

//		gui::IGUIEnvironment* env = Device->getGUIEnvironment();

		video::IVideoDriver* driver = Device->getVideoDriver();

		scene::ISceneManager* smgr = Device->getSceneManager();


		if (event.EventType == EET_GUI_EVENT)
		{
			if ( OnGUIEvent(event) )
				return true;
		}


		if(event.EventType == EET_KEY_INPUT_EVENT)
		{
			/// escape key - exit program
			if(event.KeyInput.Key == KEY_ESCAPE)
			{
				exit(0); // we exit
			}

			/// print key - create screenshot image with unique name ( myTimer based )
			if ( (event.KeyInput.Key == KEY_PRINT || event.KeyInput.Key == KEY_SNAPSHOT) && !event.KeyInput.PressedDown)
			{
//				if (Device)
//				{
//					if (driver && timer)
//					{
//						video::IImage* screenshot = driver->createScreenShot();
//						if (screenshot)
//						{
//							/// create filename
//							io::path name = "./screenshot_render_audio_spectrum_";
//							name += currentDateTimeString( timer );
//							name += ".png";
//
//							/// save screenshot
//							driver->writeImageToFile( screenshot, name);
//
//							/// delete
//							screenshot->drop();
//						}
//					}
//				}
				return true;
			}

			/// space key - enable/disable myCamera eventreceiver
			if (event.KeyInput.Key == KEY_SPACE && !event.KeyInput.PressedDown)
			{
				if (smgr)
				{
					scene::ICameraSceneNode* camera = smgr->getActiveCamera();
					if (camera)
					{
						camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
					}
				}
				return true;
			}

		}
		return false;
	}

private:
	///@brief pointer to Irrlicht-Device
	IrrlichtDevice* Device;

	///@brief boolean
	bool IsEnabled;

	///@brief pointer to IGUIElement
	gui::IGUIButton* ToggleButtonWireframe;

	///@brief pointer to IGUIElement
	gui::IGUIButton* ToggleButtonHelpWindow;

	///@brief pointer to IGUIElement
	gui::IGUIWindow* HelpWindow;

}; // end class MyEventReceiver


} // end namespace irr

#endif // MYEVENTRECEIVER_H
