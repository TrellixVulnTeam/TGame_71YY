#include "stdafx.h"
#include "StageSetup.h"
#include "../GameData.h"
#include "../Monster/Monster.h"
#include "../Monster/Monsters/TestMons.h"
#include "../Monster/Monsters/Uma.h"
#include "../Monster/Monsters/Fairy.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "..//Dungeon/DungeonData.h"
#include <string>
#include <array>

StageSetup::StageSetup()
{
	
}

StageSetup::~StageSetup()
{
}

void StageSetup::SuddenDeath(const char* files[6], MonsterID monids[6], int teams[6])
{
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		DeleteGO(mon);
	}

	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };
	int poi = 0;

	bool isp = true;
	for (int i = 0; i < 6; i++)
	{
		if (monids[i] == -1)
			break;
		if (teams[i] == 1 && isp)
		{
			poi = 3;
			isp = false;
		}
		Monster* mon = GameData::LoadMonster(monids[i]);
		mon->Setpos(poss[poi]);
		mon->Setnum(i);
		mon->Setteam(teams[i]);
		//mon->SetpyFile(files[i]);
		g_mons[i] = mon;

		mon->SuddenDeath();
		g_mons[i] = mon;

		poi++;
	}
}

void StageSetup::PVPSetup(std::vector<std::string> files, int monsterAI[6],MonsterID monids[6], int AImode[6])
{
	int team = 0;
	int num = 0;
	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		std::string* path;

		mon = GameData::LoadMonster(monids[i]);
		

		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);
		
		//python��VisualScript�̎d����
		if (AImode[i] == 0)
		{
			path = new std::string("PythonAIs.");
			*path += files[monsterAI[i]];
			mon->SetpyFile(path);
		}
		else
		{
			path = new std::string("Assets/VisualAI/");
			char wc[64];
			sprintf_s(wc, "%03d.va", monsterAI[i]);
			*path += wc;
			mon->SetVisualScriptAI(path);
		}

		g_mons[i] = mon;

	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}


void StageSetup::DungeonSetup(PyFile files, PyFile eneFiles, int monsterAI[6], MonsterID monids[6], int dunNumber, int AImode[6]) {
	int team = 0;
	int num = 0;
	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	PyFile enemyfiles = SetEnemyAI(dunNumber,monsterAI, monids);

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = GameData::LoadMonster(monids[i]);
		auto vaFiles = VisualAiFileLoad::FilesLoad();

		/*switch (monids[i])
		{
		case enTest:
			mon = NewGO<TestMons>(0, "monster");
			break;
		case enUmataur:
			mon = NewGO<Uma>(0, "monster");
			break;
		}*/
		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);
		if (team == 0) {
			//team
			//python��VisualScript�̎d����
			if (AImode[i] == 0)
			{
				std::string* path = new std::string("PythonAIs.");
				*path += files[monsterAI[i]];
				mon->SetpyFile(path);
			}
			else
			{
				std::string* path = new std::string("Assets/VisualAI/");
				*path += vaFiles[monsterAI[i]];
				*path += ".va";
				mon->SetVisualScriptAI(path);
			}
		}
		else{
			//enemy
			std::string* path = new std::string("PythonEnemyAIs.");
			//*path += eneFiles[monsterAI[i]];
			*path += enemyfiles[i-3];
			mon->SetpyFile(path);
		}
		g_mons[i] = mon;
	}
	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

//dungeon enemy ai and id
std::vector<std::string> StageSetup::SetEnemyAI(int dun, int* monAI, MonsterID* monId) {
	//TODO : Zeke : �_���W�����̓GAI�̒���
	int round = IDungeonData().GetRound();
	std::vector<std::string> filenames;
	filenames.reserve(3);
	switch (dun) {
	case 0: //1
	{
		filenames.push_back("zgob2");
		filenames.push_back("zgob1");
		filenames.push_back("zgob2");
		monAI[3] = 0;
		monId[3] = enGoblin;
		monAI[4] = 0;
		monId[4] = enGoblin;
		monAI[5] = 0;
		monId[5] = enGoblin;
	}
		break;
	case 1: //2
		if (round == 0) {
			filenames.push_back("zgob2");
			filenames.push_back("zgob3");
			filenames.push_back("zgob2");
			monAI[3] = 0;
			monId[3] = enGoblin;
			monAI[4] = 1;
			monId[4] = enGoblin;
			monAI[5] = 0;
			monId[5] = enGoblin;
		}
		if (round == 1) {
			filenames.push_back("zgob3");
			filenames.push_back("zyose1");
			filenames.push_back("zgob3");
			monAI[3] = 1;
			monId[3] = enGoblin;
			monAI[4] = 2;
			monId[4] = enFairy;
			monAI[5] = 1;
			monId[5] = enGoblin;
		}
		break;
	case 2: //2
		if (round == 0) {
			filenames.push_back("zyose2");
			filenames.push_back("zgob3");
			filenames.push_back("zyose2");
			monAI[3] = 2;
			monId[3] = enFairy;
			monAI[4] = 1;
			monId[4] = enGoblin;
			monAI[5] = 2;
			monId[5] = enFairy;
		}
		if (round == 1) {
			filenames.push_back("zgob3");
			filenames.push_back("zuma1");
			filenames.push_back("zgob3");
			monAI[3] = 1;
			monId[3] = enGoblin;
			monAI[4] = 1;
			monId[4] = enUmataur; 
			monAI[5] = 1;
			monId[5] = enGoblin;
		}
		break;
	case 3:	//2
		if (round == 0) {
			filenames.push_back("zyose2");
			filenames.push_back("zuma1");
			filenames.push_back("zyose");
			monAI[3] = 2;
			monId[3] = enFairy;
			monAI[4] = 4;
			monId[4] = enUmataur;
			monAI[5] = 2;
			monId[5] = enFairy;
		}
		if (round == 1) {
			filenames.push_back("zyose2");
			filenames.push_back("zarmor");
			filenames.push_back("zuma1");
			monAI[3] = 2;
			monId[3] = enFairy;
			monAI[4] = 5;
			monId[4] = enArmor;
			monAI[5] = 4;
			monId[5] = enUmataur;
		}
		break;
	case 4: //2
		if (round == 0) {
			filenames.push_back("04_uma");
			filenames.push_back("04_uma");
			filenames.push_back("04_uma");
			monAI[3] = 4;
			monId[3] = enUmataur;
			monAI[4] = 4;
			monId[4] = enUmataur;
			monAI[5] = 4;
			monId[5] = enUmataur;
		}
		if (round == 1) {
			filenames.push_back("05_armor");
			filenames.push_back("06_kikyo");
			filenames.push_back("05_armor");
			monAI[3] = 5;
			monId[3] = enArmor;
			monAI[4] = 6;
			monId[4] = enKikyo;
			monAI[5] = 5;
			monId[5] = enArmor;
		}
		break;
	case 5: //3
		if (round == 0) {
			filenames.push_back("05_armor");
			filenames.push_back("04_uma");
			filenames.push_back("02_fairy");
			monAI[3] = 5;
			monId[3] = enArmor;
			monAI[4] = 4;
			monId[4] = enUmataur;
			monAI[5] = 2;
			monId[5] = enFairy;
		}
		if (round == 1) {
			filenames.push_back("02_fairy");
			filenames.push_back("06_kikyo");
			filenames.push_back("04_uma");
			monAI[3] = 2;
			monId[3] = enFairy;
			monAI[4] = 6;
			monId[4] = enKikyo;
			monAI[5] = 4;
			monId[5] = enUmataur;
		}
		if (round == 2) {
			filenames.push_back("04_uma");
			filenames.push_back("07_book");
			filenames.push_back("04_uma");
			monAI[3] = 4;
			monId[3] = enUmataur;
			monAI[4] = 7;
			monId[4] = enBook;
			monAI[5] = 4;
			monId[5] = enUmataur;
		}
		break;
	case 6: //3
		if (round == 0) {
			filenames.push_back("07_book");
			filenames.push_back("06_kikyo");
			filenames.push_back("07_book");
			monAI[3] = 7;
			monId[3] = enBook;
			monAI[4] = 6;
			monId[4] = enKikyo;
			monAI[5] = 7;
			monId[5] = enBook;
		}
		if (round == 1) {
			filenames.push_back("zlarmor");
			filenames.push_back("zluma");
			filenames.push_back("zlgob");
			monAI[3] = 5;
			monId[3] = enArmor;
			monAI[4] = 4;
			monId[4] = enUmataur;
			monAI[5] = 1;
			monId[5] = enGoblin;
		}
		if (round == 2) {
			filenames.push_back("01_gob");
			filenames.push_back("01_gob");
			filenames.push_back("01_gob");
			monAI[3] = 1;
			monId[3] = enShikoChu;
			monAI[4] = 1;
			monId[4] = enShikoChu;
			monAI[5] = 1;
			monId[5] = enShikoChu;
		}
		break;
	case 7:	//3
		if (round == 0) {
			filenames.push_back("03_uma");
			filenames.push_back("06_kikyo");
			filenames.push_back("05_armor");
			monAI[3] = 3;
			monId[3] = enUmataur;
			monAI[4] = 6;
			monId[4] = enKikyo;
			monAI[5] = 5;
			monId[5] = enArmor;
		}
		if (round == 1) {
			filenames.push_back("01_gob");
			filenames.push_back("09_redHead");
			filenames.push_back("08_si_bug");
			monAI[3] = 1;
			monId[3] = enGoblin;
			monAI[4] = 9;
			monId[4] = enRedHead;
			monAI[5] = 8;
			monId[5] = enShikoChu;
		}
		if (round == 2) {
			filenames.push_back("07_book");
			filenames.push_back("10_chris");
			filenames.push_back("02_fairy");
			monAI[3] = 7;
			monId[3] = enBook;
			monAI[4] = 10;
			monId[4] = enChris;
			monAI[5] = 2;
			monId[5] = enFairy;
		}
		break;
	}
	return filenames;
}

void StageSetup::OshiFes()
{

	int team = 0;
	int num = 0;
	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180);

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		std::string* path = nullptr;
		if (i == 3)
		{
			mon = GameData::LoadMonster(enFairy);

			path = new std::string("PythonAIs.1Q");
			//path = new std::string("1Q");
		}
		else if (i == 4 || i == 5)
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.1Q");
			//path = new std::string("1Q");
		}
		else
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.1A");
			//path = new std::string("1A");
		}
		if (i < 3)
			mon->SetRotation(rot);

		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);

		
		mon->SetpyFile(path);
		g_mons[i] = mon;

	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

void StageSetup::OshiFes2()
{
	int team = 0;
	int num = 0;
	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180);

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		std::string* path;
		if (i == 3)
		{
			mon = GameData::LoadMonster(enFairy);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2Q";
		}
		else if (i == 4 || i == 5)
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2Q";
		}
		else if(i == 2)
		{
			mon = GameData::LoadMonster(enFairy);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2A-fairy";
			//*path += files[monsterAI[i]];
		}
		else
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2A-uma";
			//*path += files[monsterAI[i]];
		}
		if (i < 3)
			mon->SetRotation(rot);

		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);

		mon->SetpyFile(path);
		g_mons[i] = mon;

	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

void StageSetup::StageSet(int stage) {
	switch (stage) {
	case 0:
	{
		/*SkinModelRender* stageModel = NewGO<SkinModelRender>(0, "stageModel");
		stageModel->Init(L"Assets/modelData/Test.cmo");
		stageModel->SetPosition(CVector3::Zero());*/
	}
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void StageSetup::NetworkPvPSetup(std::vector<std::string> files,
	std::vector<std::string> enemyFiles,
	int monsterAI[6],
	int monids[6],
	int aimode[6]
	) {
	int team = 0;
	int num = 0;
	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		std::string* path;
		auto vaFiles = VisualAiFileLoad::FilesLoad();
		mon = GameData::LoadMonster(monids[i]);
		if (team == 0) {
			//My team data
			if (aimode[i] == 0) {
				path = new std::string("PythonAIs.");
				*path += files[i];
			}
			else {
				path = new std::string("Assets/VisualAI/");
				*path += vaFiles[monsterAI[i]];
				*path += ".va";
				//sprintf_s(wc, "%03d.va", monsterAI[i]);
				mon->SetVisualScriptAI(path);
				//*path += files[monsterAI[i]];
				//mon->SetVisualScriptAI(path);
			}
		}
		else {
			//Enemy team data
			if (aimode[i] == 0) {
				path = new std::string("NetworkEnemyAIs.");
				*path += enemyFiles[i - 3];
			}
			else {
				path = new std::string("NetworkEnemyAIs/");
				//*path += files[monsterAI[i]];
				auto n = std::to_string(i - 2);
				*path += n;
				*path += "enemy.va";
				mon->SetVisualScriptAI(path);
			}
		}
		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);

		mon->SetpyFile(path);
		g_mons[i] = mon;
		//delete path;
	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
	//int team = 0;
	//int num = 0;
	//CVector3 poss[6];
	//poss[0] = { 250,0,500 };
	//poss[1] = { 0,0,500 };
	//poss[2] = { -250,0,500 };
	//poss[3] = { 250,0,-500 };
	//poss[4] = { 0,0,-500 };
	//poss[5] = { -250,0,-500 };
	////load my team
	//for (int i = 0; i < 3; i++) {
	//	Monster* mon = nullptr;
	//	std::string* path;

	//	mon = GameData::LoadMonster(myMonsterId[i]);
	//	path = new std::string("PythonAIs.");
	//	//*path += files[monsterAI[i]];
	//	*path += files[myMonAI[i]];

	//	mon->Setpos(poss[i]);
	//	mon->Setnum(i);
	//	mon->Setteam(team);

	//	mon->SetpyFile(path);
	//	g_mons[i] = mon;
	//	delete path;
	//}
	////load enemy team
	//team++;
	//for (int i = 3; i < 6; i++) {
	//	Monster* mon = nullptr;
	//	std::string* path;

	//	mon = GameData::LoadMonster(enemyMonsterId[i - 3]);
	//	path = new std::string("PythonAIs.");
	//	//*path += files[];
	//	*path += files[myMonAI[i - 3]];

	//	mon->Setpos(poss[i]);
	//	mon->Setnum(i);
	//	mon->Setteam(team);

	//	mon->SetpyFile(path);
	//	g_mons[i] = mon;
	//	delete path;
	//}
	//g_buddyCount = 3;
	//g_enemyCount = 3;
	//g_monsCount = 6;
}
