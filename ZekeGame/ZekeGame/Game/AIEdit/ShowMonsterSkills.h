#pragma once
#include "..//GameData.h"
class GameCursor;

class ShowMonsterSkills : public GameObject
{
public :
	bool Start() override;
	void OnDestroy() override;
	void Update() override;
	void SetMonster(MonsterID id) {
		m_monsterId = id;
	}
private:
	MonsterID m_monsterId;
	SpriteRender* m_backSp = nullptr;
	SpriteRender* m_quitSp = nullptr;
	std::vector<FontRender*> m_defSkillNamesFR;
	std::vector<SpriteRender*> m_sps;
	GameCursor* m_cur = nullptr;
	std::wstring m_defSkillNamesStr[6] = { L"�U��",L"�ǐ�",L"���S",L"���",L"����1",L"����2" };
};

