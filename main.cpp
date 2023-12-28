//
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
using namespace std;
using namespace sf;
using namespace std::chrono;

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int main(){
    fstream file("files/board_config.cfg");
    string line;
    getline(file ,line);
    int columns = stoi(line);
    getline(file, line);
    int rows = stoi(line);
    string name;
    Game gamemaster;
    bool finishedEnteringName = false;

    sf::RenderWindow window(sf::VideoMode(columns * 32, rows * 32 + 100), "Minesweeper", sf::Style::Close);
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 150);
    welcomeText.setOrigin(welcomeText.getLocalBounds().width / 2.0f, welcomeText.getLocalBounds().height / 2.0f);

    sf::Text namePrompt("Enter your name:", font, 20);
    namePrompt.setStyle(sf::Text::Bold);
    namePrompt.setFillColor(sf::Color::White);
    namePrompt.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 75);
    namePrompt.setOrigin(namePrompt.getLocalBounds().width / 2.0f, namePrompt.getLocalBounds().height / 2.0f);

    sf::Text userInput("", font, 18);
    userInput.setStyle(sf::Text::Bold);
    userInput.setFillColor(sf::Color::Yellow);
    userInput.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 45);
    userInput.setOrigin(userInput.getLocalBounds().width / 2.0f, userInput.getLocalBounds().height / 2.0f);

    sf::Text cursor("|", font, 18);
    cursor.setStyle(sf::Text::Bold);
    cursor.setFillColor(sf::Color::Yellow);
    cursor.setOrigin(cursor.getLocalBounds().width / 2.0f, cursor.getLocalBounds().height / 2.0f);
    size_t cursorPosition = name.length();
    sf::RectangleShape background(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color::Blue);

    bool windowOpen = true;
    while (windowOpen) {
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
                windowOpen = false;
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!name.empty() && cursorPosition > 0) {
                        name.erase(cursorPosition - 1, 1);
                        cursorPosition--;
                        userInput.setString(name);}}
                else if (event.text.unicode < 128 && isalpha(event.text.unicode)) {
                    if (name.length() < 10) {
                        name.insert(cursorPosition, 1, static_cast<char>(event.text.unicode));
                        cursorPosition++;
                        userInput.setString(name);
                        if (cursorPosition == 1){
                            name[0] = static_cast<char>(toupper(name[0]));
                        }
                        else{
                            for (int i = 1; i < cursorPosition; i++) {
                                name[i] = static_cast<char>(tolower(name[i]));
                            }}}}
                else if (event.text.unicode == '\r'){
                    if (!name.empty()) {
                        finishedEnteringName = true;
                    }
                }
            }
            setText(userInput,static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 45);
            setText(cursor,static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 45);
        }
        float cursorX = userInput.findCharacterPos(name.length()).x;
        float cursorY = userInput.getPosition().y + userInput.getLocalBounds().height / 2.0f - cursor.getLocalBounds().height / 2.0f;
        cursor.setPosition(cursorX, cursorY);
        window.clear(sf::Color::Blue);
        window.draw(welcomeText), window.draw(namePrompt), window.draw(userInput), window.draw(cursor), window.display();

        if (finishedEnteringName) {
            while (window.isOpen()) {
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();}}
                window.clear(sf::Color::White);
                gamemaster.update(window), gamemaster.draw(window), window.display();
            }
            windowOpen = false;}}
    return 0;
}