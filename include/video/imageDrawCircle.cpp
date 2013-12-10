// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "imageDrawCircle.h"

#include <../source/Irrlicht/os.h>
#include <../source/Irrlicht/CColorConverter.h>
#include <../source/Irrlicht/CImage.h>

/// maybe you need to include the following lines once to your main cpp file
//#include <../source/Irrlicht/os.cpp>
//#include <../source/Irrlicht/CColorConverter.cpp>
//#include <../source/Irrlicht/CImage.cpp>

#include "imageDrawPixel.h"

#include "imageDrawLine.h"

#include "imageDrawImage.h"

namespace irr
{

namespace video
{

//! Bresenham circle with 1 color(s), if border <= 0 then filled/solid shape

void

	drawCircle(

		IImage* dst,

		const core::position2di& center,

		s32 radius,

		const SColor& color,

		s32 border,

		bool blend)

{
	if (!dst)
		return;

	if ( radius < 0 )
		return;

	else if ( radius == 0 )
	{
		drawPixel( dst, center.X, center.Y, color, blend);
	}
	else if (radius == 1)
	{
		if (border==0)
		{
			drawPixel( dst, center.X,center.Y,color,blend);
		}
		drawPixel( dst, center.X-1,center.Y,color,blend);
		drawPixel( dst, center.X,center.Y-1,color,blend);
		drawPixel( dst, center.X,center.Y+1,color,blend);
		drawPixel( dst, center.X+1,center.Y,color,blend);
	}
	else if (radius == 2)
	{
		if (border==0)
		{
		drawPixel( dst, center.X-1,center.Y+1,color,blend);
		drawPixel( dst, center.X-1,center.Y,color,blend);
		drawPixel( dst, center.X,center.Y+1,color,blend);
		drawPixel( dst, center.X,center.Y,color,blend);
		}

		drawPixel( dst, center.X-2,center.Y+1,color,blend);
		drawPixel( dst, center.X-2,center.Y,  color,blend);
		drawPixel( dst, center.X-1,center.Y+2,color,blend);
		drawPixel( dst, center.X-1,center.Y-1,color,blend);
		drawPixel( dst, center.X,  center.Y+2,color,blend);
		drawPixel( dst, center.X,  center.Y-1,color,blend);
		drawPixel( dst, center.X+1,center.Y+1,color,blend);
		drawPixel( dst, center.X+1,center.Y,  color,blend);
	}
	else
	{
		// 'Bresenham' Algorithmus (Achtelkreis Symmetrie)
		// ohne Trigonometrische- und Wurzel-Funktionen
		// und Spiegelung auf Restliche 7/8

		if (border==0) // filled
		{
			s32 i,j,F;
			i = 0;
			j = radius;
			F = 1 - radius;

			while (i < j)
			{
				++i;
				if (F < 0)
				{
					F += (i<<1) - 1;
				}
				else
				{
					F += ((i - j)<<1);
					--j;
				}

				// Verbesserungen by Benjamin Hampe (c) 2012
				drawLine( dst, center.X-i, center.Y+j-1, center.X+i-1,center.Y+j-1, color, blend );
				drawLine( dst, center.X-j, center.Y+i-1, center.X+j-1,center.Y+i-1, color, blend );
				drawLine( dst, center.X-j, center.Y-i, center.X+j-1, center.Y-i, color, blend );
				drawLine( dst, center.X-i, center.Y-j, center.X+i-1, center.Y-j, color, blend );
			}
		}

		// 'Bresenham' Algorithmus (Achtelkreis Symmetrie)
		// ohne Trigonometrische- und Wurzel-Funktionen
		// und Spiegelung auf Restliche 7/8

		else if (border == 1)
		{
			s32 i,j,F;
			i = 0;
			j = radius;
			F = 1 - radius;

			while (i < j)
			{
				++i;
				if (F < 0)
				{
					F += (i<<1) - 1;
				}
				else
				{
					F += ((i - j)<<1);
					--j;
				}
				// Verbesserungen by Benjamin Hampe (c) 2012
				drawPixel( dst, center.X+i-1,center.Y-j,color, blend); // 1st quadrant
				drawPixel( dst, center.X+j-1,center.Y-i,color, blend); // 1st quadrant
				drawPixel( dst, center.X+i-1,center.Y+j-1,color, blend); // 2nd quadrant
				drawPixel( dst, center.X+j-1,center.Y+i-1,color, blend); // 2nd quadrant
				drawPixel( dst, center.X-i,center.Y+j-1,color, blend); // 3rd quadrant
				drawPixel( dst, center.X-j,center.Y+i-1,color, blend); // 3rd quadrant
				drawPixel( dst, center.X-i,center.Y-j,color, blend); // 4th quadrant
				drawPixel( dst, center.X-j,center.Y-i,color, blend); // 4th quadrant
			}
		}

		// by Benjamin Hampe
		// create circle from undistorted temporary image

		else if (border > 1)
		{
			if (radius - border > 1)
			{
				IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
				if (!tmp)
					return;

//				tmp->enableColorKey();
				tmp->fill( 0 );
				drawCircle( tmp, core::position2di(radius,radius), radius, color, 0, blend);
				drawCircle( tmp, core::position2di(radius,radius), radius - border, 0, 0, blend);
				drawImage( tmp, dst, center - core::position2di(radius,radius), tmp->getDimension(), true, false);
				tmp->drop();
			}
		}
	}
}


//! Bresenham circle with 2 interpolated color(s) from center to outline

//! if (border <= 0) then filled/solid shape

//void ImageTool::drawCircle( IImage* dst, const core::position2di& center, s32 radius, const SColor& c1, const SColor& c2, s32 border, bool blend)
//{
//	// abort
//	if (!dst) return;
//
//	// abort
//	if (radius < 0)
//	{
//		return;
//	}
//	else if (radius == 0)
//	{
//		drawPixel( dst,center.X,center.Y,c2,blend);
//		return;
//	}
//	else if (radius == 1)
//	{
//		drawPixel( dst,center.X,center.Y,c2,blend);
//		drawPixel( dst,center.X,center.Y-1,c1,blend);
//		drawPixel( dst,center.X,center.Y+1,c1,blend);
//		drawPixel( dst,center.X+1,center.Y,c1,blend);
//		drawPixel( dst,center.X-1,center.Y,c1,blend);
//		return;
//	}
//	else
//	{
//		if (border==0) // filled
//		{
//			IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
//			if (!tmp)
//				return;
//			tmp->fill( 0 );
//			drawCircle( tmp, core::position2di(radius,radius), radius, SColor(255,255,255,255), 0, blend);
//
//			const f32 fA = (f32)c1.getAlpha(), fdA = (f32)c2.getAlpha() - fA;
//			const f32 fR = (f32)c1.getRed(), fdR = (f32)c2.getRed() - fR;
//			const f32 fG = (f32)c1.getGreen(), fdG = (f32)c2.getGreen() - fG;
//			const f32 fB = (f32)c1.getBlue(), fdB = (f32)c2.getBlue() - fB;
//			const SColor white(255,255,255,255);
//			const f32 fw = 0.5f*(f32)tmp->getDimension().Width;
//			const f32 fh = 0.5f*(f32)tmp->getDimension().Height;
//			const f32 invRadius = irr::core::reciprocal( (f32)radius );
//
//			const core::dimension2du& Size = tmp->getDimension();
//			for (u32 y = 0; y < Size.Height; y++)
//			{
//				for (u32 x = 0; x < Size.Width; x++)
//				{
//					const SColor& colorNow = tmp->getPixel(x,y);
//					if (colorNow == white)
//					{
//						const f32 dx = (f32)x - fw;
//						const f32 dy = (f32)y - fh;
//						f32 f = squareroot( dx*dx + dy*dy ) * invRadius;
//						u32 uA = (u32)irr::core::s32_clamp( irr::core::round32( fA + f*fdA ), 0, 255);
//						u32 uR = (u32)irr::core::s32_clamp( irr::core::round32( fR + f*fdR ), 0, 255);
//						u32 uG = (u32)irr::core::s32_clamp( irr::core::round32( fG + f*fdG ), 0, 255);
//						u32 uB = (u32)irr::core::s32_clamp( irr::core::round32( fB + f*fdB ), 0, 255);
//						tmp->setPixel( x, y, SColor(uA,uR,uG,uB), blend );
//					}
//				}
//			}
//
//			drawImage( tmp, dst, center - core::position2di(radius,radius), tmp->getDimension(), true, false);
//			tmp->drop();
//			return;
//		}
//		else if (border == 1) // outline with color c1
//		{
//			drawCircle( dst, center, radius, c1, 1, blend);
//		}
//		else if (border > 1)
//		{
//			if (radius - border > 0)
//			{
//				IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
//				if (!tmp)
//					return;
//
//				const SColor black(  0,  0,  0,  0);
//				const SColor white(255,255,255,255);
//
//				tmp->fill( black );
//				drawCircle( tmp, core::position2di(radius,radius), radius, white, 0, blend);
//				drawCircle( tmp, core::position2di(radius,radius), radius-border, black, 0, blend);
//
//				const f32 fA = (f32)c1.getAlpha(), fdA = (f32)c2.getAlpha() - fA;
//				const f32 fR = (f32)c1.getRed(), fdR = (f32)c2.getRed() - fR;
//				const f32 fG = (f32)c1.getGreen(), fdG = (f32)c2.getGreen() - fG;
//				const f32 fB = (f32)c1.getBlue(), fdB = (f32)c2.getBlue() - fB;
//
//				const core::dimension2du& Size = tmp->getDimension();
//
//				const f32 fw = 0.5f*(f32)Size.Width;
//				const f32 fh = 0.5f*(f32)Size.Height;
//				const f32 invRadius = irr::core::reciprocal( (f32)border );
//				const s32 innerCircle = radius-border;
//
//				for (u32 y = 0; y < Size.Height; y++)
//				{
//					for (u32 x = 0; x < Size.Width; x++)
//					{
//						const SColor& colorNow = tmp->getPixel(x,y);
//						if (colorNow == white)
//						{
//							const f32 dx = (f32)x - fw;
//							const f32 dy = (f32)y - fh;
//
//							f32 f = (squareroot( dx*dx + dy*dy ) - (f32)innerCircle ) * invRadius;
//							u32 uA = (u32)irr::core::s32_clamp( irr::core::round32( fA + f*fdA ), 0, 255);
//							u32 uR = (u32)irr::core::s32_clamp( irr::core::round32( fR + f*fdR ), 0, 255);
//							u32 uG = (u32)irr::core::s32_clamp( irr::core::round32( fG + f*fdG ), 0, 255);
//							u32 uB = (u32)irr::core::s32_clamp( irr::core::round32( fB + f*fdB ), 0, 255);
//							tmp->setPixel( x, y, SColor(uA,uR,uG,uB), blend );
//						}
//					}
//				}
//
//				drawImage( tmp, dst, center - core::position2di(radius,radius), tmp->getDimension(), true, false);
//				tmp->drop();
//			}
//		}
//	}
//}

} // end namespace video

} // end namespace irr
