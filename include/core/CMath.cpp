#include "CMath.h"

#include <irrlicht.h>

#include <ctime>

namespace irr
{
namespace core
{
void Math::Randomize()
{
	srand((u32)time(0));
}

u32 Math::Random(u32 seed)
{
	return rand()%seed;
}

/** PRINT text to Irrlicht or STL */
//	bool PRINT( IrrlichtDevice* device, const core::stringc& txt = "", ELOG_LEVEL level = ELL_INFORMATION);

s32 Math::sign( f32 value )
{
	s32 m_sign = 0;
	if (value < 0.0f)
	{
		m_sign = 1;
	}
	return m_sign;
}

s32 Math::sign( f64 value )
{
	s32 m_sign = 0;
	if (value < 0.0)
	{
		m_sign = 1;
	}
	return m_sign;
}

// Rundet gesammten Nachkommateil,
// "dirty version" durch einfachen Cast auf __int32
f32 Math::Round(f32 zahl)
{
	return (f32)(s32)((zahl<0.0f)?zahl-0.5f:zahl+0.5f);
}

f64 Math::Round(f64 zahl)
{
	return (f64)(s32)((zahl<0.0)?zahl-0.5:zahl+0.5);
}

// Rundet auf Anzahl Stellen nach dem Komma
//-> Laufzeitoptimiert, 2.Parameter nur von 0 bis 8!!!, sonst Absturz!!!
f32 Math::Round(f32 zahl, s32 stellen)
{
	f32 v[] = { 1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };
	return (f32)core::floor32(zahl * v[stellen] + 0.5) / v[stellen];
}

// Rundet auf Anzahl Stellen nach dem Komma
//-> Laufzeitoptimiert, 2.Parameter nur von 0 bis 8!!!, sonst Absturz!!!
f64 Math::Round(f64 zahl, s32 stellen)
{
	f64 v[] = { 1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };
	return (f64)floor(zahl * v[stellen] + 0.5) / v[stellen];
}


s32 Math::s32_pow(s32 x, s32 p)
{
	s32 result = 1;
	for (s32 j = 1; j < p; j++)
		result *= x;
	return result;
}

//#ifdef USE_32BIT_FLOATS
//	void Math::Split( f32 r, f32* i, f32* f)
//	{
//		*f = fabs( fmodf( r,*i ) );
//	}
//#else
//	void Math::Split( f64 r, f64* i, f64* f)
//	{
//		*f = core::Math::abs<f64>( modf( r,i ) );
//	}
//#endif

u32 Math::_nextPow2_loop( u32 n )
{
	u32 x = 1;
	while(x < n)
	{
		x <<= 1;
	}
	return x;
}

u32 Math::_next_power_of_2( u32 value )
{
	u32 pos = 1;
	while( (u32)(1<<pos) < value )
	{
		pos++;
	}
	return (1<<(pos+1));
}

//u32 Math::_nextPow2( u32 x )
//{
//    --x;
//    x |= x >> 1;
//    x |= x >> 2;
//    x |= x >> 4;
//    x |= x >> 8;
//    x |= x >> 16;
//    return ++x;
//}
//
//u32 Math::_nextPow2_IEEE( u32 n )
//{
//	const u32 MantissaMask = (1<<23) - 1;
//
//	(*(f32*)&n) = (f32) n;
//	n = n + MantissaMask & ~MantissaMask;
//	n = (u32) (*(f32*)&n);
//
//	return n;
//}


//core::vector2d<s32> Math::transformPoint2di(
//	const core::vector2d<f32>& srcPoint, const core::rect<f32>& srcRect, const core::rect<s32>& dstRect)
//{
//	core::vector2d<s32> result;
//	result.X = (s32)(((f64)dstRect.getWidth() * ((f64)srcPoint.X - (f64)srcRect.UpperLeftCorner.X) / (f64)srcRect.getWidth())+(f64)dstRect.UpperLeftCorner.X);
//	result.Y = (s32)(((f64)dstRect.getHeight() * ((f64)srcPoint.Y - (f64)srcRect.UpperLeftCorner.Y) / (f64)srcRect.getHeight())+(f64)dstRect.UpperLeftCorner.Y);
//	return result;
//}
//
//core::vector2d<f32> Math::transformPoint2df(
//	const core::vector2d<f32>& srcPoint, const core::rect<f32>& srcRect, const core::rect<f32>& dstRect)
//{
//	core::vector2d<f32> result;
//	result.X = (f32)(((f64)dstRect.getWidth() * ((f64)srcPoint.X - (f64)srcRect.UpperLeftCorner.X) / (f64)srcRect.getWidth())+(f64)dstRect.UpperLeftCorner.X);
//	result.Y = (f32)(((f64)dstRect.getHeight() * ((f64)srcPoint.Y - (f64)srcRect.UpperLeftCorner.Y) / (f64)srcRect.getHeight())+(f64)dstRect.UpperLeftCorner.Y);
//	return result;
//}

} // end namespace core

} // end namespace irr

