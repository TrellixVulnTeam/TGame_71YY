#pragma once
#include "../../Engine/character/CharacterController.h"

#include "../VisualScriptAI/VisualScriptAI.h"

class MonsterAction;
class MonsterEffect;
class MonsterActionList;
class MonsterMarker;
class PythonBridge;
class ACTEffectGrant;
enum ActionID;

class Monster:public GameObject
{
public:
	~Monster();

	struct MonsterInitParam {
		float HP;
		float MP;
		float DefencePow;
		float ExDefensePow;
		float AttackPow;
		float ExAttackPow;
		float Speed;
		float Radius;
		float Height;
		SkinModelRender* ModelRender;
		int NumAnimation;
	};

	void init(float HP, float MP,float Defence, float ExDefense, 
		float Attack,float ExAttack, float speed, 
					float radius, float height, SkinModelRender* smr, 
		int animnum);

	void init(MonsterInitParam param);

	void SuddenDeath();

	bool Start() override final;
	void Update() override final;

	void SetUseAction(ActionID* ua,int size);
	ActionID* GetUseAction()
	{
		return m_UseAction;
	}

	//Monster�̃A�N�V���������s����֐�
	void execute();

	//�ړ�����Ƃ��Ɏg���֐�
	void Move();

	//��]����Ƃ��Ɏg���֐�
	void Turn();

	void TurnEx();

	void receiveDamage();

	//�m�b�N�o�b�N���Ɏg���֐�
	void Knockback();

	//�m�b�N�o�b�N�̎n�܂�
	//v: �m�b�N�o�b�N����x�N�g��
	void StartKnockback(CVector3 v);

	void SetKnockback(CVector3 v);

	//���
	enum en_State
	{
		en_NowLoading,
		en_Execute,
		en_Dead,
	};
	
	int GetState()
	{
		return m_state;
	}


	enum AbnormalState
	{
		abNull,		//None
		abPoison,	//��
		abStan,		//�X�^��
		abBurn,		//�₯��
		abCC,		//�ړ��W�Q
	};

	//��Ԉُ�̐ݒ�
	//abn: enum
	//void SetAbnormalState(int abn)
	//{
	//	//m_abnormalState = (AbnormalState)abn;
	//	m_abnormalStates.push_back((AbnormalState)abn);
	//}
	void SetAbnormalState(ACTEffectGrant* abn)
	{
		m_abnormalStates.push_back(abn);
	}

	/*void ClearAbnormalState(int abn)
	{
		std::vector<AbnormalState>::iterator ite;
		ite = std::find(m_abnormalStates.begin(), m_abnormalStates.end(), (AbnormalState)abn);
		m_abnormalStates.erase(ite);

	}*/
	void ClearAbnormalState(ACTEffectGrant* abn)
	{
		if (!m_abnormalStates.size()) return;
		if (m_abnormalStates.size() == 1) {
			m_abnormalStates.clear();
		}
		else {
			m_abnormalStates.erase(remove(m_abnormalStates.begin(), m_abnormalStates.end(), abn));
		}
		//std::vector<ACTEffectGrant*>::iterator ite;
		//ite = std::find(m_abnormalStates.begin(), m_abnormalStates.end(), abn);
		//m_abnormalStates.erase(ite);
	}
	
	//��Ԉُ�̎擾
	//return ��Ԉُ�
	/*std::vector<AbnormalState> GetAbnormalState()
	{
		return m_abnormalStates;
	}*/
	std::vector<ACTEffectGrant*> GetAbnormalState()
	{
		return m_abnormalStates;
	}

	//��Ԉُ��Ԃ�(ID)
	int GetAbnormalStateID(int num);
	

	//�g��python�̃t�@�C����ݒ肷��
	//st: �t�@�C���̖��O
	void SetpyFile(std::string* st)
	{
		m_pyFile = st;
	}

	//�g��python�t�@�C���̖��O��Ԃ�
	std::string* GetpyFile()
	{
		return m_pyFile;
	}

	//�g��visualScript�̃t�@�C����ݒ肷��
	//st: �t�@�C���̖��O
	void SetVisualScriptAI(std::string* st)
	{
		m_pyFile = st;
		m_visualAI = new VisualScriptAI(this, st);
		m_isUseVSAI = true;
	}

	//HP��Ԃ�
	float GetHP()
	{
		return m_HP;
	}

	void SetHP(float hp)
	{
		if ((m_maxHP - hp) < 0)
		{
			m_HP = m_maxHP;
		}
		else 
			m_HP = hp;
	}

	//�_���[�W
	//d: �H�炤�_���[�W
	void Damage(float d)
	{
		//m_HP -= d;
		m_Damage += d;
	}

	void DamageEx(float d)
	{
		m_DamageEx += d;
	}

	//MP��Ԃ�
	float GetMP()
	{
		return m_MP;
	}

	void SetMP(float mp)
	{
		if ((m_maxMP - mp) < 0)
			m_MP = m_maxMP;
		else 
			m_MP = mp;
	}

	void SetMPrecv(float rmp)
	{
		m_MPrecov = rmp;
	}

	float GetMPrecv()
	{
		return m_MPrecov;
	}

	float GetMaxHP()
	{
		return m_maxHP;
	}
	float GetMaxMP()
	{
		return m_maxMP;
	}
	void SetMaxHP(float max)
	{
		m_maxHP = max;
	}
	void SetMaxMP(float max)
	{
		m_maxMP = max;
	}

	float GetDefense()
	{
		return m_Defense;
	}

	float GetExDefense()
	{
		return m_ExDefense;
	}

	void SetDefense(float d)
	{
		m_Defense = d;
	}

	void SetExDefense(float d)
	{
		m_ExDefense = d;
	}


	float GetAttack()
	{
		return m_Attack;
	}

	float GetExAttack()
	{
		return m_ExAttack;
	}

	float GetSpeed()
	{
		return m_speed;
	}

	//�R���C�_�[�̔��a��Ԃ�
	float Getradius()
	{
		return m_radius;
	}

	//�R���C�_�[�̍�����Ԃ�
	float Getheight()
	{
		return m_height;
	}

	//���݂̃|�W�V������Ԃ�
	CVector3 Getpos()
	{
		return m_pos;
	}

	//�|�W�V������ݒ肷��
	//v: �ݒ肷��|�W�V����
	void Setpos(CVector3 v);

	float GetPspeed()
	{
		return m_speed;
	}

	//�X�s�[�h��Ԃ�
	CVector3 Getspeed()
	{
		return m_movespeed;
	}

	//�X�s�[�h��ݒ肷��
	//v: �X�s�[�h�x�N�g��
	void Setspeed(CVector3 v)
	{
		m_oldmovespeed = m_movespeed;
		m_movespeed = v;
	}

	void SetSpeed(float speed) {
		m_speed = speed;
	}

	void SetDefensePower(float pow) {
		m_Defense = pow;
	}

	void SetExDefensePower(float pow) {
		m_ExDefense = pow;
	}

	void SetAttackPower(float pow) {
		 m_Attack = pow;
	}

	void SetExAttackPower(float pow) {
		m_ExAttack = pow;
	}

	//
	CVector3 GetFrontvec()
	{
		CVector3 vec = m_movespeed;
		if (vec.Length() > 1.0f)
		{
			vec.Normalize();
			m_front = vec;
		}

		return m_front;
	}

	CQuaternion GetRotation()
	{
		return m_rot;
	}
	void SetRotation(CQuaternion rot);

	//�������Ă��邩��ݒ肷��
	void Setiswalk(bool b)
	{
		m_iswalk = b;
	}

	//�`�[����Ԃ�
	int Getteam()
	{
		return m_team;
	}

	//�`�[����ݒ肷��
	//t: �`�[��
	void Setteam(int t)
	{
		m_team = t;
	}

	//num��Ԃ�
	int Getnum()
	{
		return m_num;
	}

	//num��ݒ肷��
	//num: num
	void Setnum(int num)
	{
		m_num = num;
	}

	//ID��Ԃ�
	int GetID()
	{
		return m_ID;
	}

	//�Z�̃X�^�b�N���N���A����
	void ClearActionStack() {
		m_actions.clear();
	}

	//���ꂢ��Ȃ�
	Monster* Getmon()
	{
		return this;
	}

	//�A�N�V������������Ƃ��Ɏg��
	//ma: �����X�^�[�A�N�V����
	void AddAction(MonsterAction* ma);

	//�s���Ă���E�s���\��̃A�N�V������Ԃ�
	std::vector<MonsterAction*> Getactions()
	{
		return m_actions;
	}

	void ReleaseMAL();
	void ReleaseMark();

	//�A�j���[�V����������Ƃ��͕K����������g�����ƁB
	void anim_idle();
	void anim_walk();
	void anim_atack();
	void anim_defenseF();
	void anim_defenseM();
	void anim_defenseE();
	void anim_extra1();

	bool isAnimPlay();

	//�A�j���[�V�����̏��
	enum anim
	{
		en_idle,
		en_walk,
		en_atack,
		en_defenseF,
		en_defenseM,
		en_defenseE,
		en_extra1,
		en_extra2,
		en_extra3,
		en_extra4,
		en_extra5,
	};

	void end()
	{
		m_end = true;
	}

protected:
	//const char* m_pyFile = NULL;				//�g��python�t�@�C���̖��O
	std::string* m_pyFile = nullptr;
	int m_ID = 0;								//�����X�^�[�̎�ނ𔻒f���邽�߂�ID
	int m_num = 0;								//�w�ԍ��݂����Ȋ���
	int m_team = 0;								//�`�[���ԍ�

	CharacterController m_cc;					//�L�����R��
	float m_radius = 0.0f;						//���a
	float m_height = 0.0f;						//����
	SkinModelRender* m_smr = nullptr;			//�X�L�����f�������_�[
	float m_HP = 0;								//HP
	float m_maxHP = 0;
	float m_MP = 0;								//MP
	float m_maxMP = 0;
	float m_Defense = 0;						//�h���
	float m_ExDefense = 0;						//����h���
	float m_Attack = 0;							//�U����
	float m_ExAttack = 0;						//����U����

	float m_Damage = 0;							//�_���[�W
	float m_DamageEx = 0;						//����_���[�W

	float m_MPrecov = 3;

	float m_speed = 0.0f;						//�X�s�[�h
	float m_gravity = 50.0f;					//�d��
	
	CVector3 m_movespeed = CVector3::Zero();	//���[�u�X�s�[�h
	CVector3 m_oldmovespeed = CVector3::Zero();	//�Ẫ��[�u�X�s�[�h
	CVector3 m_front = CVector3::Zero();		//�O����
	bool m_iswalk = false;						//
	bool m_isKnockback = false;					//
	CVector3 m_vKnockback = CVector3::Zero();	//
	CVector3 m_vSubKnock = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();			//�|�W�V����
	CQuaternion m_rot = CQuaternion::Identity();//��]
	int m_turncount = 0;
	float m_rotangle = 0;

	AbnormalState m_abnormalState = abNull;
	//std::vector<AbnormalState> m_abnormalStates;
	std::vector<ACTEffectGrant*> m_abnormalStates;

	PythonBridge* m_PB;

	ActionID* m_UseAction;
	int m_useActionSize = 0;
	std::vector<MonsterAction*> m_actions;		//�g���A�N�V����
	en_State m_state = en_NowLoading;
	bool isLoading = false;

	MonsterActionList* m_MAL = nullptr;
	bool m_dmal = false;

	MonsterMarker* m_marker = nullptr;

	MonsterEffect* m_effect;

	int m_AnimNum = 0;							//�A�j���[�V�����̌�

	float m_actionTime = 0.0f;
	float m_MPRecvTime = 0.0f;

	bool m_end = false;

	bool m_isUseVSAI = false;					//visualAI���g�����ǂ���
	VisualScriptAI* m_visualAI = nullptr;		//visualAI�̂��񂷂���

	float m_limitDist = 1036.f;
};