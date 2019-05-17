#pragma once
#include "../MonsterAction.h"

class Act_superBeam : public MonsterAction
{
public:
	Act_superBeam();
	bool Action(Monster* me) override;
private:
	int m_cost = 20;
	bool m_first = true;
	CVector3 m_efPos = CVector3::Zero();
	CEffect* m_efk = nullptr;

};
