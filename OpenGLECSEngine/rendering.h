#pragma once
#include <glm/glm.hpp>
#include "IShaderProgram.h"
#include "Mesh.h"
#include "Material.h"
#include "App.h"

namespace fae {
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
		const Mesh* mesh;
		const Material* material;
	};

	// Systems

	void SetupRenderer(entt::registry& registry);
	void SetupCoreShader(entt::registry& registry);
	void ClearScreen(entt::registry& registry);
	void UpdatePerspectiveCameraUniforms(entt::registry& registry);
	void RenderMeshRenderersWithTransforms(entt::registry& registry);
	void SwapBuffers(entt::registry& registry);

	// Plugins

	void RendererPlugin(App& app);
}