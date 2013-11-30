// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef ISTRINGABLE_H
#define ISTRINGABLE_H

namespace irr{
namespace core{

///@class IStringable
///@brief Interface that offers only one method - toString()

class IStringable
{
	public:
		///@brief toString()
		virtual core::stringc toString() const = 0;
};

} // end namespace core
} // end namespace irr

#endif // ISTRINGABLE_H
