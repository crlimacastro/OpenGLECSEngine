#pragma once
#include <entt/entt.hpp>
#include <GL/glew.h>
#include "InputPlugin.h"
#include "App.h"

namespace gfe {
	void CloseOnESC(const void*, entt::registry& registry)
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
}