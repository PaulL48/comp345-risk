#ifndef VEC2F_H
#define VEC2F_H

#include <iostream>

class Vec2f
{
public:
    Vec2f(float x, float y);
    friend std::ostream& operator<<(std::ostream& output, const Vec2f& v);

private:
    float x;
    float y;
};

#endif
