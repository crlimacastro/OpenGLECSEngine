#include "DebugSystems.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "InputPlugin.h"
#include "App.h"

void gfe::CloseOnESC(const void*, entt::registry& registry)
{
	auto& app = registry.ctx().at<App&>();

	// If no Input exists, add the input plugin
	if (!registry.ctx().contains<Input>()) {
		app.AddPlugin(InputPlugin);
	}

	auto& input = registry.ctx().at<Input>();
	if (input.IsJustReleased(GLFW_KEY_ESCAPE))
	{
		app.isRunning = false;
	}
}
