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
#include "Monster/Monsters/Shell.h"


Monster* g_mons[64];
int g_buddyCount = 0;
int g_enemyCount = 0;
int g_monsCount = 0;
int g_meNum = 0;
int g_meTeam = 0;

int g_monset[6] = { 0,0,0,0,0,0 };
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
	case enRingo:
		mon = NewGO<Ringo>(0, "monster");
		break;
	case enChris:
		mon = NewGO<Chris>(0, "monster");
		break;
	case enShell:
		mon = NewGO<Shell>(0, "monster");
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
	case enRingo:
		return L"Assets/sprite/mon_ringo.dds";
		break;
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
		return L"テスト";
		break;
	case enUmataur:
		return L"ウマタウロス";
		break;
	case enFairy:
		return L" 妖精";
		break;
	case enArmor:
		return L" 鎧の怪";
		break;
	case enGoblin:
		return L"ゴブリン";
		break;
	case enBook:
		return L"魔本";
		break;
	case enRedHead:
		return L"レッドヘッド";
		break;
	case enKikyo:
		return L"キキョウ";
		break;
	case enShikoChu:
		return L"死光虫";
		break;
	case enRingo:
		return L"りんごちゃん";
		break;
	case enChris:
		return L"クリス";
	case enShell:
		return L"シェル";
	default:
		assert(false);
		break;
	}
}

const char* GameData::GetMonsterNameMulti(MonsterID monID)
{
	switch (monID)
	{
	case enTest:
		return "testMons";
		break;
	case enUmataur:
		return "Uma";
		break;
	case enFairy:
		return "Yose";
		break;
	case enArmor:
		return "Armor";
		break;
	case enGoblin:
		return "Goblin";
		break;
	case enBook:
		return "Book";
		break;
	case enRedHead:
		return "RedHead";
		break;
	case enKikyo:
		return "Kikyo";
		break;
	case enShikoChu:
		return "SicoChu";
		break;
	case enRingo:
		return "Ringo";
		break;
	case enChris:
		return "Chris";
	case enShell:
		return "Shell";
	default:
		assert(false);
		break;
	}
}

const wchar_t* GameData::GetActionInfo(ActionID actID) {
	switch (actID) {
	case enChase:
		return L"追いかける";
	case enAtack:
		return L"通常攻撃";
	case enLeave:
		return L"逃げるんだよ";
	case enDefense:
		return L"防御";
	case enFire:
		return L"ファイアー";
	case enTackle:
		return L"敵をぶっとばす";
	case enGuardian:
		return L"敵の攻撃を\n集中させる";
	case enRecovery:
		return L"回復させる";
	case enSuperBeam:
		return L"当たったモンスターに\nダメージを与える";
	case enObstMove:
		return L"移動妨害をする";
	case enCleanse:
		return L"状態異常をクリア";
	case enBuffAtc:
		return L"攻撃力を上げる";
	case enDebuffAtc:
		return L"攻撃力を下げる";
	case enBuffDef:
		return L"防御力を上げる";
	case enDebuffDef:
		return L"防御力を下げる";
	case enClearStack:
		return L"敵の行動を\n全て解除する";
	case enMajinken:
		return L"チャージ&パンチ";
	case enManaHeal:
		return L"MPを回復";
	case enBlizzard:
		return L"連続ダメージ\n当たった者は凍り付く";
	case enIgnite:
		return L"対象にやけど状態";
	case enPoison:
		return L"対象に毒状態";
	case enThunder:
		return L"連続ダメージ\nしびれ状態付与";
	case enSpecialAttack:
		return L"捨て身の特攻";
	default:
		return L"ないです";
	}
}
const wchar_t* GameData::GetActionName(ActionID actID)
{
	const wchar_t* ws;
	switch (actID)
	{
	case enChase:
		ws = L"CHASE";
		break;
	case enAtack:
		ws = L"ATTACK";
		break;
	case enLeave:
		ws = L"ESCAPE";
		break;
	case enDefense:
		ws = L"DEFENSE";
		break;
	case enFire:
		ws = L"FIRE";
		break;
	case enTackle:
		ws = L"TACKLE";
		break;
	case enGuardian:
		ws = L"GUARDIAN";
		break;
	case enRecovery:
		ws = L"HEAL";
		break;
	case enSuperBeam:
		ws = L"SUPER_BEAM";
		break;
	case enObstMove:
		ws = L"Obst_Move";
		break;
	case enCleanse:
		ws = L"Cleanse";
		break;
	case enBuffAtc:
		ws = L"ATK_Buff";
		break;
	case enDebuffAtc:
		ws = L"ATK_Debuff";
		break;
	case enBuffDef:
		ws = L"DEF_Buff";
		break;
	case enDebuffDef:
		ws = L"DEF_Debuff";
		break;
	case enClearStack:
		ws = L"Clear_Stack";
		break;
	case enMajinken:
		ws = L"Majinken";
		break;
	case enManaHeal:
		ws = L"MP_Heal";
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
		ws = L"Kamikaze";
		break;
	case enMove:
		ws = L"MOVE";
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
		ua[20] = enMove;
		break;
	case enUmataur:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enActNone;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enMajinken;
		ua[6] = enMove;
		break;
	case enFairy:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enRecovery;
		ua[5] = enFire;
		ua[6] = enMove;
		break;
	case enArmor:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enGuardian;
		ua[4] = ActionID::enBuffDef;
		ua[5] = ActionID::enBuffAtc;
		ua[6] = enMove;
		break;
	case enGoblin:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enPoison;
		ua[5] = enDebuffAtc;
		ua[6] = enMove;
		break;
	case enBook:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enCleanse;
		ua[5] = enClearStack;
		ua[6] = enMove;
		break;
	case enRedHead:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enIgnite;
		ua[5] = enThunder;
		ua[6] = enMove;
		break;
	case enKikyo:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enSuperBeam;
		ua[5] = enManaHeal;
		ua[6] = enMove;
		break;
	case enShikoChu:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enSpecialAttack;
		ua[enChase] = enChase;
		ua[enLeave] = enActNone;
		ua[enDefense] = enActNone;
		ua[4] = enActNone;
		ua[5] = enActNone;
		ua[6] = enMove;
		break;
	case enRingo:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enActNone;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enMajinken;
		ua[6] = enMove;
		break;
	case enChris:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enBlizzard;
		ua[5] = enSuperBeam;
		ua[6] = enMove;
		break;
	case enShell:
		count = 7;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enBlizzard;
		ua[5] = enSuperBeam;
		ua[6] = enMove;
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
