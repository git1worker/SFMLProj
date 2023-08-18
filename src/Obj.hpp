#pragma once


class Obj {
public:
    Obj();
    virtual void Draw() = 0;
    virtual void Update();
    virtual ~Obj() = default;

    enum Names{
        DebugInfo,
        titleMainW,
        butt1MainW,
        butt2MainW,
        butt3MainW,
        butt4MainW,
        titleW1,
        titleW2,
        titleW3,
        titleW4,
    };
    Names name;
protected:
    
    float x, y, width, height;
};