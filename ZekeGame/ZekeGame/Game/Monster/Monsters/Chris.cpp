#include "stdafx.h"
#include "Chris.h"

#include "../../GameData.h"

Chris::Chris()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/chris/cri_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/chris/cri_idle.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/chris/cri_attack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);
	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/chris/cri_idle.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(false);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/chris/cri_idle.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/chris/cri_idle.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(false);
	m_anim[Monster::en_extra1].Load(L"Assets/modelData/chris/cri_ex1.tka");
	m_anim[Monster::en_extra1].SetLoopFlag(false);

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/cri.cmo", m_anim, 3);
	sr->SetScale(CVector3::One()*2);
	//sr->SetScale({ 1.8f,1.8f,1.8f });
	//sr->Init(L"Assets/modelData/uma.bone.cmo");
	sr->SetPosition(CVector3::Zero());
		
	MonsterInitParam prm;
	prm.HP = 80;
	prm.MP = 110;

	prm.DefencePow = 8;
	prm.ExDefensePow = 8;

	prm.AttackPow = 7;
	prm.ExAttackPow = 10;

	prm.Speed = 10;
	prm.Radius = 50;
	prm.Height = 300;
	prm.ModelRender = sr;
	prm.NumAnimation = 3;

	init(prm);

	m_ID = enChris;
	int cnt = 0;
	
	ActionID* ua = GameData::GetMonsterActions(m_ID, cnt);
	SetUseAction(ua, cnt);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	
}
