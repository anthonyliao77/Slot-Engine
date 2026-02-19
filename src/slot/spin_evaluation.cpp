#include "spin_evaluation.h"
#include <stdexcept>

// Next is to build a minimal spin evaluator that owns several Reels, runs one spin with a fixed RNG seed, 
// and totals payouts for a sample payline to unit-test full spin flow.

// ------- Payout logic --------

int SpinEvaluator::getPayout(Symbol symbol) {
    
    int totalPayout = 0;

    switch(symbol) {
    
    // common value
    case Symbol::Cherry:
    case Symbol::Lemon:
    case Symbol::Orange:
        totalPayout = 10;
        break;

    // uncommon value
    case Symbol::Bell:
    case Symbol::Bar:
        totalPayout = 20;
        break;

    // rare value
    case Symbol::LuckySeven:
    case Symbol::Diamond:
        totalPayout = 50;
        break;
    
    // epic value
    case Symbol::Wild:
    case Symbol::Scatter:
        totalPayout = 100;
        break;

    default:
        totalPayout = 0;
        break;
    }

    return totalPayout;
};

// ------- Evaluation ------------

int SpinEvaluator::evaluate(const std::vector<std::array<Symbol, 3>>& grid) {
    int totalWin = 0;

    // Middle row: L, M, R
    // Spun 3 same symbols = win
    if (grid[0][1] == grid[1][1] && grid[1][1] == grid[2][1]) {
        totalWin += getPayout(grid[0][1]);
    }

    return totalWin;
};