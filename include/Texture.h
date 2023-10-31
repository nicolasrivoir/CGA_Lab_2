#ifndef TEXTURE_H
#define TEXTURE_H

using BYTE = unsigned char;

struct Texture {
	const unsigned int id;
	const BYTE* data;
	const unsigned int width;
	const unsigned int height;
};

#endif