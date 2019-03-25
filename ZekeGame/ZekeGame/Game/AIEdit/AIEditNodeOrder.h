#pragma once
class AIEditMode;
class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeNum;
class AIEditNodeClick;
class AIEditLine;
class GameCursor;
class AIEditNodeTarget;
class AIEditNodeProcess;
class AIEditNodeTechnique;
class AIEditNodeAbnormalState;
class AIEditNodeSelectFonts;
class AIEditNodeDeleteKey;
class AIEditNodeOrder :public GameObject
{

public:

	~AIEditNodeOrder();
	
	bool Start() override final;
	void Update() override final;
	void DeleteGOs();
	void Fonts();
	void DeletekeyClick();
	
	AIEditNodeDeleteKey* CreateDeleteKey();

	bool GetTec()
	{

		return Technique;
	}

	void SetTec(bool a)
	{
		Technique = a;
	}

	CVector3 GetPos()
	{

		return m_pos;
	}

	bool GettechniqueOrder()
	{

		return techniqueOrder;
	}

	bool GetNextClickFlag()
	{
		return NextClickFlag;
	}

	void SetNextClickFlag(bool a)
	{
		NextClickFlag = a;
	}


private:

	bool Technique = false;		//�Z��I�������Ƃ�true�ɂȂ�B�@
	bool techniqueOrder = false;
	bool timer = false;
	bool key = false; //deletekey�ɉ�������������true�ɂȂ�B
	int num = 1;
	int fonttimer = 25;          //��ɕ\������Ă���m�F�p��font��
	float scale = 0.7;          //font�̃X�P�[���B
	bool NextClickFlag = false;  //Deletekey���g���ė��Delete�����ƋC��true�ɂȂ�B

	AIEditNodeDeleteKey* m_keepdelete[8];

	std::vector<FontRender*> m_fonts;
	CVector3 m_pos = CVector3::Zero();
	GameCursor * m_gamecursor;
	AIEditMode * m_aieditmode;
	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeClick* m_aieditnodeclick;
	AIEditLine * m_aieditline;
	SpriteRender * m_spriteRender;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeProcess* m_aieditnodeprocess;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeAbnormalState* m_aieditnodeabnormalstate;
	AIEditNodeSelectFonts* m_aieditonodeselectfonts;
	AIEditNodeDeleteKey* m_aieditnodedeletekey;

};