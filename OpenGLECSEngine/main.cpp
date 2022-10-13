#include "App.h"
#include "WindowPlugin.h"
#include "InputPlugin.h"
#include "DebugSystems.h"

using namespace std;
using namespace gfe;

int main()
{
	App{}
		.AddResource<WindowDescriptor>("GL ECS FAE", 640, 480, GL_TRUE)
		.AddPlugin(WindowPlugin)
		.AddPlugin(InputPlugin)
		.AddUpdateSystem(CloseOnESC)
		.Run();
}