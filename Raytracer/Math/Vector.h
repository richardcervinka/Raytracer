#pragma once

namespace Math
{
    class alignas(16) Vector
    {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        // Construction.
        Vector() { };
        Vector(const float x_, const float y_, const float z_, const float w_): x(x_), y(y_), z(z_), w(w_) { }
        Vector(const Vector&) = default;

        // Default destructor.
        ~Vector() = default;

        // Assignment.
        Vector& operator=(const Vector&) = default;
        void Set(const float x_, const float y_, const float z_, const float w_) noexcept;

        // Returns normalized vector.
        static Vector Normalized(const Vector&) noexcept;
        static Vector Normalized(Vector&&) noexcept;

        // Returns normal vector.
        static Vector Normal(const Vector& v1, const Vector& v2) noexcept;

        // Returns orthogonal projection v1 to the v2.
        static Vector Projection(const Vector& v1, const Vector& v2) noexcept;

        // Returns length of the result of the orthogonal projection v1 to the v2.
        static float ProjectionLength(const Vector& v1, const Vector& v2) noexcept;

        // Angle between two vectors.
        static float Angle(const Vector&, const Vector&) noexcept;

        // Cosinus of the angle between two vectors.
        static float CosAngle(const Vector&, const Vector&) noexcept;

        // Dot product.
        static float Dot(const Vector&, const Vector&) noexcept;

        // Cross product.
        static Vector Cross(const Vector&, const Vector&) noexcept;

        // Component-wise multiplication.
        static Vector Mul(const Vector&, const Vector&) noexcept;

        // Length of the vector.
        static float Length(const Vector&) noexcept;

        // Squared length of the vector.
        static float LengthSq(const Vector&) noexcept;

        static float Distance(const Vector& a, const Vector& b) noexcept;

        // Comparsion two vectors.
        bool operator==(const Vector&) const noexcept;
        bool operator!=(const Vector&) const noexcept;

        // Comparsion length of the vector and scalar.
        bool operator==(const float) const noexcept;
        bool operator!=(const float) const noexcept;
        bool operator>(const float) const noexcept;
        bool operator>=(const float) const noexcept;
        bool operator<(const float) const noexcept;
        bool operator<=(const float) const noexcept;

        // Comparsion length of the two vectors.
        bool operator>(const Vector&) const noexcept;
        bool operator>=(const Vector&) const noexcept;
        bool operator<(const Vector&) const noexcept;
        bool operator<=(const Vector&) const noexcept;

        // Add.
        Vector operator+(const Vector&) const noexcept;
        Vector& operator+=(const Vector&) noexcept;

        // Subtract.
        Vector operator-(const Vector&) const noexcept;
        Vector& operator-=(const Vector&) noexcept;

        // Multiply.
        Vector operator*(const float) const noexcept;
        Vector& operator*=(const float) noexcept;

        // Divide.
        Vector operator/(const float) const noexcept;
        Vector& operator/=(const float) noexcept;

        // Negation.
        Vector operator-() const noexcept;

        // Dot product.
        float operator*(const Vector&) const noexcept;

        // Get length.
        float Length() const noexcept;

        // Get length square.
        float LengthSq() const noexcept;

        // Set length. If initial length is 0, does nothing.
        void SetLength(const float) noexcept;

        // Set length to 1.
        void Normalize() noexcept;

        // Vector negation.
        void Invert() noexcept;
    };
}

// Include implementation file.
#include "Vector.inl"