#ifndef REEL_STRIP_H
#define REEL_STRIP_H

#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <array>

enum class Symbol {
    Cherry, // 1kr
    Lemon, // 1kr
    Bar, // 3kr
    LuckySeven, // 20
    Diamond, // 15
    Wild, // 25
    Scatter // 10
};

class Reel {
    const ReelStrip& strip;
    std::size_t stopIndex{0};

public:

    // Saving reelstrip for it to be read  
    Reel(const ReelStrip& strip, std::size_t start = 0)
    : strip(strip), stopIndex(start % strip.size()) {
        if (strip.empty()) {
            throw std::runtime_error("Reel is empty, require legal reel");
        }
    }
    // randomly choosing reelstrip
    std::size_t spin(std::mt19937& rng) {
        std::uniform_int_distribution<std::size_t> dist(1, strip.size());
        const std::size_t advance = dist(rng);

        stopIndex = (stopIndex + advance) % strip.size();
        return stopIndex;

    }
    // Get all visible symbols 
    Symbol current() const {return strip.at(stopIndex);}
    Symbol above() const {return strip.prev(stopIndex);}
    Symbol below() const {return strip.next(stopIndex);}

    // return all the chosen strips
    std::array<Symbol, 3> visibleSymbols() const {
        return { above(), current(), below() };
    }

    void setStop(std::size_t index) {
        stopIndex = index % strip.size();
    }

};

class ReelStrip {
private:
    std::vector<Symbol> symbols;

public:
    /*
    * Get size method
    */
    std::size_t size() const { return symbols.size();}
    bool empty() const {return symbols.empty();}

    /*
    * Get methods for indices
    */
    const Symbol& at(std::size_t index) const {return symbols[index % symbols.size()];}

    const Symbol& prev(std::size_t index) const {
        if(symbols.empty()) throw std::runtime_error("ReelStrip::prev called an empty strip");
        const size_t len = symbols.size();
        return symbols[(index % len) - 1];}

    const Symbol& next(std::size_t index) const {
        if(symbols.empty()) throw std::runtime_error("ReelStrip::next called an empty strip");
        const size_t len = symbols.size();
        return symbols[(index % len) + 1];}

    /*
    * Inspecting symbol frequency
    */
    std::size_t count(Symbol symbolTarget) const {
        int counter = 0;
        for (Symbol sym : symbols) {
            if (sym == symbolTarget) {counter++;} 
        }
        return counter;
    }

    /*
    * Helper methods that inserts live data
    * ReelStrip:: setSymbols belongs to that class
    */
    void ReelStrip::setSymbols(std::vector<Symbol> symbolNeedle) {
        symbols = std::move(symbolNeedle);
    }

    struct ReelStripConfig {
        std::vector<std::string> reelConfig;
    };

    static ReelStrip fromConfig(const ReelStripConfig& stringSymbols) {

        if(stringSymbols.reelConfig.empty()) {throw std::runtime_error("Given reel strip is empty!!");}
        
        std::vector<Symbol> tmp;
        tmp.reserve(stringSymbols.reelConfig.size());
        
        for(auto& reel : stringSymbols.reelConfig) {    
            tmp.push_back(toSymbol(reel));
        }

        // insert to symbols vec
        ReelStrip result;
        result.setSymbols(std::move(tmp));

        return result;
    }
    
    // converting string to symbol
    static Symbol toSymbol(const std::string& name) {
        if (name == "Cherry") return Symbol::Cherry;
        if (name == "Lemon") return Symbol::Lemon;
        if (name == "Bar") return Symbol::Bar;
        if (name == "LuckySeven") return Symbol::LuckySeven;
        if (name == "Diamond") return Symbol::Diamond;
        if (name == "Wild") return Symbol::Wild;
        if (name == "Scatter") return Symbol::Scatter;
        throw std::runtime_error("Unknown symbol name: " + name);
    }

    /*
    * Dump methods for testing
    */
    std::string toString(Symbol symbol) const {
        switch (symbol) {
        case Symbol::Cherry: return "Cherry";
        case Symbol::Lemon: return "Lemon";
        case Symbol::Bar: return "Bar";
        case Symbol::LuckySeven: return "LuckySeven";
        case Symbol::Diamond: return "Diamond";
        case Symbol::Wild: return "Wild";
        case Symbol::Scatter: return "Scatter";
        }
        return "Unknown";
    }
};

#endif