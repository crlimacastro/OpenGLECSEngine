#pragma once
#include <unordered_map>
#include <entt/entt.hpp>
#include "App.h"

namespace gfe {
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