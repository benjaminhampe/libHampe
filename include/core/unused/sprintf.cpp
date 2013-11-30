// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "sprintf.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdarg>	// for static sprintf and internal printf
#include <cmath>
#include <ctime>
#include <wchar.h>

#ifdef _DEBUG
	#include <../source/Irrlicht/os.h>
#endif // _DEBUG


namespace irr
{
namespace core
{

stringc sprintf(const char* formatString, ...)
{
	va_list p;
	va_start(p,formatString);
	char tmp[1024];
#if defined(_MSC_VER)
	vsnprintf(&(tmp[0]), 1024, formatString, p);
#elif defined(__GNUC__)
	vsnprintf(&tmp[0], 1024, formatString, p);
#else

#endif
	va_end(p);
	return stringc(tmp);
}

/// function

stringw sprintf(const wchar_t* formatString, ...)
{
	va_list p;
	va_start(p,formatString);
	wchar_t tmp[1024];
#if defined(_MSC_VER)
	_vsnwprintf(&(tmp[0]), 1024, formatString, p);
#elif defined(__GNUC__)
#if defined(_IRR_WINDOWS_)
	vsnwprintf(&tmp[0], 1024, formatString, p);
#else
	vswprintf(&tmp[0], 1024, formatString, p);
#endif
#else

#endif
	va_end(p);
	return stringw(tmp);
}


stringc formatNumber(u32 value, E_NUMBER_FORMAT srcType)
{
	stringc txt("");
	u32 c = 0;

	while (value>=1024)
	{
		value>>=10;
		c++;
	};

	txt+=(s32)value;
	txt+=" ";

	u32 dstType = (u32)srcType + c;

	if (dstType > (u32)ENF_COUNT)
		dstType = (u32)ENF_COUNT;

	switch ((E_NUMBER_FORMAT)dstType)
	{
		case ENF_BYTES: txt+="Bytes"; break;
		case ENF_KILO: txt+="KiB"; break;
		case ENF_MEGA: txt+="MiB"; break;
		case ENF_GIGA: txt+="GiB"; break;
		case ENF_TERA: txt+="TiB"; break;
		case ENF_PETA: txt+="PiB"; break;
		case ENF_EXA: txt+="EiB"; break;
		case ENF_COUNT: txt+="2^"; txt+=(s32)((u32)srcType+c); break;
		default: break;
	}

	txt+=" = 2^"; txt+=(s32)((u32)srcType+c);

	return txt;
}

// format Time
stringc formatValue( f32 value, u32 decimals )
{
	stringc s;

	s32 stellen = 1;

	if (value>0)
		stellen = 1+(s32)std::log10( value );

	for ( s32 i=0; i<(s32)decimals-stellen; i++ )
	{
		s+="0";
	}

	s+=value;
	return s;
}

stringc toString_ESCENE_NODE_TYPE( scene::ESCENE_NODE_TYPE type )
{
	stringc txt = "";
	switch (type)
	{
		case scene::ESNT_SCENE_MANAGER: txt = "ESNT_SCENE_MANAGER"; break;
		case scene::ESNT_CUBE: txt = "ESNT_CUBE"; break;
		case scene::ESNT_SPHERE: txt = "ESNT_SPHERE"; break;
		case scene::ESNT_TEXT: txt = "ESNT_TEXT"; break;
		case scene::ESNT_WATER_SURFACE: txt = "ESNT_WATER_SURFACE"; break;
		case scene::ESNT_TERRAIN: txt = "ESNT_TERRAIN"; break;
		case scene::ESNT_SKY_BOX: txt = "ESNT_SKY_BOX"; break;
		case scene::ESNT_SKY_DOME: txt = "ESNT_SKY_DOME"; break;
		case scene::ESNT_SHADOW_VOLUME: txt = "ESNT_SHADOW_VOLUME"; break;
		case scene::ESNT_OCTREE: txt = "ESNT_OCTREE"; break;
		case scene::ESNT_MESH: txt = "ESNT_MESH"; break;
		case scene::ESNT_LIGHT: txt = "ESNT_LIGHT"; break;
		case scene::ESNT_EMPTY: txt = "ESNT_EMPTY"; break;
		case scene::ESNT_DUMMY_TRANSFORMATION: txt = "ESNT_DUMMY_TRANSFORMATION"; break;
		case scene::ESNT_CAMERA: txt = "ESNT_CAMERA"; break;
		case scene::ESNT_BILLBOARD: txt = "ESNT_BILLBOARD"; break;
		case scene::ESNT_ANIMATED_MESH: txt = "ESNT_ANIMATED_MESH"; break;
		case scene::ESNT_PARTICLE_SYSTEM: txt = "ESNT_PARTICLE_SYSTEM"; break;
		case scene::ESNT_Q3SHADER_SCENE_NODE: txt = "ESNT_Q3SHADER_SCENE_NODE"; break;
		case scene::ESNT_MD3_SCENE_NODE: txt = "ESNT_MD3_SCENE_NODE"; break;
		case scene::ESNT_VOLUME_LIGHT: txt = "ESNT_VOLUME_LIGHT"; break;
		case scene::ESNT_CAMERA_MAYA: txt = "ESNT_CAMERA_MAYA"; break;
		case scene::ESNT_CAMERA_FPS: txt = "ESNT_CAMERA_FPS"; break;
		case scene::ESNT_UNKNOWN: txt = "ESNT_UNKNOWN"; break;
		case scene::ESNT_ANY: txt = "ESNT_ANY"; break;
		default: break;
	}
	return txt;
}

} // end namspace core

} // end namspace irr



