#include "DefaultPlugins.h"

void fae::DefaultPlugins(App& app)
{
	app.AddPlugin(WindowPlugin)
		.AddPlugin(RendererPlugin)
		.AddPlugin(CameraPlugin)
		.AddPlugin(InputPlugin);
}
