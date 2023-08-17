#pragma once


class Obj {
public:
    Obj();
    virtual void Draw() = 0;
    virtual ~Obj() = default;
protected:
    float x, y, width, height;

};