#ifndef KEY_H
#define KEY_H
#include <tuple>
 class Key
 {
 private:
    float xPosition;
    float yPosition;
    bool canDelete;
    int lockId1, lockId2, lockId3;
    bool tripleOpen;

 public:
    Key();
    void setPosition(const float xPos, const float yPos);
    std::tuple<float, float>getPosition() const;
    bool getIfCanDelete() const;
    void markForDeletion();
    std::tuple<int, int>getLockIdsToUnlock() const;
    std::tuple<int, int, int>getTripleLockIdsToUnlock() const;
    void setLockIds(const int id1, const int id2);
    void setLockIds(const int id1, const int id2, const int id3);
    bool isTripleOpener() const;
 };
 #endif