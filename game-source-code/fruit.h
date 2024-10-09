#ifndef FRUIT_H
#define FRUIT_H
#include <tuple>
#include "stopWatch.h"

class Fruit
{
private:
 float xPosition;
 float yPosition;
 bool canDelete;
 bool isSuperPellet;
 bool isPowerPellet;
 bool isStar;
 StopWatch lifetime;
public:
    Fruit();
    void setPosition(const float xPos,const float yPos);
    void markForDeletion();
    bool getIfCanDelete() const;
    std::tuple<float, float>getPosition() const;
    bool getIsSuperPellet() const;
    bool getIsPowerPellet() const;
    bool getIsStar() const;
    void markAsPowerPellet();
    void markAsSuperPellet();
    void markAsStar();
    float getLifeTime();
};
#endif