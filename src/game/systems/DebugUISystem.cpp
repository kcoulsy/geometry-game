#include "../components/Components.hpp"
#include "Systems.hpp"
#include <format>

void sDebugUI(Scene* scene, float dt) {
  auto& ents = scene->getEntityManager()->getEntities();

  for (auto& e : ents) {
    if (!e->hasComponents<CDebug, CUIText>())
      continue;

    CUIText& t = e->getComponent<CUIText>();
    float fps = 1.f / (dt);
    t.text = std::format("FPS: {} \n Entities: {}", fps, ents.size());
  }
}
