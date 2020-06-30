//          Copyright Heikki Berg 2017 - 2018
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#if !defined(CDSP_TYPES)
#define CDSP_TYPES

#include <cnl/all.h>

namespace cdsp
{

    template<
            int IntegerDigits,
            class RoundingTag = cnl::_impl::tag_t<cnl::rounding_integer<>>,
            class Narrowest = int>
    using rounding_elastic_integer = cnl::rounding_integer<
    cnl::elastic_integer<
            IntegerDigits,
            Narrowest>,
    RoundingTag>;

    template<
            class RoundingTag = cnl::_impl::tag_t<cnl::rounding_integer<>>,
            class Narrowest = int,
            class Input = int>
    CNL_NODISCARD rounding_elastic_integer<
            cnl::numeric_limits<Input>::digits,
            RoundingTag,
            Narrowest>
    constexpr make_rounding_elastic(Input const& input)
    {
        return input;
    }

template<int Digits, int Exponent = 0, class RoundingTag = cnl::nearest_rounding_tag, class Narrowest = signed>
using rounding_elastic_number = cnl::fixed_point<rounding_elastic_integer<Digits, RoundingTag, Narrowest>, Exponent>;
}
// Elastic fixed point types equivalent to Cirrus ADSP2
typedef cdsp::rounding_elastic_number<24, -20> q4_20;
typedef cdsp::rounding_elastic_number<48, -40> q8_40;

// Simpler type with truncation rather than rounding
// typedef cnl::static_number<24, -20> q4_20;
// typedef cnl::static_number<48, -40> q8_40;

#endif //CDSP_TYPES
