#define BOOST_TEST_MODULE ip_filter_test_module

#include "ip_class.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test)

BOOST_AUTO_TEST_CASE(ip_cmp_test)
{
    ip_t ip1 = {"10","2","3", "4"};
    ip_t ip2 = {"1","2","3", "4"};
    BOOST_CHECK(ip_class::ip_cmp(ip1, ip2));

    ip1 = {"1","2","3", "4"};
    ip2 = {"1","2","3", "4"};
    BOOST_CHECK(!ip_class::ip_cmp(ip1, ip2));

    ip1 = {"1","20","3", "4"};
    ip2 = {"1","2","3", "4"};
    BOOST_CHECK(ip_class::ip_cmp(ip1, ip2));

    ip1 = {"1","2","3", "40"};
    ip2 = {"1","2","3", "4"};
    BOOST_CHECK(ip_class::ip_cmp(ip1, ip2));

    ip1 = {"1","2","3", "4"};
    ip2 = {"1","20","3", "4"};
    BOOST_CHECK(!ip_class::ip_cmp(ip1, ip2));
}

BOOST_AUTO_TEST_CASE(ip_filter_test)
{
    ip_list list = {
        {"1","2","3", "4"},
        {"10","2","3", "4"},
        {"1","20","3", "4"},
        {"1","2","3", "5"},
    };
    BOOST_CHECK(ip_class::filter(list, 1).size() == 3);
    BOOST_CHECK(ip_class::filter(list, 1, 2).size() == 2);
    BOOST_CHECK(ip_class::filter(list, 10, 2, 3).size() == 1);
    BOOST_CHECK(ip_class::filter(list, 1,2,3,5).size() == 1);
    BOOST_CHECK(ip_class::filter(list, 1,2,3,6).size() == 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_any_test)
{
    ip_list list = {{"1","2","3", "4"}};
    BOOST_CHECK(ip_class::filter_any(list, 0).size() == 0);
    BOOST_CHECK(ip_class::filter_any(list, 1).size() == 1);
    BOOST_CHECK(ip_class::filter_any(list, 2).size() == 1);
    BOOST_CHECK(ip_class::filter_any(list, 3).size() == 1);
    BOOST_CHECK(ip_class::filter_any(list, 4).size() == 1);
}

BOOST_AUTO_TEST_SUITE_END()
