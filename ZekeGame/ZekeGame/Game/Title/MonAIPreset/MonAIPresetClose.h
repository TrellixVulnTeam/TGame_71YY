#pragma once

class MonAIPresetOpen;
class MonAIPresetClose :public GameObject
{
public:
	//des
	~MonAIPresetClose();

	//Start
	bool Start();

	//初期化関数
	void init(MonAIPresetOpen* mapo);

	//update
	void Update();
private:
	SpriteRender* m_button = nullptr;
	FontRender* m_font = nullptr;

	MonAIPresetOpen* mapo = nullptr;
};