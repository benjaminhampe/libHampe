// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "imageDrawRect.h"

#include "imageDrawPixel.h"

#include "imageDrawLine.h"

#include "imageDrawImage.h"

namespace irr
{

namespace video
{

	//! draw a bresenham rect with 1 color

	//! if ( border <= 0 ) solid/filled else (border>0) outlined/border

	void drawRect(

		IImage* dst,

		const core::recti& pos,

		const SColor& color,

		s32 border,

		bool blend )

	{

		s32 x1 = pos.UpperLeftCorner.X;
		s32 y1 = pos.UpperLeftCorner.Y;
		s32 x2 = pos.LowerRightCorner.X;
		s32 y2 = pos.LowerRightCorner.Y;

		if (border==0)
		{
			for (s32 y=y1; y<=y2; y++)
			{
				for (s32 x=x1; x<=x2; x++)
				{
					if (color.getAlpha()<255)
					{
						SColor pixel = getPixelAlways( dst, x,y );
						s32 r = (s32)irr::core::clamp<f32>((f32)color.getAlpha()*(f32)color.getRed()/255.0f, 0,255.f);
						s32 g = (s32)irr::core::clamp<f32>((f32)color.getAlpha()*(f32)color.getGreen()/255.0f, 0,255.f);
						s32 b = (s32)irr::core::clamp<f32>((f32)color.getAlpha()*(f32)color.getBlue()/255.0f, 0,255.f);
						pixel.set( pixel.getAlpha(),
							(u32)irr::core::s32_clamp(pixel.getRed() + r,0,255),
							(u32)irr::core::s32_clamp(pixel.getGreen() + g,0,255),
							(u32)irr::core::s32_clamp(pixel.getBlue() + b,0,255) );
						drawPixel( dst, x, y, pixel, blend);

					}
					else
					{
						drawPixel( dst, x, y, color, blend);
					}
				}
			}
		}
		else if ( border >= 1)
		{
			for (s32 b=0; b<border; b++)
			{
				drawLine( dst, x1+b,y1+b, x2-b,y1+b, color, blend);
				drawLine( dst, x1+b,y1+b, x1+b,y2-b, color, blend);
				drawLine( dst, x2-b,y1+b, x2-b,y2-b, color, blend);
				drawLine( dst, x1+b,y2-b, x2-b,y2-b, color, blend);
			}
		}
	}


	//! draw a bresenham rect with 4 linear interpolated colors

	//! if ( border <= 0 ) solid/filled else (border>0) outlined/border

	void drawRect(

		IImage* dst,

		const core::recti& pos,

		const SColor& bottomLeft,

		const SColor& topLeft,

		const SColor& topRight,

		const SColor& bottomRight,

		s32 border,

		bool blend )

	{
		if (border==0)
		{
			const s32& x1 = pos.UpperLeftCorner.X;
			const s32& x2 = pos.LowerRightCorner.X;
			const s32& y1 = pos.UpperLeftCorner.Y-1;
			const s32& y2 = pos.LowerRightCorner.Y-1;

			// common factor for all colors ( 1 / (dx * dy) )
			const f32 n_inv = irr::core::reciprocal( (f32)(x2 - x1) * (f32)(y2 - y1) );

			for (s32 y=y1; y<=y2; y++)
			{
				for (s32 x=x1; x<=x2; x++)
				{
					const f32 f11 = (f32)(x2 - x) * (f32)(y2 - y) * n_inv; // bottomRight
					const f32 f21 = (f32)(x - x1) * (f32)(y2 - y) * n_inv; // bottomLeft
					const f32 f12 = (f32)(x2 - x) * (f32)(y - y1) * n_inv; // topRight
					const f32 f22 = (f32)(x - x1) * (f32)(y - y1) * n_inv; // topLeft

					const f32 fA = 	(f32)topLeft.getAlpha() * f11 +
									(f32)topRight.getAlpha() * f21 +
									(f32)bottomRight.getAlpha() * f22 +
									(f32)bottomLeft.getAlpha() * f12;

					const f32 fR = 	(f32)topLeft.getRed() * f11 +
									(f32)topRight.getRed() * f21 +
									(f32)bottomRight.getRed() * f22 +
									(f32)bottomLeft.getRed() * f12;

					const f32 fG = 	(f32)topLeft.getGreen() * f11 +
									(f32)topRight.getGreen() * f21 +
									(f32)bottomRight.getGreen() * f22 +
									(f32)bottomLeft.getGreen() * f12;

					const f32 fB = 	(f32)topLeft.getBlue() * f11 +
									(f32)topRight.getBlue() * f21 +
									(f32)bottomRight.getBlue() * f22 +
									(f32)bottomLeft.getBlue() * f12;

					SColor color(
						(u32)irr::core::clamp( irr::core::round32(fA), 0, 255),
						(u32)irr::core::clamp( irr::core::round32(fR), 0, 255),
						(u32)irr::core::clamp( irr::core::round32(fG), 0, 255),
						(u32)irr::core::clamp( irr::core::round32(fB), 0, 255) );

					drawPixel( dst, x, y, color, blend);
				}
			}
		}
		else if ( border == 1)
		{
	//		drawLine( pos.UpperLeftCorner, core::position2di(pos.LowerRightCorner.X, pos.UpperLeftCorner.Y), color, blend);
	//		drawLine( pos.UpperLeftCorner, core::position2di(pos.UpperLeftCorner.X, pos.LowerRightCorner.Y), color, blend);
	//		drawLine( core::position2di(pos.LowerRightCorner.X, pos.UpperLeftCorner.Y), pos.LowerRightCorner, color, blend);
	//		drawLine( core::position2di(pos.UpperLeftCorner.X, pos.LowerRightCorner.Y), pos.LowerRightCorner, color, blend);
	//
			const s32 x = pos.LowerRightCorner.X-1;
			const s32 y = pos.LowerRightCorner.Y-1;
			drawLine( dst, pos.UpperLeftCorner.X, pos.UpperLeftCorner.Y, x, pos.UpperLeftCorner.Y, topLeft, topRight, blend);
			drawLine( dst, pos.UpperLeftCorner.X, pos.UpperLeftCorner.Y, pos.UpperLeftCorner.X, y, topLeft, bottomLeft, blend);
			drawLine( dst, x, pos.UpperLeftCorner.Y, x,y, topRight, bottomRight, blend);
			drawLine( dst, pos.UpperLeftCorner.X, y, x,y, bottomLeft, bottomRight, blend);
		}
		else if ( border > 1)
		{
			IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( (u32)pos.getWidth(), (u32)pos.getHeight() ) );
			if (!tmp)
				return;

			const SColor black(  0,  0,  0,  0);
			const SColor white(255,255,255,255);

			tmp->fill( black );
			drawRect( tmp, core::recti( core::position2di(0,0), tmp->getDimension()), white, border, blend);

			// common factor for all colors ( 1 / (w * h) )
			const u32 w = tmp->getDimension().Width;
			const u32 h = tmp->getDimension().Height;
			const f32 n_inv = irr::core::reciprocal( (f32)w * (f32)h );

			for (u32 y = 0; y < h; y++)
			{
				u32 x = 0;
				while (x < w)
				{
					const SColor& colorNow = tmp->getPixel(x,y);

					if (colorNow == white)
					{
						const f32 f11 = (f32)(w-1-x) * (f32)(h-1-y) * n_inv; // topLeft
						const f32 f21 = (f32)(x) * (f32)(h-1-y) * n_inv; // topRight
						const f32 f12 = (f32)(w-1-x) * (f32)(y) * n_inv; // bottomLeft
						const f32 f22 = (f32)(x) * (f32)(y) * n_inv; // bottomRight

						const f32 fA = (f32)topLeft.getAlpha() * f11 +
										(f32)topRight.getAlpha() * f21 +
										(f32)bottomRight.getAlpha() * f12 +
										(f32)bottomLeft.getAlpha() * f22;

						const f32 fR = 	(f32)topLeft.getRed() * f11 +
										(f32)topRight.getRed() * f21 +
										(f32)bottomRight.getRed() * f12 +
										(f32)bottomLeft.getRed() * f22;

						const f32 fG = 	(f32)topLeft.getGreen() * f11 +
										(f32)topRight.getGreen() * f21 +
										(f32)bottomRight.getGreen() * f12 +
										(f32)bottomLeft.getGreen() * f22;

						const f32 fB = 	(f32)topLeft.getBlue() * f11 +
										(f32)topRight.getBlue() * f21 +
										(f32)bottomRight.getBlue() * f12 +
										(f32)bottomLeft.getBlue() * f22;

						SColor color(
							(u32)irr::core::clamp( irr::core::round32(fA), 0, 255),
							(u32)irr::core::clamp( irr::core::round32(fR), 0, 255),
							(u32)irr::core::clamp( irr::core::round32(fG), 0, 255),
							(u32)irr::core::clamp( irr::core::round32(fB), 0, 255) );

						drawPixel( dst, x, y, color, blend);
					}
	//				else
	//				{
	//					x += ( w - (border<<1)) - 2; // skip pixels to increase speed
	//				}
					x++;
				}
			}

			drawImage( tmp, dst, pos.UpperLeftCorner, tmp->getDimension(), true, false);
			tmp->drop();

		}
	}

} // end namespace video

} // end namespace irr
