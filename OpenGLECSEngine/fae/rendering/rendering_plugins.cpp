#include "rendering_plugins.h"

void fae::RenderingPlugins(App& app)
{
	app.AddPlugin(CameraPlugin)
		.AddPlugin(LightingPlugin);
}
