#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <SOIL2/SOIL2.h>
#include "App.h"
#include "Vertex.h"
#include "Shader.h"

namespace gfe {
	/// <summary>
/// Add as a Resource to the App to set Window information on Start.
/// </summary>
	struct WindowDescriptor
	{
		const char* title = "";
		int width = 640;
		int height = 480;
		int isResizable = GL_FALSE;
	};

	struct Window
	{
		GLFWwindow* window;

		Window& SetTitle(const char* value)
		{
			glfwSetWindowTitle(window, value);
			return *this;
		}

		Window& SetIsResizable(int value)
		{
			glfwWindowHint(GLFW_RESIZABLE, value);
			return *this;
		}

		operator GLFWwindow* () { return window; }
		operator const GLFWwindow* () const { return window; }
	};

	void Resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void SetupWindow(const void*, entt::registry& registry)
	{
		// init glfw
		glfwInit();

		// use default or user-defined WindowDescriptor
		WindowDescriptor descriptor;
		if (registry.ctx().contains<WindowDescriptor>()) {
			descriptor = registry.ctx().at<WindowDescriptor>();
		}

		// create window
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_RESIZABLE, descriptor.isResizable);

		auto* window = glfwCreateWindow(descriptor.width, descriptor.height, descriptor.title, NULL, NULL);

		// set resize funciton
		glfwSetFramebufferSizeCallback(window, Resize);

		// make window the current GL context
		glfwMakeContextCurrent(window);

		// init glew
		glewExperimental = GL_TRUE;
		glewInit();

		// gl options
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// create Window resource
		registry.ctx().emplace<Window>(window);
	}

	void UpdateWindow(const void*, entt::registry& registry)
	{
		// get resources
		auto& window = registry.ctx().at<Window>();
		auto& app = registry.ctx().at<App&>();

		// poll events
		glfwPollEvents();

		// check if window should close
		if (glfwWindowShouldClose(window))
		{
			app.isRunning = false;
			return;
		}

		// draw

		// draw > clear
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// draw > start

		// ==================== TODO move into some render pipeline ====================
		Shader test("vertex_core.glsl", "fragment_core.glsl");

		Vertex vertices[]{
			{ glm::vec3{ -0.5f, 0.5, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec2{ 0, 1 } },
			{ glm::vec3{ -0.5, -0.5 , 0 }, glm::vec3{ 0, 1, 0 }, glm::vec2{ 0, 0 } },
			{ glm::vec3{ 0.5, -0.5, 0 }, glm::vec3{ 0, 0, 1 }, glm::vec2{ 1, 0 } },
			{ glm::vec3{ 0.5f, 0.5, 0 }, glm::vec3{ 1, 1, 0 }, glm::vec2{ 1, 1 } },
		};
		unsigned nVerts = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[]{
			0, 1, 2,
			0, 2, 3
		};

		unsigned nIndices = sizeof(indices) / sizeof(GLuint);

		// generate VAO, VBO, EBO
		GLuint VAO;
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// enable attributes
		GLuint attribLoc = 0;

		// position
		attribLoc = glGetAttribLocation(test, "vertex_position");
		glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(attribLoc);

		// color
		attribLoc = glGetAttribLocation(test, "vertex_color");
		glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(attribLoc);

		// texcoord
		attribLoc = glGetAttribLocation(test, "vertex_texcoord");
		glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(attribLoc);

		glBindVertexArray(0);

		// drawing texture
		GLuint texture0;
		glGenTextures(1, &texture0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		int texWidth = 0;
		int texHeight = 0;
		unsigned char* image = SOIL_load_image("brick.jpg", &texWidth, &texHeight, NULL, SOIL_LOAD_RGBA);
		if (image) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(image);
		}

		// use shader program
		glUseProgram(test);

		// update uniforms
		glUniform1i(glGetUniformLocation(test, "texture0"), 0);

		// activate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		// bind VAO
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteTextures(1, &texture0);

		// ==================== end of TODO ====================

		// draw > end
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void CleanupWindow(const void*, entt::registry& registry)
	{
		auto& window = registry.ctx().at<Window>();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowPlugin(App& app)
	{
		app.AddStartSystem(SetupWindow)
			.AddUpdateSystem(UpdateWindow)
			.AddStopSystem(CleanupWindow);
	}
}