#pragma once


#include "ggpredef"
#include "gglimits"


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
    using L_     = gg::numeric_limits<FT>;

public:
    FT xmin, ymin, xmax, ymax;


    Bbox2D()
        : xmin( L_::infinity() ), ymin( L_::infinity() ),
          xmax(-L_::infinity() ), ymax(-L_::infinity() )
    {}

    Bbox2D( FT t_xmin, FT t_ymin, FT t_xmax, FT t_ymax )
        : xmin( t_xmin ), ymin( t_ymin ), xmax( t_xmax ), ymax( t_ymax )
    {}

    Self& set( FT x1, FT y1, FT x2, FT y2 )
    {
        xmin = x1;
        ymin = y1;
        xmax = x2;
        xmax = y2;
        return *this;
    }

    // 判断该 Bbox 是否合理 ( min < max )
    BT is_valid() const
    { return !( xmin > xmax || ymin > ymax ); }

    // 无效化
    Self& reset()
    {
        xmin = ymin =  L_::infinity();
        xmax = ymax = -L_::infinity();
        return *this;
    }

    BT operator==( const Self &rhs ) const
    {
        return (
            xmin == rhs.xmin &&
            ymin == rhs.ymin &&
            xmax == rhs.xmax &&
            ymax == rhs.ymax
        );
    }

    BT operator!=( const Self &rhs ) const
    { return !( *this == rhs ); }

    Self bbox2() const
    { return *this; }

    static constexpr
    unsigned int dim() noexcept
    { return 2u; }

    FT dx() const
    { return xmax-xmin; }

    FT dy() const
    { return ymax-ymin; }

    FT get_max ( Uint32 i ) const
    {
        if ( i == 0 ) return xmax;
        return ymax;
    }
    FT get_min ( Uint32 i ) const
    {
        if ( i == 0 ) return xmin;
        return ymin;
    }

    Self& add_minmax( FT x1, FT y1, FT x2, FT y2 )
    {
        if ( x1 < xmin ) minmax[0] = x1;
        if ( y1 < ymin ) minmax[1] = y1;
        if ( x2 > xmax ) minmax[2] = x2;
        if ( y2 > ymax ) minmax[3] = y2;
        return *this;
    }

    Self& eat( FT x, FT y )
    {
        if ( x < xmin ) xmin = x;
        if ( y < ymin ) ymin = y;
        if ( x > xmax ) xmax = x;
        if ( y > ymax ) ymax = y;
        return *this;
    }

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

    Self  operator+ ( const Self &rhs ) const
    {
        return Self(
            std::min( xmin, rhs.xmin ), std::min( ymin, rhs.ymin ),
            std::max( xmax, rhs.xmax ), std::max( ymax, rhs.ymax )
        );
    }

    Self& operator+= ( const Self &rhs )
    {
        if ( rhs.xmin < xmin ) xmin = rhs.xmin;
        if ( rhs.ymin < ymin ) ymin = rhs.ymin;
        if ( rhs.xmax > xmax ) xmax = rhs.xmax;
        if ( rhs.ymax > ymax ) ymax = rhs.ymax;
        return *this;
    }

    // 获取 Bbox 中心
    Vector2 center() const
    { return Vector2( ( xmin+xmax )*static_cast<FT>(0.5), ( ymin+ymax )*static_cast<FT>(0.5) ); }

    // 延展
    Self& extend( FT r )
    {
        xmin -= r;
        ymin -= r;
        xmax += r;
        ymax += r;
        return *this;
    }

    // 获取延展尺寸
    Vector2 get_extents() const
    { return Vector2( dx()*static_cast<FT>(0.5), dy()*static_cast<FT>(0.5) ); }


    // 获取周长
    FT perimeter() const
    { return ( dx()+dy() ) * static_cast<FT>(2); }

    // 获取 面积/体积
    FT volume() const
    { return dx()*dy(); }

    // 判断相离
    BT separates_from( const Self &rhs ) const
    {
        return xmin > rhs.xmax ||
               ymin > rhs.ymax ||
               xmax < rhs.xmin ||
               ymax < rhs.ymin;
    }

    // 判断有重叠部分
    BT overlaps( const Self &rhs ) const
    { return !separates_from( rhs ); }

    // 判断包含
    BT contains( const Self &rhs ) const
    {
        return xmin <= rhs.xmin &&
               ymin <= rhs.ymin &&
               xmax >= rhs.xmax &&
               ymax >= rhs.ymax;
    }

    // 判断有重叠部分, 但不相互包含
    BT touches( const Self &rhs ) const
    { return overlaps( rhs ) && !contains( rhs ) && !rhs.contains( *this ); }

    // 判断包含一点
    BT contains(FT x, FT y) const
    {
        return x >= xmin &&
               x <= xmax &&
               y >= ymin &&
               y <= ymax;
    }

    BT contains( const Vector2 &v ) const
    {
        return v.x() >= xmin &&
               v.x() <= xmax &&
               v.y() >= ymin &&
               v.y() <= ymax;
    }

    BT strictly_contains(FT x, FT y) const
    {
        return x > xmin &&
               x < xmax &&
               y > ymin &&
               y < ymax;
    }

    BT strictly_contains( const Vector2 &v ) const
    {
        return v.x() > xmin &&
               v.x() < xmax &&
               v.y() > ymin &&
               v.y() < ymax;
    }

    // 判断包含一点 (齐次坐标)
    BT contains(FT x, FT y, FT w) const
    { return contains( Vector2( x, y, w ) ); }

    BT strictly_contains(FT x, FT y, FT w) const
    { return strictly_contains( Vector2( x, y, w ) ); }

    // 将 BBox 扩大一点
    void dilate()
    {
        xmin = gg::nextafter( xmin, -gg::numeric_limits<FT>::infinity() );
        ymin = gg::nextafter( ymin, -gg::numeric_limits<FT>::infinity() );
        xmax = gg::nextafter( xmax,  gg::numeric_limits<FT>::infinity() );
        ymax = gg::nextafter( ymax,  gg::numeric_limits<FT>::infinity() );
    }

};


template<class Box, typename BT = typename Box::BT>
BT do_overlap( const Box &a, const Box &b )
{ return a.overlaps(b); }


template<class InputIter,
    typename Kernel = typename std::iterator_traits<InputIter>::value_type::Kernel >
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


#endif
