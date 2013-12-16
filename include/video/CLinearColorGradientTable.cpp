// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CLinearColorGradientTable.h"

#ifdef _DEBUG
#include <../source/Irrlicht/os.h>
#endif // _DEBUG

#include <../source/Irrlicht/CImage.h>

namespace irr
{

namespace video
{

CLinearColorGradientTable :: CLinearColorGradientTable( u32 color_count, u32 table_size )
: IColorGradient("", color_count), InvLookUpTableSize(0.0f)
{
	#if _DEBUG
		os::Printer::log( "CLinearColorGradientTable::ctr()", ELL_INFORMATION );
	#endif // _DEBUG
    setTableSize( table_size, true );
}

CLinearColorGradientTable::~CLinearColorGradientTable()
{
	#if _DEBUG
		os::Printer::log( "CLinearColorGradientTable::dtr()", ELL_INFORMATION );
	#endif // _DEBUG
	clear();
}

core::stringc CLinearColorGradientTable :: toString( ) const
{
	const u32 color_count = getColorCount();

	// print number of colors used
	core::stringc s("CLinearColorGradientTable[");
	s += color_count;

	// print name
	if (Name.size()>0)
	{
		s += Name;
		s += ", ";
	}

	// print
	s += "] = {\n";

	// print colors
	for (u32 i=0; i<color_count; i++)
	{
		s += "\t{ ";
		s += video::toString( Colors[i].Color.toSColor() );
		s += ", ";
		s += Colors[i].Position;
		s += " }";

		if (i<color_count)
		{
			s += ",";
		}

		s += "\n";
	}

	// print
	s += "};\n";
	return s;
}

bool CLinearColorGradientTable :: read( io::IXMLReader* pXml )
{
	if (!pXml)
		return false;

	// empty for now

	return true;
}

bool
CLinearColorGradientTable :: write ( io::IXMLWriter* pXml ) const
{
	if (!pXml)
		return false;

	// empty for now

	return true;
}

//
//// swap two colors based on their indices in array
//bool
//CLinearColorGradientTable::swapColor ( u32 i1, u32 i2 )
//{
//	if (i1==i2)
//	{
//		return false;
//	}
//
//	u32 c = Colors.size();
//
//	if (i1>=c || i2>=c)
//	{
//		return false;
//	}
//
//	MyColorStruct img = Colors[i1];
//	Colors[i1] = Colors[i2];
//	Colors[i2] = img;
//	return true;
//}
//
//CLinearColorGradientTable&
//CLinearColorGradientTable::sort( bool bReverse )
//{
//	sortBubble( bReverse );
//	return *this;
//}
//
//// sort array by increasing t
//CLinearColorGradientTable&
//CLinearColorGradientTable::sortQuick( bool bReverse )
//{
//	return *this;
//}
//
//// sort array by increasing t
//CLinearColorGradientTable&
//CLinearColorGradientTable::sortBubble( bool bReverse )
//{
//	#if _DEBUG
//	os::Printer::log( "CLinearColorGradientTable::sortBubble()", ELL_INFORMATION );
//	#endif // _DEBUG
//
//	u32 n = Colors.size();
//	u32 newn;
//	u32 i;
//	do
//	{
//		newn = 1;
//		for (i=0; i<n-1; i++)
//		{
//			if (Colors[i] > Colors[i+1])
//			{
//				swapColor( i, i+1 );
//				newn = i+1;
//			} // ende if
//		} // ende for
//		n = newn;
//	}
//	while (n > 1);
//
//	return *this;
//}
//
//CLinearColorGradientTable&
//CLinearColorGradientTable::randomize ( ITimer* timer )
//{
//	if (!timer)
//		return *this;
//
//	u32 c = Colors.size();
//
//	if (c<2)
//		return *this;
//
//	srand( ((timer->getRealTime()>>2)-1) );
//
//	for (u32 i=0; i<c; i++)
//	{
//		Colors[i].Position = 1.0f/(f32)(1+rand()%((s32)c));
//	}
//	return *this;
//}
//
//// copy
//CLinearColorGradientTable&
//CLinearColorGradientTable::operator= ( const CLinearColorGradientTable& other)
//{
//	return *this;
//}
//
//// test for equality
//bool
//CLinearColorGradientTable::operator== ( const CLinearColorGradientTable& other) const
//{
//	return false;
//}
//
//SColor
//CLinearColorGradientTable::operator() ( f32 t ) const
//{
//	return getColor(t);
//}
//
//const CLinearColorGradientTable::MyColorStruct&
//CLinearColorGradientTable::operator[]	( u32 i ) const
//{
//	return Colors[i];
//}
//
//CLinearColorGradientTable::MyColorStruct&
//CLinearColorGradientTable::operator[]	( u32 i )
//{
//	return Colors[i];
//}
//
//CLinearColorGradientTable&
//CLinearColorGradientTable::operator+= ( const MyColorStruct& entry_to_add )
//{
//
//	return *this;
//}
//
//CLinearColorGradientTable&
//CLinearColorGradientTable::operator-= ( const MyColorStruct& entry_to_del )
//{
//	return *this;
//}
//
//CLinearColorGradientTable::MyColorStruct&
//CLinearColorGradientTable::MyColorStruct::operator= ( const MyColorStruct& other )
//{
//	Color = other.Color;
//	Position = other.Position;
//	return *this;
//}
//
//bool
//CLinearColorGradientTable::MyColorStruct::operator< ( const MyColorStruct& other ) const
//{
//	if (Position < other.Position)
//		return true;
//	else
//		return false;
//}
//
//bool
//CLinearColorGradientTable::MyColorStruct::operator> ( const MyColorStruct& other ) const
//{
//	if (Position > other.Position)
//		return true;
//	else
//		return false;
//}
//
//bool
//CLinearColorGradientTable::MyColorStruct::operator==	( const MyColorStruct& other ) const
//{
//	if ( core::equals( Position, other.Position ) )
//		return true;
//	else
//		return false;
//}
//
//bool
//CLinearColorGradientTable::MyColorStruct::operator!=	( const MyColorStruct& other ) const
//{
//	return (!( (*this)==other ));
//}
//
//bool
//CLinearColorGradientTable::MyColorStruct::operator<=	( const MyColorStruct& other ) const
//{
//	return ( ((*this) == other) || ((*this) < other) );
//}
//bool
//CLinearColorGradientTable::MyColorStruct::operator>=	( const MyColorStruct& other ) const
//{
//	return ( ((*this) == other) || ((*this) > other) );
//}

} // end namespace video

} // end namespace irr
