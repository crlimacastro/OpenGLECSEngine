#include "rendering.h"

#include <glm/gtc/type_ptr.hpp>

#include "window.h"

#include "rendering/renderer.h"

#include "rendering/gl/GLRenderer.h"

#include "transforms.h"
#include "rendering/Mesh.h"
#include "rendering/camera/PerspectiveCamera.h"

using namespace std;
using namespace fae;

void fae::SetupRenderer(entt::registry& registry)
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

void fae::SetupCoreShader(entt::registry& registry)
{
	static GLShaderProgram coreShader;
	coreShader
		.LoadVertexFromFile("main.vs")
		.LoadFragmentFromFile("main.fs")
		.Link();
	registry.ctx().emplace<MainShader>(coreShader);
}

void fae::ClearScreen(entt::registry& registry)
{
	auto& renderer = registry.ctx().at<Renderer>();
	float r = renderer.clearColor.r;
	float g = renderer.clearColor.g;
	float b = renderer.clearColor.b;
	float a = renderer.clearColor.a;
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void fae::UpdatePerspectiveCameraUniforms(entt::registry& registry)
{
	auto& window = registry.ctx().at<Window>();
	auto& coreShader = registry.ctx().at<MainShader>();
	for (auto [entity, localTransform, globalTransform, camera] : registry.view<const GlobalTransform, const LocalTransform, const PerspectiveCamera>().each())
	{
		Transform transform = localTransform * globalTransform;
		coreShader.shader.setv3f("camera_pos", transform.position);
		coreShader.shader.setm4f("view", transform.GetViewMatrix());
		coreShader.shader.setm4f("projection", camera.GetProjectionMatrix(window.GetBufferAspectRatio()));
	}
}

void fae::RenderMeshRenderersWithTransforms(entt::registry& registry)
{
	for (auto [entity, globalTransform, localTransform, meshRenderer] : registry.view<const GlobalTransform, const LocalTransform, const MeshRenderer>().each())
	{
		if (!meshRenderer.mesh || !meshRenderer.material) continue;

		// init vao
		GLVertexArrayObject vao;
		vao.Bind();
		GLVertexBufferObject vbo{ meshRenderer.mesh->vertices };
		vbo.Bind();
		GLElementBufferObject* ebo = nullptr;
		if (meshRenderer.mesh->indices.size() > 0)
		{
			ebo = new GLElementBufferObject{ meshRenderer.mesh->indices };
			ebo->Bind();
		}

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

		meshRenderer.material->Send();
		auto test = localTransform * globalTransform;
		meshRenderer.material->shader.setm4f("model", localTransform * globalTransform);
		meshRenderer.material->shader.Bind();

		if (meshRenderer.mesh->indices.size() <= 0)
		{
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(meshRenderer.mesh->vertices.size()));
		}
		else
		{
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(meshRenderer.mesh->indices.size()), GL_UNSIGNED_INT, 0);
		}

		if (meshRenderer.mesh->indices.size() > 0 && ebo != nullptr)
		{
			delete ebo;
		}
	}
}

void fae::SwapBuffers(entt::registry& registry)
{
	auto& window = registry.ctx().at<Window>();
	glfwSwapBuffers(window);
	glFlush();
}

void fae::RendererPlugin(App& app)
{
	app.AddPlugin(RenderingPlugins)
		.AddStartSystem(SetupRenderer, FAE_SYSTEM_ORDER_SETUP)
		.AddStartSystem(SetupCoreShader, FAE_SYSTEM_ORDER_SETUP)
		.AddUpdateSystem(ClearScreen, FAE_SYSTEM_ORDER_PRE_UPDATE)
		.AddUpdateSystem(UpdatePerspectiveCameraUniforms)
		.AddUpdateSystem(RenderMeshRenderersWithTransforms)
		.AddUpdateSystem(SwapBuffers, FAE_SYSTEM_ORDER_POST_UPDATE);
}