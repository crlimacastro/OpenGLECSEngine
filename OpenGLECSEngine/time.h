#pragma once
#include "App.h"

namespace fae {
	// Resources

	struct Time
	{
		float GetSecondsElapsed();
		float GetDeltaSeconds();
	private:
		float secondsElapsed = 0;
		float prevSecondsElapsed = 0;

		friend void UpdateTime(entt::registry& registry);
	};

	// Systems

	void SetupTime(entt::registry& registry);
	void UpdateTime(entt::registry& registry);

	// Plugins

	void TimePlugin(App& app);
}