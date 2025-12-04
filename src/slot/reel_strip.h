#ifndef REEL_STRIP_H
#define REEL_STRIP_H

#include <vector>
#include <string>
#include <stdexcept>

enum class Symbol {
    Cherry,
    Lemon,
    Orange,
    Plum,
    Watermelon,
    Grape,
    Apple,
    Bell,
    Bar,
    DoubleBar,
    TripleBar,
    Horseshoe,
    FourLeafClover,
    LuckySeven,
    Diamond,
    Ruby,
    Sapphire,
    Emerald,
    GoldCoin,
    SilverCoin,
    BronzeCoin,
    Star,
    Crown,
    Wild,
    Scatter
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
        if (name == "Orange") return Symbol::Orange;
        if (name == "Plum") return Symbol::Plum;
        if (name == "Watermelon") return Symbol::Watermelon;
        if (name == "Grape") return Symbol::Grape;
        if (name == "Apple") return Symbol::Apple;
        if (name == "Bell") return Symbol::Bell;
        if (name == "Bar") return Symbol::Bar;
        if (name == "DoubleBar") return Symbol::DoubleBar;
        if (name == "TripleBar") return Symbol::TripleBar;
        if (name == "Horseshoe") return Symbol::Horseshoe;
        if (name == "FourLeafClover") return Symbol::FourLeafClover;
        if (name == "LuckySeven") return Symbol::LuckySeven;
        if (name == "Diamond") return Symbol::Diamond;
        if (name == "Ruby") return Symbol::Ruby;
        if (name == "Sapphire") return Symbol::Sapphire;
        if (name == "Emerald") return Symbol::Emerald;
        if (name == "GoldCoin") return Symbol::GoldCoin;
        if (name == "SilverCoin") return Symbol::SilverCoin;
        if (name == "BronzeCoin") return Symbol::BronzeCoin;
        if (name == "Star") return Symbol::Star;
        if (name == "Crown") return Symbol::Crown;
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
        case Symbol::Orange: return "Orange";
        case Symbol::Plum: return "Plum";
        case Symbol::Watermelon: return "Watermelon";
        case Symbol::Grape: return "Grape";
        case Symbol::Apple: return "Apple";
        case Symbol::Bell: return "Bell";
        case Symbol::Bar: return "Bar";
        case Symbol::DoubleBar: return "DoubleBar";
        case Symbol::TripleBar: return "TripleBar";
        case Symbol::Horseshoe: return "Horseshoe";
        case Symbol::FourLeafClover: return "FourLeafClover";
        case Symbol::LuckySeven: return "LuckySeven";
        case Symbol::Diamond: return "Diamond";
        case Symbol::Ruby: return "Ruby";
        case Symbol::Sapphire: return "Sapphire";
        case Symbol::Emerald: return "Emerald";
        case Symbol::GoldCoin: return "GoldCoin";
        case Symbol::SilverCoin: return "SilverCoin";
        case Symbol::BronzeCoin: return "BronzeCoin";
        case Symbol::Star: return "Star";
        case Symbol::Crown: return "Crown";
        case Symbol::Wild: return "Wild";
        case Symbol::Scatter: return "Scatter";
        }
        return "Unknown";
    }
};

#endif