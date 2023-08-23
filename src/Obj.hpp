#pragma once


class Obj {
public:
    Obj();
    virtual void Draw() = 0;
    virtual void Update();
    virtual ~Obj() = default;
    bool DeleteIt() {return deleteIt;}

    enum Names{
        None,
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
        textBox1MainW,
        tileMapW1
    };
    Names name = None;
protected:
    
    bool deleteIt = false;
    float x, y, width, height;
};