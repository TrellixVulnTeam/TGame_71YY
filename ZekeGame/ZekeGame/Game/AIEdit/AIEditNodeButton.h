#pragma once


class AIEditNodeButton : public GameObject
{

public:
	~AIEditNodeButton();
	void Awake();
	bool Start();
	void Update();
	
	void SetButton(int num)
	{

		button = num;
	}

	void SetPos(CVector3 pos)
	{

		kari = pos;
	}

	void SetPri(int pri)
	{

		priority = pri;
	}

	SpriteRender * GetSpriteRender()
	{

		return m_spriteRender;
	}

private:

	int button;
	int priority = 0;
	//int x = 35;			//�{�^����X���W
	int x = 0;
	//int y = 120;		//�{�^����Y���W
	int y = 140;
	SpriteRender * m_spriteRender;
	CVector3 kari = CVector3::Zero();
	GameCursor * m_gamecursor;

};