#pragma once
#include "../Monster.h"

class Kikyo :public Monster
{
public:
	//�R���X�g���N�^
	Kikyo();
private:
	AnimationClip m_anim[6]; //�A�j���[�V�����N���b�v
};