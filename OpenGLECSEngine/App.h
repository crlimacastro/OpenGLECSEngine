#pragma once
#include <entt/entt.hpp>
#include <unordered_set>
#include <queue>

namespace fae {
	class App;

	typedef void (*System)(entt::registry&);
	typedef void (*Plugin)(App&);

#define FAE_SYSTEM_ORDER_DEFAULT 0

	class App
	{
	public:
		bool isRunning = false;

		/// <summary>
		/// Inits app &
		/// runs start systems.
		/// </summary>
		/// <returns></returns>
		App& Start();

		/// <summary>
		/// Run update systems.
		/// </summary>
		/// <returns></returns>
		App& Update();

		/// <summary>
		/// Calls Start once & Update on a loop until App is not running anymore.
		/// </summary>
		/// <returns></returns>
		App& Run();

		/// <summary>
		/// Sets the App to not be running &
		/// calls stop systems.
		/// </summary>
		/// <returns></returns>
		App& Stop();

		/// <summary>
		/// Adds a System that should only run once when the App starts.
		/// </summary>
		/// <param name="system"></param>
		/// <param name="order"></param>
		/// <returns></returns>
		App& AddStartSystem(System system, int order = FAE_SYSTEM_ORDER_DEFAULT);
		/// <summary>
		/// Adds a System to run on the update loop.
		/// </summary>
		/// <param name="system"></param>
		/// <param name="order"></param>
		/// <returns></returns>
		App& AddUpdateSystem(System system, int order = FAE_SYSTEM_ORDER_DEFAULT);

		/// <summary>
		/// Adds a System that should only run once when the App is stopped.
		/// </summary>
		/// <param name="system"></param>
		/// <param name="order"></param>
		/// <returns></returns>
		App& AddStopSystem(System system, int order = FAE_SYSTEM_ORDER_DEFAULT);

		/// <summary>
		/// Adds a function with access to the App itself
		/// (usually to add a set of systems & resources).
		/// </summary>
		/// <param name="plugin"></param>
		/// <returns></returns>
		App& AddPlugin(Plugin plugin);

		/// <summary>
		/// Adds a type that can be accessed anywhere from the registry context.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="...args"></param>
		/// <returns></returns>
		template<typename T, typename... Args>
		App& AddResource(Args &&...args)
		{
			registry.ctx().emplace<T>(args...);
			return *this;
		}
	private:
		entt::registry registry;

		std::queue<Plugin> pluginsToAdd;

		struct SystemAddCommand
		{
			System system;
			int order;
			std::map<int, std::vector<System>>& systemSet;
		};
		std::queue<SystemAddCommand> systemsToAdd;

		std::map<int, std::vector<System>> startSystems;
		std::map<int, std::vector<System>> updateSystems;
		std::map<int, std::vector<System>> stopSystems;

		void AddQueuedPlugins();
		void AddQueuedSystems();
	};
};