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

enum eTarget {

	enme = 100,
	enbaddy,
	enenemy,
	enTAnull = 0,
};
enum eNode {

	enHp = 200,
	enMp,
	enAb,
	enTechnique,
	enNonull = 0,
};
enum eInequ {

	enDainari = 300,
	enShowers,
	enINnull = 0,
};
enum eNum {

	en1 = 400,
	en10,
	en30,
	en50,
	en70,
	en90,
	en100,
	enNUnull = 0

};

enum eTechnique {

	enAttak = 500,
	enLeav,
	enCase,
	enProtect,
	enHeel,
	enSpecial1,
	enSpecial2,
	enTEnull = 0,
};
enum eAbnormal {

	endoku = 600,
	enyakedo,
	enhyouketu,
	ensutan,
	enABnull = 0,
};
struct sOrder
{
	eTarget tar = enTAnull;
	eNode nod = enNonull;
	eInequ ine = enINnull;
	eNum num = enNUnull;
	eTechnique tec = enTEnull;
	eAbnormal abn = enABnull;
};

class AIEditNodeOrder :public GameObject
{

public:

	~AIEditNodeOrder();
	
	bool Start() override final;
	void Update() override final;
	void DeleteGOs();
	void Fonts();

	void makeOrder(int l,int o,sOrder* order,bool isEnd=false);
	void makeFonts(sOrder* order);
	
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


	bool m_isMakeOrder = false;				//makeOrder�����ꍇ��Start���𖳎����邽�߂̃t���O
};