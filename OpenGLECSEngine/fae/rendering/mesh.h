#pragma once
#include <vector>
#include "Vertex.h"

namespace fae
{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

	};
	namespace meshes
	{
		const Mesh Quad = {
				{
					{ { -.5f, .5f, 0 }, { 1, 1, 1 }, { 0, 1 }, { 0, 0, 1 } },
					{ { -.5f, -.5f , 0 }, { 1, 1, 1 }, { 0, 0 }, { 0, 0, 1 } },
					{ { .5f, -.5f, 0 }, { 1, 1, 1 }, { 1, 0 }, { 0, 0, 1 } },
					{ { .5f, .5f, 0 }, { 1, 1, 1 }, { 1, 1 }, { 0, 0, 1 } },
				},
				{ 0, 1, 2, 0, 2, 3 },
		};

		const Mesh Tri = {
			{
				{ { 0, .5f, 0 }, { 1, 1, 1 }, { .5f, 1 }, { 0, 0, 1 } },
				{ { -.5f, -.5f, 0 }, { 1, 1, 1 }, { 0, 0 }, { 0, 0, 1 } },
				{ { .5f, -.5f, 0 }, { 1, 1, 1 }, { 1, 0 }, { 0, 0, 1 } },
			},
			{0, 1, 2},
		};
	}
}