#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "App.h"

namespace fae {
#define FAE_SYSTEM_ORDER_START_WINDOW -4096
#define FAE_SYSTEM_ORDER_UPDATE_WINDOW -4096
#define FAE_SYSTEM_ORDER_STOP_WINDOW 4096

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

		size_t GetWidth();
		size_t GetHeight();
		float GetAspectRatio();

		size_t GetBufferWidth();
		size_t GetBufferHeihgt();
		float GetBufferAspectRatio();

		operator GLFWwindow* () { return window; }
		operator const GLFWwindow* () const { return window; }
	};

	void WindowPlugin(App& app);
}