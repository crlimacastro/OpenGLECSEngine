#include "default_plugins.h"

void fae::DefaultPlugins(App& app)
{
	app.AddPlugin(WindowPlugin)
		.AddPlugin(RendererPlugin)
		.AddPlugin(TimePlugin)
		.AddPlugin(InputPlugin)
		.AddPlugin(TransformPlugin)
		.AddPlugin(CameraPlugin)
		.AddPlugin(LightingPlugin);
}
