#pragma once

#include <concepts>
#include <cstddef>

//Hydranemo Renderer Math
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

template <typename T>
Vec2<T> operator-(const Vec2<T>& v) {
    return Vec2<T>(-v.x, -v.y);
}

template <typename T>
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>(a.x + b.x, a.y + b.y);
}

template <typename T>
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>(a.x - b.x, a.y - b.y);
}

template <typename T>
Vec2<T> operator*(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>(a.x * b.x, a.y * b.y);
}

template <typename T, typename U>
    requires std::convertible_to<U, T>
Vec2<T> operator*(const Vec2<T>& v, U n) {
    return Vec2<T>(v.x * n, v.y * n);
}
template <typename T, typename U>
    requires std::convertible_to<U, T>
Vec2<T> operator*(U n, const Vec2<T>& v) {
    return Vec2<T>(v.x * n, v.y * n);
}

template <typename T, typename U>
    requires std::convertible_to<U, T>
Vec2<T> operator/(const Vec2<T>& v, U n) {
    return Vec2<T>(v.x / n, v.y / n);
}

template <typename T>
bool operator==(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x == b.x && a.y == b.y;
}

template <typename T>
bool operator!=(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x != b.x || a.y != b.y;
}

template <typename T>
inline T cross(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x * b.y - b.x * a.y;
}

    using vec2 = Vec2<float>;
    using ivec2 = Vec2<int>;
    using dvec2 = Vec2<double>;
    // using bvec2 = Vec2<bool>;
    // using lvec2 = Vec2<long long>;
    // using uvec2 = Vec2<unsigned>;
}
