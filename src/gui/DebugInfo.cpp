#include "DebugInfo.hpp"

DebugInfo::DebugInfo(sf::RenderWindow *window, sf::Font *font, sf::Event *event) : window(window), Geologica(font), event(event)
{
    info = Label(window, font, L"{DebugInfo}", window->getSize().x - maxWidth, 10, Label::Align::Left, 15, 400);
    info.getText().setFillColor(sf::Color(0, 0, 0, 130));
}

void DebugInfo::UpdateEvents(const sf::Event *event)
{
    if (event->type == sf::Event::MouseMoved)
        lastMEvent = event->mouseMove;
}

void DebugInfo::UpdateFps(float fps)
{
    this->fps = fps;
}

void DebugInfo::Update()
{

    ss << L"DebugInfo:\nMouse:\nx= " << lastMEvent.x << L"\ny= " << lastMEvent.y << L"\nFPS: " << fps << L'\n';
    info.ChangeText(ss.str());
    ss.str(L"");
}

void DebugInfo::Draw()
{
    info.Draw();
}
