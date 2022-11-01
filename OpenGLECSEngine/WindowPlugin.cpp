#include "WindowPlugin.h"
#include <entt/entt.hpp>

using namespace fae;

Window& fae::Window::SetTitle(const char* value)
{
	glfwSetWindowTitle(window, value);
	return *this;
}

Window& fae::Window::SetIsResizable(int value)
{
	glfwWindowHint(GLFW_RESIZABLE, value);
	return *this;
}

size_t fae::Window::GetWidth()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

size_t fae::Window::GetHeight()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}

float fae::Window::GetAspectRatio()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return (float)width / height;
}

size_t fae::Window::GetBufferWidth()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return width;
}

size_t fae::Window::GetBufferHeihgt()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return height;
}

float fae::Window::GetBufferAspectRatio()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return (float)width / height;
}

void SetupWindow(entt::registry& registry)
{
	// init glfw
	glfwInit();

	// use default or user-defined WindowDescriptor
	WindowDescriptor descriptor;
	if (registry.ctx().contains<WindowDescriptor>()) {
		descriptor = registry.ctx().at<WindowDescriptor>();
	}

	// set window settings
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, descriptor.isResizable ? GL_TRUE : GL_FALSE);

	// create window
	auto window = glfwCreateWindow(static_cast<int>(descriptor.width), static_cast<int>(descriptor.height), descriptor.title, NULL, NULL);

	// set resize funciton
	glfwSetFramebufferSizeCallback(window, [](auto, auto width, auto height) {
		glViewport(0, 0, width, height);
		});

	// make window the current GL context
	glfwMakeContextCurrent(window);

	// create Window resource
	registry.ctx().emplace<Window>(window);
}

void UpdateWindow(entt::registry& registry)
{
	// poll events
	glfwPollEvents();

	auto& window = registry.ctx().at<Window>();
	// check if window should close
	if (glfwWindowShouldClose(window))
	{
		auto& app = registry.ctx().at<App&>();
		app.isRunning = false;
		return;
	}
}

void CleanupWindow(entt::registry& registry)
{
	auto& window = registry.ctx().at<Window>();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void fae::WindowPlugin(App& app)
{
	app.AddStartSystem(SetupWindow, FAE_SYSTEM_ORDER_START_WINDOW)
		.AddUpdateSystem(UpdateWindow, FAE_SYSTEM_ORDER_UPDATE_WINDOW)
		.AddStopSystem(CleanupWindow, FAE_SYSTEM_ORDER_STOP_WINDOW);
}
