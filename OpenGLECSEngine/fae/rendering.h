#pragma once
#include <glm/glm.hpp>
#include "rendering/IShaderProgram.h"
#include "rendering/Mesh.h"
#include "rendering/Material.h"

#include "rendering/rendering_plugins.h"
#include "App.h"

namespace fae {
	// Resources

	/// <summary>
	/// [Resource] containing the main rendering shader.
	/// </summary>
	struct MainShader
	{
		IShaderProgram& shader;
	};

	// Components

	/// <summary>
	/// [Component] containing mesh drawing data.
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