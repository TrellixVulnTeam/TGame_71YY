#pragma once
#include "..//ACTEffect.h"
#include "IAct.h"
class Monster;

class CAct_Beam : public IAct
{
public:

	void Fire(
		Monster* me,
		Monster* target,
		const wchar_t* beamEffectPath,
		const wchar_t* soundPath,
		float range,
		float baseDamage,
		CVector3 effectScale = { 3.5,3.5,3.5 }
	);

	//�_���[�W��^���I�������true��Ԃ��܂�
	bool DamageCalc();

private:
	bool IsHitting(Monster* mon, Monster* me);
	CEffect* m_beamefk = nullptr;
	CVector3 crs = CVector3::Zero();
	CVector3 m_targetPosition = CVector3::Zero();
	Monster* m_me = nullptr;
};

