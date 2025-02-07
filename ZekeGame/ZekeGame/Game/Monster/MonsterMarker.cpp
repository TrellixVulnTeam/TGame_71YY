#include "stdafx.h"
#include "MonsterMarker.h"

#include "Monster.h"

#include "../GameData.h"

MonsterMarker::~MonsterMarker()
{
}

void MonsterMarker::OnDestroy()
{
	DeleteGO(m_marker);
	DeleteGO(m_number);
}

bool MonsterMarker::Start()
{
	return true;
}

void MonsterMarker::init(Monster * mon)
{
	m_mon = mon;
	m_marker = NewGO<SpriteRender>(0, "sr");
	if(mon->Getteam() == 0)
		m_marker->Init(L"Assets/sprite/mark_red.dds",38,64);
	else
		m_marker->Init(L"Assets/sprite/mark_blue.dds", 38, 64);

	m_marker->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);

	m_number = NewGO<SpriteRender>(1, "sr");
	switch (mon->Getnum())
	{
	case 0:
	case 3:
		m_number->Init(L"Assets/sprite/mark_1.dds", 8.75f, 29.0f);
		break;
	case 1:
	case 4:
		m_number->Init(L"Assets/sprite/mark_2.dds", 17.25f, 29.25f);
		break;
	case 2:
	case 5:
		m_number->Init(L"Assets/sprite/mark_3.dds", 17.0f, 29.0f);
		break;
	}
	m_number->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);


	switch (mon->GetID())
	{
	case enTest:
		m_offsetY = 120;
		break;
	case enUmataur:
		m_offsetY = 250;
		break;
	case enFairy:
		m_offsetY = 130;
		break;
	}
	m_offsetY = mon->Getheight();

	auto cameraForward = camera3d->GetForward() * -1.0f;
	CVector3 pos = mon->Getpos();
	pos.y += m_offsetY;

	m_marker->SetPosition(pos);
	pos.y += 12;
	m_number->SetPosition(pos + cameraForward * 10.0f);

	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotation(camera3d->GetCameraRotation());
	m_marker->SetRotation(rot);
	m_number->SetRotation(rot);
}

void MonsterMarker::Update()
{
	CVector3 pos = m_mon->Getpos();
	pos.y += m_offsetY;

	m_marker->SetPosition(pos);
	pos.y += 12;
	m_number->SetPosition(pos);

	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotation(camera3d->GetCameraRotation());
	m_marker->SetRotation(rot);
	m_number->SetRotation(rot);
}
