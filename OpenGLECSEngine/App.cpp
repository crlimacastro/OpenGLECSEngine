#include "App.h"

using namespace fae;

App& App::Start()
{
	isRunning = true;
	registry.ctx().emplace<App&>(*this);

	AddQueuedPlugins();
	AddQueuedSystems();

	for (auto& systems : startSystems)
	{
		for (auto& system : systems.second)
		{
			system(registry);
		}
	}

	return *this;
}

App& App::Update()
{
	AddQueuedPlugins();
	AddQueuedSystems();

	for (auto& systems : updateSystems)
	{
		for (auto& system : systems.second)
		{
			system(registry);
		}
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
	for (auto& systems : stopSystems)
	{
		for (auto& system : systems.second)
		{
			system(registry);
		}
	}

	return *this;
}

App& fae::App::AddStartSystem(System system, int order)
{
	systemsToAdd.push({ system, order, startSystems });
	return *this;
}

App& fae::App::AddUpdateSystem(System system, int order)
{
	systemsToAdd.push({ system, order, updateSystems });
	return *this;
}

App& fae::App::AddStopSystem(System system, int order)
{
	systemsToAdd.push({ system, order, stopSystems });
	return *this;
}

App& App::AddPlugin(Plugin plugin)
{
	pluginsToAdd.push(plugin);
	return *this;
}

void fae::App::AddQueuedPlugins()
{
	while (!pluginsToAdd.empty())
	{
		pluginsToAdd.front()(*this);
		pluginsToAdd.pop();
	}
}

void fae::App::AddQueuedSystems()
{
	while (!systemsToAdd.empty())
	{
		auto& addCommand = systemsToAdd.front();
		auto it = addCommand.systemSet.find(addCommand.order);
		if (it != addCommand.systemSet.end())
		{
			it->second.push_back(addCommand.system);
		}
		else
		{
			addCommand.systemSet.emplace(addCommand.order, std::vector{ addCommand.system });
		}
		systemsToAdd.pop();
	}
}
