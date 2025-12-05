#pragma once

#include <numeric>

#include "../parser.h"
#include "../views.h"

#include <xutility>
#include <ranges>

namespace aoc::day5
{
    inline auto solve(const bool is_test)
    {
        auto parser = Parser(2025, 5, is_test);

        // Build the ingredients and fresh ranges
        auto fresh_ranges = std::vector<Vector2D<unsigned long long>>();
        auto ingredients = std::vector<unsigned long long>();

        auto section_two = false;
        while (parser.next_line())
        {
            if (parser.get_line().empty())
            {
                section_two = true;
                continue;
            }

            if (section_two)
            {
                const auto ingredient_id = parser.consume_int<unsigned long long>();
                ingredients.push_back(ingredient_id);
            }
            else
            {
                const auto start = parser.consume_int<unsigned long long>();
                parser.consume_char();
                const auto end = parser.consume_int<unsigned long long>();
                fresh_ranges.emplace_back(start, end);
            }
        }

        // Sort and merge overlapping ranges, which is important for part 2
        std::ranges::sort(fresh_ranges, [](const auto& left, const auto& right)
        {
            return left.x < right.x;
        });
        for (auto i = 0u; i < fresh_ranges.size() - 1; ++i)
        {
            auto& range = fresh_ranges[i];
            for (auto j = i + 1; j < fresh_ranges.size(); ++j)
            {
                auto& other_range = fresh_ranges[j];
                if (other_range.x > range.y + 1)
                {
                    // No longer overlapping or adjacent, abort
                    break;
                }

                range.y = std::max(range.y, other_range.y);
                // Mark the other range is invalid
                other_range.y = other_range.x - 1;
            }
        }

        // Remove all invalid ranges
        const auto new_end = std::ranges::remove_if(fresh_ranges, [](const auto& range)
        {
            return range.y < range.x;
        }).begin();
        fresh_ranges.erase(new_end, fresh_ranges.end());

        // Calculate the result for part 1
        const unsigned long long result_p1 = std::ranges::count_if(ingredients, [&](const auto i)
        {
            return std::ranges::any_of(fresh_ranges, [&](const auto& range)
            {
                return i >= range.x && i <= range.y;
            });
        });

        // Calculate part 2
        auto counts = fresh_ranges | std::views::transform([](const auto& range)
        {
            return std::max(range.y - range.x + 1ull, 0ull);
        });
        const auto result_p2 = std::accumulate(counts.begin(), counts.end(), 0ull);

        return std::make_tuple(result_p1, result_p2);
    }
}
