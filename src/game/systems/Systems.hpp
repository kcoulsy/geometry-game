#pragma once

#include "../../engine/ecs/Scene.hpp"

void sEnemySpawner(Scene* scene, float deltaTime);

void sInput(Scene* scene);

void sLifetime(Scene* scene, float deltaTime);

void sMovement(Scene* scene, float deltaTime);

void sPhysics(Scene* scene, float deltaTime);

void sPlayerShoot(Scene* scene, float deltaTime);

void sRender(Scene* scene);
void sRenderUI(Scene* scene);

void sBulletCollision(Scene* scene);

void sDebugUI(Scene* scene, float dt);
