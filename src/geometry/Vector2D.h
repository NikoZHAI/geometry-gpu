#pragma once

#include "ggpredef"
#include "ggalgo"
#include "ggmath"
#include "gglimits"


template<class K_>
class GG_ALIGN( sizeof( typename K_::FieldType) * 2ul ) Vector2D
{

public:
    using Kernel = K_;
    using Self   = Vector2D<Kernel>;
    using FT     = typename Kernel::FieldType;
    using BT     = typename Kernel::BooleanType;

    // other geometries
    using Bbox2D = typename Kernel::Bbox2;

public:

    FT x, y;


    GG_HOST_DEVICE_MEMBER_FUNCTION
    Vector2D()
        : x( FT(0.) ), y( FT(0.) )
    {}

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Vector2D( FT t_x, FT t_y )
        : x(t_x), y(t_y)
    {}

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Vector2D( FT t_x, FT t_y, FT t_w )
        : x(t_x), y(t_y)
    {
        if ( t_w == FT(0) )
        {
            y = x = gg::numeric_limits<FT>::quiet_NaN();
        }
        this->operator/=(w);
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Vector2D( const Self &src, const Self &dst )
        : x( dst.x - src.x ), y( dst.y - src.y )
    {}

    GG_HOST_DEVICE_MEMBER_FUNCTION
    const FT* data() const
    { return &x; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT* begin()
    { return &x; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT* end()
    { return (&y) + 1ul; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    const FT* begin() const
    { return &x; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    const FT* end() const
    { return (&y) + 1ul; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& set( FT t_x, FT t_y )
    { x = t_x; y = t_y; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& copy( const Self &rhs )
    { x =; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator=( const FT &val )
    { x = y = val; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator=( const Self &rhs )
    { x = rhs.x; y = rhs.y; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& setX( const FT &val )
    { x = val; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& setY( const FT &val )
    { y = val; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    const FT& operator[]( Uint32 i ) const
    { return i&1 ? y : x; }
    
    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT& operator[]( Uint32 i )
    { return i&1 ? y : x; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT operator<( const Self &rhs ) const
    { return (BT)lexicoCompare( begin(), end(), rhs.begin(), rhs.end(), cmp_less<FT>() ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT operator>( const Self &rhs ) const
    { return (BT)lexicoCompare( begin(), end(), rhs.begin(), rhs.end(), cmp_greater<FT>() ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT operator==( const Self &rhs ) const
    { return (BT)lexicoCompare( begin(), end(), rhs.begin(), rhs.end(), cmp_equal<FT>() ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT operator!=( const Self &rhs ) const
    { return !( operator==( rhs ) ); }

    /* Vector-Scalar operations */
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator+( const FT &rhs ) const
    { return Self( x+rhs, y+rhs ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator-( const FT &rhs ) const
    { return Self( x-rhs, y-rhs ); }
    
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator*( const FT &rhs ) const
    { return Self( x*rhs, y*rhs ); }
    
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator/( const FT &rhs ) const
    { return gg::isnormal(rhs) ? Self( x/rhs, y/rhs ) : Self(); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator+=( const FT &rhs )
    {
        x += rhs;
        y += rhs;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator-=( const FT &rhs )
    {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator*=( const FT &rhs )
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator/=( const FT &rhs )
    {
        FT inv_ = gg::isnormal(rhs) ? FT(1)/rhs : FT(0);
        x *= inv_;
        y *= inv_;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator+( const Self &rhs ) const
    { return Self( x+rhs.x, y+rhs.y ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator-( const Self &rhs ) const
    { return Self( x-rhs.x, y-rhs.y ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator*( const Self &rhs ) const
    { return Self( x*rhs.x, y*rhs.y ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator/( const Self &rhs ) const
    { return rhs.isNormal() ? Self( x/rhs.x, y/rhs.y ) : Self( FT(0.), FT(0.) ); }
    
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator+=( const Self &rhs )
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator-=( const Self &rhs )
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator*=( const Self &rhs )
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator/=( const Self &rhs )
    {
        if ( rhs.isNormal() )
        {
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }
        return this->set( FT(0.), FT(0.) );
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT atan2() const
    { return gg::atan2(y, x); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT dot_prod( const Self &rhs ) const
    { return x*rhs.x + y*rhs.y; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT cross2( const Self &rhs ) const
    { return x*rhs.y - y*rhs.x; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT squared_length() const
    { return x*x + y*y; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT length ()
    { return gg::sqrt( squared_length() ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT magnitude ()
    { return gg::sqrt( squared_length() ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT squared_distance( const Self &rhs ) const
    { return (*this - rhs).squared_length(); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self normalized() const
    {
        FT mag = magnitude();
        return this->operator/( mag );
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& normalize()
    {
        FT mag = magnitude();
        return this->operator/=( mag );
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& mirror()
    { return this->set( -y, -x ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& mirror( const Self &center )
    { return center + (center - *this); }


    // /////////////////////////////
    //// GeometryConcept Methods  //
    ///////////////////////////// //
    GG_HOST_DEVICE_MEMBER_FUNCTION
    constexpr unsigned int dim() const
    { return 2u; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Bbox2D bbox2() const
    { return BBox2D( x, y, x, y ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self clone() const
    { return Self( *this ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& zero()
    { x = y = FT(0.); return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& moveX_plus( const FT &val )
    { x += val; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& moveY_plus( const FT &val )
    { y += val; return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    bool isNormal() const
    { return gg::isnormal(x) && gg::isnormal(y); }

};


GG_HOST_DEVICE_MEMBER_FUNCTION
template<class V_>
typename V_::FT
cross_prod2( const V_ &v0, const V_ &v1 )
{ return v0.x*v1.y - v1.x*v0.y; }


GG_HOST_DEVICE_MEMBER_FUNCTION
template<class V_>
typename V_::BT
compare_x( const V_ &v0, const V_ &v1 )
{ return v0.x < v1.x; }


GG_HOST_DEVICE_MEMBER_FUNCTION
template<class V_>
typename V_::BT
compare_y( const V_ &v0, const V_ &v1 )
{ return v0.y < v1.y; }

