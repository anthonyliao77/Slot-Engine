#ifndef SPIN_EVALUATION_H
#define SPIN_EVALUATION_H

#include <vector>
#include <array>

#include "reel_strip.h"

class SpinEvaluator {

public:
    // Evaluation of spins
    int evaluate(const std::vector<std::array<Symbol, 3>>& grid);

private:
    // Calculate payout based on symbols
    int getPayout(Symbol symbol);
};

#endif