#ifndef KEY_H
#define KEY_H
#include <tuple>
 class Key
 {
 private:
    float xPosition;
    float yPosition;
    bool canDelete;
    int lockId1, lockId2;

 public:
    Key();
    void setPosition(const float xPos, const float yPos);
    std::tuple<float, float>getPosition() const;
    bool getIfCanDelete() const;
    void markForDeletion();
    std::tuple<int, int>getLockIdsToUnlock() const;
    void setLockIds(const int id1, const int id2);
 };
 #endif