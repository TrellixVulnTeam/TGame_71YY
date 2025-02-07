#pragma once

class AIEditnode;
class AIEditNodeInequ;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeButton;
class AIEditNodeProcess;
class AIEditNodeNum : public GameObject
{
public:

	~AIEditNodeNum();

	bool Start() override final;
	void Update() override final;
	void Order();
	void FontsConfirmation();

	void GetChoice3(bool a)
	{
		Choice3 = a;
	}

	enum Num {

		en1 = 400,
		en10,
		en30,
		en50,
		en70,
		en90,
		en100,
		ennull = 0 

	};

	int GetNum()
	{

		return m_num;
	}

	bool Getnumfont()
	{
		return Numfont;
	}

private:

	Num m_num = ennull;
	int button = 7;					//ボタン。
	bool Choice3 = false;				//何かが選択されたらtrueになる。
	bool Numfont = false;
	float scale = 0.9;
	bool contact1 = false;
	bool contact2 = false;

	CVector2 SetShadowPos = { 5.f,-5.f };

	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;
	std::vector<SpriteRender*> m_spriteRenders;
	std::vector<AIEditNodeButton*> m_nodebuttons;

	SpriteRender * m_spriteRender;
	SpriteRender * sr;

	AIEditNode * m_aieditnode;
	GameCursor * m_gamecursor;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeProcess* m_aieditnodeprocess;
};