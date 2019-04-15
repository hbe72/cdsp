//          Copyright Heikki Berg 2017 - 2018
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#include <gtest/gtest.h>

#include <cdsp/dsp_types.h>
#include <cdsp/dsp_math.h>

#include <cnl/_impl/type_traits/assert_same.h>
#include <cnl/_impl/type_traits/identical.h>
using cnl::_impl::assert_same;
using cnl::_impl::identical;

TEST(basic_math, floor)
{
    std::vector<float> nbrs {
        0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f,
        1.7f, 1.8f, 1.9f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f,
        -0.9f, -1.0f, -1.1f, -1.2f, -1.3f, -1.4f, -1.5f, -1.6f,
        -1.7f, -1.8f, -1.9f, -2.0f, -2.1f, -2.2f, -2.3f, -2.4f
    };
    std::vector<float> res {
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f,
        -1.0f, -1.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f, -2.0f, -2.0f, -3.0f, -3.0f, -3.0f, -3.0f
    };

    {
        for (std::size_t index = 0; index < nbrs.size(); ++index)
        {
            float a = nbrs[index];
            float expected = res[index];
            EXPECT_EQ(cdsp::math::floor(a), expected)
            << "index: " << index << std::endl;
        }
    }
    {
        for (std::size_t index = 0; index < nbrs.size(); ++index)
        {
            q4_20 a = nbrs[index];
            q4_20 expected = res[index];
            EXPECT_EQ(static_cast<float>(cdsp::math::floor(a)), res[index])
            << "index: " << index << std::endl;
            EXPECT_EQ(cdsp::math::floor(a), expected)
            << "index: " << index << std::endl;
        }
    }
}

TEST(basic_math, div)
{

    q4_20 a(1.0);
    q4_20 b(2.0);
    q4_20 c1 = cdsp::math::divides<q4_20,q4_20>()(b,a);
    q4_20 c2 = cdsp::math::divides<q4_20,q4_20>()(a,b);

    EXPECT_EQ(static_cast<float>(c1), 2.0);
    EXPECT_EQ(static_cast<float>(c2), 0.5);
}

template<class Rep = int, int Exponent = 0, class RoundingTag = cnl::nearest_rounding_tag>
using rounding_fixed_point = cnl::fixed_point<cnl::rounding_integer<Rep, RoundingTag>, Exponent>;

TEST(basic_math, rounding_fixed_point)
{

    using q28_4 = rounding_fixed_point<std::int32_t, -4>;
    using q31_1 = rounding_fixed_point<std::int32_t, -1>;

    q28_4 a(0.4375);
    q31_1 b = a;
    EXPECT_EQ(a, 0.4375);
    EXPECT_EQ(b, 0.5);
}

TEST(basic_math, rounding_elastic_number)
{
    
    using q4_4 = cdsp::rounding_elastic_number<8, -4>;
    using q4_1 = cdsp::rounding_elastic_number<4, -1>;
    
    q4_4 a(0.4375);
    q4_1 b = a;
    EXPECT_EQ(a, 0.4375);
    EXPECT_EQ(b, 0.5);
}

/// Same as above but as compile time test
namespace test_rounding_elastic_number
{
    static constexpr auto a = cdsp::rounding_elastic_number<8, -4>{0.4375};
    static constexpr auto b = static_cast<cdsp::rounding_elastic_number<4, -1>>(a);
    static_assert(identical(cdsp::rounding_elastic_number<4, -1>{0.5}, b),
              "rounding_elastic_number");
    static_assert(identical(cdsp::rounding_elastic_integer<8>{7}, to_rep(a)),
              "rounding_elastic_number");
    static_assert(identical(cdsp::rounding_elastic_integer<4>{1}, to_rep(b)),
              "rounding_elastic_number");
}

namespace test_rounding_should_stay_under_64_bits
{
    static constexpr auto c = static_cast<cdsp::rounding_elastic_number<24, -20>>
        (cdsp::rounding_elastic_number<48, -40>{0.21875});
    static_assert(identical(cdsp::rounding_elastic_number<24, -20>{0.21875}, c),
                  "rounding_elastic_number assignment");
}

namespace test_convert_nearest_rounding_elastic_number
{
    static constexpr auto a = cnl::elastic_number<8, -4>{0.3125};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::elastic_number<4, -1>>(a);
    static_assert(identical(cnl::elastic_number<4, -1>{0.5}, b),
              "cnl::convert<nearest_rounding_tag, elastic_number, elastic_number>");

    static constexpr auto c = cnl::convert<cnl::nearest_rounding_tag, cnl::elastic_number<4, -2>>(a);
    static_assert(identical(cnl::elastic_number<4, -2>{0.25}, c),
              "cnl::convert<nearest_rounding_tag, elastic_number, elastic_number>");
}

namespace test_convert_nearest_rounding_fixed_point
{
    static constexpr auto a = cnl::fixed_point<int, -4>{0.3125};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::fixed_point<int, -1>>(a);
    static_assert(identical(cnl::fixed_point<int, -1>{0.5}, b),
              "cnl::convert<nearest_rounding_tag, fixed_point, fixed_point>");

    static constexpr auto c = cnl::convert<cnl::nearest_rounding_tag, cnl::fixed_point<int, -2>>(a);
    static_assert(identical(cnl::fixed_point<int, -2>{0.25}, c),
              "cnl::convert<nearest_rounding_tag, fixed_point, fixed_point>");
}
