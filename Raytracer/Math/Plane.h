#pragma once

#include "Vector.h"

namespace Math
{
    class Plane: public Vector
    {
    public:
        using Vector::Vector;

        Plane() = default;
        Plane(const Vector& point, const Vector& normal);
        Vector Normal() const;
    };

    inline Plane::Plane(const Vector& point, const Vector& normal)
    {
        Vector n = Vector::Normalized(normal);
        Set(n.x, n.y, n.z, (-n) * point);
    }

    inline Vector Plane::Normal() const
    {
        return {x, y, z, 0.f};
    }
}