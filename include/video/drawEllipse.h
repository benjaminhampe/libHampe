// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_DRAW_BRESENHAM_ELLIPSE_TO_SOFTWARE_IMAGE_H__
#define __IRR_EXT_DRAW_BRESENHAM_ELLIPSE_TO_SOFTWARE_IMAGE_H__

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

//! draw a Bresenham-ellipse, 1 color, filled or outlined, option to blend
void drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& color, s32 border, bool blend);

//! Bresenham ellipse
void drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& c1, const SColor& c2, s32 border, bool blend);

} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_BRESENHAM_ELLIPSE_TO_SOFTWARE_IMAGE_H__
