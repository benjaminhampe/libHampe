// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_DRAW_BRESENHAM_CIRCLE_TO_SOFTWARE_IMAGE_H__
#define __IRR_EXT_DRAW_BRESENHAM_CIRCLE_TO_SOFTWARE_IMAGE_H__

#include <irrlicht.h>

namespace irr
{
namespace video
{

//! Bresenham circle

void

	drawCircle(

		IImage* dst,

		const core::position2di& center,

		s32 radius,

		const SColor& color,

		s32 border,

		bool blend);
	//
////! Bresenham circle
//void ImageTool::drawCircle( IImage* dst, const core::position2di& center, s32 radius, const SColor& c1, const SColor& c2, s32 border, bool blend)
//{


} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_BRESENHAM_CIRCLE_TO_SOFTWARE_IMAGE_H__
