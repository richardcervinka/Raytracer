#include "Camera.h"

inline float ComputeFov(const float fov, const float aspectRatio)
{
    return 2.f * std::atanf(std::tanf(fov / 2.f) / aspectRatio);
}

Camera::Camera():
    look{0.f, 0.f, 1.f, 0.f},
    up{0.f, 1.f, 0.f, 0.f}
{}

void Camera::SetAspectRatio(const float numerator, const float denomainator)
{
    // Invalid arguments.
    if (numerator <= 0 || denomainator <= 0)
    {
        return;
    }
    
    const float aspectRatio = numerator / denomainator;
    const float vfov = ComputeFov(hfov, aspectRatio);

    if (vfov >= Math::Pi)
    {
        return;
    }

    this->aspectRatio = aspectRatio;
    this->vfov = vfov;
}

void Camera::SetFov(const float hfov)
{
    if (hfov >= Math::Pi)
    {
        return;
    }

    const float vfov = ComputeFov(hfov, aspectRatio);
    if (vfov >= Math::Pi)
    {
        return;
    }

    this->hfov = hfov;
    this->vfov = vfov;
}

void Camera::LookAtDirection(const Math::Vector& direction)
{
    if (direction.x == 0.f && direction.z == 0.f)
    {
        // Look in the y axis direction.
        if (direction.y > 0.f)
        {
            up = {1.f, 0.f, 0.f, 0.f};
            look = {0.f, 1.f, 0.f, 0.f};
            return;
        }

        // Look in the -y axis direction.
        if (direction.y < 0.f)
        {
            up = {-1.f, 0.f, 0.f, 0.f};
            look = {0.f, -1.f, 0.f, 0.f};
            return;
        }

        // Invalid argument.
        return;
    }

    const auto right = Math::Vector::Cross(direction, {0.f, 1.f, 0.f, 0.f});
    up = Math::Vector::Normalized(Math::Vector::Cross(right, direction));
    look = Math::Vector::Normalized(direction);
}

void Camera::LookAtTarget(const Math::Vector& target)
{
    LookAtDirection(target - position);
}

void Camera::LookAt(const Math::Vector& look, const Math::Vector& up)
{
    this->look = Math::Vector::Normalized(look);
    this->up = Math::Vector::Normalized(up);
}