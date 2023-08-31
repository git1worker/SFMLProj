#include "Animation.hpp"
#include "Debug.hpp"

Animation::Animation(Gamew *gamew, std::string path, int speed, int offset) : gamew(gamew), speed(speed), offset(offset)
{
    tAnim.loadFromFile(path);
    sprite.setTexture(tAnim);

    numFrames = sprite.getTextureRect().width / offset;
    sprite.setTextureRect(sf::IntRect(0, 0, offset, sprite.getTextureRect().height));
}

void Animation::PlayOrigin()
{
    if (flipped)
    {
        auto tmp = sprite.getTextureRect();
        tmp.width = -tmp.width;
        sprite.setTextureRect(tmp);
        flipped = false;
    }
    Play();
}

void Animation::PlayFlipped()
{
    if (!flipped)
    {
        auto tmp = sprite.getTextureRect();
        tmp.width = -tmp.width;
        sprite.setTextureRect(tmp);
        flipped = true;
        // RTDrawing(gamew->window.get(), sprite);
    }
    Play();
}

void Animation::Stop()
{
    animate = false;
}

bool Animation::getFlipped()
{
    return flipped;
}

bool Animation::getAnimated()
{
    return animate;
}

void Animation::Play()
{
    if (!animate)
    {
        start = std::chrono::system_clock::now();
        animate = true;
        currFrame = 1;
        auto tmp = sprite.getTextureRect();
        if (flipped)
            tmp.left = offset * currFrame;
        else
            tmp.left = offset * (currFrame - 1);
        sprite.setTextureRect(tmp);
    }
    else
    {
        if (std::chrono::system_clock::now() - start > std::chrono::milliseconds(speed * currFrame))
        {
            if (currFrame >= numFrames)
                start = std::chrono::system_clock::now(), currFrame = 0;

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
