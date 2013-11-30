// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_DRAW_BRESENHAM_LINE_TO_SOFTWARE_IMAGE_H__
#define __IRR_EXT_DRAW_BRESENHAM_LINE_TO_SOFTWARE_IMAGE_H__

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

	//! @brief draw fast bresenham-line with 1 color to software-image
	//! @return true if success
	bool drawLine(

		video::IImage* dst,

		s32 x0,

		s32 y0,

		s32 x1,

		s32 y1,

		const video::SColor& color,

		bool blend = false);


	//! @brief draw fast bresenham-line with 2 colors to software-image ( lin. interpolation )
	//! @return true if success
	bool drawLine(

		video::IImage* dst,

		s32 x0,

		s32 y0,

		s32 x1,

		s32 y1,

		const video::SColor& color_a,

		const video::SColor& color_b,

		bool blend = false);

	//! @brief draw fast bresenham-line with 1 color to software-image
	//! @return true if success
	bool drawLine(

		video::IImage* dst,

		const core::rectf& pos,

		const video::SColor& color,

		bool blend = false);

	//! @brief draw fast bresenham-line with 2 colors to software-image ( lin. interpolation )
	//! @return true if success
	bool drawLine(

		video::IImage* dst,

		const core::rectf& pos,

		const video::SColor& color_a,

		const video::SColor& color_b,

		bool blend = false);


} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_BRESENHAM_LINE_TO_SOFTWARE_IMAGE_H__
