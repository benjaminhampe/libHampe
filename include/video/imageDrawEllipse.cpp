// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "imageDrawEllipse.h"

#include "imageDrawPixel.h"

#include "imageDrawLine.h"

#include "imageDrawCircle.h"

namespace irr
{

namespace video
{

//! draw a Bresenham-ellipse, 1 color, filled or outlined, option to blend
void drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& color, s32 border, bool blend)

{
	if (!dst) return; // abort
//			const s32 w = dest->getDimension().Width;
//			const s32 h = dest->getDimension().Height;

	// Abbruchbedingung
	if (rx < 1 && ry < 1) return;
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	if (rx==ry)
		drawCircle( dst, center, rx, color, border, blend);

	//if (rw==1 && rh==1) dest->setPixel(x,y,color);

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

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, color, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, color, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, y+center.Y, color, blend);
			drawPixel( dst, x+center.X, -y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, color, blend);

			// Spiegelung mit meinen Anpassungen
			// drawPixel( dst, x+mx, y+my, color, blend);
			// drawPixel( dst, -x+mx+1, y+my, color, blend);
			// drawPixel( dst, x+mx, -y+my+1, color, blend);
			// drawPixel( dst, -x+mx+1, -y+my+1, color, blend);
		}
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

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, color, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, color, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, y+center.Y, color, blend);
			drawPixel( dst, x+center.X, -y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, color, blend);

			// Spiegelung mit meinen Anpassungen
//			drawPixel( dst, x+mx, y+my, color, blend);
//			drawPixel( dst, -x+mx+1, y+my, color, blend);
//			drawPixel( dst, x+mx, -y+my+1, color, blend);
//			drawPixel( dst, -x+mx+1, -y+my+1, color, blend);
		}
	}
}

//! Bresenham ellipse
void drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& c1, const SColor& c2, s32 border, bool blend)
{
	if (!dst) return; // abort
//			const s32 w = dest->getDimension().Width;
//			const s32 h = dest->getDimension().Height;

	// Abbruchbedingung
	if (rx < 1 && ry < 1) return;
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	if (rx==ry)
		drawCircle( dst, center, rx, c1, border, blend);

	//if (rw==1 && rh==1) dest->setPixel(x,y,color);

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

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, c1, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, c1, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, x+center.X, -y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, c1, blend);
		}
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

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, c1, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, c1, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, x+center.X, -y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, c1, blend);
		}
	}
}



} // end namespace video

} // end namespace irr
