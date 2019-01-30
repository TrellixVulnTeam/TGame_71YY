//2
#include "stdafx.h"
#include "AIEditNodeInequ.h"

#include "../GameCursor.h"

#include "../../GameCamera.h"

#include "AIEditNode.h"
#include "AIEditNodeNum.h"

AIEditNodeInequ::~AIEditNodeInequ()
{
	DeleteGO(m_spriteRender);
	for (SpriteRender* sp : m_spriteRenders)
	{
		DeleteGO(sp);
	}
}

bool AIEditNodeInequ::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	//m_aieditnode = FindGO<AIEditNode>("firstwin");

	//UI�̊��
	m_spriteRender = NewGO<SpriteRender>(3, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/winkari.dds", 150, 250);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNode�̃{�^���̍��W���W


	int x = 35;			//�{�^����X���W
	int y = 120;		//�{�^����Y���W

						//�{�^����p
	for (int i = 0; i < 5; i++)		//i�͐����񂷂����̃n�����Y  i<x x�̂Ƃ��낪�{�^���̐�
	{
		x *= -1;

		if (i % 2 == 0)
		{
			y -= 50;

		}

		SetPointPos(x, y);
		sr = NewGO<SpriteRender>(4, "miniwin");
		sr->Init(L"Assets/sprite/karipoint.dds", 70, 50, true);
		sr->SetPosition(m_pointposition);
		m_spriteRenders.push_back(sr);

	}
	return true;

}


//�I���{�^���̎�ł��⏕
void AIEditNodeInequ::SetPointPos(int numx, int numy)
{
	//���̒l
	float x = 0;
	float y = 0;
	x = m_position.x;
	y = m_position.y;
	m_pointposition.x = x + numx;
	m_pointposition.y = y + numy;

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

		m_spriteRenders[i]->SetCollisionTarget(cursorpos);

	}

	if (Choice2 == false) { //�����I�����Ă��Ȃ��Ƃ�

		for (int i = 0; i < button; i++) {
			if (m_spriteRenders[i]->isCollidingTarget())	//�I�����Ă��邩	
			{
				Num();

			}

		}
	}
}