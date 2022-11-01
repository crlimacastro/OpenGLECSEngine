#include "rendering.h"

#include <glm/gtc/type_ptr.hpp>

#include "WindowPlugin.h"

#include "GLShaderProgram.h"
#include "GLVertexArrayObject.h"
#include "GLTexture.h"
#include "GLVertexBufferObject.h"
#include "GLElementBufferObject.h"

#include "transforms.h"
#include "Mesh.h"
#include "PerspectiveCamera.h"

using namespace std;
using namespace fae;

void SetupRenderer(entt::registry& registry)
{
	// init glew
	glewExperimental = GL_TRUE;
	glewInit();

	// setup gl settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	registry.ctx().emplace<Renderer>();
}

void SetupCoreShader(entt::registry& registry)
{
	static GLShaderProgram coreShader;
	coreShader
		.LoadVertexFromFile("core_vertex.glsl")
		.LoadFragmentFromFile("core_fragment.glsl")
		.Link();
	registry.ctx().emplace<CoreShader>(coreShader);
}

void ClearScreen(entt::registry& registry)
{
	auto& renderer = registry.ctx().at<Renderer>();
	float r = renderer.clearColor.r;
	float g = renderer.clearColor.g;
	float b = renderer.clearColor.b;
	float a = renderer.clearColor.a;
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void UpdateLightUniforms(entt::registry& registry)
{
	auto& coreShader = registry.ctx().at<CoreShader>();

	// TODO refactor lights
	// lights
	glm::vec3 lightPos0{ 0, 0, -2 };
	coreShader.shader.setv3f("light_pos_0", lightPos0);
}

void UpdatePerspectiveCameraUniforms(entt::registry& registry)
{
	auto& window = registry.ctx().at<Window>();
	auto& coreShader = registry.ctx().at<CoreShader>();
	for (auto [entity, transform, camera] : registry.view<const GlobalTransform, const PerspectiveCamera>().each())
	{
		coreShader.shader.setv3f("camera_pos", transform.position);
		coreShader.shader.setm4f("view", transform.GetViewMatrix());
		coreShader.shader.setm4f("projection", camera.GetProjectionMatrix(window.GetBufferAspectRatio()));
	}
}

void RenderMeshRenderersWithTransforms(entt::registry& registry)
{
	for (auto [entity, transform, meshRenderer] : registry.view<const GlobalTransform, const MeshRenderer>().each())
	{
		if (!meshRenderer.mesh || !meshRenderer.material) continue;

		// init vao
		GLVertexArrayObject vao;
		vao.Bind();
		GLVertexBufferObject vbo{ meshRenderer.mesh->vertices };
		vbo.Bind();
		GLElementBufferObject ebo{ meshRenderer.mesh->indices };
		ebo.Bind();

		// enable attributes
		GLuint attribLoc = 0;

		// position
		attribLoc = glGetAttribLocation(meshRenderer.material->shader, "vertex_position");
		glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(attribLoc);

		// color
		attribLoc = glGetAttribLocation(meshRenderer.material->shader, "vertex_color");
		glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(attribLoc);

		// uvcoord
		attribLoc = glGetAttribLocation(meshRenderer.material->shader, "vertex_texcoord");
		glVertexAttribPointer(attribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uvcoord));
		glEnableVertexAttribArray(attribLoc);

		// normal
		attribLoc = glGetAttribLocation(meshRenderer.material->shader, "vertex_normal");
		glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(attribLoc);

		((GLTexture&)meshRenderer.material->diffuseTex).Bind();
		((GLTexture&)meshRenderer.material->specularTex).Bind(1);

		meshRenderer.material->shader.Bind();
		meshRenderer.material->Send();
		meshRenderer.material->shader.setm4f("model", transform);

		glDrawElements(GL_TRIANGLES, (GLsizei)meshRenderer.mesh->indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void SwapBuffers(entt::registry& registry)
{
	auto& window = registry.ctx().at<Window>();
	glfwSwapBuffers(window);
	glFlush();
}

void fae::RendererPlugin(App& app)
{
	app.AddStartSystem(SetupRenderer, FAE_SYSTEM_ORDER_START_RENDERING)
		.AddStartSystem(SetupCoreShader, FAE_SYSTEM_ORDER_START_RENDERING + 1)
		.AddUpdateSystem(ClearScreen, FAE_SYSTEM_ORDER_UPDATE_RENDERING_BEGIN)
		.AddUpdateSystem(UpdateLightUniforms, FAE_SYSTEM_ORDER_UPDATE_RENDERING_BEGIN)
		.AddUpdateSystem(UpdatePerspectiveCameraUniforms, FAE_SYSTEM_ORDER_UPDATE_RENDERING_BEGIN)
		.AddUpdateSystem(RenderMeshRenderersWithTransforms, FAE_SYSTEM_ORDER_UPDATE_RENDERING_DRAW)
		.AddUpdateSystem(SwapBuffers, FAE_SYSTEM_ORDER_UPDATE_RENDERING_END);
}