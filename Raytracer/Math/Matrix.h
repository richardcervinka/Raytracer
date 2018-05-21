#pragma once

#include "Vector.h"

namespace Math
{
    // 4x4 matrix.
    class alignas(16) Matrix
    {
    public:
        // Row major entries: m[row][column].
        float m[4][4];

        Matrix(const Matrix&) = default;
        Matrix& operator=(const Matrix&);

        // Copy the column-major entries into the raw memory.
        void StoreColumnMajor(void* const raw);

        // Copy the row-major entries into the raw memory.
        void StoreRowMajor(void* const raw);

        // Create a zero matrix.
        static Matrix Zero();

        // Create an identity matrix.
        static Matrix Identity();

        // Create transpose matrix.
        static Matrix Transpose(const Matrix& m);

        // Create inverse matrix.
        static Matrix Inverse(const Matrix& m);

        // Create rotation matrices around the world axes.
        static Matrix RotationX(const float rad);
        static Matrix RotationY(const float rad);
        static Matrix RotationZ(const float rad);

        // Create a rotation matrix around all worl axes in order Z, X, Y.
        static Matrix Rotation(const float x, const float y, const float z);
        static Matrix Rotation(const Vector&);

        // Create a rotation matrix around the axis defined as an unit vector.
        static Matrix RotationAxis(const Vector& v, const float rad);

        // Create a scale matrix.
        static Matrix Scale(const float x, const float y, const float z);
        static Matrix Scale(const Vector&);

        // Create a translation matrix.
        static Matrix Translation(const float x, const float y, const float z);
        static Matrix Translation(const Vector&);

        // Create a matrix for a local object transformations.
        static Matrix Transformations(const Vector& translations, const Vector& scales, const Vector& rotations);

        void Transpose();
        bool Invert();

        // Determinant.
        float Determinant() const;

        // Equality.
        bool operator==(const Matrix&) const;
        bool operator!=(const Matrix&) const;

        // Multiply.
        Matrix operator*(const Matrix&) const;

        // Swap rows.
        void SwapRows(const int r1, const int r2);

        // Add a multiplied src row to a dest row.
        void AddRow(const int srcRow, const int destRow, const float multiplier);

        // Multiply all entries of a row.
        void MulRow(const int row, const float value);

        // Apply transformations (this * arg).
        Vector Transform(const Vector&) const;

        void AppendTransformations(const Matrix&);
        void PrependTransformations(const Matrix&);

        void AppendTranslation(const float x, const float y, const float z);
        void PrependTranslation(const float x, const float y, const float z);

        void AppendScaling(const float x, const float y, const float z);
        void PrependScaling(const float x, const float y, const float z);

        void AppendRotations(const float x, const float y, const float z);
        void PrependRotations(const float x, const float y, const float z);

    private:
        // Create a uninitialized matrix. Only internal use.
        Matrix() = default;

        // Implementation.
        static void Transpose(const Matrix& m, Matrix* const o);
        static bool Invert(const Matrix& m, Matrix& o);

        // Friends that needs access to the Multiply function.
        friend Vector operator*(const Matrix&, const Vector&);
        friend Vector operator*(const Vector&, const Matrix&);
    };
}

// Implementation file.
#include "Matrix.inl"
