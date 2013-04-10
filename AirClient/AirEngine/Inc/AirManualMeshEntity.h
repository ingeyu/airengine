#ifndef AirManualMeshEntity_h__
#define AirManualMeshEntity_h__

#include "AirStaticMesh.h"
#include "AirRenderVertexDeclare.h"

namespace	Air{
	namespace	Engine{
		class	ManualMeshEntity	:	
			public	IProduct,
			public	Renderable,
			public	MovableObject{
		public:
			static AString	ProductTypeName;
			struct Info{
				U32									uiVertexSize;
				U32									uiVertexCount;
				U32									uiIndexCount;
				VertexDeclare::Info					vdInfo;
				AString								strMaterial;
				Render::Draw::enumPrimitiveType		enDrawType;
			};
		public:
			ManualMeshEntity(CAString& strName,Info* pInfo);

			virtual	U1	Create();
			virtual	U1	Destroy();

			virtual	void		ProcessRenderObject(U32	uiPhaseFlag);
			virtual	Matrix*		GetWorldMatrix();

			void				UpdateVB(const void* pVB,U32	uiVertexCount);
			void				UpdateIB(const void* pIB,U32	uiIndexCount);

			void				SetPrimitiveType(Render::Draw::enumPrimitiveType	t);

			inline	U32			GetVertexCount()const
			{
				return	m_Info.uiVertexCount;
			};
			inline	U32			GetIndexCount()const
			{
				return	m_Info.uiIndexCount;
			};
			void		SetIndexCount(U32 uiCount);
		protected:
			Info		m_Info;
		};
	}
}
#endif // AirMeshEntity_h__