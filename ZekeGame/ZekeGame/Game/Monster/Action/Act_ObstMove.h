#pragma once
#include "../MonsterAction.h"

class Act_ObstMove : public MonsterAction
{
public:
	//�^�[�Q�b�g�̈ړ����x��ቺ������
	Act_ObstMove();
	~Act_ObstMove();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 10.f;
	float m_enemySpeed = 0.f;
	CEffect* m_efk = nullptr;
	int m_timer = 0;
};

