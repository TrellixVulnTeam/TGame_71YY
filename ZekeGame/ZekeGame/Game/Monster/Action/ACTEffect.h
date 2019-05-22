#pragma once

class Monster;

class ACTEffectGrant :public GameObject
{
public:
	/*
	�f�X�g���N�^
	*/
	~ACTEffectGrant();

	/*
	������
	�C���X�^���X�𐶐��������ɂ͕K��������g���B
	arg:
		effect:�����Ŏg���G�t�F�N�g
		target:�����t���Ă��������X�^�[
		state:���̃N���X�ŉ������邩�A
		dam:�H��킷�_���[�W
		time:�_���[�W�̃X�p���B0�����̏ꍇ�͖��t���[��
	*/
	void init(CEffect* effect, Monster* target, int state = enNull, float dam = 0,float time = -1,float endTime = 0);

	/*
	Update
	*/
	void Update();

	//��Ԉُ�̐ݒ�
	void SetAbnormalState(int abn);
	//��Ԉُ��Ԃ��B
	int GetAbnormalState()
	{
		return m_abnormal;
	}

	//�����ݒ肷��ƃ_���[�W��H��킹����ł���B
	enum State
	{
		enNull,		//�������Ȃ�
		enDamage,	//�_���[�W
		enCC,	//�ړ��W�Q
		enbuffAtc,
	};

private:
	State m_state = enNull;

	int m_abnormal = 0;

	float m_damTime = 0;
	float m_dam = 0;

	float m_efTime = 0;
	float m_time = 0;
	float m_endTime = 0;
	CEffect* m_effect = nullptr;
	Monster* m_target = nullptr;
};