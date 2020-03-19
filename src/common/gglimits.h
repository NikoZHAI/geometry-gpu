#pragma once

/// @file Compiler std::numeric_limits<T> wrappers

#include "ggpredef"


#if defined(__CUDACC__) // NVCC

#include "thrust/limits.h"

namespace gg
{

struct numeric_limits : thrust::numeric_limits<T> {};

}

#else

#include <limits>

namespace gg
{

template <typename T>
struct numeric_limits : std::numeric_limits<T> {};

}


#endif
