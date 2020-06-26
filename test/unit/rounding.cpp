//          Copyright Heikki Berg 2017 - 2019
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#include <cnl/all.h>

#include <cnl/_impl/type_traits/assert_same.h>
#include <cnl/_impl/type_traits/identical.h>
using cnl::_impl::assert_same;
using cnl::_impl::identical;

namespace rounding_1 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{5.0};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
    cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_2 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{5.125};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_3 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{5.25};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_4 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{5.375};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_5 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{5.5};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{6.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_6 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{5.75};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{6.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_7 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{6.0};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{6.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_n1 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{-5.0};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{-5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_n2 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{-5.125};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{-5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_n3 {
    static constexpr auto a = cnl::elastic_scaled_integer<8, -4>{-5.25};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{-5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_n4 {
    static constexpr auto a = cnl::elastic_scaled_integer<8, -4>{-5.375};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{-5.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_n5 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{-5.5};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{-6.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_n6 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{-5.75};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{-6.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
namespace rounding_n7 {
    static constexpr auto a = cnl::elastic_scaled_integer<8,-4>{-6.0};
    static constexpr auto b = cnl::convert<cnl::nearest_rounding_tag, cnl::native_rounding_tag,
        cnl::elastic_scaled_integer<4,0>, cnl::elastic_scaled_integer<8, -4>>(a);
    static_assert(identical(cnl::elastic_scaled_integer<4, 0>{-6.0}, b),
            "cnl::convert<nearest_rounding_tag, elastic_scaled_integer, elastic_scaled_integer>");
}
