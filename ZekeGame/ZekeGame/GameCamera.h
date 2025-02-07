#pragma once

#include "Engine/graphics/SpringCamera.h"

class SpringCamera;

class GameCamera :public GameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	void normal();
	void focus();
	void SetTarget(CVector3 tar) {
		m_target = tar;
	}
	void SetPosition(CVector3 pos) {
		m_pos = pos;
	}
private:
	bool neko = false;
	CVector3 m_target = { 0.0f, 20.0f, 0.0f };
	CVector3 m_pos = { 0.0f, 350.0f, 10000.0f };
	//CVector3 m_toCameraPos = { 0.0f, 50.0f, 300.0f };
	CVector3 m_toCameraPos = { 0.0f, 50.0f, 1000.0f };

	SpringCamera m_Scamera;

	int m_inm = -1;

	bool m_first = true;
	float m_base = 0.f;
};

