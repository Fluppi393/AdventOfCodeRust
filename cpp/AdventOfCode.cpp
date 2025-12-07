#include "y2025/day7.h"

int main(int argc, char* argv[])
{
    aoc::assert_result(std::make_tuple(21ull, 40ull), aoc::day7::solve(true));
    aoc::assert_result(std::make_tuple(1660ull, 305999729392659ull), aoc::day7::solve(false));
    return 0;
}
