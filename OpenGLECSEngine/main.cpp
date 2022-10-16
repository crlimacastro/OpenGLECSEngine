#include "App.h"
#include "RendererPlugin.h"
#include "WindowPlugin.h"
#include "InputPlugin.h"
#include "DebugSystems.h"

using namespace std;
using namespace gfe;

int main()
{
	App{}
		.AddResource<WindowDescriptor>("GL ECS FAE", static_cast<size_t>(640), static_cast<size_t>(480), true)
		.AddPlugin(WindowPlugin)
		.AddPlugin(RendererPlugin)
		.AddPlugin(InputPlugin)
		.AddUpdateSystem(CloseOnESC)
		.Run();
}