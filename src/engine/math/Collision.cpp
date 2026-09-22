#include "Collision.hpp"

bool isCollidingWith(Vec2 aPos, Vec2 aSize, Vec2 bPos, Vec2 bSize) {
  return (aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x && aPos.y < bPos.y + bSize.y &&
          aPos.y + aSize.y > bPos.y);
}