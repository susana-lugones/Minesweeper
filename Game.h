#include "ScreenGenerator.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <chrono>
using namespace std;
using namespace sf;
using namespace std::chrono;

void leaderboard(){
    fstream file("files/board_config.cfg");
    string number;

    getline(file ,number);
    int columns = stoi(number);

    getline(file, number);
    int rows = stoi(number);

    getline(file, number);
    int mines = stoi(number);

    sf::RenderWindow window(sf::VideoMode(16 * columns, (rows * 16) + 50), "Minesweeper", sf::Style::Close);
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text welcomeText("LEADERBOARD", font, 20);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 120);
    welcomeText.setOrigin(welcomeText.getLocalBounds().width / 2.0f, welcomeText.getLocalBounds().height / 2.0f);

    ifstream leaderboard_file("files/leaderboard.txt");
    string leaderboard_str;
    string line;

    while (std::getline(leaderboard_file, line)){
        leaderboard_str += line + "\n\n";
    }
    leaderboard_file.close();
    Text leaderboard_text;
    leaderboard_text.setFont(font);
    leaderboard_text.setString(leaderboard_str);
    leaderboard_text.setCharacterSize(18);
    leaderboard_text.setStyle(sf::Text::Bold);
    leaderboard_text.setFillColor(sf::Color::White);
    leaderboard_text.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f + 20);
    leaderboard_text.setOrigin(leaderboard_text.getLocalBounds().width / 2.0f, leaderboard_text.getLocalBounds().height / 2.0f);

    sf::RectangleShape background(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color::Blue);

    bool windowOpen = true;
    while (windowOpen) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                windowOpen = false;
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(welcomeText);
        window.draw(leaderboard_text);
        window.display();
    }
}

class Game{
    Sprite minute_1, minute_2, seconds_3, seconds_4, pause, bugORnot, play, mainLeaders, face1, daHunda, daTen, daOne;
    int totalF, totalM{}, totalT{};
    bool userL{}, overDone{};
    map<string, Texture> forNew;
    vector<int> back, uppy;
    vector<bool> var7;
    bool paused;

public:
    Game();
    vector<ScreenGenerator> square;
    void Scatter(), JollyT(), minesActual(), bigSquare(), update(RenderWindow &window), debug(), draw(RenderWindow &window), refresh(), events();
    void readBoardConfig(int& columns, int& rows), initSquareSurroundings(int columns, int rows);
    void initSquareSurroundingsAtIndex(int index, int columns, int rows);

};

Game::Game(){
    fstream file("files/board_config.cfg");
    string line;

    getline(file ,line);
    int columns = stoi(line);

    getline(file, line);
    int rows = stoi(line);

    getline(file, line);
    int mines = stoi(line);

    srand(time(nullptr));
    totalF = mines;
    Texture currently;
    currently.loadFromFile("files/images/debug.png"); forNew.emplace("debug", currently);
    currently.loadFromFile("files/images/play.png"); forNew.emplace("play", currently);
    currently.loadFromFile("files/images/pause.png"); forNew.emplace("pause", currently);
    currently.loadFromFile("files/images/leaderboard.png"); forNew.emplace("leaderboard", currently);
    currently.loadFromFile("files/images/mine.png"); forNew.emplace("bomb", currently);
    currently.loadFromFile("files/images/number_6.png"); forNew.emplace("six", currently);
    currently.loadFromFile("files/images/number_7.png"); forNew.emplace("seven", currently);
    currently.loadFromFile("files/images/number_8.png"); forNew.emplace("eight", currently);
    currently.loadFromFile("files/images/digits.png"); forNew.emplace("digits", currently);
    currently.loadFromFile("files/images/number_1.png"); forNew.emplace("one", currently);
    currently.loadFromFile("files/images/number_2.png"); forNew.emplace("two", currently);
    currently.loadFromFile("files/images/number_3.png"); forNew.emplace("three", currently);
    currently.loadFromFile("files/images/number_4.png"); forNew.emplace("four", currently);
    currently.loadFromFile("files/images/number_5.png"); forNew.emplace("five", currently);
    currently.loadFromFile("files/images/flag.png"); forNew.emplace("flag", currently);
    currently.loadFromFile("files/images/face_happy.png"); forNew.emplace("happy", currently);
    currently.loadFromFile("files/images/face_lose.png"); forNew.emplace("lose", currently);
    currently.loadFromFile("files/images/face_win.png"); forNew.emplace("win", currently);
    currently.loadFromFile("files/images/tile_hidden.png"); forNew.emplace("hidden", currently);
    currently.loadFromFile("files/images/tile_revealed.png"); forNew.emplace("revealed", currently);
    daHunda.setTexture(forNew["digits"]);
    daHunda.setTextureRect(Rect<int>(0, 0, 21, 32));
    daHunda.setPosition (12, (32 * (static_cast<float>(rows) + 0.5f) + 16));
    daTen.setTexture(forNew["digits"]);
    daTen.setTextureRect(Rect<int>(21 * 5, 0, 21, 32));
    daTen.setPosition(33, (32 * (static_cast<float>(rows) + 0.5f) + 16));
    daOne.setTexture(forNew["digits"]);
    daOne.setTextureRect(Rect<int>(0, 0, 21, 32));
    daOne.setPosition(54, (32 * (static_cast<float>(rows) + 0.5f) + 16));
    minute_1.setTexture(forNew["digits"]);
    minute_1.setTextureRect(Rect<int>(0, 0, 21, 32));
    minute_1.setPosition(static_cast<float>((columns) * 32 - 97), (32 * (static_cast<float>(rows) + 0.5f) + 16));
    minute_2.setTexture(forNew["digits"]);
    minute_2.setTextureRect(Rect<int>(0, 0, 21, 32));
    minute_2.setPosition(static_cast<float>(((columns)*32)-97 + 21), (32*(static_cast<float>(rows)+0.5f)+16));
    seconds_3.setTexture(forNew["digits"]);
    seconds_3.setTextureRect(Rect<int>(0, 0, 21, 32));
    seconds_3.setPosition(static_cast<float>(((columns)*32)-54), (32*(static_cast<float>(rows)+0.5f)+16));
    seconds_4.setTexture(forNew["digits"]);
    seconds_4.setTextureRect(Rect<int>(0, 0, 21, 32));
    seconds_4.setPosition(static_cast<float>(((columns)*32)-54 + 21), (32*(static_cast<float>(rows)+0.5f)+16));
    mainLeaders.setTexture(forNew["leaderboard"]);
    mainLeaders.setPosition(static_cast<float>((columns) * 32) - 176, 32 * (static_cast<float>(rows) + 0.5f));
    face1.setTexture(forNew["happy"]);
    face1.setPosition(static_cast<float>(((columns) / 2.0) * 32) - 32, 32 * (static_cast<float>(rows) + 0.5f));
    bugORnot.setTexture(forNew["debug"]);
    bugORnot.setPosition(static_cast<float>((columns) * 32 - 304), 32 * (static_cast<float>(rows) + 0.5f));
    play.setTexture(forNew["play"]);
    play.setPosition(static_cast<float>((columns) * 32) - 240, 32 * (static_cast<float>(rows)+0.5f));
    JollyT();
    Scatter();
}

void Game::update(RenderWindow &window){
    static bool isPaused = false;
    static time_point<system_clock> pauseStart = system_clock::now();
    static int elapsedMilliseconds = 0;
    int minutes, seconds;
    fstream file("files/board_config.cfg");
    string line;
    getline(file ,line);
    int columns = stoi(line);
    getline(file, line);
    int rows = stoi(line);
    if (overDone){
        if (!isPaused){
            elapsedMilliseconds += duration_cast<std::chrono::milliseconds>(system_clock::now() - pauseStart).count();
            pauseStart = system_clock::now();
            isPaused = true;
        }
    }
    else {
        if (isPaused){
            pauseStart = system_clock::now();
            elapsedMilliseconds += duration_cast<std::chrono::milliseconds>(system_clock::now() - pauseStart).count();
        }
        else{
            int millisecondsSinceLastUpdate = duration_cast<std::chrono::milliseconds>(system_clock::now() - pauseStart).count();
            elapsedMilliseconds += millisecondsSinceLastUpdate;
            pauseStart = system_clock::now();
        }}

    if (Mouse::isButtonPressed(Mouse::Right)&& !overDone){
        Vector2i position = Mouse::getPosition(window);
        if (position.x >= 0 && position.x <= (columns * 32)){
            if (position.y >= 0 && position.y <= (rows * 32)){
                int position2 = (position.x / 32);
                int position1 = (position.y / 32);
                int temp = (position1 * columns) + position2;
                if (!square[temp].withF && !square[temp].shown){
                    square[temp].fChanges();
                    totalF--;}
                else if (!square[temp].shown && square[temp].withF){
                    square[temp].fChanges();
                    totalF++;}}
            refresh();
        }
    }
    if (totalT == ((rows * columns) - totalM) && !userL){
        overDone = true;
        for (int jj = 0; jj < (rows * columns); jj++){
            if (square[jj].mine && !square[jj].withF){
                square[jj].fChanges();}}}

    if (Mouse::isButtonPressed(Mouse::Left)){
        Vector2i position = Mouse::getPosition(window);
        if (position.y >= 0 && position.y < (rows * 32) && !overDone && !isPaused){
            if (position.x >= 0 && position.x <= (columns * 32)){
                int position2 = (position.x / 32);
                int position1 = (position.y / 32);
                int temp = (position1 * columns) + position2;
                int count = 0;
                if (square[temp].showing(count)){
                    userL = true, overDone = true;
                    int v100 = 0;
                    for (int index = 0; index < (rows * columns); index++){
                        if (square[index].withF && square[index].mine) {
                            square[index].fChanges();
                        }
                        if (square[index].mine) {
                            square[index].showing(v100);
                        }
                    }
                }
                else totalT += count;
            }
        }
        else if (position.y >= (rows * 32) && position.y < ((rows * 32) + 64)){
            if (position.x >= (((columns) * 32) - 240) && position.x < ((((columns) * 32) - 240) + 64) && !overDone){
                if (isPaused) {
                    isPaused = false;
                    paused = false;
                    play.setTexture(forNew["play"]);
                }
                else {
                    isPaused = true;
                    paused = true;
                    pauseStart = system_clock::now();
                    play.setTexture(forNew["pause"]);
                }
                play.setPosition(static_cast<float>(((columns) * 32) - 240), 32 * (static_cast<float>(rows)+0.5f));
            }
            if ((position.x >= ((((((columns) / 2.0) * 32)) - 32) + 128)) && position.x < (((columns) * 32) - 240) && !overDone){
                debug();
            }
            if ((position.x >= (((((columns) / 2.0) * 32)) - 32)) && (position.x < ((((((columns) / 2.0) * 32)) - 32) + 64))){
                Scatter();
                elapsedMilliseconds = 0;
                isPaused = false;
                pauseStart = system_clock::now();
            }
            if (position.x >= ((((columns) * 32) - 240) + 64) && position.x < ((((columns) * 32) - 240) + 128)){
                if (isPaused) {
                    isPaused = false;
                    paused = false;
                    leaderboard();
                    pauseStart = system_clock::now();
                }
                else {
                    isPaused = true;
                    paused = true;
                    pauseStart = system_clock::now();
                }
            }
        }
    }
    minutes = elapsedMilliseconds / 60000;
    seconds = (elapsedMilliseconds / 1000) % 60;
    minute_1.setTextureRect(sf::IntRect(minutes / 10 * 21, 0, 21, 32));
    minute_2.setTextureRect(sf::IntRect(minutes % 10 * 21, 0, 21, 32));
    seconds_3.setTextureRect(sf::IntRect(seconds / 10 * 21, 0, 21, 32));
    seconds_4.setTextureRect(sf::IntRect(seconds % 10 * 21, 0, 21, 32));
    events();
    draw(window);
}
void Game::debug(){
    fstream file("files/board_config.cfg");
    string line;

    getline(file ,line);
    int columns = stoi(line);

    getline(file, line);
    int rows = stoi(line);
    for (int index = 0; index < (rows * columns); index++){
        square[index].buGING();}}
void Game::events(){
    if (overDone){
        if (userL){
            face1.setTexture(forNew["lose"]);
        }
        else{
            face1.setTexture(forNew["win"]);
            daHunda.setTextureRect(Rect<int>(0, 0, 21, 32));
            daTen.setTextureRect(Rect<int>(0, 0, 21, 32));
            daOne.setTextureRect(Rect<int>(0, 0, 21, 32));}}
    else{
        face1.setTexture(forNew["happy"]);}}
void Game::JollyT(){
    float varr1 = 0; float varr2 = 0;
    fstream file("files/board_config.cfg");
    string line;
    getline(file ,line);
    int columns = stoi(line);
    getline(file, line);
    int rows = stoi(line);
    for (int index = 0; index < rows; index++){
        for (int jdex = 0; jdex < columns; jdex++){
            ScreenGenerator t = ScreenGenerator(forNew, varr1, varr2);
            square.push_back(t);
            varr1 += 32.f;}
        varr1 = 0, varr2 += 32.f;}}
void Game::Scatter(){
    fstream file("files/board_config.cfg");
    string line;
    getline(file ,line);
    int columns = stoi(line);
    getline(file, line);
    int rows = stoi(line);
    getline(file, line);
    int mines = stoi(line);
    var7.clear();
    vector<int> newNeww;
    int randomnum;
    bool getfree = false;
    for (int index = 0; index < mines; index++){
        while (!getfree){
            randomnum = rand() % (rows * columns);
            if (find(newNeww.begin(), newNeww.end(), randomnum) == newNeww.end()){
                newNeww.push_back(randomnum);
                getfree = true;}}
        getfree = false;}
    auto shift = newNeww.begin();
    for (int jdex = 0; jdex < (rows * columns); jdex++){
        shift = find(newNeww.begin(), newNeww.end(), jdex);
        if (shift == newNeww.end()){
            var7.push_back(false);}
        else{
            var7.push_back(true);}}
    minesActual();
    bigSquare();
    totalF = mines;
    refresh();
    totalM = mines;
    totalT = 0;
    userL = false, overDone = false;
}
void Game::minesActual(){
    fstream file("files/board_config.cfg");
    string line;
    getline(file ,line);
    int columns = stoi(line);
    getline(file, line);
    int rows = stoi(line);
    for (int index = 0; index < (rows * columns); index++){
        square[index].slay(var7[index]);}}
void Game::refresh(){
    int copy = abs(totalF);
    int onesplace = copy % 10;
    copy /= 10;
    int tensplace = copy % 10;

    if (totalF >= 0){
        daHunda.setTextureRect(Rect<int>(21 * 0, 0, 21, 32));
    }
    else{
        daHunda.setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
    }
    daTen.setTextureRect(Rect<int>(21 * tensplace, 0, 21, 32));
    daOne.setTextureRect(Rect<int>(21 * onesplace, 0, 21, 32));}
void Game::bigSquare() {
    int columns, rows;
    readBoardConfig(columns, rows);
    initSquareSurroundings(columns, rows);
}
void Game::readBoardConfig(int& columns, int& rows) {
    fstream file("files/board_config.cfg");
    string line;
    getline(file ,line);
    columns = stoi(line);
    getline(file, line);
    rows = stoi(line);
}
void Game::initSquareSurroundings(int columns, int rows) {
    for (int index = 0; index < (rows * columns); index++){
        square[index].surround.clear();
        for (int jdex = 0; jdex < 8; jdex++){
            square[index].surround.push_back(nullptr);}
        initSquareSurroundingsAtIndex(index, columns, rows);
    }
}
void Game::initSquareSurroundingsAtIndex(int index, int columns, int rows) {
    if (index == 0){
        square[index].surround[4] = &(square[index + 1]);
        square[index].surround[6] = &(square[index + columns]);
        square[index].surround[7] = &(square[index + (columns + 1)]);}
    else if (index == (columns - 1)){
        square[index].surround[3] = &(square[index - 1]);
        square[index].surround[5] = &(square[index + (columns - 1)]);
        square[index].surround[6] = &(square[index + columns]);}
    else if (index == ((rows * columns) - 25)){
        square[index].surround[4] = &(square[index + 1]);
        square[index].surround[1] = &(square[index - columns]);
        square[index].surround[2] = &(square[index - (columns - 1)]);}
    else if (index == ((rows * columns) - 1)){
        square[index].surround[3] = &(square[index - 1]);
        square[index].surround[1] = &(square[index - columns]);
        square[index].surround[0] = &(square[index - (columns + 1)]);}
    else if (index < (columns - 1)){
        square[index].surround[3] = &(square[index - 1]);
        square[index].surround[4] = &(square[index + 1]);
        square[index].surround[5] = &(square[index + (columns - 1)]);
        square[index].surround[6] = &(square[index + columns]);
        square[index].surround[7] = &(square[index + (columns + 1)]);}
    else if (index > ((rows * columns) - 25)){
        square[index].surround[3] = &(square[index - 1]);
        square[index].surround[4] = &(square[index + 1]);
        square[index].surround[2] = &(square[index - (columns - 1)]);
        square[index].surround[1] = &(square[index - columns]);
        square[index].surround[0] = &(square[index - (columns + 1)]);}
    else if ((index % columns) == 0){
        square[index].surround[4] = &(square[index + 1]);
        square[index].surround[6] = &(square[index + columns]);
        square[index].surround[7] = &(square[index + (columns + 1)]);
        square[index].surround[1] = &(square[index - columns]);
        square[index].surround[2] = &(square[index - (columns - 1)]);}
    else if (((index - (columns - 1)) % columns) == 0){
        square[index].surround[3] = &(square[index - 1]);
        square[index].surround[0] = &(square[index - (columns + 1)]);
        square[index].surround[1] = &(square[index - columns]);
        square[index].surround[5] = &(square[index + (columns - 1)]);
        square[index].surround[6] = &(square[index + columns]);}
    else{
        square[index].surround[3] = &(square[index - 1]);
        square[index].surround[4] = &(square[index + 1]);
        square[index].surround[5] = &(square[index + (columns - 1)]);
        square[index].surround[6] = &(square[index + columns]);
        square[index].surround[7] = &(square[index + (columns + 1)]);
        square[index].surround[2] = &(square[index - (columns - 1)]);
        square[index].surround[1] = &(square[index - columns]);
        square[index].surround[0] = &(square[index - (columns + 1)]);}
    square[index].newSMILES(forNew);}
//void Game::draw(RenderWindow &window){
//    fstream file("files/board_config.cfg");
//    string line;
//    getline(file ,line);
//    int columns = stoi(line);
//    getline(file, line);
//    int rows = stoi(line);
//    for (int index = 0; index < (rows * columns); index++)
//        square[index].draw(window);
//    window.draw(face1), window.draw(bugORnot), window.draw(play), window.draw(mainLeaders);
//    window.draw(daHunda), window.draw(daTen), window.draw(daOne);
//    window.draw(minute_1), window.draw(minute_2), window.draw(seconds_3), window.draw(seconds_4);
//}

void Game::draw(RenderWindow &window) {
    window.draw(bugORnot), window.draw(daHunda), window.draw(daTen), window.draw(daOne), window.draw(minute_1), window.draw(minute_2), window.draw(seconds_3), window.draw(seconds_4);
    for(auto &square : square) {
        square.draw(window, paused);
    }
    window.draw(pause), window.draw(play), window.draw(mainLeaders), window.draw(face1);
}

