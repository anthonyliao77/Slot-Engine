#include "spin_evaluation.h"
#include <stdexcept>

// =============================================================================
// PAYOUT LOGIC
// Defines the "Paytable" values for symbol combinations.
// =============================================================================

/**
 * @brief Returns the credit value for a specific symbol match.
 * Uses fall-through cases to group symbols into rarity tiers.
 */
int SpinEvaluator::getPayout(Symbol symbol) {
    int totalPayout = 0;

    switch(symbol) {
        // Low Tier: Frequent, small wins
        case Symbol::Cherry:
        case Symbol::Lemon:
        case Symbol::Orange:
            totalPayout = 10;
            break;

        // Mid Tier: Moderate rarity
        case Symbol::Bell:
        case Symbol::Bar:
            totalPayout = 20;
            break;

        // High Tier: Rare "Big Wins"
        case Symbol::LuckySeven:
        case Symbol::Diamond:
            totalPayout = 50;
            break;
        
        // Special Tier: Jackpots or Bonus triggers
        case Symbol::Wild:
        case Symbol::Scatter:
            totalPayout = 100;
            break;

        default:
            totalPayout = 0;
            break;
    }

    return totalPayout;
}

// =============================================================================
// EVALUATION LOGIC
// Analyzes the grid to detect winning patterns (Paylines).
// =============================================================================

/**
 * @brief Scans the result grid for winning combinations.
 * Currently checks the central horizontal payline.
 * * Index mapping for a 3-column grid:
 * [0][0] [1][0] [2][0]  <- Top Row
 * [0][1] [1][1] [2][1]  <- Middle Row (Active Payline)
 * [0][2] [1][2] [2][2]  <- Bottom Row
 */
int SpinEvaluator::evaluate(const std::vector<std::array<Symbol, 3>>& grid) {
    int totalWin = 0;

    // Safety check: Ensure we have at least 3 reels to evaluate a line
    if (grid.size() < 3) return 0;

    /**
     * @line Middle Row Win Check
     * Logic: If Reel 0, 1, and 2 all share the same symbol at index [1].
     */
    if (grid[0][1] == grid[1][1] && grid[1][1] == grid[2][1]) {
        totalWin += getPayout(grid[0][1]);
    }

    return totalWin;
}