#pragma once
#include <SFML/Graphics.hpp>

class Element {
public:
    Element() = default;
    virtual ~Element() = default;
    virtual void Draw() {};
    virtual void Update() {};
    bool DeleteIt() { return deleteIt; }

    enum Names {
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
        butt1SelectionM,
        butt2SelectionM,
        butt3SelectionM,
    };

    Names name = None;

    sf::FloatRect posRect{};

protected:
    bool deleteIt = false;
};