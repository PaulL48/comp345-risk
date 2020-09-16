#include "Vec2f.h"

#include <iostream>

Vec2f::Vec2f(float x, float y) : x(x),
                                 y(y)
{
}

std::ostream &operator<<(std::ostream &output, const Vec2f &v)
{
    output << "{" << v.x << ", " << v.y << "}";
    return output;
}
