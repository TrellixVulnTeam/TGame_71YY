#pragma once

class UIAnimator;
//�o�g���ŗ����̃`�[�����S�ł��Ă��܂������̏���
class BattleDraw :public GameObject
{
public:
	//������
	BattleDraw();
	//Start
	bool Start();
	//�X�V
	void Update();
private:
	SpriteRender* m_drawSp = nullptr;	//DRAW MOJI
};