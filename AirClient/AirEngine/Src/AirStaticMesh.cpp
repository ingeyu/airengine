#include "AirStaticMesh.h"
#include "AirRenderSystem.h"
#include "AirEngineMaterial.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceResourceSystem.h"

namespace	Air{
	namespace	Engine{

		AString StaticMesh::ProductTypeName	=	"StaticMesh";
		StaticMesh::StaticMesh( CAString& strName ):IProduct(strName)
		{

			m_uiNumVertex	=	NULL;
			m_uiNumFace		=	NULL;
			pVB				=	NULL;
			pIB				=	NULL;
		}

		Air::U1 StaticMesh::Create()
		{
			Resource::ISystem*	pResSys	=	GetGlobalSetting().m_pResourceSystem;
			pResSys->Find(m_strProductName,m_MeshData);

			U8*	pData	=	m_MeshData.buff;
			U32	uiSize	=	m_MeshData.size;
			if(pData!=NULL&&uiSize!=0){
				int	version	=	*(int*)pData;
				if(version	==	'0EMA'){
					LoadAME0();

					//memcpy(m_Bound,)
				}
				Render::System*	pSys	=	Render::System::GetSingleton();
				Buffer::Info	vbInfo;
				vbInfo.SetVertexBuffer(m_uiNumVertex,44);
				vbInfo.InitData			=	pVB;
				m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer>(m_strProductName+"VB",&vbInfo);

				Buffer::Info	ibInfo;
				ibInfo.SetIndexBuffer32(m_uiNumFace*3);
				ibInfo.InitData			=	pIB;
				m_DrawBuff.m_pIndexBuff	=	pSys->CreateProduct<Buffer>(m_strProductName+"IB",&ibInfo);

				Render::Vertex::IDeclare::Info	vdInfo;
				vdInfo.SetDeclPNTT();
				m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare>("PNTT",&vdInfo);

				m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;
				m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
				m_DrawBuff.m_DrawOption.m_uiVertexCount	=	m_uiNumVertex;
				m_DrawBuff.m_DrawOption.m_uiIndexCount	=	m_uiNumFace*3;
				
				return	true;
			}

			return	true;
		}

		Air::U1 StaticMesh::LoadAME0()
		{
			U8*	p	=	m_MeshData.buff;
			p+=sizeof(U32);
			m_BoundingBox				=	*(BoundingBox*)p;		p+=sizeof(BoundingBox);
			U32	uiMaterialNameLength	=	0;
			uiMaterialNameLength		=	*(U32*)p;				p+=sizeof(U32);
			m_strMaterialName.resize(uiMaterialNameLength);
			memcpy(&m_strMaterialName[0],p,uiMaterialNameLength);	p+=uiMaterialNameLength;
			U32	uiVBSize				=	(*(U32*)p);				p+=sizeof(U32);
			m_uiNumVertex				=	uiVBSize/44;
			pVB							=	p;						p+=uiVBSize;
			U32	uiIBSize				=	(*(U32*)p);				p+=sizeof(U32);
			m_uiNumFace					=	uiIBSize/12;
			pIB							=	p;
			return	true;
		}

		Air::U1 StaticMesh::Destroy()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pIndexBuff);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);

			m_MeshData.ReSize(0);

			m_uiNumVertex	=	NULL;
			m_uiNumFace		=	NULL;
			pVB				=	NULL;
			pIB				=	NULL;
			return	true;
		}

		const BoundingBox& StaticMesh::GetBoundingBox() const
		{
			return m_BoundingBox;
		}

		const Render::Draw::Buff& StaticMesh::GetDrawBuffer() const
		{
			return	m_DrawBuff;
		}

		Air::U1 StaticMesh::RayCast( const Ray& ray ,float* pOutDistance /*= NULL*/ )
		{
			U32*			pIndex			=	(U32*)GetIB();
			U32				uiFaceCount		=	GetFaceCount();
			Render::PNTT*	pVB				=	(Render::PNTT*)GetVB();
			U32				uiVertexCount	=	GetVertexCount();

			float	fDistance	=	999999.0f;
			U1		bHit		=	false;

			for(U32	i=0;i<uiFaceCount;i++){

				Float3&	v0	=	pVB	[pIndex[i*3]	].Position;
				Float3&	v1	=	pVB	[pIndex[i*3+1]	].Position;
				Float3&	v2	=	pVB	[pIndex[i*3+2]	].Position;
				float	fDis	=	-1.0f;
				if(ray.Intersect(v0,v1,v2,&fDis)){
					if(fDis	<	fDistance){
						fDistance	=	fDis;
					}
					bHit	=	true;
				}
			}
			
			if(pOutDistance!=NULL){
				*pOutDistance	=	fDistance;
			}

			return	bHit;
		}

		void	AddToSVO(const Float3& pos,std::vector<U32>& svo,U32& uiSVOSize,U32 iEdgeSize){
			U32 iMask = iEdgeSize;
			U32 uiLOOP=0;
			for(U32 i=0;i<32;i++){
				if((1<<i) >= iMask){
					uiLOOP	=	i;
					break;
				}
			}
			U32 x		=	pos.x;
			U32 y		=	pos.y;
			U32	z		=	pos.z;

			U32 uiOffset=0;
			for(U32 i=0;i<uiLOOP;i++){
				int ishift	=	i+1;
				U32 uiTempMask=iMask>>ishift;
				U32	uileftshr	=	uiLOOP-ishift;
				U32 idx = ((x&uiTempMask)>>uileftshr)*4;
				idx		+=((y&uiTempMask)>>uileftshr)*2;
				idx		+=((z&uiTempMask)>>uileftshr);
				U32&	uiSVO	=	svo[uiOffset+idx];
				if(i==uiLOOP-1){
					uiSVO	=	0XFFFFFFFF;
					break;
				}else{
					if(uiSVO==0){
						uiSVO	=	uiSVOSize;
						uiSVOSize+=8;
					}
					uiOffset	=	uiSVO;
					
				}
			}
		}

		Air::U1 StaticMesh::BuildSVO( const Matrix& matWorld,std::vector<U32>& SVO)
		{
			std::vector<Float3>	vecPos;
			vecPos.resize(m_uiNumVertex);
			U32*			pIndex			=	(U32*)GetIB();
			Render::PNTT*	pVB				=	(Render::PNTT*)GetVB();
			for(U32 i=0;i<m_uiNumVertex;i++){
				vecPos[i]	=	matWorld*pVB[i].Position;
			}

			Matrix matWorldInv	=	matWorld;
			matWorldInv.Inverse();
			BoundingBox	worldBound = m_BoundingBox.Transform(matWorld);
			Float3 vFloorMin	=	Float3(floor(worldBound.vMin.x),floor(worldBound.vMin.y),floor(worldBound.vMin.z));
			Float3	vBoundSize	=	worldBound.vMax	-	vFloorMin;
			float fEdgeSize	=	vBoundSize.x;
			if(vBoundSize.y > fEdgeSize){
				fEdgeSize	=	vBoundSize.y;
			}
			if(vBoundSize.z	>	fEdgeSize){
				fEdgeSize	=	vBoundSize.z;
			}
			U32 uiCmp[]={
				1,2,4,8,16,32,64,128,256,512,1024,2048,4096
			};
			int iEdgeSize	=	fEdgeSize;
			for(U32 i=0;i<13;i++){
				if(uiCmp[i]	>iEdgeSize){
					iEdgeSize	=	uiCmp[i];
					break;
				}
			}
			std::vector<U32>	vecBuffer;
			vecBuffer.resize(1048576);
			U32 uiTempSize=8;

			Float3 vDirArray[3]={
				Float3(1,0,0),
				Float3(0,1,0),
				Float3(0,0,1)
			};

			for(U32 uiFace =0;uiFace<3;uiFace++){
				Ray r;
				r.m_vDirection	=	vDirArray[uiFace];
				
				for(U32 i=0;i<iEdgeSize;i++){
					for(U32 j=0;j<iEdgeSize;j++){
						switch(uiFace){
							case 0:{
								r.m_vStart	=	vFloorMin+Float3(0,i+0.5,j+0.5);
								   }break;
							case 1:{
								r.m_vStart	=	vFloorMin+Float3(i+0.5,0,j+0.5);
								   }break;
							case 2:{
								r.m_vStart	=	vFloorMin+Float3(i+0.5,j+0.5,0);
								   }break;
						}
						float fDistance	=	10000.0f;
						for(U32	i=0;i<m_uiNumFace;i++){

							Float3&	v0	=	vecPos	[pIndex[i*3]	];
							Float3&	v1	=	vecPos	[pIndex[i*3+1]	];
							Float3&	v2	=	vecPos	[pIndex[i*3+2]	];
							float	fDis	=	-1.0f;
							if(r.Intersect(v0,v1,v2,&fDis)){
								Float3 pos	=	r.m_vStart+r.m_vDirection*fDis - vFloorMin;
								AddToSVO(pos,vecBuffer,uiTempSize,iEdgeSize);
							}
							if(r.Intersect(v2,v1,v0,&fDis)){
								Float3 pos	=	r.m_vStart+r.m_vDirection*fDis - vFloorMin;
								AddToSVO(pos,vecBuffer,uiTempSize,iEdgeSize);
							}
						}
						
					}
				}
			}

			SVO.resize(uiTempSize);
			memcpy(&SVO[0],&vecBuffer[0],uiTempSize*sizeof(U32));

			return true;
		}

	}
}