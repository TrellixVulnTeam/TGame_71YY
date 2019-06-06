#pragma once

class UIAnimator;
class ModeSelectBack :public GameObject
{
public:
	ModeSelectBack();
	void OnDestroy();

	void Update();

	enum eMode
	{
		enNone,
		endundeon,
		enpvp,
		ennetpvp,
		enAIedit
	};

	//�؂�ւ��@�_���W����
	void Dungeon();
	//�؂�ւ��@PVP
	void PVP();
	//�؂�ւ��@NETPVP
	void NetPVP();
	//�؂�ւ��@AIEdhit
	void AIedit();

	//�X�v���C�g�@ALL�@kill
	void delSprits();

	void moveDungeon();
	void movePVP();
	void moveNETPVP();
	void moveAIedit();
private:
	SkinModelRender* m_back = nullptr;	//haikei
	SpriteRender* m_backS = nullptr;	//haikei(sprite)
	eMode m_mode = enNone;				//���܂̏��
	CEffect* m_effect = nullptr;		//effect;

	std::vector<SpriteRender*> m_dungeon;//�_���W�����X�v���C�g
	std::vector<SpriteRender*> m_pvp;	//pvp�X�v���C�g
	std::vector<SpriteRender*> m_netpvp;//netpvp�X�v���C�g
	std::vector<SpriteRender*> m_AIedit;//AIedit sprite

	std::vector<SpriteRender*> m_sprits;//sprite�W����

	UIAnimator* m_uia = nullptr;	//UIAnimator

	bool m_isfirst = false;			//���߂Ă��H

};