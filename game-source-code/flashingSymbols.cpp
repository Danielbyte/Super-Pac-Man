#include "flashingSymbols.h"

FlashingSymbols::FlashingSymbols():
xPosition{-100.0f},
yPosition{-100.0f},
symbol{SymbolType::Unknown}
{}

SymbolType FlashingSymbols::getSymbolType() const
{
    return symbol;
}
void FlashingSymbols::setSymbolType(SymbolType type)
{
    symbol = type;
}

std::tuple<float, float> FlashingSymbols::getPosition() const
{
    return {xPosition, yPosition};
}

void FlashingSymbols::setPosition(const float x, const float y)
{
    xPosition = x;
    yPosition = y;
}