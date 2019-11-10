#define BOOST_TEST_MODULE ip_filter_test_module

#include "ip_class.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test)

BOOST_AUTO_TEST_CASE(vt_filter_test)
{
    ip_list list = {
        {1,255,255,255},
        {1,0,0,0},
        {46,70,2,1},
        {46,3,46,2},
        {1,1,1,46},
        {46,70,4,46},
        {46,70,0,0},
        {46,70,255,254},
        {1,1,3,3},
        {2,3,3,1}
    };
    std::sort(list.begin(), list.end(), std::greater<ip_t>());

    auto parse_res =[](auto res) {
        auto a = std::get<0>(res);
        auto b = std::get<1>(res);
        return b - a;
    };

    BOOST_CHECK(parse_res(ip_class::filter(list, 1)) == 4);
    BOOST_CHECK(parse_res(ip_class::filter(list, 46, 70)) == 4);
    BOOST_CHECK(parse_res(ip_class::filter(list, 5)) == 0);
    BOOST_CHECK(parse_res(ip_class::filter(list, 0)) == 0);
    BOOST_CHECK(parse_res(ip_class::filter(list, 1,255,255,255)) == 1);
    BOOST_CHECK(parse_res(ip_class::filter(list, 1,0,0,0)) == 1);
    BOOST_CHECK(parse_res(ip_class::filter(list, 2,3,3,1)) == 1);
    BOOST_CHECK(parse_res(ip_class::filter(list, 46,70,255,254)) == 1);
}

BOOST_AUTO_TEST_CASE(ip_filter_any_test)
{
    ip_list list = {{1,2,3, 4}};
    BOOST_CHECK(ip_class::filter_any(list, 0).size() == 1);
    BOOST_CHECK(ip_class::filter_any(list, 1).size() == 1);
    BOOST_CHECK(ip_class::filter_any(list, 2).size() == 1);
    BOOST_CHECK(ip_class::filter_any(list, 3).size() == 1);
    BOOST_CHECK(ip_class::filter_any(list, 4).size() == 1);
}

BOOST_AUTO_TEST_SUITE_END()
