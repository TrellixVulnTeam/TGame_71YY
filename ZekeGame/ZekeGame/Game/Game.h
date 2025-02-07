#pragma once
//#include "GameCamera.h"

#include "StageSetup/StageSetup.h"
enum MonsterID;
class GameCamera;
class TestListener;
class GameMenu;
class Fade;

class ReadyGO;


class Game : public GameObject
{
public:
	void GamePVPmodeInit(std::vector<std::string> files, int monsterAI[6], MonsterID MonsterID[6]);
	bool Start() override;
	void OnDestroy() override;
	void Update() override;

	void SuddenDeath()
	{
		m_suddenDeath = true;
	}
	enum Mode
	{
		enLocalPVP,
		enRandomPVP,
		enDungeon
	};
	Mode GetGameMode() {
		return m_playMode;
	}
	void LocalPVP()
	{
		m_playMode = enLocalPVP;
	}

	void DungeonMode(int number)
	{
		m_playMode = enDungeon;
		m_dunNum = number;
	}

	void SetRandomPVPMode(float rate) {
		m_playMode = enRandomPVP;
		m_eneRate = rate;
	}
private:
	SkinModelRender* m_model = nullptr;
	SkinModelRender* m_floor = nullptr;

	SpriteRender* m_sprite = nullptr;
	GameCamera* camera = nullptr;
	StageSetup* ss = nullptr;
	int m_dunNum = -1;
	float m_eneRate = 0;
	GameMenu* m_menu = nullptr;
	FontRender* m_dunInfoF = nullptr;
	Mode m_playMode = enLocalPVP;

	bool m_END = false;
	bool m_isOnlineGame = false;
	bool m_suddenDeath = false;

	float m_time = 180.0f;

	SkinModelDummy* m_smd = nullptr;
	FontRender* m_fr = nullptr;
	FontRender* m_frS = nullptr;

	CEffect* e;
	ReadyGO* m_readyGO = nullptr;
	bool m_isEndReady = false;

	Fade* m_fade = nullptr;
	bool m_Ffirst = true;

	Sound* m_BGM = nullptr;

	int m_winTeam = 0;				//勝ったチーム
	bool m_isGameSet = false;		//gameendのフェードアウトが終わった
};

