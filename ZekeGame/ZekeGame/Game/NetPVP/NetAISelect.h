#pragma once

#include "../Title/SuperMonsterSelect.h"

class GameCursor;
class MonAIPresetOpenSuper;
class NetAISelect :public SuperMonsterSelect
{
public:
	void OnDestroy() override;
	bool Start();
	void Update();

	std::vector<std::string> GetFiles()
	{
		return m_files;
	}
	std::vector<PMMonster*> GetPMMonster()
	{
		return m_pmms;
	}
private:
	CFont font;
	std::vector<std::string> m_files;
	int monai[6] = { 0 };
	int curpos = 0;
	bool sel = false;

	GameCursor* m_cursor;

	PMMonster* m_pmm = nullptr;
	std::vector<PMMonster*> m_pmms;
	//std::vector<SpriteRender*> m_monicon;

	SpriteRender* m_GO = nullptr;
	SpriteRender* m_back = nullptr;

	SpriteRender* m_return = nullptr;
	SpriteRender* m_returnMoji = nullptr;
	bool isReturnOver = false;
	CVector2 m_returnS = { 604,256 };

	Sound* m_BGM = nullptr;
	float m_vol = 1;

	//MonAIPresetOpen* m_mapo = nullptr;
	MonAIPresetOpenSuper* m_msRed = nullptr;		//preset�̃Z�[�u�p
	MonAIPresetOpenSuper* m_mlRed = nullptr;		//preset�̃��[�h�p
};