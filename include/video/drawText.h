// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_DRAW_TEXT_TO_SOFTWARE_IMAGE_H__
#define __IRR_EXT_DRAW_TEXT_TO_SOFTWARE_IMAGE_H__

#include <irrlicht.h>
#include <../source/Irrlicht/os.h>
#include <../source/Irrlicht/CColorConverter.h>
#include <../source/Irrlicht/CImage.h>

// force _IRR_COMPILE_WITH_FREETYPE2_
#ifndef _IRR_COMPILE_WITH_FREETYPE2_
	#define _IRR_COMPILE_WITH_FREETYPE2_
#endif // _IRR_COMPILE_WITH_FREETYPE2_

// use _IRR_COMPILE_WITH_FREETYPE2_
#ifdef _IRR_COMPILE_WITH_FREETYPE2_
	#include <ft2build.h>
	#include FT_FREETYPE_H
	#include FT_GLYPH_H
	#include FT_BITMAP_H
#endif // _IRR_COMPILE_WITH_FREETYPE2_

/// maybe you need to include the following lines once to your main cpp file
//#include <../source/Irrlicht/os.cpp>
//#include <../source/Irrlicht/CColorConverter.cpp>
//#include <../source/Irrlicht/CImage.cpp>

namespace irr
{
namespace video
{

	//! irrlicht API conform

	//! uses Environment->getVideoDriver() to create a renderTarget

	//! + filtering when possible )

	//! uses IGUIEnvironment and its IVideoDriver

	//! create image from text ( always centered ) with minimal size for text

	//! can be used in combination with IGUITTFont to load truetype-fonts of any size

	IImage* createImageFromText(

		gui::IGUIEnvironment* env,
		gui::IGUIFont* font,
		const core::stringw& txt,
		const SColor& txt_color = 0xffffffff,
		const SColor& background_color = SColor(0,0,0,0) );

	//! irrlicht API conform

	//! draw text to image ( must already exist )

	//! create temporary image with text and draw it into given image

	//! with 2d-coords and 2d-alignment ( -1=left/top, 0=center/middle, 1=right/bottom )

	//! can be used in combination with IGUITTFont to load truetype-fonts of any size

	//! if (!dst) return false; -> no valid image surface to draw to

	//! if (!env) return false; -> no irrlicht-factories available

	//! if (!font) fallback to Environment->getSkin()->getFont( EGDF_DEFAULT );

	//! if still (!font) fallback to Environment->getBuildInFont();

	//! if still (!font) return false;

	bool drawText(

		IImage* dst,
		gui::IGUIEnvironment* env,
		gui::IGUIFont* font,
		const core::stringw& txt,
		s32 x,
		s32 y,
		s32 hAlign = -1,
		s32 vAlign = -1,
		const SColor& txt_color = 0xffffffff,
		const SColor& background_color = SColor(0,0,0,0),
		core::recti* clipRect = 0,
		bool blend = true);

#ifdef _IRR_COMPILE_WITH_FREETYPE2_

	//! hold some data for each font

	struct SFont
	{
		core::stringc FileName;
		s32 Size;
		bool IsMonochrom;
		bool IsTransparent;
	};


	//! draw Glyph to image

	void drawBitmapFT(

		IImage* dst,
		FT_Bitmap* bitmap,
		s32 x,
		s32 y,
		const video::SColor& txt_color = 0xffffffff );

	//! create image from text ( always centered ) with minimal size for text

	//! using freetype2 library and no irrlicht-device

	IImage* createImageFromText(

		SFont* font,
		const core::stringw& txt,
		const SColor& txt_color,
		const SColor& background_color );

	//! draw text to existing software image

	//! using freetype2 library and no irrlicht-device

	//! text is aligned at borders ( -1=left/top, 0=center/middle, 1=right/bottom )

	bool drawText(

		SFont* font,
		IImage* dst,
		const core::stringw& txt,
		s32 x,
		s32 y,
		s32 hAlign = -1,
		s32 vAlign = -1,
		const SColor& txt_color = 0xffffffff,
		const SColor& background_color = SColor(0,0,0,0),
		core::recti* clipRect = 0,
		bool blend = true );

#endif // _IRR_COMPILE_WITH_FREETYPE2_

} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_TEXT_TO_SOFTWARE_IMAGE_H__
