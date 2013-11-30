// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_DRAW_BRESENHAM_RECT_TO_SOFTWARE_IMAGE_H__
#define __IRR_EXT_DRAW_BRESENHAM_RECT_TO_SOFTWARE_IMAGE_H__

#include <irrlicht.h>
#include <../source/Irrlicht/os.h>
#include <../source/Irrlicht/CColorConverter.h>
#include <../source/Irrlicht/CImage.h>

/// maybe you need to include the following lines once to your main cpp file
//#include <../source/Irrlicht/os.cpp>
//#include <../source/Irrlicht/CColorConverter.cpp>
//#include <../source/Irrlicht/CImage.cpp>

namespace irr
{
namespace video
{


	//! @brief draw fast bresenham-rect with 1 color to software-image
	//! @return true if success
	//! @details if ( border <= 0 ) solid/filled else (border>0) outlined/border

	void drawRect(

		IImage* dst,

		const core::recti& pos,

		const SColor& color,

		s32 border = 1,

		bool blend = false);

	//! @brief draw fast bresenham-rect with 4 colors to software-image
	//! @return true if success
	//! @details if ( border <= 0 ) solid/filled else (border>0) outlined/border

	void drawRect(

		IImage* dst,

		const core::recti& pos,

		const SColor& bottomLeft,

		const SColor& topLeft,

		const SColor& topRight,

		const SColor& bottomRight,

		s32 border = 1,

		bool blend = false);

} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_BRESENHAM_RECT_TO_SOFTWARE_IMAGE_H__
