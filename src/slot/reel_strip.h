#ifndef REEL_STRIP_H
#define REEL_STRIP_H

#include <vector>
#include <string>

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
    const Symbol& prev(std::size_t index) const {return symbols[(index % symbols.size()) - 1];}
    const Symbol& next(std::size_t index) const {return symbols[(index % symbols.size()) + 1];}

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
    */
    void setSymbols(std::vector<Symbol> symbols);
    // static ReelStrip fromConfig(const ReelStripConfig&) {}

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