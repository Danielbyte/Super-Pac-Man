#ifndef LOCK_H
#define LOCK_H
#include <Tuple>

class Lock
{
private:
    float xPosition;
    float yPosition;
    bool isOpen;
public:
    Lock();
    std::tuple<float, float>getPosition() const;
    bool getIsOpen() const;
    void OpenLock();
};
#endif
