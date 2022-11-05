#pragma once
#include <vector>
#include "mesh.h"
#include "Material.h"

namespace fae
{
	struct Model
	{
		std::vector<Mesh&> meshes;
		std::vector<Material&> materials;
		std::vector<std::vector<size_t>> materialIndexToMeshesIndex;
	};
}