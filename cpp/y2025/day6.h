#pragma once

#include <numeric>

#include "../parser.h"
#include "../views.h"

#include <xutility>
#include <ranges>

namespace aoc::day6
{
    inline auto solve(const bool is_test)
    {
        auto file = load_input_file(2025, 6, is_test);

        // Build a matrix of operants and a vector of operators
        auto matrix = std::vector<unsigned long long>();
        auto operators = std::vector<char>();
        auto char_matrix = std::vector<char>();
        auto num_char_matrix_columns = 0u;
        auto num_char_matrix_digit_rows = 0u;

        auto line = std::string();
        while (std::getline(file, line))
        {
            // Skip initial whitespace
            auto current = std::ranges::find_if(line.begin(), line.end(), [](const auto c) { return !std::isspace(c); });

            // Build the char matrix for p2
            char_matrix.append_range(line);
            num_char_matrix_columns = line.size();

            if (std::isdigit(*current))
            {
                ++num_char_matrix_digit_rows;

                while (current != line.end())
                {
                    const auto end = std::find_if_not(current, line.end(), [](const auto c) { return std::isdigit(c); });
                    const auto string = std::string(current, end);
                    const auto number = std::stoull(string);
                    matrix.push_back(number);

                    // Skip to the next digit
                    current = std::find_if(end, line.end(), [](const auto c) { return std::isdigit(c); });
                }
            }
            else
            {
                operators.append_range(line | std::views::filter([](const auto c) { return !std::isspace(c); }));
            }
        }

        const auto num_columns = operators.size();
        const auto num_rows = matrix.size() / num_columns;

        // Calculate part 1
        auto column_results = std::views::iota(0ull, num_columns) | std::views::transform([&](const auto column)
        {
            const auto op = operators[column];
            auto columns = std::views::iota(0ull, num_rows) | std::views::transform([&](const auto row)
            {
                const auto index = column % num_columns + row * num_columns;
                return matrix[index];
            });

            switch (op)
            {
            case '+':
                return std::accumulate(columns.begin(), columns.end(), 0ull, std::plus());
            case '*':
                return std::accumulate(columns.begin(), columns.end(), 1ull, std::multiplies());
            default:
                assert(false);
                return 0ull;
            }
        });

        // For part two we need a completely different approach, yikes...
        const auto result_p1 = std::accumulate(column_results.begin(), column_results.end(), 0ull);
        const auto num_char_matrix_rows = char_matrix.size() / num_char_matrix_columns;

        auto result_p2 = 0ull;
        auto op = char_matrix.begin() + num_char_matrix_columns * num_char_matrix_digit_rows;
        for (auto column = 0u; column < num_char_matrix_columns; ++column)
        {
            const auto op = char_matrix.begin() +;
            const auto next_op = std::find_if()

            auto numbers = std::vector<unsigned long long>();
            for (; column < num_char_matrix_columns; ++column)
            {
                for (auto row = 0u; row < num_char_matrix_rows; ++row)
                {
                }

                if (column == num_char_matrix_columns - 1 || next_op)
                {
                    break;
                }
            }
        }

        return std::make_tuple(result_p1, result_p2);
    }
}
