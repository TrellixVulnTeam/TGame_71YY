#pragma once
#include "..//ACTEffect.h"
//class Monster;
//
//class IAct {
//public:
//
//	//�ΏۂɍU�����������Ă��邩
//	virtual bool IsHitting(Monster* target, Monster* me) {};
//
//	//�ΏۂɈُ��Ԃ�t�^����
//	void GrantAbnormalState(Monster* target, Monster* me, const wchar_t* effectPath, ACTEffectGrant::State state, float endTime, float DoTParam);
//
//	//��Ԉُ�̏ڍׂ�ݒ�
//	void InitAbnormalStateInfo(const wchar_t* effectPath,
//		ACTEffectGrant::State state,
//		CVector3 effectScale,
//		float DoTTime,
//		float GrantAbsTime,
//		float DoTDamageParam = 0.f
//	) {
//		wcscpy(m_absEfkPath, effectPath);
//		m_DoTEndTime = DoTTime;
//		m_DoTDamage = DoTDamageParam;
//		m_grantAbsTime = GrantAbsTime;
//		m_efs = effectScale;
//		m_state = state;
//	};
//
//	//�Ώۂ̕���������
//	void RotateToTarget(Monster* me, Monster* target);
//protected:
//	std::map<Monster*, bool> m_isAbnormal;
//	std::map<Monster*, float> m_timerForGrantAbs;
//	CVector3 m_efs = CVector3::One();
//	float m_DoTEndTime = 0;
//	float m_baseDamage = 0;
//	float m_DoTDamage = 0;
//	wchar_t m_absEfkPath[256];
//	float m_grantAbsTime = 0;
//	ACTEffectGrant::State m_state = ACTEffectGrant::State::enNull;
//};