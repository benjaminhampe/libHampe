// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "imageDrawPixel.h"

namespace irr
{

namespace video
{
//
////! @brief set pixel for signed integer coords only if inside (0,0,w,h)
//
//void drawPixel( IImage* src, s32 x, s32 y, const SColor& color, bool blend )
//{
//	if (!src) return;
//	if (x<0) return;
//	if (y<0) return;
//    src->setPixel( (u32)x, (u32)y, color, blend);
//}
//
////! @brief set pixel for signed integer coords always - simple border align
//
//void drawPixelAlways( IImage* src, s32 x, s32 y, const SColor& color, bool blend )
//{
//	if (!src) return;
//	if (x<0) x=0;
//	if (y<0) y=0;
//
//	const core::dimension2du& Size = src->getDimension();
//
//	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
//	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
//    src->setPixel( (u32)x, (u32)y, color, blend);
//}
//
////! @brief get pixel from signed integer coords only if inside (0,0,w,h) else SColor(0,0,0,0)
//
//SColor getPixel( IImage* src, s32 x, s32 y )
//{
//	if (!src) return SColor(0,0,0,0);
//	if (x<0) return SColor(0,0,0,0);
//	if (y<0) return SColor(0,0,0,0);
//	const core::dimension2du& Size = src->getDimension();
//	if (x>(s32)Size.Width-1) return SColor(0,0,0,0);
//	if (y>(s32)Size.Height-1) return SColor(0,0,0,0);
//	return src->getPixel((u32)x,(u32)y);
//}
//
////! @brief get pixel from signed integer coords (always)
//
//SColor getPixelAlways( IImage* src, s32 x, s32 y )
//{
//	if (!src) return SColor(0,0,0,0);
//	if (x<0) x=0;
//	if (y<0) y=0;
//	const core::dimension2du& Size = src->getDimension();
//	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
//	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
//	return src->getPixel( (u32)x, (u32)y);
//}

} // end namespace video

} // end namespace irr
