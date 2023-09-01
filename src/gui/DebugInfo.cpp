#include "DebugInfo.hpp"
#include "../Gamew.hpp"

DebugInfo::DebugInfo(Gamew* gamew, sf::Font *font, sf::Event *event) : gamew(gamew), Geologica(font), event(event)
{
    info = Label(gamew->window.get(), font, L"{DebugInfo}", gamew->window->getSize().x - maxWidth, 10, Label::Align::Left, 15, 400);
    info.getText().setFillColor(sf::Color(0, 0, 0, 130));
}

void DebugInfo::UpdateFps(float fps)
{
    this->fps = fps;
}

void DebugInfo::Update()
{

    ss << L"DebugInfo:\nMouse:\nx= " << gamew->mouseX << L"\ny= " << gamew->mouseY << 
    L"\nField:\nX=" << (-gamew->offsetRelativeCenter.x / 32) + (gamew->window->getSize().x / 2) / 32 << L"\nY=" << (-gamew->offsetRelativeCenter.y / 32) + (gamew->window->getSize().y / 2) / 32 << 
    L"\nFPS: " << fps << L'\n';
    info.ChangeText(ss.str());
    ss.str(L"");
}

void DebugInfo::Draw()
{
    info.Draw();
}
