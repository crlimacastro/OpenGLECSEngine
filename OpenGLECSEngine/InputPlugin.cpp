#include "InputPlugin.h"
#include <entt/entt.hpp>
#include "WindowPlugin.h"

using namespace fae;

bool fae::Input::IsPressed(int key)
{
	return __isDown.find(key) != __isDown.end() && __isDown.at(key);
}

bool fae::Input::IsJustPressed(int key)
{
	return __isDown.find(key) != __isDown.end() && __isDown.at(key) && __wasDown.find(key) != __wasDown.end() && !__wasDown.at(key);
}

bool fae::Input::IsJustReleased(int key)
{
	return __isDown.find(key) != __isDown.end() && !__isDown.at(key) && __wasDown.find(key) != __wasDown.end() && __wasDown.at(key);
}

void SetupInput(entt::registry& registry)
{
	registry.ctx().emplace<Input>();
}

void UpdateInput(entt::registry& registry)
{
	auto& input = registry.ctx().at<Input>();
	auto& window = registry.ctx().at<Window>();
	input.__wasDown = input.__isDown;
	input.__isDown.clear();
	for (int key = 0; key <= GLFW_KEY_LAST; key++)
	{
		int state = glfwGetKey(window, key);
		if (state == GLFW_PRESS)
		{
			input.__isDown[key] = true;
		}
		else
		{
			input.__isDown[key] = false;
		}
	}
}

void fae::InputPlugin(App& app)
{
	app.AddStartSystem(SetupInput, FAE_SYSTEM_ORDER_START_INPUT)
		.AddUpdateSystem(UpdateInput, FAE_SYSTEM_ORDER_UPDATE_INPUT);
}