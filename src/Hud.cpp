#include "HUD.h"
#include "Renderer.h"

Hud::Hud()
{
    score_text = new Text("SCORE:0", Vector2(-0.95f, 0.85f));
    time_text = new Text("00:00", Vector2(0.6f, 0.85f));
}

void Hud::draw(int score)
{
    //Text score_text("SCORE:" + std::to_string((int)score), Vector2(-0.95f, 0.85f));
    score_text->change_text("SCORE:" + std::to_string((int)score));
    Renderer::get_instance()->draw_textbox(*score_text);

    int played_time = (int)Timer::getInstance()->getPlayedTime();
    //Text timer_text(std::to_string(played_time), Vector2(0.6f, 0.85f));
    time_text->change_text(std::to_string(played_time));
    Renderer::get_instance()->draw_textbox(*time_text);
}