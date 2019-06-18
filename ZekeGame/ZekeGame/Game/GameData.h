#pragma once
#include "Monster/Monster.h"
#include "Monster/MonsterAction.h"

extern Monster* g_mons[64];

enum MonsterID
{
	enTest,
	enUmataur,
	enFairy,
	enArmor,
	enGoblin,
	enBook,
	enRedHead,
	enKikyo,
	enShikoChu,
	enRingo,
	enNumMonster,
};

enum ActionID
{
	enChase,
	enAtack,
	enLeave,
	enDefense,
	enFire,
	enTackle,
	enGuardian,
	enRecovery,
	enSuperBeam,
	enObstMove,
	enCleanse,
	enBuffAtc,
	enDebuffAtc,
	enBuffDef,
	enDebuffDef,
	enClearStack,
	enMajinken,
	enManaHeal,
	enBlizzard,
	enIgnite,
	enPoison,
	enThunder,
	enSpecialAttack,
	enActNone = 999
};

struct AIsetData
{
	int AInum =0;
	int AImode = 0;
};

//static std::vector<Monster*> g_mons;
extern int g_buddyCount;
extern int g_enemyCount;
extern int g_monsCount;
extern int g_meNum;
extern int g_meTeam;

extern int g_monset[6];
extern AIsetData g_AIset[6];
static void deletemons(Monster* mon)
{
	for (Monster* gmon : g_mons)
	{
		for (auto ac : gmon->Getactions())
		{
			if(ac->Gettarget() == mon)
				ac->Settarget(nullptr);
		}
	}
	for (int i = mon->Getnum(); i < g_monsCount; i++)
	{
		g_mons[i] = g_mons[i + 1];
	}
	/*std::vector<Monster*>::iterator ite = std::find(g_mons.begin(), g_mons.end(), mon);
	g_mons.erase(ite);*/
}
class GameData
{
public:
	static void deletemons(Monster* mon);
	static Monster* LoadMonster(int monID);
	static const wchar_t* GetMonsterIconPath(int monID);
	static const wchar_t* GetMonsterName(MonsterID monID);

	/*
	�����X�^�[���g�p����ActionID��Ԃ�
	����:�K���f���[�g���ĂˁB
	args:
		monsterID: �����X�^�[��ID
		count: ���̒��Ƀ����X�^�[���g�p����Action�̌�������
	*/
	static ActionID* GetMonsterActions(int monsterID, int& count);

	/*
	�����X�^�[���g�p����w�肵���ʒu��ActionID��Ԃ�
	����:���s�����ꍇ��ActionID::enActNone��Ԃ�
	args:
		monsterID: �����X�^�[��ID
		actionIndex: ���Ԗڂ̋Z��
	*/
	static ActionID GetMonsterAction(int monsterID, int actionIndex);
};