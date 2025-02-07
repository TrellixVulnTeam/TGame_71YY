#include "stdafx.h"
#include "TestMons.h"
#include "../../PythonBridge/PythonBridge.h"
//#include "Monster.h"

TestMons::TestMons()
{
	m_HP = 10;
	m_MP = 10;
	m_radius = 20;
	m_height = 70;

	m_AnimNum = 0;

	m_smr = NewGO<SkinModelRender>(0, "smr");
	m_smr->Init(L"Assets/modelData/tesEnemy3.cmo");
	m_smr->SetPosition(CVector3::Zero());

	

	init
	(
		1000000000,		//HP
		10000,		//MP
		10,		//hδΝ
		10,		//ΑκhδΝ
		10,		//UΝ
		10,		//ΑκUΝ
		10,		//Xs[h
		20,		//RWΜΌa
		120,		//³
		m_smr,	//rkin lodel qender
		0		//Aj[VΜ
	);

	m_ID = 0;
	int cnt = 0;
	ActionID* ua = GameData::GetMonsterActions(m_ID, cnt);
	SetUseAction(ua, cnt);
}