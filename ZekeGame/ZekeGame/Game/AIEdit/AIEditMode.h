#pragma once

class GameCursor;
// THIS IS CAMERA.
class GameCamera;
class AIEditNodeProcess;
class AIEditNodeBackGround;
class AIEditNodeClick;
/*
	AIをGUIで作るためのクラス
*/
class AIEditMode :public GameObject
{
public:
	//デストラクタ
	~AIEditMode();

	bool Start() override final;
	void Update() override final;
	//必要に応じて関数を作っていこう！！	


private:
	//メンバ変数は基本ここに書こう！！
	
	//std::vector<SpriteRender*> m_sprits;

	GameCursor* m_cursor = nullptr;				// This is cursor
	GameCamera* m_camera = nullptr;				//<-THIS IS CAMERA
	AIEditNodeClick* m_aieditnodeclick= nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeBackGround* m_aieditnodebackground = nullptr;

	SpriteRender* m_spriteRender = nullptr;

};