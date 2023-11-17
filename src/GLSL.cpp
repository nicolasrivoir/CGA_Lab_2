#include "GLSL.h"

#include <iostream>
#include <fstream>

using BYTE = unsigned char;

GLSL::GLSL(std::string_view fname)
{
	int size;
	char* memblock = NULL;

	// file read based on example in cplusplus.com tutorial
	// ios::ate opens file at the end
	std::ifstream file(fname.data(), std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		size = (int)file.tellg(); // get location of file pointer i.e. file size
		memblock = new char[size + 1]; // create buffer with space for null char
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();
		memblock[size] = 0;
		std::cout << "file " << fname << " loaded" << std::endl;
	}
	else
	{
		std::cout << "Unable to open file " << fname << std::endl;
		// should ideally set a flag or use exception handling
		// so that calling function can decide what to do now
	}
	source = std::shared_ptr<const BYTE>(reinterpret_cast<BYTE*>(memblock));
}

const BYTE* GLSL::getSource()
{
	return source.get();
}
