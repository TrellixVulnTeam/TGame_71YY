#pragma once

class AIEditnode;
class AIEditNodeInequ;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeButton;
class AIEditNodeNum : public GameObject
{
public:

	~AIEditNodeNum();

	bool Start() override final;
	void Update() override final;
	void Order();

	void GetChoice3(bool a)
	{
		Choice3 = a;
	}

private:

	int button = 7;					//�{�^���B
	bool Choice3 = false;				//�������I�����ꂽ��true�ɂȂ�B


	SpriteRender * m_spriteRender;
	SpriteRender * sr;
	AIEditNode * m_aieditnode;
	GameCursor * m_gamecursor;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	AIEditNodeButton* m_aieditnodebutton;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();
	std::vector<SpriteRender*> m_spriteRenders;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};