#pragma once

#include "AudioManager.h"
#include "Renderer.h"
#include "WindowManager.h"

class Scene {
	// Any scene that could be rendered
public:
	virtual void render(Renderer& renderer) = 0;
	virtual void update(AudioManager& am, WindowManager& wm) = 0;
};