#include "vecxyz.h"


VecXYZ::VecXYZ(float xi, float yi, float zi)
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
