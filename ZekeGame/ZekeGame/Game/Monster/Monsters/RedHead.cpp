#include "stdafx.h"
#include "RedHead.h"

#include "../../GameData.h"

RedHead::RedHead()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/RedHead/idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/RedHead/run.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/RedHead/RedHead_tyoppu.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);
	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/RedHead/RedHead_defe_f.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(false);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/RedHead/RedHead_defe_m.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/RedHead/RedHead_defe_e.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(false);
	m_anim[Monster::en_extra1].Load(L"Assets/modelData/RedHead/RedHead_Zoi.tka");
	m_anim[Monster::en_extra1].SetLoopFlag(false);
	m_anim[Monster::en_extra2].Load(L"Assets/modelData/RedHead/clear.tka");
	m_anim[Monster::en_extra2].SetLoopFlag(false);

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/RedHead.cmo", m_anim, 8);
	//sr->SetScale(CVector3::One() * 20);
	sr->SetPosition(CVector3::Zero());

	MonsterInitParam prm;
	prm.HP = 80;
	prm.MP = 130;
	prm.DefencePow = 5;
	prm.ExDefensePow = 5;
	prm.AttackPow = 7;
	prm.ExAttackPow = 7;
	prm.Speed = 10;
	prm.Radius = 50;
	prm.Height = 190;
	prm.ModelRender = sr;
	prm.NumAnimation = 8;

	init(prm);

	m_ID = enRedHead;
	int cnt = 0;
	ActionID* ua = GameData::GetMonsterActions(m_ID, cnt);
	SetUseAction(ua, cnt);
}
