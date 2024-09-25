#ifndef FRUIT_H
#define FRUIT_H
#include <tuple>

class Fruit
{
private:
 float xPosition;
 float yPosition;
 bool canDelete;
 bool isSuperPellet;
 bool isPowerPellet;
public:
    Fruit();
    void setPosition(const float xPos,const float yPos);
    void markForDeletion();
    bool getIfCanDelete() const;
    std::tuple<float, float>getPosition() const;
    bool getIsSuperPellet() const;
    bool getIsPowerPellet() const;
    void markAsPowerPellet();
    void markAsSuperPellet();
};
#endif