// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_DRAW_SOFTWARE_IMAGE_TO_SOFTWARE_IMAGE_H__
#define __IRR_EXT_DRAW_SOFTWARE_IMAGE_TO_SOFTWARE_IMAGE_H__

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

		void drawImage(

			IImage* src,

			IImage* dst,

			const core::position2di& pos,

			const core::dimension2du& size,

			bool bTransparent = false,

			bool blend = false);


	} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_BRESENHAM_LINE_GRID_TO_SOFTWARE_IMAGE_H__
