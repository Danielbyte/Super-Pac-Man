#ifndef LOCK_H
#define LOCK_H
#include <Tuple>
enum class LockType {Vertical, Horizontal, Unknown};

class Lock
{
private:
    float xPosition;
    float yPosition;
    bool isOpen;
    LockType lock_type;
    int lockId;
public:
    Lock();
    std::tuple<float, float>getPosition() const;
    bool getIsOpen() const;
    void OpenLock();
    void setPosition(const float xPos, const float yPos);
    void setLockType(LockType lock_type);
    LockType getLockType() const;
    int getLockId() const;
    void setLockId(int id);
};
#endif
