#include "GameSettings.h"
#include "Renderer.h"

#include <iomanip>
#include <sstream>

GameSettings::GameSettings(World* world)
{
	this->world = world;
	txt_game_speed = new Text("SPEED:1.0x", Vector2(-0.80f, 0.60f));
	txt_wireframe = new Text("WIREFRAME:NO", Vector2(-0.80f, 0.40f));
	txt_textures = new Text("TEXTURES:YES", Vector2(-0.80f, 0.20f));
	txt_shading = new Text("SHADING:SMOOTH", Vector2(-0.80f, 0.0f));
	txt_night_mode = new Text("DAYTIME", Vector2(-0.80f, -0.20f));
	txt_camera_mode = new Text("CAMERA:NORMAL", Vector2(-0.80f, -0.40f));
	txt_quit = new Text("QUIT", Vector2(-0.80f, -0.60f));

	key_game_speed = new Text("UP,DOWN", Vector2(0.50f, 0.60f));
	key_wireframe = new Text("R", Vector2(0.50f, 0.40f));
	key_textures = new Text("T", Vector2(0.50f, 0.20f));
	key_shading = new Text("Y", Vector2(0.50f, 0.0f));
	key_night_mode = new Text("U", Vector2(0.50f, -0.20f));
	key_camera_mode = new Text("V", Vector2(0.50f, -0.40f));
	key_quit = new Text("Q", Vector2(0.50f, -0.60f));
}

void GameSettings::display_settings()
{
	Renderer renderer = *Renderer::get_instance();
	bool texts_enabled = renderer.are_textures_enabled();
	bool wf_enabled = renderer.is_wireframe_enabled();
	bool sshading_enabled = renderer.is_smooth_shading_enabled();
	string camera_mode = world->getCameraMode();

	renderer.enable_textures(true);
	renderer.enable_wireframes(false);

	// GAME SPEED
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << Timer::getInstance()->speed;
	std::string speed_value = stream.str();

	txt_game_speed->change_text("SPEED:" + speed_value + "X");
	renderer.draw_textbox(*txt_game_speed);
	renderer.draw_textbox(*key_game_speed);

	// WIREFRAME

	std::string wf_value = wf_enabled ? "YES" : "NO";
	txt_wireframe->change_text("WIREFRAME:" + wf_value);
	renderer.draw_textbox(*txt_wireframe);
	renderer.draw_textbox(*key_wireframe);
	
	// TEXTURES

	std::string tex_value = texts_enabled ? "YES" : "NO";
	txt_textures->change_text("TEXTURES:" + tex_value);
	renderer.draw_textbox(*txt_textures);
	renderer.draw_textbox(*key_textures);
	
	// SHADING

	std::string sshading_value = sshading_enabled ? "SMOOTH" : "FLAT";
	txt_shading->change_text("SHADING:" + sshading_value);
	renderer.draw_textbox(*txt_shading);
	renderer.draw_textbox(*key_shading);
	
	// NIGHT_MODE

	std::string night_value = world->is_nighttime ? "YES" : "NO";
	txt_night_mode->change_text("NIGHT MODE:" + night_value);
	renderer.draw_textbox(*txt_night_mode);
	renderer.draw_textbox(*key_night_mode);

	// CAMERA_MODE

	txt_camera_mode->change_text("CAMERA:" + (string)camera_mode);
	renderer.draw_textbox(*txt_camera_mode);
	renderer.draw_textbox(*key_camera_mode);

	// QUIT
	renderer.draw_textbox(*txt_quit);
	renderer.draw_textbox(*key_quit);

	renderer.enable_textures(texts_enabled);
	renderer.enable_wireframes(wf_enabled);
}
