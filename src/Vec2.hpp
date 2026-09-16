#pragma once

#include <string>
class Vec2 {
public:
  float x = {0};
  float y = {0};
  Vec2();
  Vec2(float x, float y);
  bool operator==(const Vec2& rhs) const;
  Vec2 operator+(const Vec2& rhs) const;
  Vec2 operator-(const Vec2& rhs) const;
  Vec2 operator*(const Vec2& rhs) const;
  Vec2 operator*(float scale) const;
  Vec2& operator+=(const Vec2& rhs);
  void print(std::string label);
};