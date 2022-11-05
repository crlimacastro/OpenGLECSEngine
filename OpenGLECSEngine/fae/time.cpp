#include "time.h"
#include <GLFW/glfw3.h>

float fae::Time::GetSecondsElapsed()
{
	return secondsElapsed;
}

float fae::Time::GetDeltaSeconds()
{
	return secondsElapsed - prevSecondsElapsed;
}

void fae::SetupTime(entt::registry& registry)
{
	registry.ctx().emplace<Time>();
}

void fae::UpdateTime(entt::registry& registry)
{
	auto& time = registry.ctx().at<Time>();

	time.prevSecondsElapsed = time.secondsElapsed;
	time.secondsElapsed = static_cast<float>(glfwGetTime());
}

void fae::TimePlugin(App& app)
{
	app.AddStartSystem(SetupTime, FAE_SYSTEM_ORDER_SETUP)
		.AddUpdateSystem(UpdateTime, FAE_SYSTEM_ORDER_PRE_UPDATE);
}