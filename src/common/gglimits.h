#pragma once

/// @file Compiler math function wrappers

#include "ggpredef"


namespace gg
{

#if defined(__CUDACC__) // NVCC

#include "thrust/limits.h"
struct numeric_limits : thrust::numeric_limits<T> {};

#else

#include <limits>

template <typename T>
struct numeric_limits : std::numeric_limits<T> {};

#endif


};  // namespace gg
