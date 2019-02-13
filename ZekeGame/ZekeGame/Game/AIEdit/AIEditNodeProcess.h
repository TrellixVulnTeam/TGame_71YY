#pragma once

class AIEditNode;
class AIEditNodeInequ;
class AIEditNum;
class AIEditNodeNum;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeTarget;
class AIEditNodeClick;
class AIEditNodeProcess :public GameObject
{

public:

	~AIEditNodeProcess();

	bool Start();
	void Update();
	void ButtonPosition();

	enum State
	{
		FirstOrder,
		SecondOrder,
		LastOrder

	};

private:

	bool NewChoice1 = false;    //AIEditNode���\������Ă��Ȃ��ꍇ�B
	bool NewChoice2 = false;    //AIEditNodeInequ���\������Ă��Ȃ��ꍇ�B
	bool NewChoice3 = false;    //AIEditNodeNum���\������Ă��Ȃ��ꍇ�B
	bool OrderChoice = false;   //AIEditNodeOrder���\������Ă��Ȃ��Ƃ�

	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeClick* m_aieditnodeclick;
	SpriteRender * m_spriteRender;

};