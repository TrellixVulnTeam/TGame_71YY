#pragma once

class MonsterAction;

//�����X�^�[�A�N�V�����̃��[�f�B���O��S���Ă���
class MonsterActionManeger:public GameObject
{
public:
	//�����X�^�[�ɋZ��������Ƃ��Ɏg�����[�_�[
	//id:		�Z��ID
	//target:	�Ώۂ̃����X�^�[
	static MonsterAction* LoadAction(int id,int target);

	
	/*enum en_action
	{
		en_Chase,
		en_Atack,
		en_Leave,

		en_Fire,
	};*/
private:
};