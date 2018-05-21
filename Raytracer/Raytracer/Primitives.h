#pragma once

#include "Math/Math.h"

// Output of the Primitive::Raycast() call.
struct RaycastSample
{
    Math::Vector position;
    Math::Vector normal;
};

// Interface for all renderable primitives.
class Primitive
{
public:
    Math::Vector position;
    Math::Vector rotation;
    int materialId = 0;

    virtual ~Primitive() = default;

    // Apply precomputations before the rendering.
    virtual void Transform() const { };

    virtual float Raycast(const Math::Ray& ray, const float maxDistance, RaycastSample& output) const = 0;
};

class Triangle: public Primitive
{
public:
    Math::Vector v0, v1, v2;

    virtual void Transform() const override;
    virtual float Raycast(const Math::Ray&, const float, RaycastSample&) const override;

private:
    // Transformed vertices.
    mutable Math::Vector w0, w1, w2;
};

class Sphere: public Primitive
{
public:
    float radius = 0.f;

    virtual float Raycast(const Math::Ray&, const float, RaycastSample&) const override;
};

class Plane: public Primitive
{
public:
    virtual void Transform() const override;
    virtual float Raycast(const Math::Ray&, const float, RaycastSample&) const override;

private:
    mutable Math::Plane p;
};