#pragma once
#include <vector>
#include "Vertex.h"

namespace fae
{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		static constexpr Mesh Quad() {
			return {
				{
					{ { -.5f, .5f, 0 }, { 1, 1, 1 }, { 0, 1 }, { 0, 0, 1 } },
					{ { -.5f, -.5f , 0 }, { 1, 1, 1 }, { 0, 0 }, { 0, 0, 1 } },
					{ { .5f, -.5f, 0 }, { 1, 1, 1 }, { 1, 0 }, { 0, 0, 1 } },
					{ { .5f, .5f, 0 }, { 1, 1, 1 }, { 1, 1 }, { 0, 0, 1 } },
				},
				{ 0, 1, 2, 0, 2, 3 }
			};
		};
	};
}