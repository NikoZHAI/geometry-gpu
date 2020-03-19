#pragma once


#include "ggpredef"
#include "gglimits"
#include "ggiterator"


/**
 * 2-D Axis-aligned Bounding Box
*/
template<class K_>
class GG_ALIGN( sizeof( typename K_::FieldType) * 2ul ) Bbox2D
{

public:
    using Kernel = K_;
    using Self   = Bbox2D<Kernel>;
    using FT     = typename Kernel::FieldType;
    using BT     = typename Kernel::BooleanType;

    // other geometries
    using Vector2 = typename Kernel::Vector2;

protected:
    using L_ = gg::numeric_limits<FT>;

public:
    FT xmin, ymin, xmax, ymax;

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Bbox2D()
        : xmin( L_::infinity() ), ymin( L_::infinity() ),
          xmax(-L_::infinity() ), ymax(-L_::infinity() )
    {}

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Bbox2D( FT t_xmin, FT t_ymin, FT t_xmax, FT t_ymax )
        : xmin( t_xmin ), ymin( t_ymin ), xmax( t_xmax ), ymax( t_ymax )
    {}

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& set( FT x1, FT y1, FT x2, FT y2 )
    {
        xmin = x1;
        ymin = y1;
        xmax = x2;
        xmax = y2;
        return *this;
    }

    // 判断该 Bbox 是否合理 ( min < max )
    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT is_valid() const
    { return !( xmin > xmax || ymin > ymax ); }

    // 无效化
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& reset()
    {
        xmin = ymin =  L_::infinity();
        xmax = ymax = -L_::infinity();
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT operator==( const Self &rhs ) const
    {
        return (
            xmin == rhs.xmin &&
            ymin == rhs.ymin &&
            xmax == rhs.xmax &&
            ymax == rhs.ymax
        );
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT operator!=( const Self &rhs ) const
    { return !( *this == rhs ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self bbox2() const
    { return *this; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    static constexpr
    unsigned int dim() noexcept
    { return 2u; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT dx() const
    { return xmax-xmin; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT dy() const
    { return ymax-ymin; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT get_max ( unsigned int i ) const
    { return i&1u ? ymax : xmax; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT get_min ( unsigned int i ) const
    { return i&1u ? ymin : xmin; }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& add_minmax( FT x1, FT y1, FT x2, FT y2 )
    {
        if ( x1 < xmin ) xmin = x1;
        if ( y1 < ymin ) ymin = y1;
        if ( x2 > xmax ) xmax = x2;
        if ( y2 > ymax ) ymax = y2;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& eat( FT x, FT y )
    {
        if ( x < xmin ) xmin = x;
        if ( y < ymin ) ymin = y;
        if ( x > xmax ) xmax = x;
        if ( y > ymax ) ymax = y;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& eat( const Vector2 &vec )
    {
        const FT x = vec.x;
        const FT y = vec.y;
        if ( x < xmin ) xmin = x;
        if ( y < ymin ) ymin = y;
        if ( x > xmax ) xmax = x;
        if ( y > ymax ) ymax = y;
        return *this;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self operator+ ( const Self &rhs ) const
    {
        return Self(
            gg::min( xmin, rhs.xmin ), gg::min( ymin, rhs.ymin ),
            gg::max( xmax, rhs.xmax ), gg::max( ymax, rhs.ymax )
        );
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& operator+= ( const Self &rhs )
    {
        if ( rhs.xmin < xmin ) xmin = rhs.xmin;
        if ( rhs.ymin < ymin ) ymin = rhs.ymin;
        if ( rhs.xmax > xmax ) xmax = rhs.xmax;
        if ( rhs.ymax > ymax ) ymax = rhs.ymax;
        return *this;
    }

    // 获取 Bbox 中心
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Vector2 center() const
    { return Vector2( ( xmin+xmax )*static_cast<FT>(0.5), ( ymin+ymax )*static_cast<FT>(0.5) ); }

    // 延展
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Self& extend( FT r )
    {
        xmin -= r;
        ymin -= r;
        xmax += r;
        ymax += r;
        return *this;
    }

    // 获取延展尺寸
    GG_HOST_DEVICE_MEMBER_FUNCTION
    Vector2 get_extents() const
    { return Vector2( dx()*static_cast<FT>(0.5), dy()*static_cast<FT>(0.5) ); }


    // 获取周长
    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT perimeter() const
    { return ( dx()+dy() ) * static_cast<FT>(2); }

    // 获取 面积/体积
    GG_HOST_DEVICE_MEMBER_FUNCTION
    FT volume() const
    { return dx()*dy(); }

    // 判断相离
    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT separates_from( const Self &rhs ) const
    {
        return xmin > rhs.xmax ||
               ymin > rhs.ymax ||
               xmax < rhs.xmin ||
               ymax < rhs.ymin;
    }

    // 判断有重叠部分
    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT overlaps( const Self &rhs ) const
    { return !separates_from( rhs ); }

    // 判断包含
    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT contains( const Self &rhs ) const
    {
        return xmin <= rhs.xmin &&
               ymin <= rhs.ymin &&
               xmax >= rhs.xmax &&
               ymax >= rhs.ymax;
    }

    // 判断有重叠部分, 但不相互包含
    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT touches( const Self &rhs ) const
    { return overlaps( rhs ) && !contains( rhs ) && !rhs.contains( *this ); }

    // 判断包含一点
    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT contains(FT x, FT y) const
    {
        return x >= xmin &&
               x <= xmax &&
               y >= ymin &&
               y <= ymax;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT contains( const Vector2 &v ) const
    {
        return v.x >= xmin &&
               v.x <= xmax &&
               v.y >= ymin &&
               v.y <= ymax;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT strictly_contains(FT x, FT y) const
    {
        return x > xmin &&
               x < xmax &&
               y > ymin &&
               y < ymax;
    }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT strictly_contains( const Vector2 &v ) const
    {
        return v.x > xmin &&
               v.x < xmax &&
               v.y > ymin &&
               v.y < ymax;
    }

    // 判断包含一点 (齐次坐标)
    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT contains(FT x, FT y, FT w) const
    { return contains( Vector2( x, y, w ) ); }

    GG_HOST_DEVICE_MEMBER_FUNCTION
    BT strictly_contains(FT x, FT y, FT w) const
    { return strictly_contains( Vector2( x, y, w ) ); }

    // 将 BBox 扩大一点
    GG_HOST_DEVICE_MEMBER_FUNCTION
    void dilate()
    {
        xmin = gg::nextafter( xmin, -L_::infinity() );
        ymin = gg::nextafter( ymin, -L_::infinity() );
        xmax = gg::nextafter( xmax,  L_::infinity() );
        ymax = gg::nextafter( ymax,  L_::infinity() );
    }

};


/**
 * @brief check if two Bbox2D overlap with each other
 * 
 * @tparam Box Bbox2D<Kernel>
 * @tparam Box::BT Boolean type of the Kernel
 * @param a box a
 * @param b box b
 * @return BT true if overlaps
 */
GG_HOST_DEVICE_MEMBER_FUNCTION
template<class Box, typename BT = typename Box::BT>
BT do_overlap( const Box &a, const Box &b )
{ return a.overlaps(b); }


/**
 * @brief Construct a big box containing all the traversed primitives
 * 
 * @tparam InputIter 
 * @tparam std::iterator_traits<InputIter>::value_type::Kernel 
 * @param begin 
 * @param end 
 * @return Bbox2D<Kernel> 
 */
GG_HOST_DEVICE_MEMBER_FUNCTION
template<class InputIter,
    typename Kernel = typename gg::iterator_traits<InputIter>::value_type::Kernel >
Bbox2D<Kernel> construct_box( InputIter begin, InputIter end )
{
    Bbox2D<Kernel> box;
    while ( begin != end )
    {
        box += begin->bbox2();
        ++begin;
    }
    return box;
}
