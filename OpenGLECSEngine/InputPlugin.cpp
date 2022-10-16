#include "InputPlugin.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "WindowPlugin.h"

using namespace gfe;

bool gfe::Input::IsPressed(int key)
{
	return __isDown.find(key) != __isDown.end() && __isDown.at(key);
}

bool gfe::Input::IsJustPressed(int key)
{
	return __isDown.find(key) != __isDown.end() && __isDown.at(key) && __wasDown.find(key) != __wasDown.end() && !__wasDown.at(key);
}

bool gfe::Input::IsJustReleased(int key)
{
	return __isDown.find(key) != __isDown.end() && !__isDown.at(key) && __wasDown.find(key) != __wasDown.end() && __wasDown.at(key);
}

void SetupInput(const void*, entt::registry& registry)
{
	registry.ctx().emplace<Input>();
}

void UpdateInput(const void*, entt::registry& registry)
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

void gfe::InputPlugin(App& app)
{
	app.AddStartSystem(SetupInput)
		.AddUpdateSystem(UpdateInput);
}