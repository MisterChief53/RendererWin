#pragma once
#include "Face.h"
#include <string>
class Parser
{
public:
	static void parse(std::vector<Face>& faces, std::string path);
};

