#pragma once


/// @file Unit Tests in lexicoCompare


#include <gtest/gtest.h>

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <random>
#include <algorithm>


namespace
{

// Fixture
class TestLexicoCompare : public testing::Test
{
protected:

    void SetUp() override
    {
        // resize every container with 20 elements
        v.resize(20);
        d.resize(20);
        l.resize(20);

        // create random engine and a uniform distribution
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1., 2.);

        // fill sequence up
        std::generate( a.begin(), a.end(), dis(gen) );
        std::generate( v.begin(), v.end(), dis(gen) );
        std::generate( d.begin(), d.end(), dis(gen) );
        std::generate( l.begin(), l.end(), dis(gen) );
    }

    bool testCompare()

    std::array<double, 20>  a;
    std::vector<double>     v;
    std::deque<double>      d;  
    std::list<double>       l;
};


// test against std::lexicographical_compare
TEST_F( TestLexicoCompare, AgainstStdLexicographicalCompare )
{
    EXPECT_EQ (
        
    );
}


}
