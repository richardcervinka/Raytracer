#pragma once

#include <cmath>

namespace Math
{
    inline void Vector::Set(const float x_, const float y_, const float z_, const float w_) noexcept
    {
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }

    inline float Vector::operator*(const Vector& r) const noexcept
    {
        return (x * r.x) + (y * r.y) + (z * r.z) + (w * r.w);
    }

    inline Vector& Vector::operator+=(const Vector& r) noexcept
    {
        Set(x + r.x, y + r.y, z + r.z, w + r.w);
        return *this;
    }

    inline Vector Vector::operator+(const Vector& r) const noexcept
    {
        return {x + r.x, y + r.y, z + r.z, w + r.w};
    }

    inline Vector& Vector::operator-=(const Vector& r) noexcept
    {
        Set(x - r.x, y - r.y, z - r.z, w - r.w);
        return *this;
    }

    inline Vector Vector::operator-(const Vector& r) const noexcept
    {
        return {x - r.x, y - r.y, z - r.z, w - r.w};
    }

    inline Vector& Vector::operator*=(const float value) noexcept
    {
        Set(x * value, y * value, z * value, w * value);
        return *this;
    }

    inline Vector Vector::operator*(const float value) const noexcept
    {
        return {x * value, y * value, z * value, w * value};
    }

    inline Vector& Vector::operator/=(const float value) noexcept
    {
        Set(x / value, y / value, z / value, w / value);
        return *this;
    }

    inline Vector Vector::operator/(const float value) const noexcept
    {
        return {x / value, y / value, z / value, w / value};
    }

    inline Vector Vector::operator-() const noexcept
    {
        return {-x, -y, -z, -w};
    }

    inline bool Vector::operator==(const Vector& r) const noexcept
    {
        return (x == r.x) && (y == r.y) && (z == r.z) && (w == r.w);
    }

    inline bool Vector::operator!=(const Vector& r) const noexcept
    {
        return (x != r.x) || (y != r.y) || (z != r.z) || (w != r.w);
    }

    inline bool Vector::operator==(const float length) const noexcept
    {
        return LengthSq() == (length * length);
    }

    inline bool Vector::operator!=(const float length) const noexcept
    {
        return LengthSq() != (length * length);
    }

    inline bool Vector::operator>(const float length) const noexcept
    {
        return LengthSq() > (length * length);
    }

    inline bool Vector::operator>=(const float length) const noexcept
    {
        return LengthSq() >= (length * length);
    }

    inline bool Vector::operator<(const float length) const noexcept
    {
        return LengthSq() < (length * length);
    }

    inline bool Vector::operator<=(const float length) const noexcept
    {
        return LengthSq() <= (length * length);
    }

    inline bool Vector::operator>(const Vector& r) const noexcept
    {
        return LengthSq() > r.LengthSq();
    }

    inline bool Vector::operator>=(const Vector& r) const noexcept
    {
        return LengthSq() >= r.LengthSq();
    }

    inline bool Vector::operator<(const Vector& r) const noexcept
    {
        return LengthSq() < r.LengthSq();
    }

    inline bool Vector::operator<=(const Vector& r) const noexcept
    {
        return LengthSq() <= r.LengthSq();
    }

    inline float Vector::Length() const noexcept
    {
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    inline float Vector::LengthSq() const noexcept
    {
        return x * x + y * y + z * z + w * w;
    }

    inline void Vector::SetLength(const float value) noexcept
    {
        float l = Length();
        if (l != 0)
        {
            float n = value / l;
            Set(x * n, y * n, z * n, w * n);
        }
    }

    inline void Vector::Normalize() noexcept
    {
        float l = Length();
        if (l != 0)
        {
            Set(x / l, y / l, z / l, w / l);
        }
    }

    inline void Vector::Invert() noexcept
    {
        Set(-x, -y, -z, -w);
    }

    inline Vector Vector::Normalized(Vector&& v) noexcept
    {
        v.Normalize();
        return v;
    }

    inline Vector Vector::Normalized(const Vector& v) noexcept
    {
        return Normalized(Vector(v));
    }

    inline Vector Vector::Normal(const Vector& v1, const Vector& v2) noexcept
    {
        return Normalized(Cross(v1, v2));
    }

    inline Vector Vector::Projection(const Vector& v1, const Vector& v2) noexcept
    {
        return (v2 * (v1 * v2)) / v2.LengthSq();
    }

    inline float Vector::ProjectionLength(const Vector& v1, const Vector& v2) noexcept
    {
        return (v1 * v2) / v2.Length();
    }

    inline float Vector::Angle(const Vector& v1, const Vector& v2) noexcept
    {
        return acosf(CosAngle(v1, v2));
    }

    inline float Vector::CosAngle(const Vector& v1, const Vector& v2) noexcept
    {
        return (v1 * v2) / (v1.Length() * v2.Length());
    }

    inline float Vector::Dot(const Vector& l, const Vector& r) noexcept
    {
        return l * r;
    }

    inline Vector Vector::Cross(const Vector& l, const Vector& r) noexcept
    {
        return {
            l.y * r.z - l.z * r.y,
            l.z * r.x - l.x * r.z,
            l.x * r.y - l.y * r.x,
            0
        };
    }

    // Component-wise multiplication.
    inline Vector Vector::Mul(const Vector& l, const Vector& r) noexcept
    {
        return {l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w};
    }

    inline float Vector::Length(const Vector& v) noexcept
    {
        return v.Length();
    }

    inline float Vector::LengthSq(const Vector& v) noexcept
    {
        return v.LengthSq();
    }

    inline float Vector::Distance(const Vector& a, const Vector& b) noexcept
    {
        return Length(b - a);
    }

    // Non-member operators.

    inline bool operator==(const float length, const Vector& v) noexcept
    {
        return v == length;
    }

    inline bool operator!=(const float length, const Vector& v) noexcept
    {
        return v != length;
    }

    inline bool operator>(const float length, const Vector& v) noexcept
    {
        return v < length;
    }

    inline bool operator>=(const float length, const Vector& v) noexcept
    {
        return v <= length;
    }

    inline bool operator<(const float length, const Vector& v) noexcept
    {
        return v > length;
    }

    inline bool operator<=(const float length, const Vector& v) noexcept
    {
        return v >= length;
    }
}
