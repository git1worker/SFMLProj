#include "AnimHuman.hpp"
#include "Debug.hpp"

AnimHuman::AnimHuman(Gamew *gamew, std::string path, Entity *entity, int speed, int offset) : Animation(gamew, path, speed, offset), entity(entity) {}

void AnimHuman::Update() {
    sprite.setPosition(entity->posRect.left - 3 + gamew->offsetRelativeCenter.x, entity->posRect.top - 4 + gamew->offsetRelativeCenter.y);
    Play();
}
