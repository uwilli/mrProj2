#ifndef VECXYZ_H
#define VECXYZ_H

#include <iostream>

class VecXYZ
{
public:
    VecXYZ();
    VecXYZ(const float xi, const float yi, const float zi);
    void print();
    float getValAt(const unsigned char i);
    void setValAt(const unsigned char i, const float val);
    float x = 0;
    float y = 0;
    float z = 0;
};

#endif // VECXYZ_H
