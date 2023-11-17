#ifndef GLSL_H
#define GLSL_H

#include <memory>
#include <string_view>

class GLSL {

	using BYTE = unsigned char;

private:

	std::shared_ptr<const BYTE> source;

public:

	GLSL(std::string_view fname);

	const BYTE* getSource();

};

#endif