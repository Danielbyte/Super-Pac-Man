#ifndef FLASHINGSYMBOLS_H
#define FLASHINGSYMBOLS_H
#include <tuple>

enum class SymbolType {Fruit, Key, Burger, Shoe, Donut, Cake, Unknown};

class FlashingSymbols
{
private:
    SymbolType symbol;
    float xPosition;
    float yPosition;
    std::tuple<float, float> getPosition() const;
public:
    FlashingSymbols();
    SymbolType getSymbolType() const;
    void setSymbolType(SymbolType type);
    void setPosition(const float x, const float y);
};
#endif