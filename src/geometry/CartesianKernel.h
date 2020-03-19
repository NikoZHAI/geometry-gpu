#pragma once
#ifndef GG_CARTESIAN_KERNEL_INCLUDED
#define GG_CARTESIAN_KERNEL_INCLUDED 1


#include "Bbox2D.h"
#include "Vector2D.h"
// #include "Matrix2D.h"


template<typename FT, typename BT = bool>
class CartesianKernel
{
public:

    using FieldType     = FT;
    using BooleanType   = BT;
    using Kernel        = CartesianKernel<FT, BT>;
    using Self          = Kernel;

    using Bbox2        = Bbox2D<Kernel>;
    using Vector2      = Vector2D<Kernel>;
    // using Mat2         = Mat2D<Kernel>;
};


#endif // CARTESIAN_KERNEL
