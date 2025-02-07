#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeMenuSave.h"
#include "AIEditNodeMenu.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeSelectButtons.h"

#include "VisualAIOpen.h"

AIEditNodeMenuSave::~AIEditNodeMenuSave()
{

}

void AIEditNodeMenuSave::OnDestroy()
{
	if (m_spriteRender != nullptr) {
		DeleteGO(m_spriteRender);
	}
	DeleteGO(m_spriteRender2);
	DeleteGO(m_spriteRender3);
	for (auto button : sp)
		DeleteGO(button);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	DeleteGO(m_fonts2);
	DeleteGO(m_fonts3);
	DeleteGO(m_fonts4);

	for (auto sp : m_buttonsF)
		DeleteGO(sp);
	for (auto fr : m_fontsF)
		DeleteGO(fr);
	DeleteGO(m_close);
	DeleteGO(m_cfont);
	DeleteGO(m_head);
	DeleteGO(m_back);

	for (auto sp : m_palette)
		DeleteGO(sp);
	DeleteGO(m_backC);
	DeleteGO(m_headC);

	for (auto sp : m_marks)
		DeleteGO(sp);
	for (auto sp : m_palmarks)
		DeleteGO(sp);
}


void AIEditNodeMenuSave::Awake()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodemenu = FindGO<AIEditNodeMenu>("menu");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_aieditselectbuttons = FindGO<AIEditNodeSelectButtons>("selectbuttons");

	/*m_spriteRender = NewGO<SpriteRender>(17, "menuconf");
	m_spriteRender->Init(L"Assets/sprite/menu.dds", 520, 200, true);
	m_spriteRender->SetPosition(confpos);
	m_positionselect = confpos; 
	m_positionselect.x -= 375;
	m_positionselect.y -= 35;

	for (int i = 0; i < button; i++) {

		sp.push_back(NewGO<SpriteRender>(18, "menuselectsieat"));
		sp[i]->Init(L"Assets/sprite/menuselectsieat.dds", 240, 120, true);
		m_positionselect.x += 250.f;
		sp[i]->SetPosition(m_positionselect);
		m_buttons.push_back(sp[i]);

		m_fonts.push_back(NewGO<FontRender>(19));
		m_fonts[i]->SetTextType(CFont::en_Japanese);

	}

	m_fonts2 = NewGO<FontRender>(19);
	m_fonts2->SetTextType(CFont::en_Japanese);

	m_fontpos.x += m_positionselect.x;
	m_fontpos.y += m_positionselect.y;
	m_fontpos2.x += m_positionselect.x;
	m_fontpos2.y += m_positionselect.y;

	m_fontpos2.x -= 370;
	m_fontpos2.y += 120;
	m_fonts2->Init(L"保存しますか", { m_fontpos2 }, 0.0, CVector4::Red, 0.8, { 0.0,0.0 });

	m_fontpos.x -= 300.f;
	m_fonts[0]->Init(L"はい", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x += 225;
	m_fonts[1]->Init(L"いいえ", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });*/

	std::vector<VisualAIState> vass = VisualAIOpen::openVAs();
	

	//ファイルの選択GUI
	m_back = NewGO<SpriteRender>(10, "sp");
	m_back->Init(L"Assets/sprite/AIbrawser.dds", 740, 700);

	CVector3 pos = { -357.5f,175.f,0 };
	int len = vass.size();
	int vasc = 999;
	if(vass.size()!=0)
		vasc = vass[0].num;
	for (int i = 0; i < 12; i++)
	{
		if (i == 4)
			pos = { -357.5f,-5.f,0 };
		else if (i == 8)
			pos = { -357.5f,-185.f,0 };

		SpriteRender* sp = NewGO<SpriteRender>(11, "sp");
		FontRender* fr = NewGO<FontRender>(11, "fr");

		if (vasc != 999 and i == vass[vasc].num)
		{
			SpriteRender* mark = NewGO<SpriteRender>(11, "sp");
			mark->Init(VisualAIOpen::getMark(vass[vasc].mark), 90, 90);
			CVector3 mpos = pos;
			mpos.x += 130;
			mpos.y -= 30;
			mark->SetPosition(mpos);
			m_marks.push_back(mark);

			sp->Init(L"Assets/sprite/AIEIcon.dds", 175, 175, true);
			//sp->SetMulCol(vass[vasc].col);
			//sp->SetMulCol({0.7f,0.7f ,0.7f,1 });
			sp->SetPivot({ 0.f,0.5f });
			sp->SetPosition(pos);

			wchar_t tx[3] = {'\0'};
			swprintf_s(tx, L"%d", vass[vasc].num);
			if (vass[vasc].num < 10)
				fr->Init(tx, (pos + CVector3(-20, 85.0f, 0)).ToTwo(), 0, { 1,1,1,1 }, 0.8f);
			else
				fr->Init(tx, (pos + CVector3(-20, 85.0f, 0)).ToTwo(), 0, { 1,1,1,1 }, 0.7f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fontsF.push_back(fr);
			if(vasc+1 < len)
				vasc++;
		}
		else
		{
			sp->Init(L"Assets/sprite/AIEIcon.dds", 175, 175, true);
			sp->SetMulCol({ 0.6f,0.6f ,0.6f ,1 });
			sp->SetPivot({ 0.f,0.5f });
			sp->SetPosition(pos);

			fr->Init(L"なし", (pos + CVector3(0, 43.75f, 0)).ToTwo(), 0, { 0.8f,0.8f,0.8f,1 },0.4f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fontsF.push_back(fr);
		}
		pos.x += 180;

		m_buttonsF.push_back(sp);
	}

	m_head = NewGO<FontRender>(11, "fr");
	m_head->SetTextType(CFont::en_JapaneseBIG);
	m_head->Init(L"保存する場所を選択してください", { -340,330.5f }, 0, { 1,1,1,1 }, 0.27f, { 0.5f,1.f });
	m_head->DrawShadow();

	CVector3 cpos = { 357.5f ,-340,0 };
	m_close = NewGO<SpriteRender>(11, "sr");
	m_close->Init(L"Assets/sprite/HOM.dds", 160, 64, true);
	m_close->SetPosition(cpos);
	m_close->SetPivot({ 1,0 });
	//m_close->SetMulCol({ 0.5,0.5,0.5,1 });

	cpos.x -= 147.5f;
	cpos.y += 55;

	m_cfont = NewGO<FontRender>(12, "fr");
	m_cfont->Init(L"とじる", cpos.ToTwo(), 0, { 1,1,1,1 }, 1);
	m_cfont->SetTextType(CFont::en_Japanese);
	m_cfont->DrawShadow();
}

bool AIEditNodeMenuSave::Start()
{
	
	return true;
}

void AIEditNodeMenuSave::Confirmation()
{
	m_spriteRender2 = NewGO<SpriteRender>(22, "sp");
	m_spriteRender2->Init(L"Assets/sprite/menu.dds", 260, 160, true);
	m_spriteRender2->SetPosition(m_Confirmationposition);

	m_spriteRender3 = NewGO<SpriteRender>(22, "sp");
	m_spriteRender3->Init(L"Assets/sprite/menuselectsieat.dds", 160, 80, true);
	m_Confirmationposition.y -= 25.f;
	m_spriteRender3->SetPosition(m_Confirmationposition);

	m_fonts4 = NewGO<FontRender>(23);
	m_fonts4->SetTextType(CFont::en_Japanese);
	m_fonts3 = NewGO<FontRender>(23);
	m_fonts3->SetTextType(CFont::en_Japanese);

	m_fontpos2.x += m_positionselect2.x += 140.f;
	m_fontpos2.y += m_positionselect2.y -= 20.f;
	m_fontpos3.x += m_Confirmationposition.x -= 55.f;
	m_fontpos3.y += m_Confirmationposition.y += 10.f;

	m_fonts4->Init(L"保存しました", { m_fontpos2 }, 0.0, CVector4::Red, 0.8, { 0.0,0.0 });
	m_fonts3->Init(L"とじる", { m_fontpos3 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });

}

void AIEditNodeMenuSave::AISelected()
{
	m_spriteRender = NewGO<SpriteRender>(17, "menuconf");
	m_spriteRender->Init(L"Assets/sprite/menu.dds", 520, 200, true);
	m_spriteRender->SetPosition(confpos);
	m_positionselect = confpos;
	m_positionselect.x -= 375;
	m_positionselect.y -= 35;

	for (int i = 0; i < button; i++) {

		sp.push_back(NewGO<SpriteRender>(18, "menuselectsieat"));
		sp[i]->Init(L"Assets/sprite/menuselectsieat.dds", 240, 120, true);
		m_positionselect.x += 250.f;
		sp[i]->SetPosition(m_positionselect);
		m_buttons.push_back(sp[i]);

		m_fonts.push_back(NewGO<FontRender>(19));
		m_fonts[i]->SetTextType(CFont::en_Japanese);

	}

	m_fonts2 = NewGO<FontRender>(19);
	m_fonts2->SetTextType(CFont::en_Japanese);

	m_fontpos.x += m_positionselect.x;
	m_fontpos.y += m_positionselect.y;
	m_fontpos2.x += m_positionselect.x;
	m_fontpos2.y += m_positionselect.y;

	m_fontpos2.x -= 370;
	m_fontpos2.y += 120;
	m_fonts2->Init(L"保存しますか", { m_fontpos2 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	//m_fonts[0]->DrawShadow();

	m_fontpos.y += 20;
	m_fontpos.x -= 300.f;
	m_fonts[0]->Init(L"はい", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	//m_fonts[0]->DrawShadow();

	m_fontpos.x += 225;
	m_fonts[1]->Init(L"いいえ", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	//m_fonts[0]->DrawShadow();
}

void AIEditNodeMenuSave::confProc()
{
	bool isLeftClick = Mouse::isTrigger(enLeftClick);
	if (!clickyes)
	{
		for (int i = 0; i < button; i++) {

			sp[i]->SetCollisionTarget(cursorpos);
		}

		if (click == false) {
			if (sp[button - 2]->isCollidingTarget()) //　はい　を選択した場合。
			{		
				sp[button - 2]->SetMulCol({1.3f,1.3f, 1.3f, 1});
				if (isLeftClick) 
				{
					PlayButtonSE();
					//m_aieditnodeprocess->AISave();

					PaletteInit();


					DeleteGO(m_spriteRender);
					m_spriteRender = nullptr;
					DeleteGO(m_fonts2);
					m_fonts2 = nullptr;
					for (int i = 0; i < 2; i++) {
						DeleteGO(sp[i]);
						sp[i] = nullptr;
						DeleteGO(m_fonts[i]);
						m_fonts[i] = nullptr;
					}

					clickyes = true;

					//Confirmation();

					click = true;

					return;
				}
			}
			else
			{
				sp[button - 2]->SetMulCol(CVector4::White);
			}
			if (sp[button - 1]->isCollidingTarget()) //　いいえ　を選択した場合。
			{		
				sp[button - 1]->SetMulCol({ 1.3f,1.3f, 1.3f, 1 });
				if (isLeftClick)
				{
					PlayButtonSE();
					m_aieditselectbuttons->Setmenuselect(false);
					DeleteGO(this);

					click = true;
				}
			}
			else
			{
				sp[button - 1]->SetMulCol(CVector4::White);
			}
		}
	}
	else
	{
		PaletteProc();
		/*if (stop == false) {
			Confirmation();
			stop = true;
		}
		m_spriteRender3->SetCollisionTarget(cursorpos);

		if (m_spriteRender3->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				m_aieditselectbuttons->Setmenuselect(false);
				DeleteGO(this);
			}
		}*/
	}
}

void AIEditNodeMenuSave::PaletteInit()
{
	CVector3 posp = { 160,-30,0 };
	m_backC = NewGO<SpriteRender>(20, "sp");
	m_backC->Init(L"Assets/sprite/AIbrawser.dds", 740, 250);
	m_backC->SetPosition(posp);

	CVector3 pos = { -357.5f,-30.f,0 };
	pos += posp;
	for (int i = 0; i < 4; i++)
	{
		SpriteRender* sp = NewGO<SpriteRender>(21, "sp");
		
		CVector4 col = CVector4::Black;
		sp->Init(L"Assets/sprite/AIEIcon.dds", 175, 175, true);
		sp->SetPivot({ 0,0.5f });
		sp->SetPosition(pos);
		//sp->SetMulCol({0.7f,0.7f,0.7f,1});

		SpriteRender* mk = NewGO<SpriteRender>(21, "sp");
		mk->Init(VisualAIOpen::getMark(i), 170, 170);
		mk->SetPivot({ 0,0.5f });
		mk->SetPosition(pos);

		pos.x += 180;

		m_palette.push_back(sp);
		m_palmarks.push_back(mk);
	}

	m_headC = NewGO<FontRender>(21, "fr");
	m_headC->SetTextType(CFont::en_Japanese);
	pos = { -280,120,0 };
	pos += posp;
	m_headC->Init(L"カテゴリを選択してください", { pos.x,pos.y }, 0, CVector4::White, 1);
	m_headC->DrawShadow();

}

void AIEditNodeMenuSave::PaletteProc()
{
	if (!m_isColSel)
	{
		for (auto sp : m_palette)
		{
			sp->SetCollisionTarget(cursorpos);
		}
		for (int i = 0; i < 4; i++)
		{
			if (m_palette[i]->isCollidingTarget())
			{
				m_palette[i]->SetMulCol({ 1.3f,1.3f, 1.3f, 1 });
				if (Mouse::isTrigger(enLeftClick))
				{
					PlayButtonSE();

					m_selCol = i;
					Confirmation();
					m_isColSel = true;
					m_aieditnodeprocess->AISave(m_SelectBlock, m_selCol);
				}
			}
			else
			{
				m_palette[i]->SetMulCol(CVector4::White);
			}
		}
	}
	else
	{
		m_spriteRender3->SetCollisionTarget(cursorpos);

		if (m_spriteRender3->isCollidingTarget()) {
			m_spriteRender3->SetMulCol({ 1.3f,1.3f, 1.3f, 1 });
			if (Mouse::isTrigger(enLeftClick)) {
				PlayButtonSE();
				m_aieditselectbuttons->Setmenuselect(false);
				DeleteGO(this);
			}
		}
		else
		{
			m_spriteRender3->SetMulCol(CVector4::White);
		}
	}
}

void AIEditNodeMenuSave::Update()
{
	bool isLeftClick = Mouse::isTrigger(enLeftClick);
	cursorpos = m_gamecursor->GetCursor();
	if (!m_isSelected)
	{
		for (auto sp : m_buttonsF)
		{
			sp->SetCollisionTarget(cursorpos);
		}
		m_close->SetCollisionTarget(cursorpos);

		for (int i = 0; i < 12; i++)
		{
			if (m_buttonsF[i]->isCollidingTarget())
			{
				m_buttonsF[i]->SetMulCol({ 1.3f,1.3f,1.3f,1 });
				if (isLeftClick)
				{
					m_SelectBlock = i;
					AISelected();
					m_isSelected = true;
					PlayButtonSE();
				}
			}
			else
			{
				m_buttonsF[i]->SetMulCol(CVector4::White);
			}
		}
		if (m_close->isCollidingTarget())
		{
			m_close->SetMulCol({ 1.3f,1.3f,1.3f,1 });
			if (isLeftClick)
			{
				m_aieditselectbuttons->Setmenuselect(false);
				PlayButtonSE();

				DeleteGO(this);
			}
		}
		else
		{
			m_close->SetMulCol(CVector4::White);
		}
	}
	else
		confProc();
}