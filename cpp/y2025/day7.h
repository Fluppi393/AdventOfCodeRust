#pragma once

#include "../parser.h"
#include "../views.h"

#include <ranges>

namespace aoc::day7
{
    struct Params
    {
        std::string diagram;
        unsigned long long num_lines = 0ull;
        unsigned long long line_width = 0ull;
    };

    inline unsigned long long simulate_beams(const Params& params, std::string prev_line, const unsigned long long start_row, const bool p2)
    {
        auto result = 0ull;
        for (auto row_idx = start_row; row_idx < params.num_lines; ++row_idx)
        {
            auto new_line = params.diagram.substr(row_idx * params.line_width, params.line_width);
            for (auto column_idx = 0ull; column_idx < params.line_width; ++column_idx)
            {
                if (prev_line[column_idx] != 'S')
                {
                    continue;
                }

                if (new_line[column_idx] == '^')
                {
                    result += 1;

                    if (p2)
                    {
                        new_line[column_idx - 1] = 'S';
                        result += simulate_beams(params, new_line, row_idx + 1, p2);
                        new_line[column_idx - 1] = '.';

                        new_line[column_idx + 1] = 'S';
                        result += simulate_beams(params, new_line, row_idx + 1, p2);

                        return result;
                    }

                    new_line[column_idx - 1] = 'S';
                    new_line[column_idx + 1] = 'S';
                }
                else
                {
                    new_line[column_idx] = 'S';
                }
            }

            prev_line = std::move(new_line);
        }

        return result;
    };

    inline auto solve(const bool is_test)
    {
        auto file = load_input_file(2025, 7, is_test);

        // Build the diagram
        auto params = Params();
        auto first_line = std::string();
        auto line = std::string();
        while (std::getline(file, line))
        {
            if (first_line.empty())
            {
                first_line = line;
            }
            else
            {
                params.diagram.append_range(line);
                params.line_width = line.size();
                ++params.num_lines;
            }
        }

        // Calculate part 1
        auto result_p1 = simulate_beams(params, first_line, 0, false);

        // Calculate part 2
        auto result_p2 = simulate_beams(params, first_line, 0, true) + 1;

        return std::make_tuple(result_p1, result_p2);
    }
}
