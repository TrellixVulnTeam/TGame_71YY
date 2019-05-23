#pragma once

class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeNum;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeTarget;
class AIEditNodeClick;
class AIEditNodeTechnique;
class AIEditNodeMenu;
class AIEditNodeSelectButtons;
class AIEditNodeDeleteKey;
class AIEditNodeProcess :public GameObject
{

public:

	~AIEditNodeProcess();

	bool Start();
	void Update();
	void Click();
	void Target();
	void Technique();
	void DeleteKey(AIEditNodeOrder* a);

	//flagkeep��orderkeep������
	void DeleteAll();
	AIEditNodeOrder* CreateOrder();
	
	void AISave(int num,int col);

	bool GetClickFlag()
	{
		return Clickflag;
	}

	void SetClickFlag(bool a)
	{
		Clickflag = a;
	}

	int GettechniqeCount()
	{
		return TechniqueCount;
	}

	bool GetTechniqueGenerate()
	{
		return TechniqueGenerate;
	}

	void SetTechniqueGenerate(bool a)
	{
		TechniqueGenerate = a;
	}

	//�������牺�Ŋe�N���X��enum��ۑ����Ă����B

	//�^�[�Q�b�g��ێ��B
	void Setkeeptarget(int n)
	{
		flagkeep[keep1][keep2][0] = n;
	}

	//node��ێ��B
	void Setkeeonode(int n)
	{
		flagkeep[keep1][keep2][1] = n;
	}

	//������ێ��B
	void Setkeepinequ(int n)
	{
		flagkeep[keep1][keep2][2] = n;
	}

	//���l(��)��ێ��B
	void Setkeepnum(int n)
	{
		flagkeep[keep1][keep2][3] = n; 
		keep2 += 1;
	}

	//��Ԉُ��ێ��B
	void Setkeepabnormal(int n)
	{
		flagkeep[keep1][keep2][4] = n;
		keep2 += 1;
	}

	//�Z��ێ��B
	void Setkeeptechnique(int n);

	void setOrderkeep(int l,int o,AIEditNodeOrder* order)
	{
		m_orderkeep[l][o] = order;
	}

	/*
	flagkeep �ɃZ�b�g����
	arg:
		y:Y��
		x:X��
		k:���
			0 = target
			1 = node
			2 = inequ
			3 = num
			4 = abnormal
			5 = technique
		v:�l
	*/
	void setFlagkeep(int y, int x, int k, int v)
	{
		flagkeep[y][x][k] = v;
	}

	//flagkeep�̒l��S���O�ɂ���
	void allDeleteFlagkeep()
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				for (int k = 0; k < 6; k++)
				{
					flagkeep[y][x][k] = 0;
				}
			}
		}
	}

	//�N���b�N���N���b�N����
	void ClickClicking()
	{
		m_isClickClicked = true;
	}

	//�N���b�N���N���b�N�������ǂ���
	bool isClickClicked()
	{
		return m_isClickClicked;
	}

private:

	int flagkeep[8][3][6];   //�e�N���X�ŉ���I����������ێ����Ă������߂̂��́B
	int keep1 = 0; //�W�s������̉��ڂ��B
	int keep2 = 0; //�R��̂����̉��ڂ��B
	int keep3 = 0; /*�ǂ̃N���X��I���������B 0 = target
				                              1 = node
											  2 = inequ
											  3 = num
											  4 = abnormal
											  5 = technique �@�@*/

	AIEditNodeOrder* m_orderkeep[8][3];

	int StateNum = 1;
	
	int num = 0;
	int TechniqueCount = 0;
	float ClickePosY = 275;				//AIEditNodeClick��New����Ƃ���Y���W�B
	bool Clickflag = 0;
	bool OrderChoice = false;			//AIEditNodeOrder���\������Ă��Ȃ��Ƃ��B
	bool TechniqueGenerate = false;		//technique���\��������true�ɂȂ�Bdeletekey�Ŏg���B

	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeClick* m_aieditnodeclick;
	SpriteRender * m_spriteRender;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeMenu* m_aieditnodemenu;
	AIEditNodeSelectButtons* m_aieditnodeselectbuttons;
	AIEditNodeDeleteKey* m_aieditnodedeletekey;

	bool m_isClickClicked = false;		//�N���b�N���N���b�N���ꂽ��
};