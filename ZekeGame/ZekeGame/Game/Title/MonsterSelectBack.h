#pragma once


class MonsterSelectBack :public GameObject
{
public:
	MonsterSelectBack();
	void OnDestroy();
	void Update();
private:
	SpriteRender* m_back = nullptr;		//�������̂��
	std::vector<SpriteRender*> m_hexs;	//hex no�@kazari

	float m_addrot[2] = { 0.5,0.7 };
	float m_rot[2] = { 0,0 };
};