#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include"AIEditNodeClick.h"
#include "../GameCursor.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeBackGround.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"

AIEditMode::~AIEditMode()
{
	//メモリ開放はしっかりしよう！！

	// CAMERA IS DEAD.
	delete m_camera;

	//CURSOR IS DEAD.
	DeleteGO(m_cursor);
	DeleteGO(m_spriteRender);
}

bool AIEditMode::Start()
{
	// THIS IS CAMERA.
	m_camera = new GameCamera;

	m_cursor = NewGO<GameCursor>(0, "cursor");
	m_aieditnodebackground = NewGO<AIEditNodeBackGround>(0, "background");
	m_aieditnodeprocess = NewGO<AIEditNodeProcess>(0, "process");

	//!!!--RETURN TRUE--!!!
	//↑草
	return true;
	//!!!--RETURN TRUE--!!!
}

void AIEditMode::Update()
{

}
