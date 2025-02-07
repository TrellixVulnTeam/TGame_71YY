#include "stdafx.h"
#include "AIEditNodeInequ.h"

#include "../GameCursor.h"

#include "../../GameCamera.h"

#include "AIEditNode.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeSelectFonts.h"

AIEditNodeInequ::~AIEditNodeInequ()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	for (auto fonts : m_font)
		DeleteGO(fonts);
}

bool AIEditNodeInequ::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnode = FindGO<AIEditNode>("firstwin");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(9, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/menu2.dds", 175, 140);
	m_spriteRender->SetPivot({ 0.5f, 0.1f });
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 87.5f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標
	
	//ボタンの設定。
	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(10, "button ");
		m_aieditnodebutton->SetPri(10);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}

	//フォント
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(11));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}
	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();  //fontの座標。
	m_fontpos.x = bacon.x - 60.0;
	m_fontpos.y = bacon.y + 105.0;
	m_fonts[0]->Init(L"より大", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	m_fonts[0]->DrawShadow({ SetShadowPos });
	m_fontpos.y -= 54.f;
	m_fonts[1]->Init(L"より小", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	m_fonts[1]->DrawShadow({ SetShadowPos });

	m_font.push_back(NewGO<FontRender>(3));
	m_font[0]->SetTextType(CFont::en_Japanese);
	
	return true;

}


void AIEditNodeInequ::Num()
{
	if (Choice2 == false) { //何も選択していないとき
		m_aieditnodenum = NewGO<AIEditNodeNum>(0, "Num");

		Choice2 = true;
		Inequfont = true;
	}
	
}

void AIEditNodeInequ::FontsConfirmation()
{
	CVector2 m_fontpos1 = CVector2::Zero();
	m_fontpos1.x += 181;
	m_fontpos1.y += 360;
	bool cont = true;

	if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"以上", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ SetShadowPos });

		contact1 = true;
	}

	else if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"以下", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ SetShadowPos });

		contact1 = true;
	}

	else {
		cont = false;
	}

	if (contact1 == true) {
		if (cont == false) {
			m_font[0]->Init(L"", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
			contact1 = false;
		}
	}
}


void AIEditNodeInequ::Update()
{
	
	cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);
	}

	if (contact2 == false) {
		FontsConfirmation();
	}

	if (Mouse::isTrigger(enLeftClick)) {	//左クリック
		if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
			m_inequ = enDainari;
			m_aieditnodeprocess->Setkeepinequ(enDainari);
			Num();
			contact2 = true;
			PlayButtonSE();
		}

		if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
			m_inequ = enShowers;
			m_aieditnodeprocess->Setkeepinequ(enShowers);
			Num();
			contact2 = true;
			PlayButtonSE();
		}
	}
}
