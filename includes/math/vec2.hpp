#pragma once

#include <cstddef>

namespace hrm {

template <typename T>
class Vec2 {
public:
    using value_type = T;
    static constexpr std::size_t dim = 2;
    T x;
    T y;

    explicit Vec2(T vx, T vy) : x(vx), y(vy) {}
    Vec2(T t) : x(t), y(t) {}
    Vec2() : x(T{}), y(T{}) {}
    Vec2(const Vec2&) = default;
    Vec2& operator=(const Vec2&) = default;
    Vec2(Vec2&&) noexcept = default;
    Vec2& operator=(Vec2&&) = default;

    T& operator[](std::size_t i) {
        return i == 0 ? x : y;
    }
    const T& operator[](std::size_t i) const {
        return i == 0 ? x : y;
    }

    Vec2 operator+(const Vec2& v) const {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 operator-(const Vec2& v) const {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 operator*(T n) const {
        return Vec2(x * n, y * n);
    }

    Vec2 operator*(const Vec2& v) const {
        return Vec2(x * v.x, y * v.y);
    }

    Vec2 operator/(T n) const {
        return Vec2(x / n, y / n);
    }

    Vec2 operator-() const {
        return Vec2(-x, -y);
    }

    bool operator==(const Vec2& v) const {
        return (x == v.x && y == v.y);
    }

    bool operator!=(const Vec2& v) const {
        return (x != v.x || y != v.y);
    }

    Vec2& operator+=(const Vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vec2& operator*=(T n) {
        x *= n;
        y *= n;
        return *this;
    }
    Vec2& operator*=(const Vec2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    Vec2& operator/=(T n) {
        x /= n;
        y /= n;
        return *this;
    }
};

    using vec2 = Vec2<float>;
    using ivec2 = Vec2<int>;
    using dvec2 = Vec2<double>;
    // using bvec2 = Vec2<bool>;
    // using lvec2 = Vec2<long long>;
    // using uvec2 = Vec2<unsigned>;
}
