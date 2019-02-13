#pragma once

class GameCursor;
// THIS IS CAMERA.
class GameCamera;
class AIEditNode;
class AIEditNodeNum;
class AIEditNodeButton;
class AIEditNodeInequ : public GameObject
{

public:

	~AIEditNodeInequ();
	bool Start() override final;
	void Update() override final;
	void Num();

	void GetChoice2(bool a)
	{
		Choice2 = a;
	}

private:

	int button = 2;							//�{�^���̐��B
	bool Choice2 = false;					//�������I�����ꂽ��true�ɂȂ�B


	SpriteRender * m_spriteRender;
	SpriteRender* sr;
	GameCursor * m_gamecursor;
	AIEditNodeNum* m_aieditnodenum;
	AIEditNodeButton* m_aieditnodebutton;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();
	AIEditNode * m_aieditnode;
	std::vector<SpriteRender*> m_spriteRenders;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};