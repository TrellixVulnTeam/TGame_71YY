//3
#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeOrder.h"
#include "AIEditLine.h"
#include "AIEditNodeButton.h"

AIEditNodeNum::~AIEditNodeNum()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}


bool AIEditNodeNum::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	//UI�̊��
	m_spriteRender = NewGO<SpriteRender>(5, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/sieat.dds", 150, 400);
	m_spriteRender->SetPivot({ 0.5f, 0.7f });
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNode�̃{�^���̍��W���W

	//�{�^��
	for (int i = 0; i < button; i++) {               //�{�^���̐������[�v����B
		m_aieditnodebutton = NewGO<AIEditNodeButton>(6, "button");
		m_aieditnodebutton->SetPri(6);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}

	//�t�H���g
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(7));
	}

	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 50.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L" 1", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[1]->Init(L" 10", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[2]->Init(L" 30", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[3]->Init(L" 50", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[4]->Init(L" 70", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[5]->Init(L" 90", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x -= 20.f;
	m_fontpos.y -= 55.f;
	m_fonts[6]->Init(L" 100", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });

	return true;
}

void AIEditNodeNum::Order()
{

	if (Mouse::isTrigger(enLeftClick)) {	//���N���b�N
		m_aieditnodeorder = NewGO<AIEditNodeOrder>(0, "Order");
		Choice3 = true;
	}
}

void AIEditNodeNum::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}
	
	for (int i = 0; i < button; i++)
	{
		if (Choice3 == false) {
			if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())
			{
				Order();
			}
		}
	}

}
