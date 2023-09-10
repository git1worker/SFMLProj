#include "Animation.hpp"
#include "Debug.hpp"

Animation::~Animation() {
    gamew->AnimsVector.remove(this);
}

Animation::Animation(Gamew *gamew, std::string path, int speed, int offset, bool infinity)
    : gamew(gamew), speed(speed), offset(offset), infinity(infinity) {

    tAnim.loadFromFile(path);
    sprite.setTexture(tAnim);
    numFrames = sprite.getTextureRect().width / offset;
    sprite.setTextureRect(sf::IntRect(0, 0, offset, sprite.getTextureRect().height));
}

void Animation::SetOrigin() {
    if (flipped) {
        auto tmp = sprite.getTextureRect();
        tmp.width = -tmp.width;
        sprite.setTextureRect(tmp);
        flipped = false;
    }
}

void Animation::SetFlipped() {
    if (!flipped) {
        auto tmp = sprite.getTextureRect();
        tmp.width = -tmp.width;
        sprite.setTextureRect(tmp);
        flipped = true;
        // RTDrawing(gamew->window.get(), sprite);
    }
}

void Animation::Update() { Play(); sprite.setPosition(sf::Vector2f(pos.x + gamew->offsetRelativeCenter.x, pos.y + gamew->offsetRelativeCenter.y)); }

void Animation::Draw() { gamew->window->draw(sprite); }

void Animation::setPosition(sf::Vector2f pos) {
    this->pos = pos;
}

void Animation::Stop() {
    animate = false;
    stop = true;
}

void Animation::Play() {
    if (!stop) {
        if (!animate) {
            start = std::chrono::system_clock::now();
            animate = true;
            currFrame = 1;
            auto tmp = sprite.getTextureRect();
            if (flipped)
                tmp.left = offset * currFrame;
            else
                tmp.left = offset * (currFrame - 1);
            sprite.setTextureRect(tmp);
        } else {
            if (std::chrono::system_clock::now() - start > std::chrono::milliseconds(speed * currFrame)) {
                if (currFrame >= numFrames) {
                    if (infinity)
                        start = std::chrono::system_clock::now(), currFrame = 0;
                    else
                        stop = true, animate = false;
                }

                currFrame++;
                auto tmp = sprite.getTextureRect();
                if (flipped)
                    tmp.left = offset * currFrame;
                else
                    tmp.left = offset * (currFrame - 1);
                sprite.setTextureRect(tmp);
            }
        }
    }
}
