#include "vecxyz.h"


VecXYZ::VecXYZ(const float xi, const float yi, const float zi)
{
    x = xi;
    y = yi;
    z = zi;
}

void VecXYZ::print()
{
    std::cout << "x : " << x
              << "    y : " << y
              << "    z : " << z
              << std::endl;
}

void VecXYZ::setValAt(const unsigned char i, const float val)
{
    switch (i) {
    case 0:
        x = val;
        break;
    case 1:
        y = val;
        break;
    case 2:
        z = val;
        break;
    default:
        throw std::out_of_range("VecXYZ has only 3 arguments (0-indexed)");
    }
}

float VecXYZ::getValAt(const unsigned char i)
{
    switch (i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        throw std::out_of_range("VecXYZ has only 3 arguments (0-indexed)");
    }
}
