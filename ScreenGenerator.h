#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class ScreenGenerator{
    Sprite standard, overlay, individual, pictureF;
    bool buggy, gamePaused;

public:
    ScreenGenerator(map<string,Texture> &textures, float count1, float count2);
    vector<ScreenGenerator*> surround;
    int mineTotal{};
    bool mine, withF, shown, fChanges(), showing(int &totalNew);
    void slay(bool mine_var), newSMILES(map<string, Texture> &textures), buGING(), draw(RenderWindow &dubs, bool gamePaused);
};
ScreenGenerator::ScreenGenerator(map<string, Texture> &textures, float count1, float count2){
    standard.setPosition(count1, count2), overlay.setPosition(count1, count2);
    pictureF.setPosition(count1, count2), individual.setPosition(count1, count2);
    standard.setTexture(textures["revealed"]), overlay.setTexture(textures["hidden"]), pictureF.setTexture(textures["flag"]);

    pictureF.setColor(Color(255, 255, 255, 0)), mine = false, shown = false, withF = false, buggy = false;
}
//void ScreenGenerator::draw(RenderWindow &dubs){
//    dubs.draw(standard), dubs.draw(overlay), dubs.draw(individual), dubs.draw(pictureF);
//}
void ScreenGenerator::draw(RenderWindow &dubs, bool gamePaused){
    dubs.draw(standard);
    dubs.draw(individual);
    dubs.draw(pictureF);

    if (!gamePaused) {
        dubs.draw(overlay);
    }
}

void ScreenGenerator::buGING(){
    if (!shown && mine){
        if (buggy){
            buggy = false, individual.setColor(Color(255, 255, 255, 0));
        }
        else{
            buggy = true, individual.setColor(Color(255, 255, 255, 255));
        }
    }
}
void ScreenGenerator::slay(bool mine_var){
    mine = mine_var;
}

void ScreenGenerator::newSMILES(map<string, Texture> &textures){
    mineTotal = 0;
    for (int index = 0; index < 8; index++){
        if (surround[index] != nullptr && surround[index]->mine){
            mineTotal++;
        }
    }
    if (mine)
        individual.setTexture(textures["bomb"]);
    else{
        switch (mineTotal){
            case 1: individual.setTexture(textures["one"]); break;
            case 2: individual.setTexture(textures["two"]); break;
            case 3: individual.setTexture(textures["three"]); break;
            case 4: individual.setTexture(textures["four"]); break;
            case 5: individual.setTexture(textures["five"]); break;
            case 6: individual.setTexture(textures["six"]); break;
            case 7: individual.setTexture(textures["seven"]); break;
            case 8: individual.setTexture(textures["eight"]); break;
            default: individual.setTexture(textures["revealed"]); break;
        }
    }
    individual.setColor(Color(255, 255, 255, 0)), pictureF.setColor(Color(255, 255, 255, 0)), overlay.setColor(Color(255, 255, 255, 255));
    shown = false, withF = false, buggy = false;
}
bool ScreenGenerator::showing(int &totalNew){
    if (!shown && !withF){
        shown = true;
        totalNew++;
        overlay.setColor(Color(255, 255, 255, 0)), individual.setColor(Color(255, 255, 255, 255));
        if (!mine && mineTotal == 0){
            for (int index = 0; index < 8; index++){
                if (surround[index] != nullptr && !(surround[index]->mine))
                    surround[index]->showing(totalNew);
            }
        }
    }
    return mine;
}
bool ScreenGenerator::fChanges(){
    if (!shown){
        if (withF){
            withF = false, pictureF.setColor(Color(255, 255, 255, 0));
        }
        else{
            withF = true, pictureF.setColor(Color(255, 255, 255, 255));
        }
    }
    return withF;
}

