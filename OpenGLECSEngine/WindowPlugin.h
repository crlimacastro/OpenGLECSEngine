#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "App.h"

namespace gfe {
	/// <summary>
	/// Add as a Resource to the App to set Window information on Start.
	/// </summary>
	struct WindowDescriptor
	{
		const char* title = "";
		size_t width = 640;
		size_t height = 480;
		bool isResizable = false;
	};

	struct Window
	{
		GLFWwindow* window;

		Window& SetTitle(const char* value);
		Window& SetIsResizable(int value);

		operator GLFWwindow* () { return window; }
		operator const GLFWwindow* () const { return window; }
	};

	void WindowPlugin(App& app);
}