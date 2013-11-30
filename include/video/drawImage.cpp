// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "drawImage.h"

#include "drawPixel.h"

namespace irr
{

namespace video
{

void drawImage(

	IImage* src,

	IImage* dst,

	const core::position2di& pos,

	const core::dimension2du& size,

	bool bTransparent,

	bool blend)

{

	if (!src)
		return;

	const u32 x_max = irr::core::min_<u32>( dst->getDimension().Width, src->getDimension().Width );
	const u32 y_max = irr::core::min_<u32>( dst->getDimension().Height, src->getDimension().Height );

	for (u32 y=0; y<y_max; y++)
	{
		for (u32 x=0; x<x_max; x++)
		{
			const SColor& color = src->getPixel(x,y);

			drawPixel( dst, (s32)x+pos.X, (s32)y+pos.Y, color, blend);
		}
	}
}


} // end namespace video

} // end namespace irr
