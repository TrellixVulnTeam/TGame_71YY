#pragma once

class Fade :public GameObject
{
public:
	Fade();
	void OnDestroy();

	void Update();

	//��Z�F�̃Q�b�g
	CVector4 GetMulCol()
	{
		return m_mulcol;
	}

	//��Z�F�̃Z�b�g�B
	void SetMulCol(CVector4 col)
	{
		m_mulcol = col;
	}

	//�t�F�[�h�X�s�[�h�̃Q�b�g�B
	float GetSpeed()
	{
		return m_speed;
	}
	//�t�F�[�h�X�s�[�h�̃Z�b�g�B
	void SetSpeed(float sp)
	{
		m_speed = sp;
	}

	//�t�F�[�h�C��
	void FadeIn()
	{
		m_state = enFadein;
	}
	//�t�F�[�h�A�E�g
	void FadeOut()
	{
		m_state = enFadeout;
	}

	//���t�F�[�h�͎~�܂��Ă��邩�H
	bool isFadeStop()
	{
		if (m_state == enFadeStop)
		{
			return true;
		}
		return false;
	}
private:
	enum State
	{
		enFadeStop,
		enFadein,
		enFadeout,
	};
	State m_state = enFadeStop;			//�t�F�[�h�̏��
	SpriteRender* m_black = nullptr;	//�t�F�[�h�̃X�v���C�g�@�u���b�N�ƂȂ��Ă��邪�A���̎������Ɏg���Ă���摜��1x1�̔����摜�Ȃ̂��B

	CVector4 m_mulcol = { 0,0,0,0 };	//�X�v���C�g�ɂ�����F
	float m_speed = 1;					//�t�F�[�h�̃X�s�[�h 1���ƃf���^�^�C�������̂܂ܓ���B
};