#pragma once

#include <cstddef>

namespace hrm {

    template <typename T>
    class Vec3 {
    public:
        using value_type = T;
        static constexpr std::size_t dim = 3;
        T x;
        T y;
        T z;

        explicit Vec3(T vx, T vy, T vz) : x(vx), y(vy), z(vz) {}
        Vec3(T t) : x(t), y(t), z(t) {}
        Vec3() : x(T{}), y(T{}), z(T{}) {}
        Vec3(const Vec3&) = default;
        Vec3& operator=(const Vec3&) = default;
        Vec3(Vec3&&) noexcept = default;
        Vec3& operator=(Vec3&&) noexcept = default;

        T& operator[](std::size_t i) {
            return i == 0 ? x : (i == 1 ? y : z);
        }
        const T& operator[](std::size_t i) const {
            return i == 0 ? x : (i == 1 ? y : z);
        }

        Vec3 operator+(const Vec3& v) const {
            return Vec3(x + v.x, y + v.y, z + v.z);
        }

        Vec3 operator-(const Vec3& v) const {
            return Vec3(x - v.x, y - v.y, z - v.z);
        }

        Vec3 operator*(T n) const {
            return Vec3(x * n, y * n, z * n);
        }
        Vec3 operator*(const Vec3& v) const {
            return Vec3(x * v.x, y * v.y, z * v.z);
        }

        Vec3 operator/(T n) const {
            return Vec3(x / n, y / n, z / n);
        }

        Vec3 operator-() const {
            return Vec3(-x, -y, -z);
        }

        bool operator==(const Vec3& v) const {
            return (x == v.x && y == v.y && z == v.z);
        }
        bool operator!=(const Vec3& v) const {
            return (x != v.x || y != v.y || z != v.z);
        }

        Vec3& operator+=(const Vec3& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vec3& operator-=(const Vec3& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        Vec3& operator*=(T n) {
            x *= n;
            y *= n;
            z *= n;
            return *this;
        }
        Vec3& operator*=(const Vec3& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        Vec3& operator/=(T n) {
            x /= n;
            y /= n;
            z /= n;
            return *this;
        }
    };

    using vec3 = Vec3<float>;
    using ivec3 = Vec3<int>;
    using dvec3 = Vec3<double>;
}