// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use,ntsee copyright notice in irrlicht.h

#ifndef __IRR_EXT_ADDIDTIONAL_ENUMERATION_STRINGS_H__
#define __IRR_EXT_ADDIDTIONAL_ENUMERATION_STRINGS_H__

// LibC
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <cwchar>
#include <ctime>
#include <cmath>
#include <getopt.h>

// Irrlicht Engine
#include <irrlicht.h>
#include <driverChoice.h>

// Irrlicht adds
#include <../source/Irrlicht/CImage.h>
#include <../source/Irrlicht/os.h>
#include <../source/Irrlicht/CGeometryCreator.h>

//! @brief Macro _IRR_TEXT() for older Irrlicht versions < 1.8
//! @return Macro _IRR_TEXT() for older Irrlicht versions < 1.8
#if IRRLICHT_VERSION_MINOR < 8
	#if defined(_IRR_WCHAR_FILESYSTEM)
		typedef wchar_t fschar_t;
		#define _IRR_TEXT(X) L##X
	#else
		typedef char fschar_t;
		#define _IRR_TEXT(X) X
	#endif
#endif

namespace irr
{
	//! @brief Strings for Enumeration E_DEVICE_TYPE
	//! @return String for Enumeration E_DEVICE_TYPE
	const char* const E_DEVICE_TYPE_STRINGS[] =
	{
		"EIDT_WIN32",
		"EIDT_WINCE",
		"EIDT_X11",
		"EIDT_OSX",
		"EIDT_SDL",
		"EIDT_FRAMEBUFFER",
		"EIDT_CONSOLE",
		"EIDT_BEST",
		"EIDT_COUNT"
	};

	//! @brief Strings for Enumeration E_VERTEX_TYPE
	//! @return String for Enumeration E_VERTEX_TYPE
	const char* const E_VERTEX_TYPE_STRINGS[] =
	{
		"EVT_STANDARD",
		"EVT_2TCOORDS",
		"EVT_TANGENT",
		"EVT_COUNT"
	};

	//! @brief Strings for Enumeration E_INDEX_TYPE
	//! @return String for Enumeration E_INDEX_TYPE
	const char* const E_INDEX_TYPE_STRINGS[] =
	{
		"EIT_16BIT",
		"EIT_32BIT",
		"EIT_COUNT"
	};

	//! @brief Strings for Enumeration E_PRIMITIVE_TYPE
	//! @return String for Enumeration E_PRIMITIVE_TYPE
	const char* const E_PRIMITIVE_TYPE_STRINGS[] =
	{
		"EPT_POINTS",
		"EPT_LINE_STRIP",
		"EPT_LINE_LOOP",
		"EPT_LINES",
		"EPT_TRIANGLE_STRIP",
		"EPT_TRIANGLE_FAN",
		"EPT_TRIANGLES",
		"EPT_QUAD_STRIP",
		"EPT_QUADS",
		"EPT_POLYGON",
		"EPT_POINT_SPRITES"
	};


//	//! @brief setActiveCamera()
//	//! @return SUCCESS if true
//	bool setActiveCamera( scene::ISceneManager* smgr, scene::ICameraSceneNode* newActive );
//
//	//! @brief showMessage()
//	//! @return SUCCESS if true
//	bool showMessage ( gui::IGUIEnvironment* env, const core::stringw& title,
//		const core::stringw& msg, bool bModal = false,
//		const core::recti& rectangle = core::recti( core::position2di(-1,-1), core::dimension2du(160,120) ) );
//
//	//! @brief showAboutText()
//	//! @return SUCCESS if true
//	bool showAboutText( gui::IGUIEnvironment* env );
//
//	//! @brief hasModalDialog()
//	//! @return SUCCESS if true
//	bool hasModalDialog( gui::IGUIEnvironment* env );
//
//	//! @brief onKillFocus()
//	//! @return SUCCESS if true
//	bool onKillFocus( scene::ICameraSceneNode* camera);



} // end namespace irr


#endif // __IRR_EXT_ADDIDTIONAL_ENUMERATION_STRINGS_H__
