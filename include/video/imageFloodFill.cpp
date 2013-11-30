// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "imageFloodFill.h"

namespace irr
{

namespace video
{

////! MS Paint Style
//bool floodFill( IrrImage* dst, s32 x, s32 y, const IrrColor& fillcolor, const IrrColor& old)
//{
//	if (!dst)
//		return false;
//
//	IrrColor oldcolor(old);
//	if (old.color==0)
//		oldcolor=getPixelEx(dst,x,y);
//
//	if (getPixelEx(dst,x,y)==fillcolor)
//       return false;
//
//	s32 lg, rg, px=x;
//	while(x>=0 && getPixelEx(dst,x,y)==oldcolor)
//	{
//		setPixelEx(dst,x,y,fillcolor);
//		x--;
//	}
//
//	lg=x+1;
//	x=px+1;
//
//	const IrrDim2u& Size = dst->getDimension();
//	while(x<(s32)Size.Width && getPixelEx(dst,x,y)==oldcolor)
//	{
//		setPixelEx(dst,x,y,fillcolor);
//		x++;
//	}
//	rg=x-1;
//
//	for(x=rg; x>=lg; x--)
//	{
//		//! alle Zeilen oberhalb
//		if((getPixelEx(dst,x,y-1)==oldcolor) && (y-1>0))
//			floodFill( dst,x, y-1, fillcolor, oldcolor);
//		//! alle Zeilen unterhalb
//		if((getPixelEx(dst,x,y+1)==oldcolor) && (y<(s32)Size.Height-1))
//			floodFill( dst,x,y+1,fillcolor,oldcolor);
//	}
//
//	return true;
//}

} // end namespace video

} // end namespace irr
