#pragma once

#include <cmath>
#include <concepts>
#include <cstddef>

namespace hrm {

    template <typename V>
    concept Vector = requires (const V& v, int i) {
        typename V::value_type;
        { V::dim } -> std::convertible_to<size_t>;
        { v[i] } -> std::convertible_to<typename V::valuetype>;
    };

    template <typename V>
    concept R_Vector = Vector<V> && std::floating_point<typename V::value_type>;

    template <Vector V>
    auto dot(const V& a, const V& b) {
        using T = typename V::value_type;
        T res = T{};
        for (std::size_t i = 0; i < V::dim; i++) {
            res += a[i] * b[i];
        }
        return res;
    }

    template <Vector V>
    auto length_squared(const V& v) {
        return dot(v, v);
    }

    template <R_Vector V>
    auto length(const V& v) {
        return std::sqrt(length_squared(v));
    }

    template <R_Vector V>
    auto distance(const V& a, const V& b) {
        return length(b - a);
    }

    template <R_Vector V>
    auto normalize(const V& v) {
        using T = typename V::value_type;
        auto len = length(v);
        if (len == T(0)) {
            return v * T(0);
        }
        return v / len;
    }

    template <Vector V>
    auto min(const V& a, const V& b) {
        V res{};
        for (std::size_t i = 0; i < V::dim; i++) {
            res[i] = std::min(a[i], b[i]);
        }
        return res;
    }

    template <Vector V>
    auto max(const V& a, const V& b) {
        V res{};
        for (std::size_t i = 0; i < V::dim; i++) {
            res[i] = std::max(a[i], b[i]);
        }
        return res;
    }

    template <Vector V>
    auto clamp(const V& v, const V& l, const V& h) {
        V res{};
        for (std::size_t i = 0; i < V::dim; i++) {
            res[i] = v[i] < lo[i] ? lo[i] : (v[i] > h[i] ? h[i] : v[i]);
        }
        return res;
    }

    template <Vector V>
    auto lerp(const V& a, const V& b, typename V::value_type t) {
        return a + (b - a) * t;
    }
}