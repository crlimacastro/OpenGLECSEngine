#pragma once
#include <entt/entt.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "App.h"

namespace fae {
	// Resources

	/// <summary>
	/// [Resource] Add to the App before Start stage to set Window data.
	/// </summary>
	struct WindowDescriptor
	{
		const char* title = "";
		size_t width = 640;
		size_t height = 480;
		bool isResizable = false;
		int glfwVersionMajor = 3;
		int glfwVersionMinor = 3;
	};

	/// <summary>
	/// [Resource] Window data.
	/// </summary>
	struct Window
	{
		GLFWwindow* window;

		Window& SetTitle(const char* value);
		Window& SetIsResizable(bool value);

		size_t GetWidth() const;
		size_t GetHeight() const;
		float GetAspectRatio() const;

		size_t GetBufferWidth() const;
		size_t GetBufferHeihgt() const;
		float GetBufferAspectRatio() const;

		operator GLFWwindow* () { return window; }
		operator const GLFWwindow* () const { return window; }
	private:
	};

	// Systems

	void SetupWindow(entt::registry& registry);
	void UpdateWindow(entt::registry& registry);
	void CleanupWindow(entt::registry& registry);

	// Plugins

	void WindowPlugin(App& app);
}