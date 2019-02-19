//2
#include "stdafx.h"
#include "AIEditNodeInequ.h"

#include "../GameCursor.h"

#include "../../GameCamera.h"

#include "AIEditNode.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeButton.h"

AIEditNodeInequ::~AIEditNodeInequ()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}

bool AIEditNodeInequ::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnode = FindGO<AIEditNode>("firstwin");

	//UI�̊��
	m_spriteRender = NewGO<SpriteRender>(3, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/sieat.dds", 150, 120);
	m_spriteRender->SetPivot({ 0.5f, 0.0f });
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNode�̃{�^���̍��W���W
	

	for (int i = 0; i < button; i++) {               //�{�^���̐������[�v����B
		m_aieditnodebutton = NewGO<AIEditNodeButton>(4, "button ");
		m_aieditnodebutton->SetPri(4);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}

	//�t�H���g
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(5));
	}
	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 55.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L"����", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[1]->Init(L"��菬", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	return true;

}



void AIEditNodeInequ::Num()
{

	if (Mouse::isTrigger(enLeftClick)) {	//���N���b�N
		m_aieditnodenum = NewGO<AIEditNodeNum>(0, "Num");

		Choice2 = true;
	}
}


void AIEditNodeInequ::Update()
{
	
	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}

	if (Choice2 == false) { //�����I�����Ă��Ȃ��Ƃ�

		for (int i = 0; i < button; i++) {
			if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())	//�I�����Ă��邩	
			{
				Num();

			}

		}
	}
}