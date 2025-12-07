#pragma once

#include <numeric>

#include "../parser.h"
#include "../views.h"

#include <ranges>

namespace aoc::day7
{
    inline auto solve(const bool is_test)
    {
        auto file = load_input_file(2025, 7, is_test);

        // Build the diagram
        auto diagram = std::vector<long long>();
        auto num_rows = 0ull;
        auto num_columns = 0ull;

        auto line = std::string();
        while (std::getline(file, line))
        {
            diagram.append_range(line | std::views::transform([](const char c)
            {
                return c == 'S' ? 1 : c == '^' ? -1 : 0;
            }));
            ++num_rows;
            num_columns = line.size();
        }

        // Calculate part 1 (and do the groundwork for part 2)
        auto result_p1 = 0ull;
        for (auto row_idx = 0ull; row_idx < num_rows - 1; ++row_idx)
        {
            const auto row = std::span(diagram.begin() + row_idx * num_columns, diagram.begin() + (row_idx + 1) * num_columns);
            auto next_row = std::span(diagram.begin() + (row_idx + 1) * num_columns, diagram.begin() + (row_idx + 2) * num_columns);
            for (auto column_idx = 0ull; column_idx < num_columns; ++column_idx)
            {
                const auto count = row[column_idx];
                if (count < 1)
                {
                    continue;
                }

                if (next_row[column_idx] == -1)
                {
                    // The beam splits, add to the number of paths that fields below can be reached from
                    next_row[column_idx - 1] += count;
                    next_row[column_idx + 1] += count;
                    result_p1 += 1;
                }
                else
                {
                    // Beam isn't split, keep the number of timelines
                    next_row[column_idx] += count;
                }
            }

            const auto row_range = next_row | std::views::transform([](const auto i)
            {
                return i < 0ll ? '^' : i > 0ll ? '0' + static_cast<char>(std::min(i, 9ll)) : '.';
            });
            std::cout << std::string(row_range.begin(), row_range.end()) << "\n";
        }

        // Calculate part 2
        const auto last_row = std::span(diagram.end() - num_columns, diagram.end());
        const auto result_p2 = std::accumulate(last_row.begin(), last_row.end(), 0ull);

        return std::make_tuple(result_p1, result_p2);
    }
}
