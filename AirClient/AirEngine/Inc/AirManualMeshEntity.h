#ifndef AirManualMeshEntity_h__
#define AirManualMeshEntity_h__

#include "AirStaticMesh.h"
#include "AirRenderVertexDeclare.h"

namespace	Air{
	namespace	Client{
		class	ManualMeshEntity	:	
			public	IProduct,
			public	Renderable,
			public	MovableObject{
		public:
			struct Info{
				U32						uiVertexSize;
				U32						uiVertexCount;
				U32						uiFaceCount;
				VertexDeclare::Info		vdInfo;
				AString					strMaterial;
			};
		public:
			ManualMeshEntity(CAString& strName,Info* pInfo);

			virtual	U1	Create();
			virtual	U1	Destroy();

			virtual	void		ProcessRenderObject(U32	uiPhaseFlag);
			virtual	Matrix*		GetWorldMatrix();

			void				UpdateVB(const void* pVB,U32	uiVertexCount);
			void				UpdateIB(const void* pIB,U32	uiFaceCount);

			void				SetPrimitiveType(Render::Draw::enumPrimitiveType	t);

			inline	U32			GetVertexCount()const
			{
				return	m_Info.uiVertexCount;
			};
			inline	U32			GetFaceCount()const
			{
				return	m_Info.uiFaceCount;
			};
		protected:
			Info		m_Info;
		};
	}
}
#endif // AirMeshEntity_h__