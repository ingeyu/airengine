#include "AirNavMesh.h"

namespace	Air{

	struct VB{
		Float3 vPos;
		Float3 vNormal;
		Float2 vTexCoord;
		Float3 vTangent;
	};

	NavMesh::NavMesh( CAString& strName,Info* pInfo ):Common::IProduct(strName),m_Tree(NULL)
	{
		m_uiNumVertex	=	NULL;
		m_uiNumFace		=	NULL;
		pVB				=	NULL;
		pIB				=	NULL;
		if(pInfo!=NULL){
			if(pInfo->pData!=NULL	&& pInfo->uiSize!=0){
				m_MeshData.ReSize(pInfo->uiSize);
				memcpy(m_MeshData.buff,pInfo->pData,pInfo->uiSize);
			}
		}
	}

	NavMesh::~NavMesh()
	{

	}

	Air::U1 NavMesh::Create()
	{
		if(m_MeshData.IsNull())
			return	false;
		int	version	=	*(int*)m_MeshData.buff;
		if(version	==	'0EMA'){
			LoadAME0();
		}
		BuildElement();
		return true;
	}

	Air::U1 NavMesh::Destroy()
	{
		for(U32 i=0;i<m_uiNumFace;i++){
			delete m_vecTriangle[i];
			m_vecTriangle[i]=NULL;
		}
		m_vecTriangle.clear();

		m_MeshData.Clear();
		return true;
	}

	Air::U1 NavMesh::LoadAME0()
	{
		U8*	p	=	m_MeshData.buff;
		p+=sizeof(U32);
		m_BoundingBox				=	*(BoundingBox*)p;		p+=sizeof(BoundingBox);
		U32	uiMaterialNameLength	=	*(U32*)p;				p+=sizeof(U32);
		p+=uiMaterialNameLength;
		U32	uiVBSize				=	(*(U32*)p);				p+=sizeof(U32);
		m_uiNumVertex				=	uiVBSize/44;
		pVB							=	p;						p+=uiVBSize;
		U32	uiIBSize				=	(*(U32*)p);				p+=sizeof(U32);
		m_uiNumFace					=	uiIBSize/12;
		pIB							=	p;
		return	true;
	}

	Air::U1 NavMesh::BuildElement()
	{

		VB*		pVBuffer	=	(VB*)pVB;
		U32*	pIBuffer	=	(U32*)pIB;
		m_vecTriangle.resize(m_uiNumFace);
		for(U32 i=0;i<m_uiNumFace;i++){
			U32	idx[3];
			for(U32	j=0;j<3;j++){
				idx[j]	=	pIBuffer[i*3+j	];
			}
			
			m_vecTriangle[i]	=	new	TriangleElement(pVBuffer[	idx[0	]	].vPos,
														pVBuffer[	idx[1	]	].vPos,
														pVBuffer[	idx[2	]	].vPos,
														i);
			TriangleElement*	pTriangle	=	(TriangleElement*)m_vecTriangle[i];

			pTriangle->m_Edge[0]	=	AddEdge(idx[0],idx[1],pTriangle);
			pTriangle->m_Edge[1]	=	AddEdge(idx[1],idx[2],pTriangle);
			pTriangle->m_Edge[2]	=	AddEdge(idx[2],idx[0],pTriangle);
		}
		m_Tree.m_BoundingBox	=	m_BoundingBox;
		m_Tree.Build(m_vecTriangle);

		return true;
	}
	U1	RayCastTriangleFunc(const Ray&	ray,TreeElement* pTriangle,float*	pOutDistance,void* pUserData){
		NavMesh* pMesh	=	(NavMesh*)pUserData;
		VB*		pVBuffer	=	(VB*)pMesh->GetVB();
		U32*	pIBuffer	=	(U32*)pMesh->GetIB();

		U32		uiFace		=	pTriangle->m_pData;
		float fDistance		=	999999.0f;

		if(ray.Intersect(	
			pVBuffer[	pIBuffer[uiFace*3	]	].vPos,
			pVBuffer[	pIBuffer[uiFace*3+1	]	].vPos,
			pVBuffer[	pIBuffer[uiFace*3+2	]	].vPos,
			&fDistance))
		{
			if(pOutDistance!=NULL){
				*pOutDistance	=	fDistance;
			}
			return true;
		}

		return false;
	}

	U1	FindTriangleElementFunc(const Float3& vPos,TreeElement* pTriangle,void* pUserData){
		NavMesh* pMesh	=	(NavMesh*)pUserData;
		VB*		pVBuffer	=	(VB*)pMesh->GetVB();
		U32*	pIBuffer	=	(U32*)pMesh->GetIB();

		U32		uiFace		=	pTriangle->m_pData;

		Float3 v[3];
		for(U32 i=0;i<3;i++){
			v[i]	=	pVBuffer[	pIBuffer[uiFace*3+i	]	].vPos;
		}

		S32	iCount	=	0;
		
		for(U32	i=0;i<3;i++){
			U32	uiNext	=	(i+1)%3;
			Float3	vDir		=	(v[uiNext]	-	v[i]).NormalizeCopy();
			Float3	vPosDir		=	(vPos	-	v[i]).NormalizeCopy();
			Float3	vCross		=	vPosDir.Cross(vDir);
			iCount	+=	vCross.z>0.0f?1:-1;
		}

		if(iCount<0){
			iCount	=	-iCount;
		}
		return iCount==3;

	};

	TreeElement* NavMesh::RayCast( const Ray& ray,float* pOutDistance /*= NULL*/ )
	{
		return m_Tree.RayCast(ray,RayCastTriangleFunc,(void*)this,pOutDistance);
	}

	Air::U1 NavMesh::FindPath( const Float3& vBegin,const Float3& vEnd,ElementList* lstElement /*= NULL*/ )
	{
		TreeElement*	pBeginElement	=	m_Tree.FindElement(vBegin,FindTriangleElementFunc,this);
		TreeElement*	pEndElement		=	m_Tree.FindElement(vEnd,FindTriangleElementFunc,this);

		if(pBeginElement	==	NULL	||
			pEndElement		==	NULL)
		{
			return false;
		}

		VB* pVBuffer	=	(VB*)GetVB();
		
		//标记所有为-1
		MaskVector	vecMask;
		vecMask.reserve(m_vecEdge.size());
		for(U32 i=0;i<m_vecEdge.size();i++){
			vecMask[i]	=	999999.0f;
		}
		U1	bFinded	=	false;
		Edge* pEndEdge =	NULL;
		

		for(U32 i=0;i<3;i++){
			TriangleElement* pTriangle	=	(TriangleElement*)pBeginElement;
			Edge*	pEdge	=	&m_vecEdge[ pTriangle->m_Edge[i]	];

			Float3	vCenter	=	(pVBuffer[pEdge->vertexIdx[0]].vPos + pVBuffer[pEdge->vertexIdx[1]].vPos)*0.5f;
			float fDistance	=	vCenter.Distance(vBegin);
			//距离Mask
			vecMask[pEdge->uiIndex]	=	fDistance;

			if(Find(pEdge,(TriangleElement*)pEndElement,vecMask,fDistance,pEndEdge)){
				bFinded	=	true;
				break;
			};
		}
		if(bFinded){


		}

		//Find(pBeginElement,)

		return bFinded;
	}

	U32 NavMesh::AddEdge( U32 v0,U32 v1,TriangleElement* pTriangle )
	{
		U32	uiIndex	=	0;
		Edge*	pEdge	=	NULL;
		U32	uiHash	=	v0^v1;
		EdgeMap::iterator	i	=	m_mapEdge.find(uiHash);
		if(i!=m_mapEdge.end()){
			pEdge	=	i->second;
			if(pEdge->pTriangle[0]==NULL){
				pEdge->pTriangle[0]	=	pTriangle;
			}else	if(pEdge->pTriangle[1]==NULL){
				pEdge->pTriangle[1]	=	pTriangle;
			}
			uiIndex	=	pEdge->uiIndex;
		}else{
			m_vecEdge.push_back(Edge());
			uiIndex	=	m_vecEdge.size()-1;
			pEdge	=	&m_vecEdge[uiIndex];
			pEdge->uiIndex	=	uiIndex;
			pEdge->pTriangle[0]	=	pTriangle;
			m_mapEdge[uiHash]	=	pEdge;
		}
		return uiIndex;
	}

	U1 NavMesh::Find( Edge* pEdge,TriangleElement* pEnd,MaskVector& vecMask,float fLastDistance,Edge*& pEndEdge )
	{
		if(pEdge==NULL	||	pEnd==NULL)
			return false;
		//if(pEdge	==	pEnd)
		//	return true;

		U32	uiNeighbor	=	0;
		Edge*	pNeighbor[4];
		for(U32	i=0;i<2;i++){
			TriangleElement*	pTri	=	pEdge->pTriangle[i];
			if(pTri	==	pEnd){
				pEndEdge	=	pEdge;
				return true;
			}
			if(pTri!=NULL){
				for(U32 j=0;j<3;j++){
					U32	uiIndex	=	pTri->m_Edge[j];
					if(	uiIndex				!=	pEdge->uiIndex	&&
						vecMask[uiIndex]	>	900000.0f)
					{
						Edge*	pEdge	=	&m_vecEdge[uiIndex];

					}
				}
			}
		}


	}

}