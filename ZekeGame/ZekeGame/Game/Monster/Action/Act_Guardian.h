#pragma once

//����̓e���v���[�g������R�s�[����Ɗy�����ˁH

#include "../MonsterAction.h"

class Monster;

//�����ƃN���X���͕ς��悤�ˁH
class Act_Guardian :public MonsterAction
{
public:
	Act_Guardian();
	bool Action(Monster* me) override;
private:
};