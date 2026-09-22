#include "../../Component.hpp"
#include "Systems.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

void sRenderUI(Scene* scene) {
  auto em = scene->getEntityManager();
  auto window = scene->getWindow();

  auto& entities = em->getEntities("ui");

  for (auto e : entities) {
    if (e->hasComponent<CUIText>()) {
      auto& t = e->getComponent<CUIText>();
      sf::Text& text = t.textObject(*scene->getFont());

      // set the string to display
      text.setString(t.text);

      // set the character size
      text.setCharacterSize(24); // in pixels, not points!

      // set the color
      text.setFillColor(sf::Color::Red);

      // set the text style
      text.setStyle(sf::Text::Bold | sf::Text::Underlined);

      if (e->hasComponent<CTransform>()) {
        auto& t = e->getComponent<CTransform>();
        text.setPosition(sf::Vector2f(t.position.x, t.position.y));
      }
      window->draw(text);
    }
  }
}
