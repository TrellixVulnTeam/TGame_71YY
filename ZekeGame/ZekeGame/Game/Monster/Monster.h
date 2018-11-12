#pragma once
#include "../../Engine/character/CharacterController.h"
//#include "MonsterAI.h"
class MonsterAction;
class PythonBridge;
//class CharacterController;
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


	enum en_State
	{
		en_NowLoading,
		en_Execute,
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
		return m_speed;
	}
	void Setspeed(CVector3 v)
	{
		m_oldspeed = m_speed;
		m_speed = v;
	}
	int Getteam()
	{
		return m_team;
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

protected:
	const char* m_pyFile = NULL;				//�g��python�t�@�C���̖��O
	int m_ID = 0;								//�����X�^�[�̎�ނ𔻒f���邽�߂�ID
	int m_num = 0;								//�w�ԍ��݂����Ȋ���
	int m_team = 0;								//�`�[���ԍ�
	//std::vector<int> m_useAction;

	CharacterController m_cc;					//�L�����R��
	SkinModelRender* m_smr = nullptr;			//�X�L�����f�������_�[
	int m_HP = 0;								//HP
	int m_MP = 0;								//MP
	float m_gravity = 50.0f;					//�d��
	CVector3 m_speed = CVector3::Zero();		//���[�u�X�s�[�h
	CVector3 m_oldspeed = CVector3::Zero();		//�Ẫ��[�u�X�s�[�h
	CVector3 m_pos = CVector3::Zero();			//�|�W�V����
	CQuaternion m_rot = CQuaternion::Identity();//��]

	PythonBridge* m_PB;
	std::vector<MonsterAction*> m_actions;		//�g���A�N�V����
	en_State m_state = en_NowLoading;
};