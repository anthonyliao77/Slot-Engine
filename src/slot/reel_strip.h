#ifndef REEL_STRIP_H
#define REEL_STRIP_H

#include <vector>
#include <string>
#include <random>
#include <array>

/**
 * @brief Enum representing all possible symbols in the slot machine.
 * Scoped as 'class' to prevent name collisions and improve type safety.
 */
enum class Symbol {
    // Low Tier (Frequent payouts)
    Cherry, Lemon, Orange, 
    // Mid Tier
    Bell, Bar, 
    // High Tier (Jackpot symbols)
    LuckySeven, Diamond, 
    // Special (Game mechanics)
    Wild, Scatter
};

// Forward declaration to allow Reel to hold a reference to ReelStrip
class ReelStrip;

/**
 * @class Reel
 * @brief Represents an active, stateful reel in the game.
 * * Tracks where the reel has stopped and provides a "window" view 
 * of the symbols visible to the player.
 */
class Reel {
private:
    const ReelStrip& strip;      ///< Reference to the static symbol data
    std::size_t stopIndex{0};    ///< Current position on the strip

public:
    /**
     * @param strip The underlying ReelStrip data (must outlive the Reel).
     * @param start Initial stop index on the strip.
     */
    Reel(const ReelStrip& strip, std::size_t start = 0);

    /**
     * @brief Randomizes the stopIndex using the provided RNG.
     * @return The new stopIndex.
     */
    std::size_t spin(std::mt19937& rng);
    
    // Viewport Methods
    Symbol current() const;                      ///< Symbol at the center payline
    Symbol above() const;                        ///< Symbol in the top row
    Symbol below() const;                        ///< Symbol in the bottom row
    std::array<Symbol, 3> visibleSymbols() const; ///< Snapshot of {Top, Center, Bottom}

    /** @brief Manually set the stop position for testing or logic overrides. */
    void setStop(std::size_t index);
};

/**
 * @class ReelStrip
 * @brief Container for the static symbol sequence.
 * * Provides utility methods for circular navigation (wrapping around 
 * from the end of the strip to the beginning).
 */
class ReelStrip {
private:
    std::vector<Symbol> symbols;

public:
    /** @brief Simple wrapper for string-based configuration data. */
    struct ReelStripConfig {
        std::vector<std::string> reelConfig;
    };

    // Metadata
    std::size_t size() const { return symbols.size(); }
    bool empty() const { return symbols.empty(); }

    // Circular Navigation Logic
    const Symbol& at(std::size_t index) const;   ///< Get symbol at index (with wrap-around)
    const Symbol& prev(std::size_t index) const; ///< Get symbol "above" current index
    const Symbol& next(std::size_t index) const; ///< Get symbol "below" current index

    /** @brief Updates the internal symbol vector using move semantics. */
    void setSymbols(std::vector<Symbol> symbolNeedle);

    // Static Utilities (Factory and Conversion)
    /** @brief Creates a ReelStrip from a list of strings (e.g., from a JSON config). */
    static ReelStrip fromConfig(const ReelStripConfig& config);
    
    /** @brief Helper to convert string names to Symbol enum values. */
    static Symbol toSymbol(const std::string& name);
    
    /** @brief Helper to convert Symbol enum values back to strings for logging/UI. */
    static std::string toString(Symbol symbol);
};

#endif