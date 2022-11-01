#pragma once
#include <glm/glm.hpp>
#include "IShaderProgram.h"
#include "Mesh.h"
#include "Material.h"
#include "App.h"

namespace fae {
#define FAE_SYSTEM_ORDER_START_RENDERING -2048
#define FAE_SYSTEM_ORDER_UPDATE_RENDERING_BEGIN 2048-512
#define FAE_SYSTEM_ORDER_UPDATE_RENDERING_DRAW 2048
#define FAE_SYSTEM_ORDER_UPDATE_RENDERING_END 2048+512

	// Resources

	/// <summary>
	/// Resource containing globally shared rendering data.
	/// </summary>
	struct Renderer
	{
		glm::vec4 clearColor = { 1, 1, 1, 1 };
	};

	/// <summary>
	/// Resource containing the main rendering shader.
	/// </summary>
	struct CoreShader
	{
		IShaderProgram& shader;
	};

	// Components

	/// <summary>
	/// Component containing mesh drawing data.
	/// </summary>
	struct MeshRenderer
	{
		Mesh* mesh;
		Material* material;
	};

	// Systems

	void RendererPlugin(App& app);
}