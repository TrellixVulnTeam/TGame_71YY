#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"

#include "AIEditNodeTarget.h"
#include"AIEditNodeButton.h"
AIEditNodeTarget::~AIEditNodeTarget()
{
	DeleteGO(m_spriteRender);

	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}



bool AIEditNodeTarget::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	m_spriteRender = NewGO<SpriteRender>(0, "target");
	m_spriteRender->Init(L"Assets/sprite/sieat.dds", 150, 190);
	m_spriteRender->SetPivot({ 0.5f, 0.35f });
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNode�̃{�^���̍��W���W

	//�ڂ���
	for (int i = 0; i < button; i++) {               //�{�^���̐������[�v����B
		m_aieditnodebutton = NewGO<AIEditNodeButton>(1, "button");
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
	m_fontpos.x = bacon.x - 50.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L"����", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[1]->Init(L"����", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[2]->Init(L" �G", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });



	return true;
}

void AIEditNodeTarget::Num() 
{

	if (Mouse::isTrigger(enLeftClick))	//���N���b�N
	{
		NewGO<AIEditNode>(0, "firstwin");

		Choice0 = true;
	}


}

void AIEditNodeTarget::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}

	if (Choice0 == false) { //�����I�����Ă��Ȃ��Ƃ�

		for (int i = 0; i < button; i++) {
			if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())	//�I�����Ă��邩	
			{
				Num();

			}

		}

	}
}