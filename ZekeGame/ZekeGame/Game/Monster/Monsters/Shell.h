#pragma once
#include "../Monster.h"

class Shell :public Monster
{
public:
	//�R���X�g���N�^
	Shell();
private:
	AnimationClip m_anim[6]; //�A�j���[�V�����N���b�v
};