#pragma once
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include "App.h"
#include "WindowPlugin.h"

namespace gfe {
	struct Input
	{
	public:
		bool IsPressed(int key)
		{
			return isDown.find(key) != isDown.end() && isDown.at(key);
		}

		bool IsJustPressed(int key)
		{
			return isDown.find(key) != isDown.end() && isDown.at(key) && wasDown.find(key) != wasDown.end() && !wasDown.at(key);
		}

		bool IsJustReleased(int key)
		{
			return isDown.find(key) != isDown.end() && !isDown.at(key) && wasDown.find(key) != wasDown.end() && wasDown.at(key);
		}

	private:
		std::unordered_map<int, bool> isDown;
		std::unordered_map<int, bool> wasDown;

		friend void UpdateInput(const void*, entt::registry& registry);
	};

	void SetupInput(const void*, entt::registry& registry)
	{
		auto& window = registry.ctx().at<Window>();
		registry.ctx().emplace<Input>();
	}

	void UpdateInput(const void*, entt::registry& registry)
	{
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
	}

	void InputPlugin(App& app)
	{
		app.AddStartSystem(SetupInput)
			.AddUpdateSystem(UpdateInput);
	}
}