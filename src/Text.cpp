#include "Text.h"

#include "FileLoader.h"

Text::Text(std::string str, Vector2 pos)
{
	position = { pos.x, pos.y, 0 };

	if (!has_charmap) {
		texture = new Texture(FileLoader::load_PNG("data/textures/bitmap.png"));
		has_charmap = true;
	}

	for (int i = 0; i < str.length(); i++) {
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * i,0,0)/10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * (i+1),1,0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * i,1,0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * i,0,0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * (i+1),0,0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * (i+1),1,0) / 10.0f);

		Vector2 uv = get_char_coord(str[i]);
		mesh.texture_map.push_back(uv);
		mesh.texture_map.push_back({ uv.x + W, uv.y + H});
		mesh.texture_map.push_back({ uv.x, uv.y + H});
		mesh.texture_map.push_back(uv);
		mesh.texture_map.push_back({ uv.x + W, uv.y});
		mesh.texture_map.push_back({ uv.x + W, uv.y + H});

		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
	}
}

Vector2 Text::get_char_coord(char c)
{
	Vector2 res;
	Vector2 pos = { 0, 8 };
	int diff = c - ',';
	return { W * (pos.x + (diff % 9)), H * (pos.y - (diff / 9)) };
}

void Text::change_text(std::string text)
{
	mesh.vertices.clear();
	mesh.texture_map.clear();
	mesh.normals.clear();
	for (int i = 0; i < text.length(); i++) {
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * i, 0, 0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * (i + 1), 1, 0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * i, 1, 0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * i, 0, 0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * (i + 1), 0, 0) / 10.0f);
		mesh.vertices.push_back(Vector3((2.0f / 3.0f) * (i + 1), 1, 0) / 10.0f);


		Vector2 uv = get_char_coord(text[i]);
		mesh.texture_map.push_back(uv);
		mesh.texture_map.push_back({ uv.x + W, uv.y + H });
		mesh.texture_map.push_back({ uv.x, uv.y + H });
		mesh.texture_map.push_back(uv);
		mesh.texture_map.push_back({ uv.x + W, uv.y });
		mesh.texture_map.push_back({ uv.x + W, uv.y + H });

		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
		mesh.normals.push_back({ 0,0,0 });
	}
}
