#pragma once

class AIEditNode;
class AIEditNodeInequ;
class AIEditNum;
class AIEditNodeProcess :public GameObject
{

public:

	~AIEditNodeProcess();

	bool Start();
	void Update();

private:

	bool NewChoice1 = false;    //AIEditNode���\������Ă��Ȃ��ꍇ�B
	bool NewChoice2 = false;    //AIEditNodeInequ���\������Ă��Ȃ��ꍇ�B
	bool NewChoice3 = false;    //AIEditNodeNum���\������Ă��Ȃ��ꍇ�B

	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;

};