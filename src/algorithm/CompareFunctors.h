#pragma once

#include "ggpredef"


/**
 * @brief mimic the behavior of std::less<T>
 * 
 * @tparam T 
 */
template<typename T>
struct cmp_less
{
    GG_HOST_DEVICE_MEMBER_FUNCTION
    constexpr
    bool operator () ( T &lhs, T &rhs ) const
    { return lhs < rhs; }
};


/**
 * @brief Returns boolean result of `lhs > rhs`
 * 
 * @tparam T 
 */
template<typename T>
struct cmp_greater
{
    GG_HOST_DEVICE_MEMBER_FUNCTION
    constexpr
    bool operator () ( T &lhs, T &rhs ) const
    { return lhs > rhs; }
};


/**
 * @brief Returns boolean result of `lhs == rhs`
 * 
 * @tparam T 
 */
template<typename T>
struct cmp_equal
{
    GG_HOST_DEVICE_MEMBER_FUNCTION
    constexpr
    bool operator () ( T &lhs, T &rhs ) const
    { return lhs == rhs; }
};


/**
 * @brief Returns boolean result of `lhs <= rhs`
 * 
 * @tparam T 
 */
template<typename T>
struct cmp_less_equal
{
    GG_HOST_DEVICE_MEMBER_FUNCTION
    constexpr
    bool operator () ( T &lhs, T &rhs ) const
    { return lhs <= rhs; }
};


/**
 * @brief Returns boolean result of `lhs >= rhs`
 * 
 * @tparam T 
 */
template<typename T>
struct cmp_greater_equal
{
    GG_HOST_DEVICE_MEMBER_FUNCTION
    constexpr
    bool operator () ( T &lhs, T &rhs ) const
    { return lhs >= rhs; }
};
