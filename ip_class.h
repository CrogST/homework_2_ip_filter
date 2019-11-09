#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

using ip_t = std::vector<int>;
using ip_list = std::vector<ip_t>;
using filter_res = std::pair<ip_list::iterator, ip_list::iterator>;

struct ip_class {

    template <typename ...Args>
    static auto filter(ip_list & list, Args... args) {
        ip_t ip_low = {args...};
        ip_t ip_upper = ip_low;
        ip_low.insert(  ip_low.end(),   static_cast<size_t>(4 - ip_low.size()),   0);
        ip_upper.insert(ip_upper.end(), static_cast<size_t>(4 - ip_upper.size()), 255);
        //ищем первый ip, который меньше либо равен искомому
        auto low_iter = std::lower_bound(list.begin(), list.end(), ip_upper, std::greater<ip_t>());
        //ищем первый ip, который меньше искомого
        auto upper_iter = std::upper_bound(low_iter, list.end(), ip_low, std::greater<ip_t>());
        return filter_res(low_iter, upper_iter);
    }

    static auto filter_any(ip_list list, int val) {
        ip_list list_out;
        auto cmp_oct = [val](int oct) { return (oct == val); };
        auto cmp_ip = [&cmp_oct](ip_t ip) {
            return std::any_of(ip.begin(), ip.end(), cmp_oct); };
        std::copy_if(list.begin(), list.end(), std::back_inserter(list_out), cmp_ip);
        return list_out;
    }

};
