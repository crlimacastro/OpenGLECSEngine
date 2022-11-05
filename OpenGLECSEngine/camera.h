#pragma once
#include "ICamera.h"
#include "App.h"

namespace fae
{
	/// <summary>
	/// Resource containing the currently active camera
	/// </summary>
	struct ActiveCamera
	{
		ICamera* camera;
	};

	void CameraPlugin(App& app);
}