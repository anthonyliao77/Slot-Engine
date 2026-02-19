#ifndef REEL_STRIP_H
#define REEL_STRIP_H

#include <vector>
#include <string>
#include <random>
#include <array>

enum class Symbol {
    // Low Tier (Frequent)
    Cherry, Lemon, Orange, 
    // Mid Tier
    Bell, Bar, 
    // High Tier
    LuckySeven, Diamond, 
    // Special
    Wild, Scatter
};

class ReelStrip;

class Reel {
private:
    const ReelStrip& strip;
    std::size_t stopIndex{0};

public:
    Reel(const ReelStrip& strip, std::size_t start = 0);
    std::size_t spin(std::mt19937& rng);
    
    Symbol current() const;
    Symbol above() const;
    Symbol below() const;
    std::array<Symbol, 3> visibleSymbols() const;

    void setStop(std::size_t index);
};

class ReelStrip {
private:
    std::vector<Symbol> symbols;

public:
    struct ReelStripConfig {
        std::vector<std::string> reelConfig;
    };

    std::size_t size() const { return symbols.size(); }
    bool empty() const { return symbols.empty(); }

    const Symbol& at(std::size_t index) const;
    const Symbol& prev(std::size_t index) const;
    const Symbol& next(std::size_t index) const;

    void setSymbols(std::vector<Symbol> symbolNeedle);

    static ReelStrip fromConfig(const ReelStripConfig& config);
    static Symbol toSymbol(const std::string& name);
    static std::string toString(Symbol symbol);
};

#endif