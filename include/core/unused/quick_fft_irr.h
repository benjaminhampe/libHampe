// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_FFT_TEMPLATE_ALGORITHM_H__
#define __IRR_EXT_FFT_TEMPLATE_ALGORITHM_H__

#include <irrTypes.h>
#include <irrArray.h>
#include <irrMath.h>
#include <irrString.h>
#include <cmath>
#include <complex>

#ifdef _DEBUG
	#include <../source/Irrlicht/os.h>
#endif // _DEBUG

namespace irr
{

template <class T>
void fft( const core::array<std::complex<T>>& data, s32 sign = 0 /* forward*/ )
{
    u32 j=0;

    // Warning about signed vs unsigned comparison
    for(u32 i=0; i<data.size()-1; ++i)
    {
        if (i < j)
        {
            auto t = data[i];
            data[i] = data[j];
            data[j] = t;
        }

        u32 m=data.size()/2;
        j^=m;
        while ((j & m) == 0)
        {
            m/=2;
            j^=m;
        }
    }

    for(u32 j=1; j<data.size(); j*=2)
    {
        for(u32 m=0; m<j; ++m)
        {
            auto t = core::PI64 * sign * m / j;

            auto w = std::complex<T>(cos(t), sin(t));

            for(u32 i = m; i<data.size(); i+=2*j)
            {
                std::complex<T> zi = data[i];
                std::complex<T> t = w * data[i + j];
                data[i] = zi + t;
                data[i + j] = zi - t;
            }
        }
    }
}

} // end namespace irr

#endif // __IRR_EXT_FFT_GORTZEL_ALGORITHM_H__
