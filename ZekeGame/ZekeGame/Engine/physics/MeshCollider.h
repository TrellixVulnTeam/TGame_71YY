#pragma once
#include "Engine/Physics/ICollider.h"


class SkinModel;

/*!
* @brief	メッシュコライダー。
*/
class MeshCollider : public ICollider
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	MeshCollider();
	/*!
	* @brief	デストラクタ。
	*/
	~MeshCollider();
	/*!
	* @brief	CSkinModelからメッシュコライダーを生成。
	*@param[in]	model		スキンモデル。
	*/
	void CreateFromSkinModel(const SkinModel& model, const CMatrix* offsetMatrix);
	btCollisionShape* GetBody() const override
	{
		return m_meshShape.get();
	}
private:
	typedef std::vector<CVector3>					VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>				IndexBuffer;		//インデックスバッファ。
	typedef std::unique_ptr<VertexBuffer>			VertexBufferPtr;
	typedef std::unique_ptr<IndexBuffer>			IndexBufferPtr;
	std::vector<VertexBufferPtr>					m_vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBufferPtr>						m_indexBufferArray;		//インデックスバッファの配列。
	std::unique_ptr<btBvhTriangleMeshShape>			m_meshShape;				//メッシュ形状。
	std::unique_ptr<btTriangleIndexVertexArray>		m_stridingMeshInterface;
};

