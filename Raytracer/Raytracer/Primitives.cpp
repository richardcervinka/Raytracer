#include "Primitives.h"
#include "Math/Math.h"

// Triangle.

void Triangle::Transform() const
{
    const auto transformations = Math::Matrix::Transformations(position, {1.f, 1.f, 1.f, 0.f}, rotation);
    w0 = transformations.Transform(v0);
    w1 = transformations.Transform(v1);
    w2 = transformations.Transform(v2);
}

float Triangle::Raycast(const Math::Ray& ray, const float maxDistance, RaycastSample& output) const
{
    // Normal vector.
    const auto normal = Math::Vector::Normal(w1 - w0, w2 - w0);

    // Backface culling.
    if (ray.direction * normal >= 0.f)
    {
        return INFINITY;
    }

    // Intersection distance.
    const float t = Math::IntersectTriangle(ray, w0, w1, w2);

    if (t >= maxDistance)
    {
        return INFINITY;
    }

    // Set output values.
    output.position = ray.origin + ray.direction * t;
    output.normal = normal;

    return t;
}

// Sphere.

float Sphere::Raycast(const Math::Ray& ray, const float maxDistance, RaycastSample& output) const
{
    // Intersection distance.
    const float t = Math::IntersectSphere(ray, position, radius);

    if (t >= maxDistance)
    {
        return INFINITY;
    }

    const auto point = ray.origin + ray.direction * t;
    const auto normal = Math::Vector::Normalized(point - position);

    // Backface culling.
    if (ray.direction * normal >= 0.f)
    {
        return INFINITY;
    }

    // Set output values.
    output.position = point;
    output.normal = normal;

    return t;
}

// Plane.

void Plane::Transform() const
{
    const auto transformations = Math::Matrix::Rotation(rotation);
    const auto normal = transformations.Transform({0.f, 1.f, 0.f, 0.f});
    p = Math::Plane(position, normal);
}

float Plane::Raycast(const Math::Ray& ray, const float maxDistance, RaycastSample& output) const
{
    //const Math::Plane plane(position, normal);
    const auto normal = p.Normal();

    // Backface culling.
    if (ray.direction * normal >= 0.f)
    {
        return INFINITY;
    }

    // Intersection distance.
    const float t = Math::IntersectPlane(ray, p);

    if (t >= maxDistance)
    {
        return INFINITY;
    }

    // Set output values.
    output.position = ray.origin + ray.direction * t;
    output.normal = normal;

    return t;
}