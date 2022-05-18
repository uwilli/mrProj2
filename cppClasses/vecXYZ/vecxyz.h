#ifndef VECXYZ_H
#define VECXYZ_H

#include <iostream>

class VecXYZ
{
public:
    VecXYZ();
    VecXYZ(float xi, float yi, float zi);
    void print();
    float x = 0;
    float y = 0;
    float z = 0;
};

#endif // VECXYZ_H
