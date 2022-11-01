#pragma once
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "App.h"

namespace fae {
#define FAE_SYSTEM_ORDER_START_INPUT -1024
#define FAE_SYSTEM_ORDER_UPDATE_INPUT -1024

	struct Input
	{
	public:
		bool IsPressed(int key);
		bool IsJustPressed(int key);
		bool IsJustReleased(int key);

		std::unordered_map<int, bool> __isDown;
		std::unordered_map<int, bool> __wasDown;
	};

	void InputPlugin(App& app);
}