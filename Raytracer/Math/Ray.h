#pragma once

#include "Vector.h"

namespace Math
{
    class Ray
    {
    public:
        const Vector origin;
        const Vector direction;

        Ray(const Vector& origin_, const Vector& direction_):
            origin{origin_},
            direction{Vector::Normalized(direction_)}
        { }
    };
}