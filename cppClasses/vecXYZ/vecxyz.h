#ifndef VECXYZ_H
#define VECXYZ_H

#include <iostream>

class VecXYZ
{
public:
    VecXYZ();
    VecXYZ(const float xi, const float yi, const float zi);
    void print();
    void it(const unsigned char i);
    float x = 0;
    float y = 0;
    float z = 0;
};

#endif // VECXYZ_H
