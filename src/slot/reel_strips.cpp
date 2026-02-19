#include "reel_strip.h"
#include <stdexcept>

// --- Reel Implementation ---
Reel::Reel(const ReelStrip& strip, std::size_t start) : strip(strip) {
    if (strip.empty()) throw std::runtime_error("ReelStrip is empty!");
    stopIndex = start % strip.size();
}

std::size_t Reel::spin(std::mt19937& rng) {
    std::uniform_int_distribution<std::size_t> dist(0, strip.size() - 1);
    stopIndex = dist(rng);
    return stopIndex;
}

Symbol Reel::current() const { return strip.at(stopIndex); }
Symbol Reel::above() const { return strip.prev(stopIndex); }
Symbol Reel::below() const { return strip.next(stopIndex); }

std::array<Symbol, 3> Reel::visibleSymbols() const {
    return { above(), current(), below() };
}

void Reel::setStop(std::size_t index) {
    stopIndex = index % strip.size();
}

// --- ReelStrip Implementation ---
const Symbol& ReelStrip::at(std::size_t index) const {
    return symbols[index % symbols.size()];
}

const Symbol& ReelStrip::prev(std::size_t index) const {
    // Correct wraparound for index 0
    return symbols[(index + symbols.size() - 1) % symbols.size()];
}

const Symbol& ReelStrip::next(std::size_t index) const {
    return symbols[(index + 1) % symbols.size()];
}

void ReelStrip::setSymbols(std::vector<Symbol> symbolNeedle) {
    symbols = std::move(symbolNeedle);
}

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