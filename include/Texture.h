#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <memory>

enum class ImageFormat {
	PNG, JPEG
};

class Texture {

	using BYTE = unsigned char;

private:

	unsigned int id;

public:

	Texture() = default;

	Texture(std::vector<BYTE> data, unsigned int width, unsigned int height);

	void bind() const;

	bool empty() const;

};

#endif