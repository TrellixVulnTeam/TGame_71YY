#include "stdafx.h"
#include "GameData.h"
#include "Monster/Monsters/TestMons.h"
#include "Monster/Monsters/Uma.h"
#include "Monster/Monsters/Fairy.h"
#include "Monster/Monsters/Armor.h"
#include "Monster/Monsters/Goblin.h"
#include "Monster/Monsters/Book.h"
#include "Monster/Monsters/RedHead.h"
#include "Monster/Monsters/kikyo.h"
#include "Monster/Monsters/ShikoChu.h"
#include "Monster/Monsters/Ringo.h"
#include "Monster/Monsters/Chris.h"


Monster* g_mons[64];
int g_buddyCount = 0;
int g_enemyCount = 0;
int g_monsCount = 0;
int g_meNum = 0;
int g_meTeam = 0;

int g_monset[6] = { 1,1,1,1,1,1 };
AIsetData g_AIset[6] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
void GameData::deletemons(Monster * mon)
{
	for (Monster* gmon : g_mons)
	{
		if (gmon == nullptr)
			break;
		for (auto ac : gmon->Getactions())
		{
			if (ac->Gettarget() == mon)
				ac->Settarget(nullptr);
		}
	}
	g_monsCount--;
	for (int i = mon->Getnum(); i < g_monsCount+1; i++)
	{
		g_mons[i] = g_mons[i + 1];
		if(g_mons[i] != NULL)
			g_mons[i]->Setnum(i);
	}
	/*std::vector<Monster*>::iterator ite = std::find(g_mons.begin(), g_mons.end(), mon);
	g_mons.erase(ite);*/
}

Monster * GameData::LoadMonster(int monID)
{
	Monster* mon = nullptr;
	switch (monID)
	{
	case enTest:
		mon = NewGO<TestMons>(0, "monster");
		break;
	case enUmataur:
		mon = NewGO<Uma>(0, "monster");
		break;
	case enFairy:
		mon = NewGO<Fairy>(0, "monster");
		break;
	case enArmor:
		mon = NewGO<Armor>(0, "monster");
		break;
	case enGoblin:
		mon = NewGO<Goblin>(0, "monster");
		break;
	case enBook:
		mon = NewGO<Book>(0, "monster");
		break;
	case enRedHead:
		mon = NewGO<RedHead>(0, "monster");
		break;
	case enKikyo:
		mon = NewGO<Kikyo>(0, "monster");
		break;
	case enShikoChu:
		mon = NewGO<ShikoChu>(0, "monster");
		break;
	/*case enRingo:
		mon = NewGO<Ringo>(0, "monster");
		break;*/
	case enChris:
		mon = NewGO<Chris>(0, "monster");
		break;
	}
	return mon;
}

const wchar_t * GameData::GetMonsterIconPath(int monID)
{
	switch (monID)
	{
	case enTest:
		return L"Assets/sprite/mon_one.dds";
		break;
	case enUmataur:
		return L"Assets/sprite/mon_uma.dds";
		break;
	case enFairy:
		return L"Assets/sprite/mon_fairy.dds";
		break;
	case enArmor:
		return L"Assets/sprite/mon_armor.dds";
		break;
	case enGoblin:
		return L"Assets/sprite/mon_gob.dds";
		break;
	case enBook:
		return L"Assets/sprite/mon_book.dds";
		break;
	case enRedHead:
		return L"Assets/sprite/mon_RedHead.dds";
		break;
	case enKikyo:
		return L"Assets/sprite/mon_kikyo.dds";
		break;
	case enShikoChu:
		return L"Assets/sprite/mon_bug.dds";
		break;
	/*case enRingo:
		return L"Assets/sprite/mon_ringo.dds";
		break;*/
	case enChris:
		return L"Assets/sprite/mon_cri.dds";
		break;
	case enShell:
		return L"Assets/sprite/mon_shell.dds";
		break;
	}
	return nullptr;
}

const wchar_t* GameData::GetMonsterName(MonsterID id) {
	switch (id)
	{
	case enTest:
		return L"�e�X�g";
		break;
	case enUmataur:
		return L"�n�^�E���X";
		break;
	case enFairy:
		return L" �d��";
		break;
	case enArmor:
		return L" �Z";
		break;
	case enGoblin:
		return L"�S�u����";
		break;
	case enBook:
		return L"�{";
		break;
	case enRedHead:
		return L"���b�h�w�b�h";
		break;
	case enKikyo:
		return L"�L�L���E";
		break;
	case enShikoChu:
		return L"������";
		break;
	/*case enRingo:
		return L"��񂲂����";
		break;*/
	case enChris:
		return L"�N���X";
	case enShell:
		return L"�V�F��";
	default:
		assert(false);
		break;
	}
}

const wchar_t* GameData::GetActionInfo(ActionID actID) {
	switch (actID) {
	case enChase:
		return L"�ǂ�������";
	case enAtack:
		return L"�ʏ�U��";
	case enLeave:
		return L"������񂾂�";
	case enDefense:
		return L" �h��";
	case enFire:
		return L"�t�@�C�A�[";
	case enTackle:
		return L"�G���Ԃ��Ƃ΂�";
	case enGuardian:
		return L"�G�̍U����\n�W��������";
	case enRecovery:
		return L"�񕜂�����";
	case enSuperBeam:
		return L"�������������X�^�[��\n�_���[�W��^����";
	case enObstMove:
		return L"�ړ��W�Q������";
	case enCleanse:
		return L"��Ԉُ���N���A";
	case enBuffAtc:
		return L"�U���͂��グ��";
	case enDebuffAtc:
		return L"�U���͂�������";
	case enBuffDef:
		return L"�h��͂��グ��";
	case enDebuffDef:
		return L"�h��͂�������";
	case enClearStack:
		return L"�G�̍s����\n�S�ĉ�������";
	case enMajinken:
		return L"�`���[�W&�p���`";
	case enManaHeal:
		return L"MP����";
	case enBlizzard:
		return L"�A���_���[�W\n��Ԉُ��t�^";
	case enIgnite:
		return L"�Ώۂɂ₯�Ǐ��";
	case enPoison:
		return L"�Ώۂɓŏ��";
	case enThunder:
		return L"�A���_���[�W\n���т��ԕt�^";
	case enSpecialAttack:
		return L"�����̗̑͂�\n����ēG���U��";
	default:
		return L"�Ȃ��ł�";
	}
}
const wchar_t* GameData::GetActionName(ActionID actID)
{
	const wchar_t* ws;
	switch (actID)
	{
	case enChase:
		//ws = L"�ǐ�";
		ws = L"CHASE";
		break;
	case enAtack:
		//ws = L"�p���`";
		ws = L"ATTACK";
		break;
	case enLeave:
		//ws = L"������";
		ws = L"ESCAPE";
		break;
	case enDefense:
		//ws = L"���";
		ws = L"DEFENSE";
		break;
	case enFire:
		//ws = L"�t�@�C�A";
		ws = L"FIRE";
		break;
	case enTackle:
		//ws = L"�^�b�N��";
		ws = L"TACKLE";
		break;
	case enGuardian:
		//ws = L"���";
		ws = L"GUARDIAN";
		break;
	case enRecovery:
		//ws = L"��";
		ws = L"HEAL";
	case enSuperBeam:
		ws = L"SUPER BEAM";
		break;
	case enObstMove:
		ws = L"Obst Move";
		break;
	case enCleanse:
		ws = L"Cleanse";
		break;
	case enBuffAtc:
		ws = L"Attack Buff";
		break;
	case enDebuffAtc:
		ws = L"Attack Debuff";
		break;
	case enBuffDef:
		ws = L"Defense Buff";
		break;
	case enDebuffDef:
		ws = L"Defense Debuff";
		break;
	case enClearStack:
		ws = L"Clear Stack";
		break;
	case enMajinken:
		ws = L"Majinken";
		break;
	case enManaHeal:
		ws = L"MP Heal";
		break;
	case enBlizzard:
		ws = L"Blizzard";
		break;
	case enIgnite:
		ws = L"Ignite";
		break;
	case enPoison:
		ws = L"Poison";
		break;
	case enThunder:
		ws = L"Thunder";
		break;
	case enSpecialAttack:
		ws = L"Tokkou";
		break;
	default:
		ws = L"";
	}
	return ws;
}

ActionID* GameData::GetMonsterActions(int monsterID, int& count)
{
	ActionID* ua = nullptr;
	count = 0;
	switch (monsterID)
	{
	case enTest:
		count = 99;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enActNone;
		ua[6] = enSuperBeam;
		ua[7] = enObstMove;
		ua[8] = enCleanse;
		ua[9] = enBuffAtc;
		ua[10] = enDebuffAtc;
		ua[11] = enBuffDef;
		ua[12] = enDebuffDef;
		ua[13] = enMajinken;
		ua[14] = enClearStack;
		ua[15] = enManaHeal;
		ua[16] = enBlizzard;
		ua[17] = enIgnite;
		ua[18] = enPoison;
		ua[19] = enThunder;
		break;
	case enUmataur:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enActNone;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enMajinken;
		break;
	case enFairy:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enRecovery;
		ua[5] = enFire;
		break;
	case enArmor:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enGuardian;
		break;
	case enGoblin:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enPoison;
		ua[5] = enDebuffAtc;
		break;
	case enBook:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enCleanse;
		ua[5] = enClearStack;
		break;
	case enRedHead:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enIgnite;
		ua[5] = enThunder;
		break;
	case enKikyo:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enSuperBeam;
		ua[5] = enManaHeal;
		break;
	case enShikoChu:
		count = 2;
		ua = new ActionID[count];
		ua[enAtack] = enSpecialAttack;
		ua[enChase] = enChase;
		break;
	/*case enRingo:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enActNone;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enMajinken;*/
	case enChris:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enBlizzard;
		ua[5] = enSuperBeam;
		break;
	case enShell:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enBlizzard;
		ua[5] = enSuperBeam;
		break;
		break;
	}
	return ua;
}

ActionID GameData::GetMonsterAction(int monsterID, int actionIndex)
{
	int cnt = 0;
	ActionID* ua = GetMonsterActions(monsterID, cnt);
	
	if (actionIndex >= cnt)
		return ActionID::enActNone;

	ActionID ad = ua[actionIndex];
	delete ua;
	return ad;
}
