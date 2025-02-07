#pragma once

class GameCursor;
class IconAI :public GameObject
{
public:
	~IconAI();
	bool Start();
	void init(std::string py, int num, GameCursor* cursor, bool isVisualAI = false,int mark = 0);
	void Update();
	void PostRender();

	void Setpos(CVector3 pos);
	CVector3 Getpos();

	bool isClick()
	{
		return m_isClick;
	}

	//
	int getVisualAIname()
	{
		return _wtoi(m_fr->getText());
	}
private:
	GameCursor* m_cursor;

	SpriteRender* m_dummy = nullptr;
	SpriteRender* m_frame = nullptr;
	bool m_issel = false;

	//const wchar_t* m_py;
	std::wstring m_py;
	int m_num = 0;

	bool m_isClick = false;

	CFont m_font;
	FontRender* m_fr = nullptr;
	FontRender* m_frShadow = nullptr;

	bool m_isVisualAI = false;
	SpriteRender* m_mark = nullptr;		//visualAI 用 のマーク
};