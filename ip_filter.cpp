#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "ip_class.h"

static const bool debug = false;

auto split(const std::string &str, char delim)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delim);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(delim, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main()
{
    try
    {
        ip_list ip_pool;

        if constexpr(!debug) {
            //чтение файла построчно
            //формирование вектора ip адресов.
            for(std::string line; std::getline(std::cin, line);)
            {
                auto v = split(line, '\t');
                auto ip_str = split(v.at(0), '.');
                ip_t ip;
                for(const auto & s : ip_str)
                    ip.push_back(std::stoi(s));
                ip_pool.push_back(ip);
            }
        } else { //отладка
            ip_pool = {
                {1,255,255,255},
                {1,0,0,0},
                {46,70,2,1},
                {46,3,46,2},
                {1,1,1,46},
                {46,70,4,46},
                {46,70,0,0},
                {46,70,255,255},
                {1,1,3,3},
                {2,3,3,1}
            };
        }

        //вывод списка адресов
        auto ip_list_out = [](auto start, auto stop) {
            for(auto ip = start; ip < stop; ++ip)
            {
                for(auto ip_oct = ip->begin(); ip_oct != ip->end(); ++ip_oct)
                {
                    if (ip_oct != ip->begin())
                        std::cout << ".";
                    std::cout << *ip_oct;
                }
                std::cout << std::endl;
            }
        };

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ip_t>());
        ip_list_out(ip_pool.begin(), ip_pool.end());

        if(debug) std::cout << std::endl << "filter 1:" << std::endl;
        auto res = ip_class::filter(ip_pool, 1);
        ip_list_out(std::get<0>(res), std::get<1>(res));

        if(debug) std::cout << std::endl << "filter 2:" << std::endl;
        res = ip_class::filter(ip_pool, 46, 70);
        ip_list_out(std::get<0>(res), std::get<1>(res));

        if(debug) std::cout << std::endl << "filter 3:" << std::endl;
        auto res_any = ip_class::filter_any(ip_pool, 46);
        ip_list_out(res_any.begin(), res_any.end());
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
