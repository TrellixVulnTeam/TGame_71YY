#pragma once
#include "../Monster.h"

class Goblin :public Monster
{
public:
	//�R���X�g���N�^
	Goblin();
private:
	AnimationClip m_anim[6]; //�A�j���[�V�����N���b�v
};