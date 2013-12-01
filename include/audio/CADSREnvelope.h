// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_ADSR_ENVELOPE_H__
#define __IRR_C_ADSR_ENVELOPE_H__

#include <irrlicht.h>

#include "../core/IFunction.h"

namespace irr
{
	/// @brief class that simulates a digital saw/ramp oscillator
	template <class T>
	class CADSREnvelope : public IFunction<T>
	{
		public:
			/// @brief class constructor
			explicit CADSREnvelope(
				const T& a = (T)20 /* in milliseconds */,
				const T& d = (T)100 /* in milliseconds */,
				const T& s = (T)0.7 /* in range [0,1] of amplitude_range ( max - min ) */,
				const T& r = (T)1000 /* in milliseconds */,
				const T& amplitude_max = (T)1,
				const T& amplitude_min = (T)0 )
			{
				setAttack( a );
				setDecay( d );
				setSustain( s );
				setRelease( r );
				setAmplitudeRange( amplitude_max, amplitude_min );
			}

			/// @brief class destructor
			virtual ~CADSREnvelope()
			{

			}

			/// @brief setter
			virtual void setAttack( const T& a )
			{
				A = a;
			}

			/// @brief getter
			virtual T getAttack( ) const
			{
				return A;
			}

			/// @brief setter
			virtual void setDecay( const T& d )
			{
				D = d;
			}

			/// @brief getter
			virtual T getDecay( ) const
			{
				return D;
			}

			/// @brief setter
			virtual void setSustain( const T& s )
			{
				S = s;
			}

			/// @brief getter
			virtual T getSustain( ) const
			{
				return S;
			}

			/// @brief setter
			virtual void setRelease( const T& r )
			{
				R = r;
			}

			/// @brief getter
			virtual T getRelease( ) const
			{
				return R;
			}

			/// @brief setter
			virtual void setAmplitudeRange( const T& amplitude_max, const T& amplitude_min )
			{
				//Amplitude = core::clamp<T>( amplitude, (T)0, (T)32767 );
				Amplitude_Min = amplitude_min;
				Amplitude_Max = amplitude_max;
			}

			/// @brief setter
			virtual void setAmplitudeMin( const T& amplitude_min )
			{
				Amplitude_Min = amplitude_min;
			}

			/// @brief setter
			virtual void setAmplitudeMax( const T& amplitude_max )
			{
				Amplitude_Max = amplitude_max;
			}

			/// @brief getter
			virtual T getAmplitudeMin( ) const
			{
				return Amplitude_Min;
			}

			/// @brief getter
			virtual T getAmplitudeMax( ) const
			{
				return Amplitude_Max;
			}

			///@brief implementation of interface IFunctionOfTime
			virtual T operator() ( const T& seconds ) const
			{
				const T t_modded = fmod( seconds - Period*Phase, Period );

				// nothing so far

				return T(1);
			}

		private:
			T A;
			T D;
			T S;
			T R;
			T Amplitude_Min;
			T Amplitude_Max;
	};

} // end namespace irr

#endif // __IRR_C_ADSR_ENVELOPE_H__
