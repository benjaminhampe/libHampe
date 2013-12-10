// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_DRAW_PIXEL_TO_SOFTWARE_IMAGE_H__
#define __IRR_EXT_DRAW_PIXEL_TO_SOFTWARE_IMAGE_H__

#include <irrlicht.h>

namespace irr
{
namespace video
{


//! @brief set pixel for signed integer coords only if inside (0,0,w,h)

REALINLINE void drawPixel( IImage* src, s32 x, s32 y, const SColor& color, bool blend )
{
	if (!src) return;
	if (x<0) return;
	if (y<0) return;
    src->setPixel( (u32)x, (u32)y, color, blend);
}

//! @brief set pixel for signed integer coords always - simple border align

REALINLINE void drawPixelAlways( IImage* src, s32 x, s32 y, const SColor& color, bool blend )
{
	if (!src) return;
	if (x<0) x=0;
	if (y<0) y=0;

	const core::dimension2du& Size = src->getDimension();

	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
    src->setPixel( (u32)x, (u32)y, color, blend);
}

//! @brief get pixel from signed integer coords only if inside (0,0,w,h) else SColor(0,0,0,0)

REALINLINE SColor getPixel( IImage* src, s32 x, s32 y )
{
	if (!src) return SColor(0,0,0,0);
	if (x<0) return SColor(0,0,0,0);
	if (y<0) return SColor(0,0,0,0);
	const core::dimension2du& Size = src->getDimension();
	if (x>(s32)Size.Width-1) return SColor(0,0,0,0);
	if (y>(s32)Size.Height-1) return SColor(0,0,0,0);
	return src->getPixel((u32)x,(u32)y);
}

//! @brief get pixel from signed integer coords (always)

REALINLINE SColor getPixelAlways( IImage* src, s32 x, s32 y )
{
	if (!src) return SColor(0,0,0,0);
	if (x<0) x=0;
	if (y<0) y=0;
	const core::dimension2du& Size = src->getDimension();
	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
	return src->getPixel( (u32)x, (u32)y);
}

////! @brief set pixel for signed integer coords only if inside (0,0,w,h)
//void drawPixel( IImage* src, s32 x, s32 y, const SColor& color, bool blend );
//
////! @brief set pixel for signed integer coords always - simple border align
//void drawPixelAlways( IImage* src, s32 x, s32 y, const SColor& color, bool blend );
//
////! @brief get pixel from signed integer coords only if inside (0,0,w,h) else SColor(0,0,0,0)
//SColor getPixel( IImage* src, s32 x, s32 y );
//
////! @brief get pixel from signed integer coords (always)
//SColor getPixelAlways( IImage* src, s32 x, s32 y );

//
//IrrColor ImageTool::getColorFromWavelength( f64 lambda, f64 gamma)
//{
//    // setze ? ? [380, 780]
//    if (lambda < 380.0) lambda = 380.0;
//    if (lambda > 780.0) lambda = 780.0;
//
//    // Fallunterscheidung
//    f64 r,g,b,f;
//
//    if ((lambda >= 380.0) && (lambda < 440.0)) { r = (440.0-lambda)/(440.0-380.0); g = 0.0; b = 1.0; }
//    else if ((lambda >= 440.0) && (lambda < 490.0)) { r = 0.0; g = (lambda-440.0)/(490.0-440.0); b = 1.0; }
//    else if ((lambda >= 490.0) && (lambda < 510.0)) { r = 0.0; g = 1.0; b = (510.0-lambda)/(510.0-490.0); }
//    else if ((lambda >= 510.0) && (lambda < 580.0)) { r = (lambda-510.0)/(580.0-510.0); g = 1.0; b = 0.0; }
//    else if ((lambda >= 580.0) && (lambda < 645.0)) { r = 1.0; g = (645.0-lambda)/(645.0-580.0); b = 0.0; }
//    else /* if ((lambda >= 645.0) && (lambda <= 780.0)) */ { r = 1.0; g = 0.0; b = 0.0; }
//
//    // reduce intesity at the borders
//    if ((lambda >= 380.0) && (lambda < 420.0)) { f = 0.3 + 0.7*(lambda-380.0)/(420.0-380.0); }
//    else if ((lambda >= 420.0) && (lambda <= 700.0)) { f = 1.0; }
//    else /* if ((lambda > 700.0) && (lambda <= 780.0)) */ { f = 0.3 + 0.7*(780.0-lambda)/(780.0-700.0); }
//
//    // eigentliche Korrektur
//    if (f!=1.0) { r *= f; g *= f; b *= f; }
//
//    // Gamma Korrektur
//    if (gamma!=1.0) { r = pow(r, gamma); g = pow(g, gamma); b = pow(b, gamma); }
//
//    // Clamping to [0,255]
//    r *= 255.0; g *= 255.0; b *= 255.0;
//
//    // hoffentlicht optimiert der compiler dies mit mmx und sse befehlen
//    if (r<0.0) r=0.0; if (g<0.0) g=0.0; if (b<0.0) b=0.0;
//
//    if (r>255.0) r=255.0; if (g>255.0) g=255.0; if (b>255.0) b=255.0;
//
//    // return ARGB 32bit color (Alpha = 'opaque' = 'nicht transparent' = '255')
//    return IrrColor(255,(u32)r, (u32)g, (u32)b );
//}
//
//IrrColor ImageTool::getColorFromRainbow( u32 i, u32 count, f64 gamma)
//{
//    //! division by zero would lead to runtime error !!!
//    if (count < 1) return IrrColor(255,255,255,255);
//	//! just a simple wrapper function, that linear inperpolates
//    return getColorFromWavelength(380.0 + 400.0*(f64)i/(f64)count, gamma);
//}
//
////! @author BenjaminHampe@gmx.de
////! @brief fill user defined color-planes with color-planes from another image or blend together
////! @param image to copy color-planes (all pixels involed) from
////! @param image to copy color-planes (all pixels involed) from
////! @param signed 32bit y-coord
////! @return nothing
//void ImageTool::fill( IrrImage* dst, const IrrColor& color, IrrColorPlane planes, bool blend)
//{
//	if (!dst) return; 														// abort
//
//	IrrColor c;
//	const IrrDim2u& Size = dst->getDimension();
//	for (u32 y=0; y<Size.Height; y++)													// loop y
//	{	for (u32 x=0; x<Size.Width; x++)												// loop x
//		{
//			c = color;
//			const IrrColor& old = dst->getPixel(x,y);							// read pixel
//			if (!(planes&irr::video::ECP_ALPHA)) c.setAlpha(old.getAlpha());		// set alpha channel to old pixel, if channel not used
//			if (!(planes&irr::video::ECP_RED)) c.setRed(old.getRed());				// set red channel to old pixel, if channel not used
//			if (!(planes&irr::video::ECP_GREEN)) c.setGreen(old.getGreen());		// set green channel to old pixel, if channel not used
//			if (!(planes&irr::video::ECP_RED)) c.setBlue(old.getBlue());			// set blue channel to old pixel, if channel not used
//			dst->setPixel(x,y,c,blend);									// write pixel
//		}
//	}
//}
//
//


} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_BRESENHAM_LINE_GRID_TO_SOFTWARE_IMAGE_H__
