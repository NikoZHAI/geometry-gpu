#pragma once

#include "ggpredef"


/**
 * @brief Compare values in lexico-graphical order
 * 
 * @tparam InputItLhs 
 * @tparam InputItRhs 
 * @param first1 
 * @param last1 
 * @param first2 
 * @param last2 
 * @return true 
 * @return false 
 */
GG_HOST_DEVICE_MEMBER_FUNCTION
template<class InputItLhs, class InputItRhs>
bool lexicoCompare(
    InputItLhs first1, InputItLhs last1,
    InputItRhs first2, InputItRhs last2
) {
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}



/**
 * @brief Compare values in lexico-graphical order
 * 
 * @tparam InputItLhs 
 * @tparam InputItRhs 
 * @tparam Compare 
 * @param first1 
 * @param last1 
 * @param first2 
 * @param last2 
 * @param cmp 
 * @return true 
 * @return false 
 */
GG_HOST_DEVICE_MEMBER_FUNCTION
template<class InputItLhs, class InputItRhs, class Compare>
bool lexicoCompare(
    InputItLhs first1, InputItLhs last1,
    InputItRhs first2, InputItRhs last2,
    const Compare &cmp
) {
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (cmp(*first1, *first2)) return true;
        if (cmp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}
