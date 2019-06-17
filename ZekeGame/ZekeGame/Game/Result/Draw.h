#pragma once

class UIAnimator;
class Fade;
//�o�g���ŗ����̃`�[�����S�ł��Ă��܂������̏���
class BattleDraw :public GameObject
{
public:
	//������
	BattleDraw();

	//�f�X�g���N�^
	void OnDestroy();

	//Start
	bool Start();
	//�X�V
	void Update();

	/*
	���[�h���Z�b�g����
	*/
	void SetPVPMode(int n)
	{
		m_monsel = n;
	}

	/*
	�_���W�����̔ԍ����Z�b�g����
	*/
	void SetDunNum(int n)
	{
		m_dunNum = n;
	}

	//UI�A�j���[�V�������Đ�
	void playDraw();
private:
	SpriteRender* m_drawSp = nullptr;	//DRAW MOJI
	UIAnimator* m_uia = nullptr;		//UIAnimator

	FontRender* m_fr = nullptr;			//�N���b�N���Ă�������

	Fade* m_fade = nullptr;				//�t�F�[�h

	bool isEND = false;					//�I������E�E�E

	int m_monsel = 0;					//�ǂ̃��[�h��
	int m_dunNum = 0;					//�_���W�����̔ԍ�
};