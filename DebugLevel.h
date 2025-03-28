#pragma once
#include "Level.h"
#include "CanvasWidget.h"
#include "CameraManager.h"
#include "CameraActor.h"

using namespace Camera;

struct GameplayHUDData
{
	CanvasWidget* canvas;

};

class DebugLevel : public Level
{
	HUD* hud;
	GameplayHUDData gameHUD;
	CameraActor* camera;
	Camera::CameraManager* cameraManager;

public:
	DebugLevel(const string& _name);

protected:
	virtual void InitLevel() override;
};

