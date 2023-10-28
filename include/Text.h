#pragma once
#include "Object.h"

#define W 1.0f/9.0f
#define H 1.0f/9.0f

class Text : public Object
{

public:

	bool has_charmap = false;

	Text(std::string str, Vector2 pos);

	Vector2 get_char_coord(char c);

	void change_text(std::string text);

};

