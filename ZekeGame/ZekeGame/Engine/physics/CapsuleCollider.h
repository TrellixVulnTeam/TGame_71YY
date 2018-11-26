/*!
* @brief	�J�v�Z���R���C�_�[�B
*/

#pragma once

#include "Engine/Physics/ICollider.h"


class CapsuleCollider : public ICollider
{
public:
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~CapsuleCollider();
	/*!
	* @brief	�쐬�B
	*@param[in] radius	�J�v�Z���̔��a�B
	*@param[in]	height	�J�v�Z���̍����B
	*/
	void Create(float radius, float height, EnFbxUpAxis axis)
	{
		m_axis = axis;
		if (axis == enFbxUpAxisY) {
			shape = new btCapsuleShape(radius, height);
		}
		else if(axis == enFbxUpAxisZ){
			shapez = new btCapsuleShapeZ(radius, height);
		}
		this->radius = radius;
		this->height = height;
	}
	btCollisionShape* GetBody() const override
	{
		if (m_axis == enFbxUpAxisY) {
			return shape;
		}
		else if (m_axis == enFbxUpAxisZ) {
			return shapez;
		}
	}
	float GetRadius() const
	{
		return radius;
	}
	float GetHeight() const
	{
		return height;
	}
private:
	btCapsuleShape * shape = nullptr;
	btCapsuleShapeZ * shapez = nullptr;
	EnFbxUpAxis m_axis;
	float radius = 0.0f;
	float height = 0.0f;
};
