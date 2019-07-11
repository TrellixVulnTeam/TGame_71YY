#pragma once

//����̓e���v���[�g������R�s�[����Ɗy�����ˁH

#include "../MonsterAction.h"

class Monster;

//�����ƃN���X���͕ς��悤�ˁH
class Act_Move :public MonsterAction
{
public:
	Act_Move();
	bool Action(Monster* me) override;
	void SetTargetPosition(float x, float y)
	{
		mTarpos.x = x;
		mTarpos.z = y;
	}
private:
	CVector3 mTarpos = CVector3::Zero();
};