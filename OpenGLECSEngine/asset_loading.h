#pragma once
#include <vector>
#include "vertex.h"

namespace fae {
	std::vector<Vertex> LoadOBJ(const char* filename);
}