//Click�𐶐�����N���X
#include "stdafx.h"

#include "AIEditNode.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeProcess.h"
#include "AIEditLine.h"
#include "AIEditNodeOrder.h"
#include "AIEditLine.h"
#include "AIEditNodeTarget.h"
#include "AIEditNodeClick.h"
#include "AIEditNodeTechnique.h"
#include "AIEditNodeMenu.h"
#include "../GameCursor.h"
#include "AIEditNodeSelectButtons.h"
#include "AIEditNodeDeleteKey.h"

#include "VisualAIOpen.h"

//camera
#include "../../GameCamera.h"


AIEditNodeProcess::~AIEditNodeProcess()
{

}

bool AIEditNodeProcess::Start()
{

	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");
	m_aieditnodeorder = FindGO<AIEditNodeOrder>("order");

	if (num <= 7) {
		Click();
	}

	//m_aieditnodemenu = NewGO<AIEditNodeMenu>(0, "menu");
	m_aieditnodeselectbuttons = NewGO<AIEditNodeSelectButtons>(0, "selectbuttons");


	//���ׂĂ�flagkeep��null�������Ă����B
	for (int i = 0; i <= 7; i++) {

		for (int j = 0; j <= 1; j++) {

			for (int k = 0; k <= 4; k++) {

				flagkeep[i][j][k] = 0;            //0�͉����I�����Ă��Ȃ���ԁB(nulptr)

			}
		}
	}

	for (int i = 0; i <= 7; i++) {

		for (int j = 0; j <= 2; j++) {
			m_orderkeep[i][j] = nullptr;
		}
	}
	
	return true;
}

void AIEditNodeProcess::Setkeeptechnique(int n)
{

	flagkeep[keep1][keep2][5] = n;
	m_isClickClicked = false;

	for (int i = 0; i <= 7; i++) {
		m_orderkeep[i][0];
		if (m_orderkeep[i][0] == nullptr) {
			
			keep1 = i;
			keep2 = 0;
			break;
		}
	}
}


void AIEditNodeProcess::Click()
{

	//click���o�Ă�����Delete����B
	QueryGOs<AIEditNodeClick>("click",[&](auto* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	
	for (int i = 0; i <= 7; i++) {

		m_orderkeep[i][0];

		//order��������Ă��Ȃ��s��click��new����B
		if (m_orderkeep[i][0] == nullptr) {

			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			float y = ClickePosY - 85 * i;
			m_aieditnodeclick->SetPosition({ -430,y,0 });

			//Click��\�������s�̏�Ԃ����Z�b�g(null)�ɂ���B
			for (int j = 0; j <= 2; j++) {

				for (int k = 0; k <= 5; k++) {

					flagkeep[i][j][k] = 0;           //0�͉����I�����Ă��Ȃ���ԁB(nulptr)

					keep1 = i;						 //��Ԃ�ۑ�����s��ݒ肷��B
					keep2 = 0;						 //����P��ڂɐݒ肷��B
				}

			}
			break;
		}
	}

}


void AIEditNodeProcess::Target()
{

	m_aieditnodetarget = NewGO<AIEditNodeTarget>(0, "target");
	TechniqueCount += 1;

}

void AIEditNodeProcess::Technique()
{

	m_aieditnodetechnique = NewGO<AIEditNodeTechnique>(0, "Technique");
	TechniqueCount = 0;

}

void AIEditNodeProcess::DeleteKey(AIEditNodeOrder* a)
{

	bool isBreak = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			if (m_orderkeep[i][j] == a) {
				//order��Delete����B
				DeleteGO(m_orderkeep[i][0]);
				DeleteGO(m_orderkeep[i][1]);
				DeleteGO(m_orderkeep[i][2]);
				m_orderkeep[i][0] = nullptr;
				m_orderkeep[i][1] = nullptr;
				m_orderkeep[i][2] = nullptr;
				////deletekey��Delete����B
				//DeleteGO(m_aieditnodedeletekey);
				isBreak = true;

				break;
			}
		}

		if (isBreak == true)
			break;

	}
}

void AIEditNodeProcess::DeleteAll()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			DeleteGO(m_orderkeep[y][x]);
			m_orderkeep[y][x] = nullptr;

			for (int k = 0; k < 6; k++)
			{
				flagkeep[y][x][k] = 0;
			}
		}
	}
}

//order�̏�Ԃ�ێ�����B
AIEditNodeOrder * AIEditNodeProcess::CreateOrder()
{

	m_aieditnodeorder = NewGO<AIEditNodeOrder>(0,"order");
	bool flaflag = false;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			if (m_orderkeep[i][j] != nullptr) 
			{
				if (j < 2 && !m_orderkeep[i][j]->isTechniqueOrder())
				{
					if (m_orderkeep[i][j + 1] == nullptr)
					{
						m_orderkeep[i][j + 1] = m_aieditnodeorder;
						flaflag = true;
						break;
					}
				}
				else if (m_orderkeep[i][j]->isTechniqueOrder() == true) {
					if (m_orderkeep[i + 1][0] == nullptr)
					{
						m_orderkeep[i + 1][0] = m_aieditnodeorder;
						flaflag = true;
						break;
					}
				}
			}
			else if (j == 0)
			{
				m_orderkeep[i][0] = m_aieditnodeorder;
				flaflag = true;
				break;
			}
		}

		if (flaflag == true) {
			break;
		}

	}

	return m_aieditnodeorder;
}


//�t�H���_�ɍ쐬����AI��ۑ����邽�߂̏����B
void AIEditNodeProcess::AISave(int num,int col)
{
	char path[255];
	sprintf(path, "Assets/VisualAI/%03d.va", num);
	FILE* f = fopen(path,"w");

	char head[] = "VISAI";
	fwrite(head, 5, 1,f);
	int i = 0;
	fwrite(&i, 1, 1, f);

	fwrite(&col, 1, 1, f);
	
	for (int i0 = 0;i0 < 8; i0++)
	{
		for (int i1 = 0;i1 < 3;i1++)
		{
			for (int i2 = 0; i2 < 6; i2++)
			{
				fwrite(&flagkeep[i0][i1][i2], 2, 1, f);
			}
		}
	}
	fclose(f);
}

void AIEditNodeProcess::Update()
{
		


}
