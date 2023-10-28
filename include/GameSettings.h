#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "Text.h"
#include "World.h"

class GameSettings
{
private:

	World* world;

	Text* txt_game_speed;

	Text* txt_wireframe;

	Text* txt_textures;

	Text* txt_shading;

	Text* txt_night_mode;

	Text* txt_camera_mode;

	Text* txt_quit;

	Text* key_game_speed;

	Text* key_wireframe;

	Text* key_textures;

	Text* key_shading;

	Text* key_night_mode;

	Text* key_camera_mode;

	Text* key_quit;

public:

	GameSettings(World* world);

	void display_settings();

};

#endif