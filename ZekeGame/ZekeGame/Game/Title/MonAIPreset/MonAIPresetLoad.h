#pragma once

class GameCursor;
class SuperMonsterSelect;
class MonAIPresetLoad :public GameObject
{
public:
	bool Start();
	void init(SuperMonsterSelect* sms,int num,int team,GameCursor* cursor);
	void Update();

	//�Z�b�g�|��
	//pos: �Z�b�g����|�W�V����
	void setPos(CVector3 pos)
	{
		m_pos = pos;
	}

	//�N���b�N���ꂽ��
	bool IsClick()
	{
		return m_isClick;
	}
private:
	SpriteRender* m_button = nullptr;
	FontRender* m_font = nullptr;
	GameCursor* m_cursor = nullptr;

	SuperMonsterSelect* m_sms = nullptr;
	int m_num = 0;
	int m_team = 0;

	CVector3 m_pos = CVector3::Zero();
	bool m_isClick = false;					//�N�b���N���ꂽ���H
};