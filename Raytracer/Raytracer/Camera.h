#pragma once

#include "Math/Math.h"

class Camera
{
public:
    Math::Vector position;
    float drawDistance = INFINITY;

    Camera();

    void SetAspectRatio(const float numerator, const float denomainator);
    void SetFov(const float hfov);
    float HFov() const { return hfov; }
    float VFov() const { return vfov; }

    void LookAtDirection(const Math::Vector& direction);
    void LookAtTarget(const Math::Vector& target);
    void LookAt(const Math::Vector& look, const Math::Vector& up);

    Math::Vector Look() const { return look; }
    Math::Vector Up() const { return up; }

private:
    float hfov = Math::PiHalf;
    float vfov = Math::PiHalf;
    float aspectRatio = 1.f;

    Math::Vector look;
    Math::Vector up;
};
