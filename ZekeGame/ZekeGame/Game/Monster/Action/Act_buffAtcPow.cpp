#include "stdafx.h"
#include "Act_buffAtcPow.h"
#include "../MonsterAction.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_buffAtcPow::Act_buffAtcPow()
{
	m_ActionId = enBuffAtc;
}


Act_buffAtcPow::~Act_buffAtcPow()
{
}

bool Act_buffAtcPow::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		me->SetMP(mp - m_cost);

		/*m_pow = m_target->GetAttack();
		m_target->SetAttackPower(m_pow * 1.5);
		m_ExPow = m_target->GetExAttack();
		m_target->SetAttackPower(m_ExPow * 1.5);*/
		me->anim_extra1();
		auto m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale({ 8,8,8 });
		m_efk->SetPosition(m_target->Getpos());
		m_efk->Play(L"Assets/effect/buff.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target, ACTEffectGrant::State::enBuffAtcPow, 0, 0, 150,me);
		actEG->SetBuffDebuffParam(2.0);
		m_target->SetAbnormalState(actEG);

		Sound* snd = NewGO<Sound>(0, "snd");
		snd->Init(L"Assets/sound/buff.wav");
		snd->SetVolume(1.2f);
		snd->Play();

		CVector3 v = m_target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_first = false;
	}
	else {
		m_timer+= IGameTime().GetFrameDeltaTime();
		if (/*!me->isAnimPlay() and*/ m_timer >= m_cooltime)
		{
			//m_target->SetAttackPower(m_pow);
			//m_target->SetExAttackPower(m_ExPow);
			me->anim_idle();
			return true;
		}
	}
	return false;
}
