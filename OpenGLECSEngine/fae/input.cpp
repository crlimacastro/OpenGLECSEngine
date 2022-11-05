#include "input.h"
#include <entt/entt.hpp>
#include "window.h"

using namespace fae;

bool fae::Input::IsPressed(int key)
{
	return isDown.find(key) != isDown.end() && isDown.at(key);
}

bool fae::Input::IsJustPressed(int key)
{
	return isDown.find(key) != isDown.end() && isDown.at(key) && wasDown.find(key) != wasDown.end() && !wasDown.at(key);
}

bool fae::Input::IsJustReleased(int key)
{
	return isDown.find(key) != isDown.end() && !isDown.at(key) && wasDown.find(key) != wasDown.end() && wasDown.at(key);
}

glm::vec2 fae::Input::GetMousePosition()
{
	return mousePosition;
}

glm::vec2 fae::Input::GetMouseMoveDelta()
{
	return mousePosition - prevMousePosition;
}

void fae::SetupInput(entt::registry& registry)
{
	registry.ctx().emplace<Input>();
}

void fae::UpdateInput(entt::registry& registry)
{
	// Keyboard
	auto& input = registry.ctx().at<Input>();
	auto& window = registry.ctx().at<Window>();
	input.wasDown = input.isDown;
	input.isDown.clear();
	for (int key = 0; key <= GLFW_KEY_LAST; key++)
	{
		int state = glfwGetKey(window, key);
		if (state == GLFW_PRESS)
		{
			input.isDown[key] = true;
		}
		else
		{
			input.isDown[key] = false;
		}
	}

	// Mouse
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	input.prevMousePosition = input.mousePosition;
	input.mousePosition = { mouseX, mouseY };

}

void fae::InputPlugin(App& app)
{
	app.AddStartSystem(SetupInput, FAE_SYSTEM_ORDER_SETUP)
		.AddUpdateSystem(UpdateInput, FAE_SYSTEM_ORDER_PRE_UPDATE);
}