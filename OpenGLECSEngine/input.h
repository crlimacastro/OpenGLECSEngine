#pragma once
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "App.h"

namespace fae {
	// Resources

	struct Input
	{
	public:
		bool IsPressed(int key);
		bool IsJustPressed(int key);
		bool IsJustReleased(int key);

		glm::vec2 GetMousePosition();
		glm::vec2 GetMouseMoveDelta();

	private:
		std::unordered_map<int, bool> isDown;
		std::unordered_map<int, bool> wasDown;
		glm::vec2 mousePosition;
		glm::vec2 prevMousePosition;

		friend void UpdateInput(entt::registry& registry);
	};

	// Systems

	void SetupInput(entt::registry& registry);
	void UpdateInput(entt::registry& registry);

	// Plugins

	void InputPlugin(App& app);
}