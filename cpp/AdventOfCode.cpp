#include "y2025/day4.h"
#include "y2025/day5.h"

int main(int argc, char* argv[])
{
    aoc::assert_result(std::make_tuple(3ull, 14ull), aoc::day5::solve(true));
    aoc::assert_result(std::make_tuple(617ull, 0ull), aoc::day5::solve(false));
    return 0;
}
