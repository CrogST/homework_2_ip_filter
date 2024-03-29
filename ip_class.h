#pragma once

#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <iostream>

using ip_t = std::array<uint8_t, 4>;
using ip_list = std::vector<ip_t>;
using ip_list_iter = ip_list::iterator;
using filter_res = std::pair<ip_list_iter, ip_list_iter>;

#define log_enable false

class ip_class {

#if log_enable
static auto ip_out(ip_t val) {
    std::string str;
   for(const auto & el : val)
       str += std::to_string(el) + " ";
   return str;
}
#endif

public:    

    template <typename ...Args>
    static auto filter(ip_list & list, Args... args) {
        ip_t ip_low = {static_cast<uint8_t>(args)...};
        ip_t ip_upper = {static_cast<uint8_t>(args)...};
        for(auto i = sizeof...(args); i < 4; i++) {
            ip_low[i] = 0;
            ip_upper[i] = 255;
        }

        //ищем первый ip, который меньше либо равен искомому
        auto low_iter = std::lower_bound(list.begin(), list.end(), ip_upper,
                                         [](const auto & it, const auto &val) {
            auto cond = val < it;
            if constexpr(log_enable) std::cout << "it " << ip_out(it) << ", val " << ip_out(val) <<
                         "cond is " << ( cond ? "true" : "false") << std::endl;
            return cond;
        });
        if constexpr(log_enable) std::cout << "low is " << ip_out(*low_iter) << std::endl;

        //ищем первый ip, который меньше искомого
        auto upper_iter = std::upper_bound(low_iter, list.end(), ip_low,
                                           [](const auto & val, const auto & it) {
            auto cond = it < val;
            if constexpr(log_enable) std::cout << "it " << ip_out(it) << ", val " << ip_out(val) <<
                         "cond is " << ( cond ? "true" : "false") << std::endl;
            return cond;
        });
        if constexpr(log_enable) std::cout << "upper is " << ip_out(*upper_iter) << std::endl;
        return filter_res(low_iter, upper_iter);
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
