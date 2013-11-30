// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "drawLine.h"

#include "drawPixel.h"

/// ----------------------------

/// BASIC DIALECT MACROS

/// ----------------------------

#ifdef BEGIN_FUNCTION
	#undef BEGIN_FUNCTION
#endif // BEGIN_FUNCTION

#ifndef BEGIN_FUNCTION
	#define BEGIN_FUNCTION {
#endif // BEGIN_FUNCTION

#ifdef END_FUNCTION
	#undef END_FUNCTION
#endif // END_FUNCTION

#ifndef END_FUNCTION
	#define END_FUNCTION }
#endif // END_FUNCTION

/// ----------------------------

#ifdef IF
	#undef IF
#endif // IF

#ifndef IF
	#define IF if (
#endif // IF

#ifdef THEN
	#undef THEN
#endif // THEN

#ifndef THEN
	#define THEN ) {
#endif // THEN

#ifdef ENDIF
	#undef ENDIF
#endif // ENDIF

#ifndef ENDIF
	#define ENDIF }
#endif // ENDIF

#ifdef ELSE
	#undef ELSE
#endif // ELSE

#ifndef ELSE
	#define ELSE } else {
#endif // ELSE

#ifdef ELIF
	#undef ELIF
#endif // ELIF

#ifndef ELIF
	#define ELIF } else if (
#endif // ELIF

/// ----------------------------

#ifdef WHILE
	#undef WHILE
#endif // WHILE

#ifndef WHILE
	#define WHILE while (
#endif // WHILE

#ifdef END_WHILE
	#undef END_WHILE
#endif // END_WHILE

#ifndef END_WHILE
	#define END_WHILE }
#endif // END_WHILE

/// ----------------------------

#ifdef AND
	#undef AND
#endif // AND

#ifndef AND
	#define AND &&
#endif // AND

#ifdef OR
	#undef OR
#endif // OR

#ifndef OR
	#define OR ||
#endif // OR

/// ----------------------------

#ifdef BEGIN
	#undef BEGIN
#endif // BEGIN

#ifndef BEGIN
	#define BEGIN {
#endif // BEGIN

#ifdef END
	#undef END
#endif // END

#ifndef END
	#define END }
#endif // END

namespace irr
{

namespace video
{

//! draw a line with 1 color(s) to image ( Bresenham, no AA )

bool drawLine(

	video::IImage* dst,

	s32 x0,

	s32 y0,

	s32 x1,

	s32 y1,

	const video::SColor& color,

	bool blend )

BEGIN_FUNCTION

	IF !dst
	THEN
		return false;
	ENDIF

	const core::dimension2du img_size = dst->getDimension();

	IF img_size.Width==0 AND img_size.Height==0
	THEN
		return false;
	ENDIF

	const s32 dx = core::abs_<s32>( x1 - x0 );
	const s32 dy = core::abs_<s32>( y1 - y0 );

	IF dx==0 AND dy==0
	THEN
		return false;
	ENDIF

	s32 sx=1; // sign
	s32 sy=1; // sign

	IF x0>x1
	THEN
		sx = -1;
	ENDIF

	IF y0>y1
	THEN
		sy = -1;
	ENDIF

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = x0;
	s32 y = y0;

	WHILE 1	THEN

		drawPixel( dst,x,y,color, blend);

		IF x==x1 AND y==y1
		THEN
			break;
		ENDIF

		e2 = err << 1;

		IF e2 > -dy
		THEN
			err -= dy;
			x += sx;
		ENDIF

		IF e2 < dx
		THEN
			y += sy;
			err += dx;
		ENDIF

	END_WHILE

	return true;

END_FUNCTION

//! draw a line with 2 color(s) to image ( Bresenham, no AA )

bool drawLine(

	video::IImage* dst,

	s32 x0,

	s32 y0,

	s32 x1,

	s32 y1,

	const video::SColor& color_a,

	const video::SColor& color_b,

	bool blend )

{

	if (!dst)
		return false;

	const core::dimension2du img_size = dst->getDimension();

	if ( ( img_size.Width == 0 ) || ( img_size.Height == 0 ) )
		return false;

	const s32 dx = core::abs_<s32>( x1 - x0 );
	const s32 dy = core::abs_<s32>( y1 - y0 );

	if (dx==0 && dy==0)
		return false;

	s32 sx = 1; // sign
	s32 sy = 1; // sign

	if (x0 > x1)
		sx = -1;
	if (y0 > y1)
		sy = -1;

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = x0;
	s32 y = y0;

	s32 numpixels = 0;

	// count pixels
	while (1)
	{
		numpixels++;

		if (x == x1 && y == y1)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}

	}

	// reset vars;
	err = dx-dy;
	e2 = 0;
	x = x0;
	y = y0;

	// values for linear color interpolation
	const f32 A1=(f32)color_a.getAlpha();
	const f32 R1=(f32)color_a.getRed();
	const f32 G1=(f32)color_a.getGreen();
	const f32 B1=(f32)color_a.getBlue();
	const f32 dA=(f32)color_b.getAlpha()-A1;
	const f32 dR=(f32)color_b.getRed()-R1;
	const f32 dG=(f32)color_b.getGreen()-G1;
	const f32 dB=(f32)color_b.getBlue()-B1;

	// actual drawing
	f32 f=0.f;
	s32 k=0;
	u32 cR=0, cG=0, cB=0, cA=0;
	while (1)
	{
		f = (f32)k/(f32)numpixels;
		k++;

		cA=A1;
		cR=R1;
		cG=G1;
		cB=B1;

		// maybe faster under the assumption that colors have most likely same alpha value
		if (dA>0) cA = (u32)core::clamp( core::round32(A1+dA*f), 0, 255);
		if (dR>0) cR = (u32)core::clamp( core::round32(R1+dR*f), 0, 255);
		if (dG>0) cG = (u32)core::clamp( core::round32(G1+dG*f), 0, 255);
		if (dB>0) cB = (u32)core::clamp( core::round32(B1+dB*f), 0, 255);

		drawPixel( dst, x, y, video::SColor( cA, cR, cG, cB), blend );

		if (x == x1 && y == y1)
			break;

		e2 = err << 1;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
	return true;
}

//! draw a line with 2 color(s) to image ( Bresenham, no AA )

bool drawLine(

	video::IImage* dst,

	const core::rectf& pos,

	const video::SColor& color,

	bool blend )

{
	const s32 x0 = core::floor32( pos.UpperLeftCorner.X );
	const s32 y0 = core::floor32( pos.UpperLeftCorner.Y );
	const s32 x1 = core::floor32( pos.LowerRightCorner.X );
	const s32 y1 = core::floor32( pos.LowerRightCorner.Y );

	return drawLine( dst, x0, y0, x1, y1, color, blend);
}

//! draw a line with 2 color(s) to image ( Bresenham, no AA )

bool drawLine(

	video::IImage* dst,

	const core::rectf& pos,

	const video::SColor& color_a,

	const video::SColor& color_b,

	bool blend )

{
	if (!dst)
		return false;

	const core::dimension2du img_size = dst->getDimension();

	if ( ( img_size.Width == 0 ) || ( img_size.Height == 0 ) )
		return false;

	const s32 x0 = core::floor32( pos.UpperLeftCorner.X );
	const s32 y0 = core::floor32( pos.UpperLeftCorner.Y );
	const s32 x1 = core::floor32( pos.LowerRightCorner.X );
	const s32 y1 = core::floor32( pos.LowerRightCorner.Y );

	return drawLine( dst, x0, y0, x1, y1, color_a, color_b, blend );
}

} // end namespace video

} // end namespace irr
