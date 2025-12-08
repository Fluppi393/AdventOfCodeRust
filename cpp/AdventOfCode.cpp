#include "y2025/day8.h"

int main(int argc, char* argv[])
{
    aoc::assert_result(std::make_tuple(40ull, 25272ull), aoc::day8::solve(true));
    aoc::assert_result(std::make_tuple(54180ull, 25325968ull), aoc::day8::solve(false));
    return 0;
}
