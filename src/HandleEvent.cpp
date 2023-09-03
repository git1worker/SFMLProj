#include "HandleEvent.hpp"
#include "Gamew.hpp"
#include "Player.hpp"
#include "gui/Button.hpp"
#include "gui/TextBox.hpp"

HandleEvent::HandleEvent(Gamew *gamew) : gamew(gamew) {}

void HandleEvent::operator()(const sf::Event &event) {
    if (gamew) {
        if (event.type == sf::Event::Closed)
            gamew->window->close(), gamew->isActive = false;
        else if (event.type == sf::Event::MouseMoved)
            eventMouseMoved(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            eventMouseButtonPressed(event);
        else if (event.type == sf::Event::MouseButtonReleased)
            eventMouseButtonReleased(event);
        else if (event.type == sf::Event::KeyPressed)
            eventKeyPressed(event);
        else if (event.type == sf::Event::KeyReleased)
            eventKeyReleased(event);
        else if (event.type == sf::Event::MouseWheelScrolled)
            eventMouseWheelScrolled(event);
    }
}

void HandleEvent::eventMouseMoved(const sf::Event &event) {
    gamew->mouseX = event.mouseMove.x;
    gamew->mouseY = event.mouseMove.y;
    gamew->TextBoxContains = false;
    for (const auto &i : gamew->ObjVector) {

        if (auto *b = dynamic_cast<Button *>(i.get());
            b && b->getRect().getGlobalBounds().contains(
                     sf::Vector2f((float)event.mouseMove.x + gamew->screenOffsetX, (float)event.mouseMove.y + gamew->screenOffsetY))) {
            b->SetHovered();
        } else if (b && b->isHovered() &&
                   !b->getRect().getGlobalBounds().contains(
                       sf::Vector2f((float)event.mouseMove.x + gamew->screenOffsetX, (float)event.mouseMove.y + gamew->screenOffsetY)))
            b->ResetHovered();
        else if (auto *b = dynamic_cast<TextBox *>(i.get());
                 b && b->getRect().getGlobalBounds().contains(
                          sf::Vector2f((float)event.mouseMove.x + gamew->screenOffsetX, (float)event.mouseMove.y + gamew->screenOffsetY))) {
            if (!gamew->cursorSetted) {
                gamew->window->setMouseCursor(gamew->cursorText);
                gamew->cursorSetted = true;
            }
            gamew->TextBoxContains = true;
        }
    }
    if (gamew->cursorSetted && !gamew->TextBoxContains) {
        gamew->window->setMouseCursor(gamew->cursorArrow);
        gamew->cursorSetted = false;
    }
}

void HandleEvent::eventMouseButtonPressed(const sf::Event &event) {
    for (const auto &i : gamew->ObjVector) {
        if (gamew->selectedTextBox)
            gamew->selectedTextBox->SetDrawCursor(false), gamew->selectedTextBox = nullptr;
        if (auto *b = dynamic_cast<Button *>(i.get());
            b && b->getRect().getGlobalBounds().contains(
                     sf::Vector2f((float)event.mouseButton.x + gamew->screenOffsetX, (float)event.mouseButton.y + gamew->screenOffsetY)))
            gamew->HandleButton(b);
        else if (auto *b = dynamic_cast<TextBox *>(i.get());
                 b && b->getRect().getGlobalBounds().contains(
                          sf::Vector2f((float)event.mouseButton.x + gamew->screenOffsetX, (float)event.mouseButton.y + gamew->screenOffsetY)))
            gamew->selectedTextBox = b, b->SetDrawCursor(true);
        if (gamew->player) gamew->player->Shoot();
    }
}

void HandleEvent::eventMouseButtonReleased(const sf::Event &event) {
    for (const auto &i : gamew->ObjVector) {
        if (auto *b = dynamic_cast<Button *>(i.get()); b && b->getWasClicked())
            b->Release();
    }
}

void HandleEvent::eventKeyPressed(const sf::Event &event) {

    if (event.key.code == sf::Keyboard::Escape) {
        if (!gamew->switchWindow && gamew->currentWindow == 0)
            gamew->window->close(), gamew->isActive = false;
        else if (!gamew->switchWindow && gamew->currentWindow != Windows::MainW)
            gamew->switchWindow = true, gamew->currentWindow = 0;
    } else if (gamew->selectedTextBox != nullptr)
        gamew->selectedTextBox->HandleTextbox(event);
    else if (event.key.code == sf::Keyboard::R) {
        std::cout << "Before view zoom: " << gamew->view.getSize().x / gamew->window->getSize().x << std::endl;
        gamew->view.zoom(1 / (gamew->view.getSize().x / (float)gamew->window->getSize().x));
        gamew->window->setView(gamew->view);
        std::cout << "After view zoom: " << gamew->view.getSize().x / gamew->window->getSize().x << std::endl;
    }
}

void HandleEvent::eventKeyReleased(const sf::Event &event) {
    if (gamew->player)
        gamew->player->MoveStop();
}

void HandleEvent::eventMouseWheelScrolled(const sf::Event &event) {
    if (event.mouseWheelScroll.delta > 0) {
        gamew->view.zoom(0.9f);
        gamew->window->setView(gamew->view);
    } else if (event.mouseWheelScroll.delta < 0) {
        gamew->view.zoom(1.1f);
        gamew->window->setView(gamew->view);
    }
    // std::cout << "Current view zoom: " << view.getSize().x /
    // window->getSize().x << std::endl;
}
