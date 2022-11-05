#include "debug_systems.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "App.h"

bool isEscPressed = false;
bool wasEscPressed = false;

void fae::CloseOnESC(entt::registry& registry)
{
	auto& window = registry.ctx().at<Window>();
	wasEscPressed = isEscPressed;
	isEscPressed = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	if (!isEscPressed && wasEscPressed)
	{
		auto& app = registry.ctx().at<App&>();
		app.isRunning = false;
	}
}
