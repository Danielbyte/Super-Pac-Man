#ifndef KEY_H
#define KEY_H
#include <tuple>
 class Key
 {
 private:
    float xPosition;
    float yPosition;

 public:
    Key();
    void setPosition(float xPos, float yPos);
    std::tuple<float, float>getPosition() const;
 };
 #endif