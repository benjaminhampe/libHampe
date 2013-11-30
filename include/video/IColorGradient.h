// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_INTERFACE_I_COLOR_GRADIENT_H__
#define __IRR_EXTENSION_INTERFACE_I_COLOR_GRADIENT_H__

#include <irrlicht.h>

namespace irr
{
namespace video
{

	/// @function convert SColor to formatted string
	core::stringc toString( const SColor& color );

	/// @function convert SColorf to formatted string
	core::stringc toString( const SColorf& color );



	/// class IColorGradient ( pure virtual/abstract methods -> interface definition )
	class IColorGradient : public IReferenceCounted
	{
	public:
		/// getter ( const )
		virtual core::stringc getName( ) const = 0;

		/// getter ( const )
		virtual core::stringc toString( ) const = 0;

		virtual bool isTransparent( ) const = 0;

		virtual E_MATERIAL_TYPE getMaterialType( ) const = 0;

		virtual ECOLOR_FORMAT getColorFormat( ) const = 0;

		virtual u32 getColorCount() const = 0;

		/// return interpolated color t in range [0,1]
		virtual SColor getColor( f32 t ) const = 0;

		/// return interpolated color t in range [0,1]
		virtual SColorf getColorf( f32 t ) const = 0;

		/// create image
		virtual IImage* createImage( u32 w, u32 h, bool bVertical = false ) const = 0;

		/// create texture
		virtual ITexture* createTexture( video::IVideoDriver* driver, u32 w, u32 h, bool bVertical = false, const io::path& name = "" ) const = 0;

		/// setter
		virtual bool setName( const core::stringc& name ) = 0;

		virtual bool clear() = 0;

		virtual bool addColor( const SColor& stopColor, f32 t = 0.5f ) = 0;

		virtual bool addColor( const SColorf& stopColor, f32 t = 0.5f ) = 0;

		virtual bool setColor( u32 index, const SColor& stopColor, f32 t = 0.5f ) = 0;

		virtual bool setColor( u32 index, const SColorf& stopColor, f32 t = 0.5f ) = 0;

	};


} // end namespace video

} // end namespace irr

#endif // ICOLORGRADIENT_H
