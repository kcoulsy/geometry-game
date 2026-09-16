#include "Vec2.hpp"

Vec2::Vec2() {}
Vec2::Vec2(float init_x, float init_y) : x(init_x), y(init_y) {}

bool Vec2::operator==(const Vec2& rhs) const {
  return x == rhs.x && y == rhs.y;
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
  return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
  return Vec2(x - rhs.x, y - rhs.y);
}
Vec2 Vec2::operator*(const Vec2& rhs) const {
  return Vec2(x * rhs.x, y * rhs.y);
}
Vec2 Vec2::operator*(float scale) const { return Vec2(x * scale, y * scale); }

Vec2& Vec2::operator+=(const Vec2& rhs) {
  x += rhs.x;
  y += rhs.y;

  return *this;
}