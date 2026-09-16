#include "Vec2.hpp"
#include <cmath>
#include <iostream>

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

Vec2 Vec2::normalize() {
  float length = std::sqrt(x * x + y * y);
  return Vec2(x / length, y / length);
}

void Vec2::print(std::string label) {
  std::cout << "Vec2 " << label << " (" << x << "," << y << ")\n";
}