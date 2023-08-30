#include "TextBox.hpp"

TextBox::TextBox(sf::RenderWindow *window, sf::Font *font, const float x, const float y, const unsigned int fSize, const float w, const float h) 
    : window(window), Geologica(font)
{
    posRect.left = x;
    posRect.top = y;
    posRect.width = w;
    posRect.height = h;
    if (fSize > h) posRect.height = fSize;

    // Box
    rect.setSize(sf::Vector2f(posRect.width, posRect.height));
    rect.setOrigin(sf::Vector2f(0, 0));
    rect.setPosition(sf::Vector2f(posRect.left, posRect.top));
    rect.setFillColor(sf::Color(220, 220, 220, 220));
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color(50, 50, 50));
    // Text
    text.setFont(*Geologica);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(sf::Vector2f(0, 0));
    text.setCharacterSize(fSize);
    text.setPosition(posRect.left + text.getLetterSpacing(), posRect.top - text.getLineSpacing());
    // Cursor
    cursor.setSize(sf::Vector2f(text.getCharacterSize()/12, text.getCharacterSize()));
    cursor.setOrigin(sf::Vector2f(0, 0));
    cursor.setPosition(sf::Vector2f(posRect.left, posRect.top));
    cursor.setFillColor(sf::Color(50, 50, 50));
    
}

void TextBox::Draw()
{   
    window->draw(rect);
    window->draw(text);
    if (drawCursor){
        if (cursorClock.getElapsedTime().asMilliseconds() > 500)
        {
            showCursor = !showCursor;
            cursorClock.restart();
        }
        if (showCursor)
            window->draw(cursor);
    }
}

void TextBox::Update()
{
    
}

void TextBox::SetDrawCursor(bool v)
{
    drawCursor = v;
}

void TextBox::AppendLetter(wchar_t cr)
{   
    text.setString(text.getString() + std::wstring(1, cr));
    //std::wcout << text.getString().toWideString() << std::endl;
    CheckWidthText();
}

void TextBox::DelLetter()
{   
    std::wstring tmp = text.getString();
    if (!tmp.empty())
        tmp.erase(tmp.size() - 1, 1);
    text.setString(tmp);
    CheckWidthText();
}

void TextBox::ChangeText(std::wstring t)
{
    text.setString(t);
    CheckWidthText();
}

sf::RectangleShape &TextBox::getRect() { return rect; }

void TextBox::CheckWidthText()
{
    std::wstring newStr;
    int i = 1;
    sf::String lastStr = text.getString();
    for (auto it = lastStr.begin(); it != lastStr.end(); ++it){
        int currW = text.findCharacterPos(i).x - text.findCharacterPos(0).x;
        if (posRect.width > currW){
            newStr.push_back(*it);
            ++i;
        }
        else {
            newStr.push_back(L'\n');
            newStr.push_back(*it);
            text.setString(newStr);
            if (posRect.height < text.getGlobalBounds().height){
                newStr.pop_back();
                newStr.pop_back();
                text.setString(newStr);
            }
        }
    }
    if (!text.getString().isEmpty()){
        text.setString(newStr);
    }
    cursor.setPosition(text.findCharacterPos(text.getString().getSize()).x, text.findCharacterPos(text.getString().getSize()).y);

}

