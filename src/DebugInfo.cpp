#include "DebugInfo.hpp"
#include <sstream>

DebugInfo::DebugInfo(sf::RenderWindow *window, sf::Font &font, sf::Event *event) : window(window), Geologica(font), event(event)
{   
    info = std::make_unique<Label>(window, font, L"{DebugInfo}", window->getSize().x - maxWidth/2, 10, 15, 400);
}

void DebugInfo::Update(sf::Event *event)
{
    std::wstringstream ss;
    if (event->type == sf::Event::MouseMoved)
        lastMEvent = event->mouseMove;
    ss << L"DebugInfo:\nMouse: x= " << lastMEvent.x << L" y= " << lastMEvent.y << L'\n';
    info->ChangeText(ss.str());
}

void DebugInfo::Draw()
{
    info->Draw();
}
