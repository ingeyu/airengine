#ifndef AirStaticMesh_h__
#define AirStaticMesh_h__

#include "AirEngineHeader.h"
#include "AirBoundingBox.h"
#include "AirEngineRenderable.h"
#include "AirEngineMovableObject.h"

namespace	Air{
	namespace	Client{
		class	ENGINE_EXPORT	StaticMesh	:	
			public	IProduct{
		public:
			StaticMesh(CAString&	strName);
			virtual	U1	Create();
			virtual	U1	Destroy();

			U32					GetVertexCount(){
				return	m_uiNumVertex;
			};
			void*				GetVB(){
				return	pVB;
			};
			U32					GetFaceCount(){
				return	m_uiNumFace;
			};
			void*				GetIB(){
				return	pIB;
			};
			const AString&		GetMaterialName(){
				return	m_strMaterialName;
			};
			const BoundingBox&	GetBoundingBox()const;

			const Render::Draw::Buff&	GetDrawBuffer()const;

			U1	RayCast(const Ray& ray ,float*	pOutDistance	=	NULL);
		protected:
			U1			LoadAME0();

			U32			m_uiNumVertex;
			U32			m_uiNumFace;
			void*		pVB;
			void*		pIB;

			Data		m_MeshData;
			AString		m_strMaterialName;

			BoundingBox	m_BoundingBox;
			Render::Draw::Buff	m_DrawBuff;
		};
	}
}
#endif // AirMesh_h__