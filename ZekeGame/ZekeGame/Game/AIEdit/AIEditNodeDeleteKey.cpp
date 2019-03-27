#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeDeleteKey.h"
#include "AIEditNodeOrder.h"
#include "AIEditLine.h"
#include "AIEditNodeProcess.h"

AIEditNodeDeleteKey::~AIEditNodeDeleteKey()
{
	DeleteGO(m_spriteRender);


}


bool AIEditNodeDeleteKey::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	//m_aieditnodeorder = FindGO<AIEditNodeOrder>("order");
	m_aieditline = FindGO<AIEditLine>("Line");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	//��ԐV����order�̍��W�𒲂ׂ�B
	CVector3 v = CVector3::Zero();
	QueryGOs<AIEditNodeOrder>("order", [&](auto go)->bool
	{
		v = go->GetPos();
		return true;
	});
	m_position = v;
	
	m_spriteRender = NewGO<SpriteRender>(3, "delete");
	m_spriteRender->Init(L"Assets/sprite/deletepoint.dds", 25, 25, true);
	m_position.x += 160;
	m_spriteRender->SetPosition(m_position);


	return true;
}

void AIEditNodeDeleteKey::SetOrder(AIEditNodeOrder* a)
{
	m_orderpoint = a;

}

void AIEditNodeDeleteKey::deleteclick()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();
	m_spriteRender->SetCollisionTarget(cursorpos);

	if (Mouse::isTrigger(enLeftClick)) {
		if (m_spriteRender->isCollidingTarget())
		{
			//�񂷂ׂĂ̂��̂�Delete�B
			m_aieditnodeprocess->DeleteKey(m_orderpoint);
			m_aieditnodeprocess->Click();
		}
	}
}

void AIEditNodeDeleteKey::Update() 
{

	deleteclick();

}