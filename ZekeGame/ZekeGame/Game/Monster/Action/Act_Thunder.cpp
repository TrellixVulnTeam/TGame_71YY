#include "stdafx.h"
#include "Act_Thunder.h"
#include "ACTEffect.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_Thunder::Act_Thunder() {
	m_ActionId = enThunder;
}

bool Act_Thunder::Action(Monster* me) {
	if (m_target == nullptr) return true;

	if (m_first) {
		if (me->GetMP() < m_cost) return true;
		m_cBeam.InitAbnormalStateInfo(L"Assets/effect/SIBIRUD.efk", ACTEffectGrant::State::enHardCC,m_efs,m_DoTEndTime, m_grantAbsTime);
		m_cBeam.Fire(me, m_target, L"Assets/effect/thuder.efk", L"Assets/sound/lightning.wav", laserRange, m_damage,m_cost);
		m_first = false;
	}
	else if (m_timer >= m_cooltime) {
		me->anim_idle();
		return true;
	}

	if (m_cBeam.DamageCalc()) m_timer += IGameTime().GetFrameDeltaTime();

	return false;
}
