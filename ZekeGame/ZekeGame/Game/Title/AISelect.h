#pragma once

class SuperMonsterSelect;
class PvPModeSelect;
class AIMSelect;
class GameCursor;
class PMMonster;
class IconAI;
class AISelect :public GameObject
{
public:
	~AISelect();
	bool Start();
	void init(PMMonster* pmm,AIMSelect* aims);
	void Update();
	void PostRender();

	//python�ł�����AI�̈ꗗ��\������
	void CreatePyAI();
	
	//VisualScript�ō����AI�̈ꗗ��\������
	void CreateViAI();

	//AI�̈ꗗ������
	void DeleteAI();
private:
	PMMonster* m_pmm;
	AIMSelect* m_AIMS;
	GameCursor* m_cursor = nullptr;
	SpriteRender* m_back = nullptr;

	float m_minScroll = 0.0f;
	float m_maxScroll = 0.0f;
	float m_scroll = 316.5f;

	std::vector<IconAI*> m_icons;
	SuperMonsterSelect* m_ppms = nullptr;

	SpriteRender* m_AIsel = nullptr;

	FontRender* m_title = nullptr;			//��ɕ\�����镶��


	enum AIMode
	{
		enPy,
		enVi,
	};
	int m_AImode = enPy;

	SpriteRender* m_changeAI = nullptr;		//visualAI��pythonAI�Ƃ̐؂�ւ��p��sprite
	FontRender* m_CAfont = nullptr;			//visualAI��pythonAI�Ƃ̐؂�ւ��p�̃t�H���g
};