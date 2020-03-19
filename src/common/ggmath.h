/// @file Compiler math function wrappers
#pragma once

#include "ggpredef"


#ifdef __CUDACC__
#else
#   include <cmath>
#   include <algorithm>
#endif


namespace gg
{

#if defined(__CUDACC__) // NVCC


/////////////////////////////////////////////////
// std::isnormal(x)                            //
//  Mimic the behavior of std::isnormal(x) but //
//  detections of subnormals are not supported //
/////////////////////////////////////////////////
GG_INLINE GG_DEVICE_FUNCTION
bool isnormal( float x )
{ return isfinitef(x) && ( x != 0f ); }

GG_INLINE GG_DEVICE_FUNCTION
bool isnormal( double x )
{ return isfinite(x) && ( x != 0. ); }


/////////////////////////////////////////////////
// std::atan2(x)                               //
/////////////////////////////////////////////////
GG_INLINE GG_DEVICE_FUNCTION
float atan2( float x )
{ return atan2f(x); }


/////////////////////////////////////////////////
// std::sqrt(x)                                //
/////////////////////////////////////////////////
GG_INLINE GG_DEVICE_FUNCTION
float sqrt( float x )
{ return sqrtf(x); }


/////////////////////////////////////////////////
// std::nextafter(x, dest)                     //
/////////////////////////////////////////////////
GG_INLINE GG_DEVICE_FUNCTION
float nextafter( float x, float y )
{ return nextafterf(x, y); }


/////////////////////////////////////////////////
// std::max(x, y) / std::min(x, y)             //
//  Note that this is not fully portable since //
//  C99 fmax() is not std::max(...)            //
/////////////////////////////////////////////////
GG_INLINE GG_DEVICE_FUNCTION
float max( float x, float y )
{ return fmaxf( x, y ); }

GG_INLINE GG_DEVICE_FUNCTION
double max( double x, double y )
{ return fmax( x, y ); }

GG_INLINE GG_DEVICE_FUNCTION
float min( float x, float y )
{ return fminf( x, y ); }

GG_INLINE GG_DEVICE_FUNCTION
double max( double x, double y )
{ return fmin( x, y ); }


#else


using std::isnormal;
using std::atan2;
using std::sqrt;
using std::nextafter;
using std::min;
using std::max;

#endif

};  // namespace gg
