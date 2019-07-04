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
	void init(CEffect* effect , Monster* target, int state = enNull, float dam = 0,float time = -1,float endTime = 0, Monster* me = nullptr, float dmgParam = 0.01);

	/*
		�o�t�ƃf�o�t�Ńf�t�H���g�l�����{���邩�̃p�����[�^��ݒ肷��
	*/
	void SetBuffDebuffParam(float param) {
		m_buffdebuffParam = param;
	}

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

	//�^�[�Q�b�g�����񂾎����N���X�ɋ�����
	void SetTargetAliveFlag(bool flag) {
		m_isTargetAlive = flag;
	}

	//��Ԉُ킪���������
	void Clense() {
		m_isTargetAlive = false;
	}

	//�����ݒ肷��ƃ_���[�W��H��킹����ł���B
	enum State
	{
		enNull,		//�������Ȃ�
		enDamage,	//�_���[�W
		enCC,	//�ړ��W�Q
		enBuffAtcPow, //�U���̓o�t
		enBuffDefPow,	//�h��̓o�t
		enDebuffAtcPow,	//�U���̓f�o�t
		enDebuffDefPow,	//�h��͑S�ʒቺ
		enbuffAtc,	//�U���͑S�ʃo�t
		enDoT,	//Damage over time(�p���_���[�W���󂯂�)
		enHardCC, //�s���W�Q(�ړ��s��and�X�L���g�p�s��)
		enMajinken
	};

	State GetState() {
		return m_state;
	}

private:
	void AddAct();
	void Clear();
	State m_state = enNull;

	int m_abnormal = 0;

	float m_damTime = 0;
	float m_dam = 0;

	float m_efTime = 0;
	float m_time = 0;
	double m_endTime = 0;
	double m_tarSpeed = 0;
	double m_pow = 0;
	double m_ExPow = 0;
	CEffect* m_effect = nullptr;
	Monster* m_target = nullptr;
	float m_DoTParam = 0;
	Monster* m_Invoker = nullptr;
	float m_buffdebuffParam = 1.f;
	float m_invokerExAtk = 1.f;
	bool m_isTargetAlive = true;
};