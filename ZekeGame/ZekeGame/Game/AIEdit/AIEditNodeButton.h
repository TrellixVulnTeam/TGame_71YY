#pragma once


class AIEditNodeButton : public GameObject
{

public:
	~AIEditNodeButton();
	bool Start();
	void Update();
	void Awake();
	
	//�{�^���̐����w��B
	void SetButton(int num)
	{
		button = num;
	}

	//���W���w��B
	void SetPos(CVector3 pos)
	{
		kari = pos;
	}

	//�v���C�I���e�B��ݒ�B
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

private:

	int sizex = 140;      //�{�^���̃T�C�Yx
	int sizey = 50;       //�{�^���̃T�C�Yy
	int button = 0;       //�{�^���̐�����B   
	int priority = 0;     //�`��D�揇��
	int x = 0;   
	int y = 140;

	CVector3 kari = CVector3::Zero();

	SpriteRender * m_spriteRender = nullptr;

	GameCursor * m_gamecursor = nullptr;

};