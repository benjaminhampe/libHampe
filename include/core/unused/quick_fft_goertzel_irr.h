// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_FFT_GORTZEL_ALGORITHM_H__
#define __IRR_EXT_FFT_GORTZEL_ALGORITHM_H__

#include <irrlicht.h>
#include <cmath>

#ifdef _DEBUG
	#include <../source/Irrlicht/os.h>
#endif // _DEBUG

namespace irr
{
    //Nterms defined here
    //Kterm selected here
    //omega = 2 * PI * Kterm / Nterms;
    //wr = cos(omega);
    //wi = sin(omega);
    //coeff = 2 * wr;
    //sprev = 0;
    //sprev2 = 0;
    //for each index k in range 0 to Nterms-1
    //{
    //    s = x[k] + coeff * sprev - sprev2;
    //    sprev2 = sprev;
    //    sprev = s;
    //    end
    //}
    //
    //return power = sprev2*sprev2 + sprev*sprev - coeff*sprev*sprev2;
    // Read more: http://www.answers.com/topic/goertzel-algorithm#ixzz2hASQitat

    /// fast fft for only one frequency at sample_rate, if 0 then sample_rate = data.size()
    template <class T>
    f64 goertzel( const core::array<T>& data, u32 sample_rate, f64 search_freq = 440.0 ) // A4
    {
        const u32 i_max = data.size();
        const f64 f_max = (f64)i_max;

        if (sample_rate==0)
            sample_rate = i_max;

        const f64 k = 0.5 + (f_max*(f64)search_freq) / (f64)sample_rate;
        const f64 w = (core::PI64 * 2.0 * k) / f_max;
        const f64 s = sin( w );
        const f64 c = cos( w );
        const f64 coeff = 2.0 * c;

        f64 q0(0),q1(0),q2(0);

        for( u32 i=0; i<i_max; i++)
        {
            q0 = coeff * q1 - q2 + (f64)data[i];
            q2 = q1;
            q1 = q0;
        }

        const f64 re = (q1 - q2 * c);
        const f64 im = (q2 * s);
        const f64 result=core::squareroot( re*re + im*im );

        //#ifdef _DEBUG
        printf("Goertzel-Algorithm |z| = gfft(data,sample_count=%d,sample_rate=%d,freq=%lf) = %lf\n", i_max, sample_rate, search_freq, result );
        //#endif // _DEBUG

        return result;
    }

} // end namespace irr

#endif // __IRR_EXT_FFT_GORTZEL_ALGORITHM_H__
