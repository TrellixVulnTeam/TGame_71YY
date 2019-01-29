//1
#include "stdafx.h"
#include "AIEditNode.h"

#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"

#include "AIEditNodeHp.h"
#include "AIEditNodeInequ.h"

AIEditNode::~AIEditNode()
{
	DeleteGO(m_spriteRender);
	for (SpriteRender* sp : m_spriteRenders)
	{
		DeleteGO(sp);
	}

}



bool AIEditNode::Start()
{

	m_gamecursor = FindGO<GameCursor>("cursor");

	//UI�̊��
	m_spriteRender = NewGO<SpriteRender>(1, "firstwin");
	m_spriteRender->Init(L"Assets/sprite/winkari.dds", 150, 250);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);			//�J�[�\���̍��W

	int x = 35;			//�{�^����X���W
	int y = 120;		//�{�^����Y���W
	
	//�{�^����p
	for (int i = 0; i < button; i++)		//i�͐����񂷂����̃n�����Y  
	{
		x *= -1;					

		if (i % 2 == 0)
		{
			y -= 50;

		}

		SetPointPos(x,y);
		sr = NewGO<SpriteRender>(2, "miniwin");
		sr->Init(L"Assets/sprite/karipoint.dds", 70, 50, true);
		sr->SetPosition(m_pointposition);
		m_spriteRenders.push_back(sr);
		
	}
	return true;

}

//�I���{�^���̎�ł��⏕
void AIEditNode::SetPointPos(int numx, int numy)
{
	//���̒l
	float x = 0;
	float y = 0;
	x = m_position.x;
	y = m_position.y;
	m_pointposition.x = x + numx;
	m_pointposition.y = y + numy;


}

void AIEditNode::Inequ()
{
	if (Mouse::isTrigger(enLeftClick))	//���N���b�N
	{
		NewGO<AIEditNodeInequ>(0, "Inequality");
			
		Choice1 = true;
	}

}

void AIEditNode::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {

		m_spriteRenders[i]->SetCollisionTarget(cursorpos);

	}

	if (Choice1 == false) { //�����I�����Ă��Ȃ��Ƃ�

		for (int i = 0; i < button; i++) {
			if (m_spriteRenders[i]->isCollidingTarget())	//�I�����Ă��邩	
			{
				Inequ();
			
			}
			
		}

	}
	
}

