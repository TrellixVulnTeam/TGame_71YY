#include "stdafx.h"
#include "Act_Majinken.h"
#include "ACTEffect.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_Majinken::Act_Majinken() {
	m_ActionId = enMajinken;
}

Act_Majinken::~Act_Majinken() {
	if (m_efk != nullptr and m_efk->IsPlay())
		m_efk->Stop();
}


bool Act_Majinken::Action(Monster* me) {
	if (m_target == nullptr) return true;

	bool res = false;
	switch (m_state)
	{
	case enSChase:
	{
		bool ench = false;
		ench = Chase(me);
		if (ench)
			m_state = enSAttack;
	}
	break;
	case enSAttack:
		res = Attack(me);
		break;
	}
	return res;
	
}

bool Act_Majinken::Chase(Monster* me)
{
	CVector3 mepo = me->Getpos();
	CVector3 v = m_target->Getpos() - mepo;
	if (v.Length() < m_target->Getradius() + me->Getradius() + 1)
	{
		me->Setspeed(CVector3::Zero());
		//me->Setiswalk(false);
		me->anim_idle();
		return true;
	}
	me->anim_walk();
	v.Normalize();


	v *= 15;
	me->Setspeed(v);
	me->Setiswalk(true);

	m_time += IGameTime().GetFrameDeltaTime();
	if (m_time > 10.0f)
	{
		me->Setspeed(CVector3::Zero());
		me->anim_idle();
		return true;
	}

	return false;
}

bool Act_Majinken::Attack(Monster* me)
{
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		me->SetMP(mp - m_cost);

		knock = m_target->Getpos() - me->Getpos();
		CVector3 v = m_target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale(CVector3::One() * 3.5);
		m_efk->SetPosition(me->Getpos());
		m_efk->Play(L"Assets/effect/majinken_wiat.efk");
		ACTEffectGrant * actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, me, ACTEffectGrant::State::enNull);
		me->SetAbnormalState(actEG);

		Sound * se = NewGO<Sound>(0, "snd");
		//se->Init(L"Assets/sound/hai-hai1.wav");
		se->Init(L"Assets/sound/dissonance1.wav");
		se->Play();
		m_first = false;
	}
	if (m_timer >= m_chargeTime and !m_attacked) {
		float len = (m_target->Getpos() - me->Getpos()).Length();
		float mil = m_target->Getradius() + me->Getradius() + 30;
		m_efk->Stop();
		if (len <= mil) {
			auto efk = NewGO<CEffect>(0, "ef");
			efk->SetScale(CVector3::One() * 2);
			efk->SetPosition(me->Getpos());
			efk->Play(L"Assets/effect/majinken_attack.efk");
			knock.Normalize();
			knock *= 300;
			m_target->StartKnockback(knock);
			//float dam = m_damagePow * me->GetExAttack() * 1 / m_target->GetExDefense();
			m_target->Damage(m_damagePow);
			m_attacked = true;
			Sound* se = NewGO<Sound>(0, "snd");
			se->Init(L"Assets/sound/punch-high2.wav");
			se->Play();
		}
		else {
			m_attacked = true;
		}
	}
	if (m_timer >= m_cooltime and m_attacked) {
		me->anim_idle();
		m_efk->Stop();
		return true;
	}

	m_timer += 60 * IGameTime().GetFrameDeltaTime();
	return false;
}
