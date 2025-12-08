#pragma once

#include <iostream>

#include "vector_2d.h"

namespace aoc
{
    inline bool default_predicate(const char)
    {
        return true;
    }

    inline auto load_input_file(const int year, const int day, const bool is_test)
    {
        const auto filename =
            std::filesystem::current_path().parent_path() /
            std::format("input/{}/day{}{}.txt", year, day, is_test ? "_test" : "");

        return std::ifstream(filename);
    }

    // Consumes the next character and returns it if available
    std::optional<char> consume_char(auto&& first, auto&& last, auto&& predicate)
    {
        if (first != last && predicate(*first))
        {
            const auto c = *first;
            ++first;
            return c;
        }

        return std::nullopt;
    }

    auto consume_char(auto&& first, auto&& last)
    {
        return consume_char(first, last, default_predicate);
    }

    auto consume_string(auto&& first, auto&& last, auto&& predicate = default_predicate)
    {
        const auto start = first;
        while (const auto c = consume_char(first, last, predicate))
        {
        }
        return std::string_view(start, first);
    }

    // Consumes all consecutive digits and returns them as an int
    template <typename T>
    auto consume_int(auto&& first, auto&& last)
    {
        const auto string = consume_string(first, last, [](const auto c)
        {
            return std::isdigit(c);
        });

        const auto chars = std::string(string);

        if constexpr (std::is_same_v<T, int>)
        {
            return std::stoi(chars);
        }
        else if constexpr (std::is_same_v<T, unsigned int>)
        {
            return std::stoul(chars);
        }
        else if constexpr (std::is_same_v<T, long long>)
        {
            return std::stoll(chars);
        }
        else if constexpr (std::is_same_v<T, unsigned long long>)
        {
            return std::stoull(chars);
        }
    }

    inline auto index_to_coord(const int index, const Vector2D<int>& size)
    {
        return Vector2D(index % size.x, index / size.x);
    }

    inline auto coord_to_index(const Vector2D<int>& coord, const Vector2D<int>& size)
    {
        return coord.x + coord.y * size.x;
    }

    inline bool is_valid_coord(const Vector2D<int>& coord, const Vector2D<int>& size)
    {
        return coord.x >= 0 && coord.x < size.x && coord.y >= 0 && coord.y < size.y;
    }

    template <typename T>
    void assert_result(const T& expected, const T& actual)
    {
        if (expected != actual)
        {
            std::cout << std::format("Expected {}, got {}\n", expected, actual);
        }
    }

    template <typename T1, typename T2>
    void assert_result(const std::tuple<T1, T2>& expected, const std::tuple<T1, T2>& actual)
    {
        if (expected != actual)
        {
            std::cout << std::format("Expected ({},{}), got ({},{})\n", std::get<0>(expected), std::get<1>(expected), std::get<0>(actual), std::get<1>(actual));
        }
    }
}
