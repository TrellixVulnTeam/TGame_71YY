#include "stdafx.h"
#include "IconAI.h"
#include "../GameCursor.h"
#include "../AIEdit/VisualAIOpen.h"

#include <string>

IconAI::~IconAI()
{
	DeleteGO(m_frame);
	DeleteGO(m_dummy);
	DeleteGO(m_fr);
	DeleteGO(m_frShadow);

	DeleteGO(m_mark);
}

bool IconAI::Start()
{
	
	return true;
}

void IconAI::init(std::string py,int num,GameCursor* cursor, bool isVisualAI, int mark)
{
	m_cursor = cursor;
	std::wstring ws = std::wstring(py.begin(), py.end());
	m_py = ws;
	m_num = num;
	m_frame = NewGO<SpriteRender>(6, "sp");

	m_isVisualAI = isVisualAI;
	if (!m_isVisualAI)
		m_frame->Init(L"Assets/sprite/ai_even.dds", 360, 77);
	else
	{
		m_frame->Init(L"Assets/sprite/ai_evenV.dds", 360, 77);

		m_mark = NewGO<SpriteRender>(6, "sp");
		m_mark->Init(VisualAIOpen::getMark(mark),60,60);
	}

	//��������
	if (m_py.length() > 10)
	{
		m_py[9] = '\0';
	}

	m_dummy = NewGO<SpriteRender>(0, "sp");
	m_dummy->Init(nullptr, 372, 77, true);

	m_frShadow = NewGO<FontRender>(25, "font");
	m_fr = NewGO<FontRender>(25, "font");
	//m_fr->Init(m_py, { pos.x - 150 ,pos.y + 20 }, 0, CVector4::White, 1, { 0.5f,0.5f });
}

void IconAI::Update()
{
	m_isClick = false;
	m_dummy->SetCollisionTarget(m_cursor->GetCursor());
	if (m_dummy->isCollidingTarget())
	{
		if (!m_issel)
		{
			m_frame->Init(L"Assets/sprite/ai_sel.dds", 372, 77);
			m_issel = true;
		}
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;
		}
	}
	else
	{
		if (m_issel)
		{
			if(!m_isVisualAI)
				m_frame->Init(L"Assets/sprite/ai_even.dds", 360, 77);
			else
				m_frame->Init(L"Assets/sprite/ai_evenV.dds", 360, 77);
			m_issel = false;
		}
	}
}

void IconAI::PostRender()
{
	//CVector3 pos = m_frame->GetPosition();
	//m_fr->Init(m_py, {pos.x-150 ,pos.y+20 }, 0, CVector4::White, 1, { 0.5f,0.5f });
}

void IconAI::Setpos(CVector3 pos)
{
	m_frame->SetPosition(pos);
	m_dummy->SetPosition(pos);
	CVector2 fontpo = pos.ToTwo();
	fontpo.x -= 150;
	fontpo.y += 40;
	m_fr->Init(m_py.c_str(), fontpo, 0, CVector4::White, 1, { 0.5f,0.5f });
	m_frShadow->Init(m_py.c_str(), { fontpo.x + 5 ,fontpo.y - 5 }, 0, { 0,0,0,1 }, 1, { 0.5f,0.5f });

	if (m_isVisualAI)
	{
		pos.x += 130;
		m_mark->SetPosition(pos);
	}
}

CVector3 IconAI::Getpos()
{
	return m_frame->GetPosition();
}
