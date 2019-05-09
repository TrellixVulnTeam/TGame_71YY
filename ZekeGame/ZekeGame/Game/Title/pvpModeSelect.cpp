// my name is pvp.


#include "stdafx.h"
#include "SuperMonsterSelect.h"
#include "pvpModeSelect.h"


#include <string>
#include "../GameCursor.h"

#include "ModeSelect.h"

#include "../StageSetup/StageSetup.h"
#include "../Game.h"

#include "../SaveLoad/PythonFileLoad.h"

#include "PMMonster.h"

#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"

#include "../ReturnButton/ReturnButton.h"


//#include "MonAIPreset/MonAIPresetSave.h"
//#include "MonAIPreset/MonAIPresetLoad.h"
//#include "MonAIPreset/MonAIPresetOpen.h"

#include "MonAIPreset/MonAIPresetOpenSuper.h"
#include "MonAIPreset/MonAIPresetSaveOpen.h"
#include "MonAIPreset/MonAIPresetLoadOpen.h"

PvPModeSelect::~PvPModeSelect()
{
	DeleteGO(m_cursor);
	for (auto go : m_pmms)
	{
		DeleteGO(go);
	}
	DeleteGO(m_GO);
	DeleteGO(m_back);
	DeleteGO(m_return);
	DeleteGO(m_returnMoji);
	//DeleteGO(m_mapo);

	DeleteGO(m_msRed);
	DeleteGO(m_mlRed);
	DeleteGO(m_msBlue);
	DeleteGO(m_mlBlue);
}

bool PvPModeSelect::Start()
{
	m_BGM = FindGO<Sound>("BGM");
	if (m_BGM == nullptr)
	{
		m_BGM = NewGO<Sound>(0,"BGM");
		m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_Strategy5_loop.wav", true);
		m_BGM->SetVolume(m_vol);
		m_BGM->Play();
	}

	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	m_back = NewGO<SpriteRender>(0, "sp");
	m_back->Init(L"Assets/sprite/monsel_back.dds", 1280, 720);

	m_files = PythonFileLoad::FilesLoad();
	m_cursor = NewGO<GameCursor>(0, "cursor");


	/*MonAIPresetSave* maps = NewGO<MonAIPresetSave>(0, "maps");
	maps->init(this, 0,m_cursor);

	MonAIPresetLoad* mapl = NewGO<MonAIPresetLoad>(0, "mapl");
	mapl->init(this, 0, 0, m_cursor);*/

	//m_mapo = NewGO<MonAIPresetOpen>(0, "mapo");
	//m_mapo->init(this, m_cursor, 0);

	//m_ms = NewGO<MonAIPresetOpenSuper>(0, "mapos");
	//m_ms->init(this, m_cursor, L"h", { 560,100,0 }, 0);

	//�@�g�g�p�̃`�[����ۑ�������
	m_msRed = NewGO<MonAIPresetSaveOpen>(0, "mapso");
	m_msRed->init(this, m_cursor, L"�`�[����ۑ�", { 410,130,0 }, 0);
	//�@�g�g�p�̃`�[�����J�����
	m_mlRed = NewGO<MonAIPresetLoadOpen>(0, "maplo");
	m_mlRed->init(this, m_cursor, L"�`�[�����J��", { 410,60,0 }, 0);

	//�@AO�g�p�̃`�[����ۑ�������
	m_msBlue = NewGO<MonAIPresetSaveOpen>(0, "mapso");
	m_msBlue->init(this, m_cursor, L"�`�[����ۑ�", { 410,-230,0 }, 1);
	//�@AO�g�p�̃`�[�����J�����
	m_mlBlue = NewGO<MonAIPresetLoadOpen>(0, "maplo");
	m_mlBlue->init(this, m_cursor, L"�`�[�����J��", { 410,-300,0 }, 1);
	
	CVector3 pos = { -290,180,0 };
	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
		{
			pos = { -290,-180,0 };
		}
		PMMonster* pmm = NewGO<PMMonster>(0, "pmm");
		pmm->init(i,pos);
		pmm->Setteam(i >= 3);
		pos += {260, 0, 0};
		std::wstring ws = std::wstring(m_files[g_AIset[i].AInum].begin(), m_files[g_AIset[i].AInum].end());
		pmm->SetPython(ws.c_str(), g_AIset[i].AInum, g_AIset[i].AImode);
		m_pmms.push_back(pmm);
	}
	//m_pmm = NewGO<PMMonster>(0, "pmm");
	//m_pmm->init({ -250,-200,0 });
	for (int i = 0; i < 6; i++)
	{
		/*SpriteRender* sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/mon",);*/
	}

	m_GO = NewGO<SpriteRender>(0, "sp");
	m_GO->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_GO->SetPosition({ 520,240,0 });

	CVector3 repo = { -520,-260,0 };
	/*m_returnS.x /= 3;
	m_returnS.y /= 3;
	m_return = NewGO<SpriteRender>(0, "sp");
	m_return->Init(L"Assets/sprite/return.dds", m_returnS.x, m_returnS.y);*/
	//m_returnMoji = NewGO<SpriteRender>(0, "sp");
	//m_returnMoji->Init(L"Assets/sprite/moji_return.dds", m_returnS.x, m_returnS.y,true);
	//m_return->SetPosition(repo);
	//m_returnMoji->SetPosition(repo);

	m_returnButton = NewGO<ReturnButton>(0, "rb");
	m_returnButton->setName("modesel");
	m_returnButton->SetScene(this);
	return true;
}

void PvPModeSelect::Update()
{
	
	if (m_isfade)
	{
		if (m_fade->isFadeStop())
		{
			MonsterID moid[6];
			int AImodes[6];
			for (int i = 0; i < 6; i++)
			{
				moid[i] = (MonsterID)m_pmms[i]->GetMonsterID();
				monai[i] = m_pmms[i]->GetAI();
				AImodes[i] = m_pmms[i]->GetAImode();
			}
			Game* game = NewGO<Game>(0, "Game");
			////game->GamePVPmodeInit(m_files, monai,moid);
			StageSetup::PVPSetup(m_files, monai, moid,AImodes);
			//m_BGM->Stop();
			DeleteGO(this);
		}
	}

	bool ispmm = false;
	for (auto pmm : m_pmms)
	{
		ispmm = pmm->isOpen();
		if (ispmm)
			break;
	}

	static bool isopen = false;

	//�����J���Ă����ꍇ�͑��̂��̂̓N���b�N���Ă��������Ȃ��B
	if (!(m_msRed->IsOpen() || m_mlRed->IsOpen() || m_msBlue->IsOpen() || m_mlBlue->IsOpen() || ispmm || isopen))
	{
		m_returnButton->UpdateEx<ModeSelect>();

		m_msRed->UpdateEx();
		m_mlRed->UpdateEx();
		m_msBlue->UpdateEx();
		m_mlBlue->UpdateEx();
		//�v���Z�b�g�̃Z�[�u
		if (m_msRed->IsClick()) 
		{
			m_msRed->Open();
		}
		if (m_mlRed->IsClick())
		{
			m_mlRed->Open();
		}
		if (m_msBlue->IsClick())
		{
			m_msBlue->Open();
		}
		if (m_mlBlue->IsClick())
		{
			m_mlBlue->Open();
		}
		for (auto pmm : m_pmms)
		{
			pmm->UpdateEX();
		}


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
		CVector3 curs = m_cursor->GetCursor();
		m_GO->SetCollisionTarget(curs);
		if (m_GO->isCollidingTarget())
		{
			if (Mouse::isTrigger(enLeftClick))
			{
				m_fade->FadeOut();
				m_isfade = true;
				MusicFade* mf = NewGO<MusicFade>(0, "mf");
				mf->init(m_BGM, m_vol);
			}
		}

		/*m_returnMoji->SetCollisionTarget(curs);
		if (m_returnMoji->isCollidingTarget())
		{
			if (!isReturnOver)
			{
				m_return->Init(L"Assets/sprite/simple_button_blue.dds", m_returnS.x, m_returnS.y);
				isReturnOver = true;
			}
			if (Mouse::isTrigger(enLeftClick))
			{
				NewGO<ModeSelect>(0, "modesel");
				DeleteGO(this);
			}
		}
		else if (isReturnOver)
		{
			m_return->Init(L"Assets/sprite/simple_button.dds", m_returnS.x, m_returnS.y);
			isReturnOver = false;
		}*/
	}
	isopen = ispmm;

	//isopen = m_mapo->IsOpen();

	//if (count == 6)
	//{
	//	count = 0;
	//}
	//if (!ismonsel)
	//{
	//	if (g_pad[0].IsTrigger(enButtonB))
	//	{
	//	}
	//	else if (g_pad[0].IsTrigger(enButtonDown))
	//	{
	//		if (count < 3)
	//		{
	//			m_pmms[count]->notSelect();
	//			count += 3;
	//			m_pmms[count]->yesSelect();
	//		}
	//	}
	//	else if (g_pad[0].IsTrigger(enButtonUp))
	//	{
	//		if (count > 2)
	//		{
	//			m_pmms[count]->notSelect();
	//			count -= 3;
	//			m_pmms[count]->yesSelect();
	//		}
	//	}
	//	else if (g_pad[0].IsTrigger(enButtonLeft))
	//	{
	//		if (count != 0 && count != 3)
	//		{
	//			m_pmms[count]->notSelect();
	//			count--;
	//			m_pmms[count]->yesSelect();
	//		}
	//	}
	//	else if (g_pad[0].IsTrigger(enButtonRight))
	//	{
	//		if (count != 2 && count != 5)
	//		{
	//			m_pmms[count]->notSelect();
	//			count++;
	//			m_pmms[count]->yesSelect();
	//		}
	//	}
	//}

	//if (g_pad[0].IsTrigger(enButtonA))
	//{
	//	if (curpos == 6)
	//	{
	//		Game* game = NewGO<Game>(0, "Game");
	//		//game->GamePVPmodeInit(m_files, monai);.
	//		
	//		DeleteGO(this);
	//	}
	//	else if (!sel)
	//	{
	//		sel = true;
	//	}
	//	else
	//	{
	//		sel = false;
	//	}
	//}

	//if (!sel)
	//{
	//	if (g_pad[0].IsTrigger(enButtonB))
	//	{
	//		NewGO<ModeSelect>(0, "modesel");
	//		DeleteGO(this);
	//	}
	//	else if (g_pad[0].IsTrigger(enButtonDown))
	//	{
	//		if (curpos < 5+1)
	//		{
	//			curpos++;
	//		}
	//	}
	//	else if (g_pad[0].IsTrigger(enButtonUp))
	//	{
	//		if (curpos > 0)
	//		{
	//			curpos--;
	//		}
	//	}
	//}
	//else
	//{
	//	if (g_pad[0].IsTrigger(enButtonLeft))
	//	{
	//		if (monai[curpos] > 0)
	//		{
	//			monai[curpos]--;
	//		}
	//	}
	//	else if (g_pad[0].IsTrigger(enButtonRight))
	//	{
	//		if (monai[curpos] < m_files.size()-1)
	//		{
	//			monai[curpos]++;
	//		}
	//	}
	//}
}

void PvPModeSelect::LoadFiles()
{
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	std::vector<std::string> filenames;

	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd+"/PythonAIs/*.py";
	hfind = FindFirstFile(key.c_str(), &win32d);
	
	do
	{
		if(win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{ }
		else
		{
			std::string p = win32d.cFileName;
			p.resize(p.length() - 3);
			m_files.push_back(p);
			
		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
}

void PvPModeSelect::PostRender()
{
	/*CVector4 colors[7];
	for (CVector4& col : colors)
	{
		col = CVector4::White;
	}
	if(sel)
		colors[curpos] = CVector4::Yellow;
	else
		colors[curpos] = CVector4::Red;
	CVector2 pos = { -520,10};
	font.Begin();
	for (int i = 0; i < 7; i++)
	{
		if (i == 3)
		{
			pos = { -30,10 };
		}
		else if (i == 6)
		{
			pos = { 320,-210, };
			font.Draw(L"GO!", pos, colors[i],0,2);
			break;
		}
		std::wstring ws = std::wstring(m_files[monai[i]].begin(), m_files[monai[i]].end());
		font.Draw(ws.c_str(), pos, colors[i]);

		pos.y -= 50;
	}
	font.End();*/
}
