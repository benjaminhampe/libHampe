// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_RECTANGLE_OSCILLATOR_H__
#define __IRR_C_RECTANGLE_OSCILLATOR_H__

#include <irrlicht.h>

#include "../core/IFunction.h"

namespace irr
{
	///@brief class that simulates a digital pulse/rectangle/square oscillator
	template <class T>
	class CRectangleOscillator : public IFunction<T>
	{
	public:
		///@brief class contructor
		explicit
		CRectangleOscillator(
			const T& freq = (T)440,
			const T& phase = (T)0,
			const T& amplitude_max = (T)1,
			const T& amplitude_min = (T)0 )
		{
			setFrequency( freq );
			setPhase( phase );
			setAmplitudeRange( amplitude_max, amplitude_min );
		}

		///@brief class destructor
		virtual ~CRectangleOscillator()
		{

		}

		///@brief setter
		virtual void setFrequency( const T& frequency )
		{
			Frequency = core::clamp<T>( frequency, (T)1, (T)22050 );
		}

		///@brief setter
		virtual void setPhase( const T& phase )
		{
			Phase = core::clamp<T>( phase, (T)0, (T)(2.0*core::PI64) );
		}

		///@brief setter
		virtual void setAmplitude( const T& amplitude )
		{
			Amplitude = core::clamp<T>( amplitude, (T)0, (T)32767 );
		}

		///@brief getter
		virtual T getFrequency( ) const
		{
			return Frequency;
		}

		///@brief getter
		virtual T getPhase( ) const
		{
			return Phase;
		}

		///@brief getter
		virtual T getAmplitude( ) const
		{
			return Amplitude;
		}

		///@brief implementation of interface IFunctionOfTime
		virtual T operator() ( const T& seconds ) const
		{
			return Amplitude*sin( 2.0*core::PI*seconds*Frequency + Phase );
		}

	private:

		T Frequency;
		T Phase;
		T Amplitude;
	};

} // end namespace irr

#endif // __IRR_C_RECTANGLE_OSCILLATOR_H__

