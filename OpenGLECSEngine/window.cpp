#include "window.h"
#include <iostream>

using namespace fae;

Window& fae::Window::SetTitle(const char* value)
{
	glfwSetWindowTitle(window, value);
	return *this;
}

Window& fae::Window::SetIsResizable(bool value)
{
	glfwWindowHint(GLFW_RESIZABLE, static_cast<GLboolean>(value));
	return *this;
}

size_t fae::Window::GetWidth() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

size_t fae::Window::GetHeight() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}

float fae::Window::GetAspectRatio() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return (float)width / height;
}

size_t fae::Window::GetBufferWidth() const
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return width;
}

size_t fae::Window::GetBufferHeihgt() const
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return height;
}

float fae::Window::GetBufferAspectRatio() const
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return (float)width / height;
}

void fae::SetupWindow(entt::registry& registry)
{
	glfwInit();

	// use default or user-defined WindowDescriptor
	WindowDescriptor descriptor;
	if (registry.ctx().contains<WindowDescriptor>()) {
		descriptor = registry.ctx().at<WindowDescriptor>();
	}

	// set window settings
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, descriptor.glfwVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, descriptor.glfwVersionMinor);
	glfwWindowHint(GLFW_RESIZABLE, static_cast<GLboolean>(descriptor.isResizable));

	auto window = glfwCreateWindow(static_cast<int>(descriptor.width), static_cast<int>(descriptor.height), descriptor.title, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// set viewport dimensions
	glViewport(0, 0, static_cast<GLsizei>(descriptor.width), static_cast<GLsizei>(descriptor.height));

	// set resize callback function
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});

	// make window the current GL context
	glfwMakeContextCurrent(window);

	// create Window resource
	registry.ctx().emplace<Window>(window);
}

void fae::UpdateWindow(entt::registry& registry)
{
	glfwPollEvents();

	auto& window = registry.ctx().at<Window>();
	if (glfwWindowShouldClose(window))
	{
		auto& app = registry.ctx().at<App&>();
		app.isRunning = false;
		return;
	}
}

void fae::CleanupWindow(entt::registry& registry)
{
	glfwTerminate();
}

void fae::WindowPlugin(App& app)
{
	app.AddStartSystem(SetupWindow, FAE_SYSTEM_ORDER_PRE_SETUP)
		.AddUpdateSystem(UpdateWindow, FAE_SYSTEM_ORDER_PRE_UPDATE)
		.AddStopSystem(CleanupWindow, FAE_SYSTEM_ORDER_POST_STOP);
}
