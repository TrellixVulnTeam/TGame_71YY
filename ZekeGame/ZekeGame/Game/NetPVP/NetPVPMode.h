#pragma once

class Fade;
class MusicFade;

class ModeSelect;
class ExchangeData;
class NetPVPMode :public GameObject
{
public:
	//������
	NetPVPMode();

	//�������B
	void init(std::vector<std::string > files, int monai[3], int moid[3]);

	bool Start() override;
	void Update() override;
	//�f�X�g���N�^
	void OnDestroy() override;
private:
	void RaiseData();
	void LoadEnemyData();
	bool m_dataRaised = false;
	bool m_dataLoaded = false;
	void BattleStart();
	Fade* m_fade = nullptr;				//fade
	MusicFade* m_mscfade = nullptr;		//musicfade
	ModeSelect* m_modesel = nullptr;	//modeselect
	ExchangeData* m_exdata = nullptr;	//�l�b�g�ł���肷��Ƃ��Ɏg�����

	std::vector<std::string> m_files;		//python�t�@�C���̖��O
	int m_monai[6] = { 0 };				//�����X�^�[��AI
	int m_moid[6] = { 0 };				//�����X�^�[��ID
	int m_enemyAi[3] = { 0 };
	int m_enemyId[3] = { 0 };
	bool m_isConect = false;			//�q�����Ă��܂����H
	//UI
	SpriteRender* m_informationSp;
	CVector3 m_informationPos = { 0.f,300.f,0.f };
};