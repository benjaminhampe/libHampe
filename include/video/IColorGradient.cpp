// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IColorGradient.h"

namespace irr
{

namespace video
{

/// /// /// /// /// /// /// /// /// /// /// ///

/// format SColor to string

/// /// /// /// /// /// /// /// /// /// /// ///


core::stringc toString( const SColor& color )
{
	core::stringc s("SColor(");
	s += color.getAlpha();
	s += ",";
	s += color.getRed();
	s += ",";
	s += color.getGreen();
	s += ",";
	s += color.getBlue();
	s += ")";
	return s;
}

core::stringc toString( const SColorf& color )
{
	core::stringc s("SColorf(");
	s += color.getAlpha();
	s += ",";
	s += color.getRed();
	s += ",";
	s += color.getGreen();
	s += ",";
	s += color.getBlue();
	s += ")";
	return s;
}

} // end namespace video

} // end namespace irr
