#pragma once

#include <cmath>
#include <iostream>

namespace math {
template <typename T> struct Vector2 {
  T x, y;

  Vector2 &operator+=(const Vector2 &v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vector2 &operator-=(const Vector2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  Vector2 &operator*=(const T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vector2 &operator/=(const T scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  Vector2 operator-() const { return Vector2{-x, -y}; }

  friend Vector2 operator+(Vector2 a, const Vector2 &b) { return a += b; }

  friend Vector2 operator-(Vector2 a, const Vector2 &b) { return a -= b; }

  friend Vector2 operator*(Vector2 a, T scalar) { return a *= scalar; }

  friend Vector2 operator*(T scalar, Vector2 a) { return a *= scalar; }

  friend Vector2 operator/(Vector2 a, T scalar) { return a /= scalar; }

  friend T dot(const Vector2 &a, const Vector2 &b) {
    return (a.x * b.x) + (a.y * b.y);
  }

  T lengthSquared() const { return x * x + y * y; }

  T length() const { return std::sqrt(lengthSquared()); }

  // might need better checking (len > 0) precision issues
  Vector2 &normalize() {
    T len = length();
    if (len > 0) {
      *this /= len;
    }
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const Vector2 &v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
  }
};
} // namespace math
