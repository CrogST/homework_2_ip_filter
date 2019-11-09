#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using ip_t = std::vector<int>;
using ip_list = std::vector<ip_t>;
using ip_list_iter = ip_list::iterator;
using filter_res = std::pair<ip_list_iter, ip_list_iter>;

class ip_class {

    static auto vt_filter(ip_list_iter begin, ip_list_iter end, ip_t::size_type) {
        return filter_res(begin, end);
    }

    template <typename T, typename ...Args>
    static auto vt_filter(ip_list_iter begin, ip_list_iter end, ip_t::size_type oct_ind, T val, Args... args) {

        //ищем первый ip, октет которого меньше, либо равен искомому значению
        auto low_iter = std::lower_bound(begin, end, ip_t{}, [oct_ind, val](const auto & it, const auto &) {
            return it[oct_ind] > val;
        });
        //проверяем, что у найденного ip октет равен. Иначе - результат пустой.
        if((*low_iter)[oct_ind] != val) return filter_res(begin, begin);

        //ищем первый ip, октет которого меньше искомого значения
        auto upper_iter =
                std::upper_bound(low_iter, end, ip_t{}, [oct_ind, val](const auto &, const auto & it) {
            return it[oct_ind] < val;
        });

        return vt_filter(low_iter, upper_iter, oct_ind+1, args...);
    }

public:

    template <typename ...Args>
    static auto filter(ip_list & list, Args... args) {
        return vt_filter(list.begin(), list.end(), 0, args...);
    }

    static auto filter_any(ip_list list, int val) {
        ip_list list_out;
        auto cmp_oct = [val](int oct) {
            return (oct == val);
        };
        auto cmp_ip = [&cmp_oct](ip_t ip)
        {
            return std::any_of(ip.begin(), ip.end(), cmp_oct);
        };
        std::copy_if(list.begin(), list.end(), std::back_inserter(list_out), cmp_ip);
        return list_out;
    }

};
