#include <tuple>

class Component {
  public:
    bool exists;
};

class CTransform : public Component {
  public:
    // Vec2 position = {0, 0};
};

typedef std::tuple<CTransform> Components;