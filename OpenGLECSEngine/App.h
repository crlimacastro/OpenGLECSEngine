#pragma once
#include <entt/entt.hpp>
#include <unordered_set>

namespace gfe {
	class App;

	typedef void (*System)(const void*, entt::registry&);
	typedef void (*Plugin)(App&);

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
		/// Runs Start once & Update on a loop until App is not running anymore.
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
		/// Adds a System that should only run once.
		/// </summary>
		/// <param name="system"></param>
		/// <returns></returns>
		App& AddStartSystem(System system);
		/// <summary>
		/// Adds a System to run on the update loop.
		/// </summary>
		/// <param name="system"></param>
		/// <returns></returns>
		App& AddUpdateSystem(System system);

		/// <summary>
		/// Adds a System that should only run once when the App is stopped.
		/// </summary>
		/// <param name="system"></param>
		/// <returns></returns>
		App& AddStopSystem(System system);

		/// <summary>
		/// Adds a function with access to the App itself
		/// (usually to add a set of systems & resources).
		/// </summary>
		/// <param name="plugin"></param>
		/// <returns></returns>
		App& AddPlugin(Plugin plugin);

		/// <summary>
		/// Adds a type that can be accessed anywhere from the registry ctx.
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
		std::unordered_set<Plugin> plugins;
		entt::organizer startSystems;
		entt::organizer updateSystems;
		entt::organizer stopSystems;
	};
};