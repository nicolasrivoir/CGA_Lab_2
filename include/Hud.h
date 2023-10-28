// Hud.h
#ifndef HUD_H
#define HUD_H

#include "timer.h"
#include <string>
#include "SDL.h"
#include "SDL_opengl.h"

#include "utils.h"
#include "Text.h"

using namespace std;
using namespace math;

class Hud {
public:
    Hud();
    Text* score_text;
    Text* time_text;
    void draw(int score);

//private:
    SDL_Texture* fontTexture;
};

#endif // HUD_H
