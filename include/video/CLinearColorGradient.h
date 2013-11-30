// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_C_LIENAR_COLOR_GRADIENT_H__
#define __IRR_EXTENSION_C_LIENAR_COLOR_GRADIENT_H__

#include <irrlicht.h>

#include "IColorGradient.h"

namespace irr
{
	namespace video
	{
		/// @class CLinearColorGradient

		class CLinearColorGradient : public IColorGradient
		{
		private:

			struct MyColorStruct
			{
				SColorf Color;
				f32 Position;			// in range 0..1

				/// ADDED: 02.04.2013

				// default constructor
				MyColorStruct( ) : Color(SColorf(0,0,0,0)), Position(0) { }
				// value constructor
				MyColorStruct( const SColor& color, f32 t ) : Color(SColorf(color)), Position(t) { }
				// value constructor
				MyColorStruct( const SColorf& color, f32 t ) : Color(color), Position(t) { }
				// copy constructor
				MyColorStruct( const MyColorStruct& other) : Color(other.Color), Position(other.Position) { }
				// copy operator
				MyColorStruct&	operator= ( const MyColorStruct& other );

				// lower than operator
				bool operator<	( const MyColorStruct& other ) const;
				// greater than operator
				bool operator>	( const MyColorStruct& other ) const;
				// equality operator
				bool operator==	( const MyColorStruct& other ) const;
				// inequality operator
				bool operator!=	( const MyColorStruct& other ) const;
				// lower or equal than operator
				bool operator<=	( const MyColorStruct& other ) const;
				// greater or equal than operator
				bool operator>=	( const MyColorStruct& other ) const;

			};

			core::stringc Name;
			core::array<MyColorStruct> Colors;

		public:

			CLinearColorGradient( u32 color_count = 2 ); // const SColor& startColor = SColor(0,0,0,0), const SColor& endColor = SColor(255,255,255,255) );

			virtual ~CLinearColorGradient();

			/// interface IColorGradient

			virtual core::stringc getName( ) const;

			virtual bool setName( const core::stringc& name );

			virtual SColor getColor( f32 t ) const;

			virtual SColorf getColorf( f32 t ) const;

			virtual u32 getColorCount() const;

			virtual bool isTransparent( ) const;

			virtual E_MATERIAL_TYPE getMaterialType( ) const;

			virtual ECOLOR_FORMAT getColorFormat( ) const;

			virtual core::stringc toString( ) const;

			virtual bool clear();

			virtual bool addColor( const SColor& stopColor, f32 t = 0.5f );

			virtual bool addColor( const SColorf& stopColor, f32 t = 0.5f );

			virtual bool setColor( u32 index, const SColor& stopColor, f32 t = 0.5f );

			virtual bool setColor( u32 index, const SColorf& stopColor, f32 t = 0.5f );

			virtual IImage* createImage( u32 w, u32 h, bool bVertical = false ) const;

			virtual ITexture* createTexture( video::IVideoDriver* driver, u32 w, u32 h, bool bVertical = false, const io::path& name = "" ) const;



			/// ADDED: 02.04.2013
			// swap two colors based on their indices in array
			virtual bool 					swapColor 	( u32 i1, u32 i2 );
			// sort array by increasing t
			virtual CLinearColorGradient& 	sort 		( bool bReverse = false );

			// sort array by increasing t
			virtual CLinearColorGradient& 	sortQuick 	( bool bReverse = false );
			// sort array by increasing t
			virtual CLinearColorGradient& 	sortBubble	( bool bReverse = false );
			// sort array randomly
			virtual CLinearColorGradient& 	randomize 	( ITimer* timer );
			// read from opened xml file
			virtual bool 					read		( io::IXMLReader* pReader );
			// write to opened xml file
			virtual bool 					write		( io::IXMLWriter* pWriter ) const;
			// copy operator
			virtual CLinearColorGradient& 	operator= 	( const CLinearColorGradient& other);
			// equality operator
			virtual bool 					operator==	( const CLinearColorGradient& other) const;
			// get SColor at t in range [0..1]
			virtual video::SColor			operator()	( f32 t ) const;
			// read-only access to array-elements
			virtual const MyColorStruct&	operator[]	( u32 i ) const;
			// write access to array-elements
			virtual MyColorStruct& 			operator[]	( u32 i );
			// add MyColorStruct to array
			virtual CLinearColorGradient& 	operator+= 	( const MyColorStruct& entry_to_add );
			// del MyColorStruct from array
			virtual CLinearColorGradient& 	operator-= 	( const MyColorStruct& entry_to_del );
		};

		class CRadialColorGradient : public IReferenceCounted
		{
		public:

			CRadialColorGradient(  );

			virtual ~CRadialColorGradient();

		private:
		};


	} // end namespace video

} // end namespace irr


#endif // IRRCOLORGRADIENTS_H
