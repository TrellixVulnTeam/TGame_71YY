#include "stdafx.h"
#include "AIEditMode.h"

#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"

AIEditMode::~AIEditMode()
{
	//�������J���͂������肵�悤�I�I

	// CAMERA IS DEAD.
	delete m_camera;
}

bool AIEditMode::Start()
{
	// THIS IS CAMERA.
	m_camera = new GameCamera;

	m_cursor = NewGO<GameCursor>(0, "cursor");

	//!!!--RETURN TRUE--!!!
	return true;
	//!!!--RETURN TRUE--!!!
}

void AIEditMode::Update()
{
}
