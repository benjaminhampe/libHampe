// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_INTERFACE_FUNCTION_OF_TIME_H__
#define __IRR_INTERFACE_FUNCTION_OF_TIME_H__

namespace irr
{

	/// this class is a functor

	/// because it overloads the "function call" operator.

	/// it has no states, only interface

	template <class T>
	class IFunctionOfTime
	{
		public:
			/// @brief IFunctionOfTime interface
			virtual T operator() ( const T& seconds ) const = 0;

	};

} // end namespace irr

#endif // __IRR_INTERFACE_FUNCTION_OF_TIME_H__
