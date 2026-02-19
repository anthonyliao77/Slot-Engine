#ifndef SPIN_EVALUATION_H
#define SPIN_EVALUATION_H

#include <vector>
#include <array>
#include "reel_strip.h"

/**
 * @class SpinEvaluator
 * @brief The "Math Engine" of the slot machine.
 * * This class is responsible for analyzing the final state of the reels (the grid)
 * and calculating the total payout based on the game's rules and paytables.
 */
class SpinEvaluator {

public:
    /**
     * @brief Evaluates the entire result grid for winning combinations.
     * * @param grid A 2D structure where each element is a reel (column) 
     * containing 3 visible symbols {Top, Middle, Bottom}.
     * Example: grid[0] is the first reel, grid[0][1] is the center symbol.
     * * @return The total number of credits/coins won in the spin.
     */
    int evaluate(const std::vector<std::array<Symbol, 3>>& grid);

private:
    /**
     * @brief Core Paytable Lookup.
     * * Translates a specific symbol or combination into a numeric reward.
     * This is where the mathematical "weight" of each symbol is defined.
     * * @param symbol The symbol to check against the paytable.
     * @return The payout value for a 3-of-a-kind match of this symbol.
     */
    int getPayout(Symbol symbol);
};

#endif