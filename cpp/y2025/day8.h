#pragma once

#include <numeric>

#include "../parser.h"
#include "../views.h"

#include <ranges>
#include <set>

namespace aoc::day8
{
    struct JunctionBox
    {
        int64_t x;
        int64_t y;
        int64_t z;

        auto distance_sq(const JunctionBox& other) const
        {
            const auto dx = x - other.x;
            const auto dy = y - other.y;
            const auto dz = z - other.z;
            return static_cast<uint64_t>(dx * dx) + static_cast<uint64_t>(dy * dy) + static_cast<uint64_t>(dz * dz);
        }
    };

    struct ConnectionCandidate
    {
        size_t boxes[2];
        uint64_t dist_sq;

        bool operator<(const ConnectionCandidate& other) const
        {
            return dist_sq < other.dist_sq;
        }
    };

    inline auto solve_internal(const bool is_test, const bool is_p2)
    {
        auto file = load_input_file(2025, 8, is_test);

        // Parse all junction boxes
        auto boxes = std::vector<JunctionBox>();

        auto line = std::string();
        while (std::getline(file, line))
        {
            auto pos = line.begin();

            auto new_box = JunctionBox();
            new_box.x = consume_int<int64_t>(pos, line.end());
            consume_char(pos, line.end());
            new_box.y = consume_int<int64_t>(pos, line.end());
            consume_char(pos, line.end());
            new_box.z = consume_int<int64_t>(pos, line.end());
            boxes.push_back(new_box);
        }

        // Build a vector of possible connections
        auto connection_candidates = std::vector<ConnectionCandidate>();
        for (auto box_idx = 0ull; box_idx < boxes.size() - 1; ++box_idx)
        {
            const auto& box = boxes[box_idx];
            for (auto other_box_idx = box_idx + 1; other_box_idx < boxes.size(); ++other_box_idx)
            {
                const auto& other_box = boxes[other_box_idx];

                auto& candidate = connection_candidates.emplace_back();
                candidate.boxes[0] = box_idx;
                candidate.boxes[1] = other_box_idx;
                candidate.dist_sq = box.distance_sq(other_box);
            }
        }

        // Sort connections by distance
        std::ranges::sort(connection_candidates, std::less());

        // Saves circuits as a set of all box indices inside of them
        auto circuits = std::vector<std::set<size_t>>();
        const auto find_circuit = [&](const size_t box_idx)
        {
            return std::ranges::find_if(circuits, [&](const auto& circuit)
            {
                return circuit.contains(box_idx);
            });
        };

        const auto merge_circuits = [&](const ConnectionCandidate& candidate)
        {
            auto circuit = find_circuit(candidate.boxes[0]);
            auto other_circuit = find_circuit(candidate.boxes[1]);
            if (circuit != circuits.end() && other_circuit != circuits.end())
            {
                if (circuit != other_circuit)
                {
                    // Both boxes are in different circuits, we need to merge them
                    circuit->merge(*other_circuit);
                    const auto size = circuit->size();
                    circuits.erase(other_circuit);
                    return size;
                }

                return 0ull;
            }

            if (circuit != circuits.end())
            {
                circuit->insert(candidate.boxes[1]);
                return circuit->size();
            }

            if (other_circuit != circuits.end())
            {
                other_circuit->insert(candidate.boxes[0]);
                return other_circuit->size();
            }

            // Neither box is in a circuit yet, need to create a new one
            auto& new_circuit = circuits.emplace_back();
            new_circuit.insert(candidate.boxes[0]);
            new_circuit.insert(candidate.boxes[1]);
            return new_circuit.size();
        };

        // Make connections and build circuits
        const auto max_num_connections = is_test ? 10ull : 1000ull;
        for (auto i = 0ull; i < max_num_connections || is_p2; ++i)
        {
            const auto& candidate = connection_candidates[i];

            // Move both boxes into the same circuit
            const auto num_boxes_in_circuit = merge_circuits(candidate);

            // Check if we are done with part 2
            if (is_p2 && num_boxes_in_circuit == boxes.size())
            {
                return static_cast<uint64_t>(boxes[candidate.boxes[0]].x * boxes[candidate.boxes[1]].x);
            }
        }

        // Sort circuits by size
        std::ranges::sort(circuits, [](const auto& lhs, const auto& rhs)
        {
            return lhs.size() > rhs.size();
        });

        // Calculate part 1
        auto circuit_sizes = circuits | std::views::take(3) | std::views::transform([](const auto& circuit) { return circuit.size(); });
        return std::accumulate(circuit_sizes.begin(), circuit_sizes.end(), 1ull, std::multiplies());
    }

    inline auto solve(const bool is_test)
    {
        return std::make_tuple(solve_internal(is_test, false), solve_internal(is_test, true));
    }
}
