// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "drawRoundRect.h"

#include "drawPixel.h"

#include "drawLine.h"

#include "drawImage.h"

namespace irr
{

namespace video
{

	typedef core::array<core::position2di> PointList;

	PointList traverseLine( const core::position2di& A, const core::position2di& B )
	{
		PointList dst( irr::core::abs_<s32>(B.X-A.X)+irr::core::abs_<s32>(B.Y-A.Y) );
		return dst;
	}

	PointList traverseCircle( const core::position2di& center, s32 radius )
	{
		PointList dst( radius+3 );
		dst.set_used(0);

		// Bresenham
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
			dst.push_back( core::position2di( center.X+i,center.Y+j ) );
			dst.push_back( core::position2di( center.X+j,center.Y+i ) );
		}
		return dst;
	}


	PointList traverseEllipse( const core::position2di& center, s32 rx, s32 ry )
	{
	//	const s32 w = dest->getDimension().Width;
	//	const s32 h = dest->getDimension().Height;

		if (rx==ry)
			return traverseCircle( center, rx );

		PointList dst;
		dst.reallocate(rx+ry);
		dst.set_used(0);

		// Abbruchbedingung
		if ( (rx==0) && (ry==0) )
			return dst;

		const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
		const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
		s32 x = center.X;
		s32 y = center.Y;
	//	const s32 mx = center.X;	 // Ellipsen Mittelpunkt
	//	const s32 my = center.Y; 	 // Ellipsen Mittelpunkt

		// Bresenham Anfangswerte
		// Trick: nur 1/4 Ellipse berechne und restliche 3/4 durch Spiegelung (gerade Ellipse!!!)
		s32 ddF_x=0;
		s32 ddF_y=((rx2*ry)<<1);
		x=0;
		y=ry;

		// Bresenham Alghorithmus
		s32 F=irr::core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
		while( ddF_x < ddF_y )
		{
			if (F >= 0)
			{
				y     -= 1;        // south
				ddF_y -= (rx2<<1);
				F     -= ddF_y;
			}
			x     += 1;          // east
			ddF_x += (ry2<<1);
			F     += ddF_x + ry2;

			dst.push_back( core::position2di( center.X+x, center.Y+y) );
		}

		// Bresenham Alghorithmus
		F = irr::core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
		while( y > 0 )
		{
			if(F <= 0)
			{
				x     += 1;        // east
				ddF_x += (ry2<<1);
				F     += ddF_x;
			}
			y     -= 1;           // south
			ddF_y -= (rx2<<1);
			F     += rx2 - ddF_y;

			dst.push_back( core::position2di( center.X+x, center.Y+y) );
		}
		return dst;
	}


	//! draw a Bresenham-round-rect, 1 colors, filled (border=0) or outlined with border, option to blend
	void drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& color, s32 border, bool blend)
	{
		// abort
		if (!dst)
			return;

		// abort
		if (rx < 1 && ry < 1)
			return;

		// set equal, if one radius is zero --> circle
		if (rx==0) rx = ry;
		if (ry==0) ry = rx;

		s32 w = pos.getWidth();
		s32 h = pos.getHeight();

	//	core::position2di m = pos.getCenter();
	//	core::position2di dA( (w-1)>>1, ry);
	//	core::position2di lowerRight(w-1-rx, ry);
	//	core::position2di upperLeft(rx, h-1-ry);
	//	core::position2di upperRight(w-1-rx, h-1-ry);

		core::position2di lowerLeft = core::position2di(rx, ry) + pos.UpperLeftCorner;
		core::position2di lowerRight = core::position2di(w-1-rx, ry) + pos.UpperLeftCorner;
		core::position2di upperLeft = core::position2di(rx, h-1-ry) + pos.UpperLeftCorner;
		core::position2di upperRight = core::position2di(w-1-rx, h-1-ry) + pos.UpperLeftCorner;

		// draw a filled round-rect
		if (border == 0)
		{
			// Ellipsen-Code
			const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
			const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
			s32 x = 0;
			s32 y = 0;

			// Bresenham Ellipse Anfangswerte
			s32 ddF_x=0;
			s32 ddF_y=((rx2*ry)<<1);
			x=0;
			y=ry;

			// Bresenham Alghorithmus
			s32 F=irr::core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
			while( ddF_x < ddF_y )
			{
				if (F >= 0)
				{
					y     -= 1;        // south
					ddF_y -= (rx2<<1);
					F     -= ddF_y;
				}
				x     += 1;          // east
				ddF_x += (ry2<<1);
				F     += ddF_x + ry2;
				drawLine( dst, upperLeft.X-x, upperLeft.Y+y, upperRight.X+x, upperRight.Y+y, color, blend);
				drawLine( dst, lowerLeft.X-x, lowerLeft.Y-y, lowerRight.X+x, lowerRight.Y-y, color, blend);
			}

			// Bresenham Alghorithmus
			F = irr::core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
			while( y > 0 )
			{
				if(F <= 0)
				{
					x     += 1;        // east
					ddF_x += (ry2<<1);
					F     += ddF_x;
				}
				y     -= 1;           // south
				ddF_y -= (rx2<<1);
				F     += rx2 - ddF_y;

				drawLine( dst, upperLeft.X-x, upperLeft.Y+y, upperRight.X+x, upperRight.Y+y, color, blend);
				drawLine( dst, lowerLeft.X-x, lowerLeft.Y-y, lowerRight.X+x, lowerRight.Y-y, color, blend);
			}

			s32 y1 = pos.UpperLeftCorner.Y + ry;
			s32 y2 = pos.UpperLeftCorner.Y + pos.getHeight() - ry;
			y = y1;
			while( y < y2 )
			{
				drawLine( dst, pos.UpperLeftCorner.X , y, pos.LowerRightCorner.X, y, color, blend);
				y++;
			}

		}
		// draw a bordered round-rect
		else
		{
			if (border == 1)
			{
				PointList points = traverseEllipse( core::position2di(0,0), rx,ry);

				for (u32 i=0; i<points.size(); i++)
				{
					dst->setPixel(upperRight.X + points[i].X, upperRight.Y + points[i].Y, color);
					dst->setPixel(lowerRight.X + points[i].X, lowerRight.Y - points[i].Y, color);
					dst->setPixel(upperLeft.X - points[i].X, upperLeft.Y + points[i].Y, color);
					dst->setPixel(lowerLeft.X - points[i].X, lowerLeft.Y - points[i].Y, color);
				}

				//! core::recti has flaws, i.e. it does not guarantee that UpperLeftCorner is more upper and left than LowerRightCorner !!!
				const s32 x1 = irr::core::s32_min( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
				const s32 y1 = irr::core::s32_min( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);
				const s32 x2 = irr::core::s32_max( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
				const s32 y2 = irr::core::s32_max( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);

				drawLine( dst, x1+rx, y1, x2-1-rx, y1, color, blend);
				drawLine( dst, x1+rx, y2-1, x2-1-rx, y2-1, color, blend);
				drawLine( dst, x1, y1+ry, x1, y2-1-ry, color, blend);
				drawLine( dst, x2-1, y1+ry, x2-1, y2-1-ry, color, blend);
			}
			else
			{
				IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du(w+1,h+1));
				if (!tmp)
					return;

				tmp->fill(0);
				drawRoundRect( tmp, core::recti(0,0,(s32)w, (s32)h), rx,ry, color, 0, false);
				drawRoundRect( tmp, core::recti(border, border, (s32)w-border, (s32)h-border), rx,ry, 0, 0, false);

				drawImage( tmp, dst, pos.UpperLeftCorner, tmp->getDimension(), true, false);
				tmp->drop();

	//			floodFill(x1)
			}
		}
	}

	void drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border, bool blend)
	{
		// abort
		if (!dst)
			return;

		//! guarantee that UpperLeftCorner is more upperleft than LowerRightCorner
		const s32 x1 = irr::core::s32_min( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
		const s32 y1 = irr::core::s32_min( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);
		const s32 x2 = irr::core::s32_max( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
		const s32 y2 = irr::core::s32_max( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);

		core::dimension2du size( (u32)(x2-x1)+1, (u32)(y2-y1)+1 );

		// abort
		if ((size.Width == 0) || (size.Height == 0))
			return;

		// create temporary canvas-image
		IImage* tmp = new CImage( dst->getColorFormat(), size);

		// abort
		if (!tmp)
			return;

		const SColor black(0,0,0,0);
		const SColor white(255,255,255,255);

		tmp->fill( black );

		drawRoundRect( tmp, core::recti( core::position2di(0,0), size), rx,ry, white, border, false);

		// interpolate colors
		// common factor for all colors ( 1 / (dx * dy) )
		const f32 n_inv = irr::core::reciprocal( (f32)(x2 - x1) * (f32)(y2 - y1) );

		for (u32 y=0; y<size.Height; y++)
		{
			for (u32 x=0; x<size.Width; x++)
			{
				if (getPixel( tmp,x,y ) == white)
				{
					const f32 f11 = (f32)(size.Width-1-x) * (f32)(size.Height-1 - y) * n_inv; // topLeft
					const f32 f21 = (f32)(x) * (f32)(size.Height-1 - y) * n_inv; // topRight
					const f32 f12 = (f32)(size.Width-1 - x) * (f32)(y) * n_inv; // bottomLeft
					const f32 f22 = (f32)(x) * (f32)(y) * n_inv; // bottomRight

					const f32 fA = 	(f32)topLeft.getAlpha() * f11 +
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

					drawPixel( tmp, x, y, color, blend);
				}
			}
		}

		// drawing finished and copy dst to srcImage
		drawImage( dst, tmp, core::position2di(x1,y1), size, true, false);
		tmp->drop();
	}

} // end namespace video

} // end namespace irr
