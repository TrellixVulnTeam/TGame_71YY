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

	CVector3 GetPos() {
		return kari;
	}

	void SetX(int x) {
		sizex = x;
	}

	void SetY(int y) {
		sizey = y;
	}

private:

	int sizex = 140;      //�{�^���̃T�C�Yx
	int sizey = 50;       //�{�^���̃T�C�Yy
	int button;          
	int priority = 0;     //�`��D�揇��
	int x = 0;   
	int y = 140;
	SpriteRender * m_spriteRender;
	CVector3 kari = CVector3::Zero();
	GameCursor * m_gamecursor;

};