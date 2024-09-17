#ifndef KEY_H
#define KEY_H
#include <tuple>
 class Key
 {
 private:
    float xPosition;
    float yPosition;
    bool canDelete;

 public:
    Key();
    void setPosition(const float xPos, const float yPos);
    std::tuple<float, float>getPosition() const;
    bool getIfCanDelete() const;
    void markForDeletion();
 };
 #endif