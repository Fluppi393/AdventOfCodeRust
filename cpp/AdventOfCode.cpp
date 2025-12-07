#include "y2025/day6.h"

int main(int argc, char* argv[])
{
    aoc::assert_result(std::make_tuple(4277556ull, 0ull), aoc::day6::solve(true));
    aoc::assert_result(std::make_tuple(0ull, 0ull), aoc::day6::solve(false));
    return 0;
}
