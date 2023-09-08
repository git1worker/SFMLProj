#pragma once
#include "Animation.hpp"

class AnimHuman : public Animation {
  public:
    AnimHuman(Gamew *gamew, std::string path, Entity *entity, int speed = 110, int offset = 32);
    void Start() override { stop = false; }
    void Update() override;

  private:
    Entity *entity;
};