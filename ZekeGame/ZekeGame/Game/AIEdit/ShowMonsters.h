#pragma once
class GameCursor;

class ShowMonsters : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetWindowActive(bool active) {
		m_isActive = active;
	}
private:
	void InitFont();
	void InitButtons();
	void ButtonUpdate();
	bool m_isActive = true;
	std::vector<SpriteRender*> m_monsterSps;
	std::vector<SpriteRender*> m_frames;
	std::wstring m_MonsterNameList[500] = {L" �n", L"�d��",L"�A�[�}�[",L"�S�u����",L"�{",L"RedHead",L"�L�L���E",L"������"};
	std::vector<FontRender*> m_MonsterNames;
	SpriteRender* m_backSp = nullptr;
	const int nX =3;
	const int nY = 7;
	CVector3 m_basePos = { -370, 447.5,0 };
	GameCursor* m_cur = nullptr;
};

