#define BOOST_TEST_MODULE test_vec3
#include <boost/test/included/unit_test.hpp>

#include "../vec3.h"

BOOST_AUTO_TEST_CASE( zero_vector ) {
    vec3 v(0, 0, 0);
    BOOST_TEST(v.x() == 0);
    BOOST_TEST(v.y() == 0);
    BOOST_TEST(v.z() == 0);
}
