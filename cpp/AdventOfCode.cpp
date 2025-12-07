#include "y2025/day7.h"

int main(int argc, char* argv[])
{
    aoc::assert_result(std::make_tuple(21ull, 40ull), aoc::day7::solve(true));
    aoc::assert_result(std::make_tuple(1660ull, 0ull), aoc::day7::solve(false));
    return 0;
}
