#pragma once
#include "..//ACTEffect.h"

#include "../../../GameData.h"
class Monster;
class IAct {
public:
	void RotateToTarget(Monster* me, Monster* target) {
		CVector3 v = target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);
	};

	void GrantAbnormalState(Monster* target,
		Monster* me,
		const wchar_t* effectPath,
		ACTEffectGrant::State state,
		float endTime,
		float DoTParam);

	void InitAbnormalStateInfo(const wchar_t* effectPath,
		ACTEffectGrant::State state,
		CVector3 effectScale,
		float DoTTime,
		float GrantAbsTime,
		float DoTDamageParam = 0.f
	) {
		wcscpy(m_absEfkPath, effectPath);
		m_DoTEndTime = DoTTime;
		m_DoTDamage = DoTDamageParam;
		m_grantAbsTime = GrantAbsTime;
		m_state = state;
		efs = effectScale;
	};
protected:
	CVector3 efs = CVector3::One();
	std::map<Monster*, bool> m_isAbnormal;
	std::map<Monster*, float> m_timerForGrantAbs;
	float m_DoTEndTime = 0.f;
	float m_baseDamage = 0.f;
	float m_DoTDamage = 0.f;
	wchar_t m_absEfkPath[256];
	float m_grantAbsTime = 0.f;
	ACTEffectGrant::State m_state = ACTEffectGrant::State::enNull;
};

//class Monster;
//
//class IAct {
//public:
//
//	//対象に攻撃が当たっているか
//	virtual bool IsHitting(Monster* target, Monster* me) {};
//
//	//対象に異常状態を付与する
//	void GrantAbnormalState(Monster* target, Monster* me, const wchar_t* effectPath, ACTEffectGrant::State state, float endTime, float DoTParam);
//
//	//状態異常の詳細を設定
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
//	//対象の方向を向く
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