#pragma once
#include "../GameData.h"
class PMMonster;
class MonsterSelect :public GameObject
{
public:

	bool Start();
	void init(PMMonster* pmm);
	void Update();
private:
	PMMonster* m_pmm;
	MonsterID m_selmon = enTest;
	SpriteRender* m_back;
	CVector3 m_backsize = { 148,148,0 };

	std::vector<SpriteRender*> m_mons;
	CVector2 m_iconsize = { 128,128 };

	int m_monstercount = 2;
};