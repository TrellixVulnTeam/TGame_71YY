#include "stdafx.h"
#include <string>
#include "../GameCursor.h"
#include "../StageSetup/StageSetup.h"
#include "../Game.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "../Title/ModeSelect.h"
#include "../Title/PMMonster.h"
#include "DungeonAISelect.h"

DungeonAISelect::DungeonAISelect()
{
}


DungeonAISelect::~DungeonAISelect()
{
	DeleteGO(m_cursor);
	for (auto go : m_pmms)
	{
		DeleteGO(go);
	}
	DeleteGO(m_GO);
}

bool DungeonAISelect::Start() {
	m_files = PythonFileLoad::FilesLoad();
	m_cursor = NewGO<GameCursor>(0, "cursor");

	CVector3 pos = { -320,210,0 };
	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
		{
			pos = { -320,-200,0 };
		}
		PMMonster* pmm = NewGO<PMMonster>(0, "pmm");
		pmm->init(i, pos);
		pos += {240, 0, 0};
		std::wstring ws = std::wstring(m_files[g_AIset[i]].begin(), m_files[g_AIset[i]].end());
		pmm->SetPython(ws.c_str(), g_AIset[i]);
		m_pmms.push_back(pmm);
	}
	//m_pmm = NewGO<PMMonster>(0, "pmm");
	//m_pmm->init({ -250,-200,0 });
	for (int i = 0; i < 6; i++)
	{
		/*SpriteRender* sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/mon",);*/
	}

	m_GO = NewGO<SpriteRender>(0
		, "sp");
	m_GO->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_GO->SetPosition({ 400,-160,0 });

	return true;
}

void DungeonAISelect::Update() {
	bool ismonsel = false;
	int count = 0;
	for (auto pmm : m_pmms)
	{
		ismonsel = pmm->isMonSel();
		if (ismonsel || pmm->isSelect())
		{
			break;
		}

		count++;
	}
	if (ismonsel)
		return;
	m_GO->SetCollisionTarget(m_cursor->GetCursor());
	if (m_GO->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			MonsterID moid[6];
			for (int i = 0; i < 6; i++)
			{
				moid[i] = (MonsterID)m_pmms[i]->GetMonsterID();
				monai[i] = m_pmms[i]->GetAI();
			}
			Game* game = NewGO<Game>(0, "Game");
			////game->GamePVPmodeInit(m_files, monai,moid);
			StageSetup::PVPSetup(m_files, monai, moid);
			DeleteGO(this);
		}
	}


	if (count == 6)
	{
		count = 0;
	}
	if (!ismonsel)
	{
		if (g_pad[0].IsTrigger(enButtonB))
		{
		}
		else if (g_pad[0].IsTrigger(enButtonDown))
		{
			if (count < 3)
			{
				m_pmms[count]->notSelect();
				count += 3;
				m_pmms[count]->yesSelect();
			}
		}
		else if (g_pad[0].IsTrigger(enButtonUp))
		{
			if (count > 2)
			{
				m_pmms[count]->notSelect();
				count -= 3;
				m_pmms[count]->yesSelect();
			}
		}
		else if (g_pad[0].IsTrigger(enButtonLeft))
		{
			if (count != 0 && count != 3)
			{
				m_pmms[count]->notSelect();
				count--;
				m_pmms[count]->yesSelect();
			}
		}
		else if (g_pad[0].IsTrigger(enButtonRight))
		{
			if (count != 2 && count != 5)
			{
				m_pmms[count]->notSelect();
				count++;
				m_pmms[count]->yesSelect();
			}
		}
	}

	if (g_pad[0].IsTrigger(enButtonA))
	{
		if (curpos == 6)
		{
			Game* game = NewGO<Game>(0, "Game");
			//game->GamePVPmodeInit(m_files, monai);.

			DeleteGO(this);
		}
		else if (!sel)
		{
			sel = true;
		}
		else
		{
			sel = false;
		}
	}

	if (!sel)
	{
		if (g_pad[0].IsTrigger(enButtonB))
		{
			NewGO<ModeSelect>(0, "modesel");
			DeleteGO(this);
		}
		else if (g_pad[0].IsTrigger(enButtonDown))
		{
			if (curpos < 5 + 1)
			{
				curpos++;
			}
		}
		else if (g_pad[0].IsTrigger(enButtonUp))
		{
			if (curpos > 0)
			{
				curpos--;
			}
		}
	}
	else
	{
		if (g_pad[0].IsTrigger(enButtonLeft))
		{
			if (monai[curpos] > 0)
			{
				monai[curpos]--;
			}
		}
		else if (g_pad[0].IsTrigger(enButtonRight))
		{
			if (monai[curpos] < m_files.size() - 1)
			{
				monai[curpos]++;
			}
		}
	}
}

void DungeonAISelect::LoadFiles() {
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	std::vector<std::string> filenames;

	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd + "/PythonAIs/*.py";
	hfind = FindFirstFile(key.c_str(), &win32d);

	do
	{
		if (win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			std::string p = win32d.cFileName;
			p.resize(p.length() - 3);
			m_files.push_back(p);

		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
}