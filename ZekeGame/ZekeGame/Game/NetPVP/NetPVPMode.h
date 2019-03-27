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

	//�f�X�g���N�^
	void OnDestroy() override;
private:


	Fade* m_fade = nullptr;				//fade
	MusicFade* m_mscfade = nullptr;		//musicfade
	ModeSelect* m_modesel = nullptr;	//modeselect
	ExchangeData* m_exdata = nullptr;	//�l�b�g�ł���肷��Ƃ��Ɏg�����
};