#include "reel_strip.h"
#include <stdexcept>

// =============================================================================
// REEL IMPLEMENTATION
// Handles the state of a single spinning reel (the "stop" position).
// =============================================================================

/**
 * @brief Construct a new Reel.
 * @param strip The physical sequence of symbols this reel uses.
 * @param start The initial position (defaults to 0).
 */
Reel::Reel(const ReelStrip& strip, std::size_t start) : strip(strip) {
    if (strip.empty()) throw std::runtime_error("ReelStrip is empty!");
    stopIndex = start % strip.size();
}

/**
 * @brief Simulates a physical spin using a Random Number Generator.
 * @param rng A Mersenne Twister engine passed from the engine or Python.
 * @return The new stop index after the spin.
 */
std::size_t Reel::spin(std::mt19937& rng) {
    std::uniform_int_distribution<std::size_t> dist(0, strip.size() - 1);
    stopIndex = dist(rng);
    return stopIndex;
}

// Simple accessors for the "Window" (the symbols the player sees)
Symbol Reel::current() const { return strip.at(stopIndex); }
Symbol Reel::above() const   { return strip.prev(stopIndex); }
Symbol Reel::below() const   { return strip.next(stopIndex); }

/**
 * @brief Returns the 3 symbols currently visible on this reel.
 * Format: {Top, Middle, Bottom}
 */
std::array<Symbol, 3> Reel::visibleSymbols() const {
    return { above(), current(), below() };
}

/**
 * @brief Manually force the reel to a specific position.
 * Useful for unit testing or recreating a specific game state from a log.
 */
void Reel::setStop(std::size_t index) {
    stopIndex = index % strip.size();
}

// =============================================================================
// REELSTRIP IMPLEMENTATION
// Handles the static layout of symbols (the "physical" strip).
// =============================================================================

/**
 * @brief Returns symbol at index with safety wrap-around logic.
 */
const Symbol& ReelStrip::at(std::size_t index) const {
    return symbols[index % symbols.size()];
}

/**
 * @brief Wraps backward to the previous symbol.
 * Uses (index + size - 1) to prevent negative results with unsigned size_t.
 */
const Symbol& ReelStrip::prev(std::size_t index) const {
    return symbols[(index + symbols.size() - 1) % symbols.size()];
}

/**
 * @brief Wraps forward to the next symbol.
 */
const Symbol& ReelStrip::next(std::size_t index) const {
    return symbols[(index + 1) % symbols.size()];
}

/**
 * @brief Replaces current strip symbols. 
 * Uses std::move to efficiently transfer large vectors from Python/Config.
 */
void ReelStrip::setSymbols(std::vector<Symbol> symbolNeedle) {
    symbols = std::move(symbolNeedle);
}

/**
 * @brief Factory method: Converts a list of strings into a ReelStrip object.
 * @throw std::runtime_error if the config contains invalid symbol names.
 */
ReelStrip ReelStrip::fromConfig(const ReelStripConfig& config) {
    if(config.reelConfig.empty()) throw std::runtime_error("Config is empty!");
    
    std::vector<Symbol> tmp;
    for(const auto& name : config.reelConfig) {
        tmp.push_back(toSymbol(name));
    }
    
    ReelStrip rs;
    rs.setSymbols(std::move(tmp));
    return rs;
}

// Creates a fair and weighted reel strip
std::vector<Symbol> createReelStrip(const std::map<Symbol, int>& strip) {
    std::vector<Symbol> fullStrip;

    // every symbol has weighted connected to their rarity
    for (auto const& [symbol, weight] : strip) {
        for (int i = 0; i < weight; i++) {
            fullStrip.push_back(symbol);
        }
    }

    std::shuffle(fullStrip.begin(), fullStrip.end(), std::mt19937{std::random_device{}()});

    return fullStrip;
}

/**
 * @brief Map: String name -> Enum value.
 */
Symbol ReelStrip::toSymbol(const std::string& name) {
    if (name == "Cherry")     return Symbol::Cherry;
    if (name == "Lemon")      return Symbol::Lemon;
    if (name == "Orange")     return Symbol::Orange;
    if (name == "Bell")       return Symbol::Bell;
    if (name == "Bar")        return Symbol::Bar;
    if (name == "LuckySeven") return Symbol::LuckySeven;
    if (name == "Diamond")    return Symbol::Diamond;
    if (name == "Wild")       return Symbol::Wild;
    if (name == "Scatter")    return Symbol::Scatter;
    throw std::runtime_error("Unknown symbol: " + name);
}

/**
 * @brief Map: Enum value -> String name (for Debugging/UI).
 */
std::string ReelStrip::toString(Symbol symbol) {
    switch (symbol) {
        case Symbol::Cherry:     return "Cherry";
        case Symbol::Lemon:      return "Lemon";
        case Symbol::Orange:     return "Orange";
        case Symbol::Bell:       return "Bell";
        case Symbol::Bar:        return "Bar";
        case Symbol::LuckySeven: return "LuckySeven";
        case Symbol::Diamond:    return "Diamond";
        case Symbol::Wild:       return "Wild";
        case Symbol::Scatter:    return "Scatter";
        default:                 return "Unknown";
    }
}