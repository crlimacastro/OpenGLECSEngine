#include "App.h"

using namespace gfe;

App& App::Start()
{
	registry.ctx().emplace<App&>(*this);

	for (auto& plugin : plugins)
	{
		plugin(*this);
	}

	isRunning = true;
	for (auto& node : startSystems.graph())
	{
		node.callback()(nullptr, registry);
	}
	return *this;
}

App& App::Update()
{
	for (auto& node : updateSystems.graph())
	{
		node.callback()(nullptr, registry);
	}
	return *this;
}

App& App::Run()
{
	Start();
	while (isRunning)
	{
		Update();
	}
	Stop();
	return *this;
}

App& App::Stop()
{
	for (auto& node : stopSystems.graph())
	{
		node.callback()(nullptr, registry);
	}
	return *this;
}

App& App::AddStartSystem(System system)
{
	startSystems.emplace(system);
	return *this;
}

App& App::AddUpdateSystem(System system)
{
	updateSystems.emplace(system);
	return *this;
}

App& App::AddStopSystem(System system)
{
	stopSystems.emplace(system);
	return *this;
}

App& App::AddPlugin(Plugin plugin)
{
	plugins.insert(plugin);
	return *this;
}
