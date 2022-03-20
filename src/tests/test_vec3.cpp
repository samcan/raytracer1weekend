#define BOOST_TEST_MODULE test_vec3
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>


namespace un=boost::unit_test;
namespace bdata=boost::unit_test::data;
namespace tt=boost::test_tools;

#include "../vec3.h"

BOOST_AUTO_TEST_CASE( zero_vector ) {
    vec3 v(0, 0, 0);
    BOOST_TEST(v.x() == 0);
    BOOST_TEST(v.y() == 0);
    BOOST_TEST(v.z() == 0);
}

auto neg100gen = bdata::xrange<double>( (bdata::begin=-100, bdata::end=100, bdata::step=0.5));
auto n100gen = bdata::xrange<double>( (bdata::begin=-100, bdata::end=-0.5, bdata::step=0.5));
auto p100gen = bdata::xrange<double>( (bdata::begin=0.5, bdata::end=100, bdata::step=0.5));
auto deftol = tt::tolerance(0.000001);

BOOST_DATA_TEST_CASE(vec_members_x, neg100gen) {
    BOOST_TEST(vec3(sample, 0, 0).x() == sample);
}

BOOST_DATA_TEST_CASE(vec_members_y, neg100gen) {
    BOOST_TEST(vec3(0, sample, 0).y() == sample);
}

BOOST_DATA_TEST_CASE(vec_members_z, neg100gen) {
    BOOST_TEST(vec3(0, 0, sample).z() == sample);
}

BOOST_DATA_TEST_CASE(vec_mult_const, neg100gen) {
    BOOST_TEST((vec3(sample, 0, 0)*sample).x() == sample*sample);
}

BOOST_DATA_TEST_CASE(vec_div_const_pos, p100gen) {
    BOOST_TEST((vec3(sample, 0, 0)/sample).x() == 1, deftol);
}

BOOST_DATA_TEST_CASE(vec_div_const_neg, n100gen) {
    BOOST_TEST((vec3(sample, 0, 0)/sample).x() == 1, deftol);
}

BOOST_DATA_TEST_CASE(vec_add_const, neg100gen) {
    BOOST_TEST((vec3(sample, 0, 0)+vec3(sample, 0, 0)).x() == 2*sample, deftol);
}

BOOST_DATA_TEST_CASE(vec_minus_const, neg100gen) {
    BOOST_TEST((vec3(sample, 0, 0)-vec3(sample, 0, 0)).x() == 0, deftol);
}