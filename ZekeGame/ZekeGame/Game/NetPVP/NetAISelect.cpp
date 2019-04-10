#include "stdafx.h"
#include "NetAISelect.h"

#include "NetPVPMode.h"

#include "../GameCursor.h"
#include "../Title/MonAIPreset/MonAIPresetOpenSuper.h";
#include "../Fade/Fade.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "../Title/PMMonster.h"
#include "../Title/MonAIPreset/MonAIPresetSaveOpen.h"
#include "../Title/MonAIPreset/MonAIPresetLoadOpen.h"

void NetAISelect::OnDestroy()
{
}

bool NetAISelect::Start()
{
	m_back = NewGO<SpriteRender>(0, "sp");
	m_back->Init(L"Assets/sprite/monsel_back.dds", 1280, 720);

	m_files = PythonFileLoad::FilesLoad();
	m_cursor = NewGO<GameCursor>(0, "cursor");

	//�@�g�g�p�̃`�[����ۑ�������
	m_msRed = NewGO<MonAIPresetSaveOpen>(0, "mapso");
	m_msRed->init(this, m_cursor, L"�`�[����ۑ�", { 410,130,0 }, 0);
	//�@�g�g�p�̃`�[�����J�����
	m_mlRed = NewGO<MonAIPresetLoadOpen>(0, "maplo");
	m_mlRed->init(this, m_cursor, L"�`�[�����J��", { 410,60,0 }, 0);

	CVector3 pos = { -290,0,0 };
	for (int i = 0; i < 3; i++)
	{
		if (i == 3)
		{
			pos = { -290,-180,0 };
		}
		PMMonster* pmm = NewGO<PMMonster>(0, "pmm");
		pmm->init(i, pos);
		pmm->Setteam(i >= 3);
		pos += {260, 0, 0};
		std::wstring ws = std::wstring(m_files[g_AIset[i]].begin(), m_files[g_AIset[i]].end());
		pmm->SetPython(ws.c_str(), g_AIset[i]);
		m_pmms.push_back(pmm);
	}

	m_GO = NewGO<SpriteRender>(0, "sp");
	m_GO->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_GO->SetPosition({ 520,240,0 });

	CVector3 repo = { -520,-260,0 };
	m_returnS.x /= 3;
	m_returnS.y /= 3;
	m_return = NewGO<SpriteRender>(0, "sp");
	m_return->Init(L"Assets/sprite/simple_button.dds", m_returnS.x, m_returnS.y);
	m_returnMoji = NewGO<SpriteRender>(0, "sp");
	m_returnMoji->Init(L"Assets/sprite/moji_return.dds", m_returnS.x, m_returnS.y, true);
	m_return->SetPosition(repo);
	m_returnMoji->SetPosition(repo);
	return true;
}

void NetAISelect::Update()
{
	bool ispmm = false;
	for (auto pmm : m_pmms)
	{
		ispmm = pmm->isOpen();
		if (ispmm)
			break;
	}

	static bool isopen = false;

	//�����J���Ă����ꍇ�͑��̂��̂̓N���b�N���Ă��������Ȃ��B
	if (!(m_msRed->IsOpen() || m_mlRed->IsOpen() || ispmm || isopen))
	{
		m_msRed->UpdateEx();
		m_mlRed->UpdateEx();
		//�v���Z�b�g�̃Z�[�u
		if (m_msRed->IsClick())
		{
			m_msRed->Open();
		}
		if (m_mlRed->IsClick())
		{
			m_mlRed->Open();
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

		m_returnMoji->SetCollisionTarget(curs);
		if (m_returnMoji->isCollidingTarget())
		{
			if (!isReturnOver)
			{
				m_return->Init(L"Assets/sprite/simple_button_blue.dds", m_returnS.x, m_returnS.y);
				isReturnOver = true;
			}
			if (Mouse::isTrigger(enLeftClick))
			{
				//NewGO<ModeSelect>(0, "modesel");
				//DeleteGO(this);
			}
		}
		else if (isReturnOver)
		{
			m_return->Init(L"Assets/sprite/simple_button.dds", m_returnS.x, m_returnS.y);
			isReturnOver = false;
		}
	}
	isopen = ispmm;
}
