#pragma once


class Obj {
public:
    Obj();
    virtual void Draw() = 0;
    virtual void Update();
    virtual ~Obj() = default;
    bool DeleteIt() {return deleteIt;}

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
        textBox1MainW
    };
    Names name;
protected:
    
    bool deleteIt = false;
    float x, y, width, height;
};