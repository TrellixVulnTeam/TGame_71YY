#pragma once
#include "../../Engine/character/CharacterController.h"

class MonsterAction;
class PythonBridge;
class Monster:public GameObject
{
public:
	~Monster();

	bool Start();
	void Update();

	//Monster�̃A�N�V���������s����֐�
	void execute();

	//�ړ�����Ƃ��Ɏg���֐�
	void Move();

	//��]����Ƃ��Ɏg���֐�
	void Turn();

	void Knockback();

	void StartKnockback(CVector3 v);

	enum en_State
	{
		en_NowLoading,
		en_Execute,
		en_Dead,
	};

	
	void SetpyFile(const char* st)
	{
		m_pyFile = st;
	}
	const char* GetpyFile()
	{
		return m_pyFile;
	}

	int GetHP()
	{
		return m_HP;
	}
	void Damage(int d)
	{
		m_HP -= d;
	}
	int GetMP()
	{
		return m_MP;
	}
	CVector3 Getpos()
	{
		return m_pos;
	}
	void Setpos(CVector3 v)
	{
		m_pos = v;
	}
	CVector3 Getspeed()
	{
		return m_movespeed;
	}
	void Setspeed(CVector3 v)
	{
		m_oldmovespeed = m_movespeed;
		m_movespeed = v;
	}

	void Setiswalk(bool b)
	{
		m_iswalk = b;
	}
	int Getteam()
	{
		return m_team;
	}
	void Setteam(int t)
	{
		m_team = t;
	}
	int Getnum()
	{
		return m_num;
	}
	void Setnum(int num)
	{
		m_num = num;
	}

	Monster* Getmon()
	{
		return this;
	}

	void AddAction(MonsterAction* ma);
	std::vector<MonsterAction*> Getactions()
	{
		return m_actions;
	}

	//�A�j���[�V����������Ƃ��͕K����������g�����ƁB
	void anim_idle();
	void anim_walk();
	void anim_atack();
	void anim_defense();
	void anim_recovery();

	enum anim
	{
		en_idle,
		en_walk,
		en_atack,
		en_defense,
		en_recovery,
	};

protected:
	const char* m_pyFile = NULL;				//�g��python�t�@�C���̖��O
	int m_ID = 0;								//�����X�^�[�̎�ނ𔻒f���邽�߂�ID
	int m_num = 0;								//�w�ԍ��݂����Ȋ���
	int m_team = 0;								//�`�[���ԍ�

	CharacterController m_cc;					//�L�����R��
	SkinModelRender* m_smr = nullptr;			//�X�L�����f�������_�[
	int m_HP = 0;								//HP
	int m_MP = 0;								//MP
	float m_gravity = 50.0f;					//�d��
	CVector3 m_movespeed = CVector3::Zero();	//���[�u�X�s�[�h
	CVector3 m_oldmovespeed = CVector3::Zero();	//�Ẫ��[�u�X�s�[�h
	bool m_iswalk = false;						//
	bool m_isKnockback = false;					//
	CVector3 m_vKnockback = CVector3::Zero();	//
	CVector3 m_vSubKnock = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();			//�|�W�V����
	CQuaternion m_rot = CQuaternion::Identity();//��]

	PythonBridge* m_PB;
	std::vector<MonsterAction*> m_actions;		//�g���A�N�V����
	en_State m_state = en_NowLoading;

	int m_AnimNum = 0;							//�A�j���[�V�����̌�

	float m_time = 0.0f;
};