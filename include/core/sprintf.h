// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_STRING_UTILS_H__
#define __IRR_EXTENSION_STRING_UTILS_H__

#include <irrlicht.h>

namespace irr
{
namespace core
{

	enum E_NUMBER_FORMAT
	{
		ENF_BYTES=0,
		ENF_KILO=1,
		ENF_MEGA=2,
		ENF_GIGA=3,
		ENF_TERA=4,
		ENF_PETA=5,
		ENF_EXA=6,
		ENF_COUNT=7
	};

	// format value
	stringc sprintf( const char* formatString, ...);

	// format value
	stringw sprintf( const wchar_t* formatString, ...);

	// format value
	stringc formatValue( f32 value, u32 decimals = 10 );

	stringc formatNumber(u32 value, E_NUMBER_FORMAT srcType = ENF_KILO);

	/// toString
	stringc toString_ESCENE_NODE_TYPE( scene::ESCENE_NODE_TYPE type );

	/// convert rect<T> to stringc
	template <class T>
	stringc toString( const rect<T>& r, const stringc& name = "" )
	{
		stringc txt = name;
		if (name.size()==0)
		{
			txt += "rect<T>";
		}

		txt += " { ";
		txt += r.UpperLeftCorner.X;
		txt += "; ";
		txt += r.UpperLeftCorner.Y;
		txt += "; ";
		txt += r.LowerRightCorner.X;
		txt += "; ";
		txt += r.LowerRightCorner.Y;
		txt += " }";
		return txt;
	}

	/// convert vector3d<T> to stringc
	template <class T>
	stringc toString( const vector3d<T>& r, const stringc& name = "" )
	{
		stringc txt = name;
		if (name.size()==0)
		{
			txt += "vector3d<T>";
		}
		txt += " { ";
		txt += r.UpperLeftCorner.X;
		txt += "; ";
		txt += r.UpperLeftCorner.Y;
		txt += "; ";
		txt += r.LowerRightCorner.X;
		txt += "; ";
		txt += r.LowerRightCorner.Y; txt += " }";
		return txt;
	}

	//
	//template <class T> T PROMT( 	// create GUI Window with button and editbox or spinbox for one value s32 u32 f32 f64)
	//		gui::IGUIEnvironment* env, const stringw& title, const stringw& message,
	//		T fMin = (T)0, T fMax = (T)100, T fNow = (T)50,	T fStep = (T)1,
	//		stringc s_format = "%8.4f",
	//		recti& r_win = recti( position2di(-1,-1),dimension2du(160,120)) )
	//{
	//	if (!env)
	//		return 0.0;
	//
	//	gui::IGUIWindow* win = env->addWindow( r_win, false, title.c_str(), env->getRootGUIElement(),  -1 );
	//	recti r_client = win->getClientRect();
	//	const s32& x = r_client.UpperLeftCorner.X;
	//	const s32& y = r_client.UpperLeftCorner.Y;
	//	const s32& w = r_client.getWidth();
	//	const s32& h = r_client.getHeight();
	//	recti r_edt( x,y,x+w-1,y+h/2-1);
	//	recti r_btn( x,y+h/2,x+w-1,y+h-1);
	//	gui::IGUISpinBox* edt = env->addSpinBox( title.c_str(), r_edt, true, win, -1 );
	//	gui::IGUIButton* btn = env->addButton( r_client, win, -1, message.c_str(), message.c_str());
	//	edt->setRange( (f32)fMin, (f32)fMax);
	//	edt->setDecimalPlaces( 2 );
	//	edt->setValue( (f32)fNow );
	//	edt->setStepSize( (f32)fStep );
	//
	//	btn->setOverrideFont( env->getFont("../media/fonts/Lucida_Console_Regular_8_AA_Alpha.xml") );
	//
	//	T value = (T)edt->getValue();
	//	return value;
	//}

} // end namespace core

} // end namespace irr

#endif

