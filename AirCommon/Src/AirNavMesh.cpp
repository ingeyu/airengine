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

	U32 AddVertex(const Float3& pos,std::vector<Float3>& vecVB){
		U32 uiSize = vecVB.size();
		for(U32 j=0;j<uiSize;j++){
			Float3&	p	= vecVB[j];
			if(pos.Distance(p)	<	0.0001f)
			{
				return j;
			}
		}
		vecVB.push_back(pos);
		return uiSize;
	}

	Air::U1 NavMesh::Create()
	{
		if(m_MeshData.IsNull())
			return	false;
		int	version	=	*(int*)m_MeshData.buff;
		if(version	==	'0EMA'){
			LoadAME0();
		}
		VB* pVBuffer	= (VB*)pVB;
		U32* pIBuffer	=	(U32*)pIB;
		m_IB.resize(m_uiNumFace*3);
		memcpy(&m_IB[0],pIB,sizeof(U32)*m_uiNumFace*3);

		for(U32 i=0;i<m_uiNumFace;i++){
			for(U32 j=0;j<3;j++){
				U32& idx	=	m_IB[i*3+j];
				idx			=	AddVertex(pVBuffer[idx],m_VB);
			}
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


		m_vecTriangle.resize(m_uiNumFace);
		for(U32 i=0;i<m_uiNumFace;i++){
			U32	idx[3];
			for(U32	j=0;j<3;j++){
				idx[j]	=	m_IB[i*3+j	];
			}
			
			m_vecTriangle[i]	=	new	TriangleElement(m_VB[	idx[0	]	],
														m_VB[	idx[1	]	],
														m_VB[	idx[2	]	],
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
		Float3*		pVBuffer	=	(Float3*)pMesh->GetVB();
		U32*		pIBuffer	=	(U32*)pMesh->GetIB();

		U32		uiFace		=	pTriangle->m_pData;
		float fDistance		=	999999.0f;

		if(ray.Intersect(	
			pVBuffer[	pIBuffer[uiFace*3	]	],
			pVBuffer[	pIBuffer[uiFace*3+1	]	],
			pVBuffer[	pIBuffer[uiFace*3+2	]	],
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
		Float3*		pVBuffer	=	(Float3*)pMesh->GetVB();
		U32*		pIBuffer	=	(U32*)pMesh->GetIB();

		U32		uiFace		=	pTriangle->m_pData;

		Float3 v[3];
		for(U32 i=0;i<3;i++){
			v[i]	=	pVBuffer[	pIBuffer[uiFace*3+i	]	];
		}

		S32	iCount	=	0;

		Float3 vTempDir[3];
		
		for(U32	i=0;i<3;i++){
			U32	uiNext	=	(i+1)%3;
			Float3	vDir		=	(v[uiNext]	-	v[i]).NormalizeCopy();
			Float3	vPosDir		=	(vPos	-	v[i]).NormalizeCopy();
			vTempDir[i]		=	vPosDir.Cross(vDir);
		}

		float	fDirValue	=	(vTempDir[0].Dot(vTempDir[1])	*	vTempDir[1].Dot(vTempDir[2]));

		return fDirValue	>=	0.0f;

	};

	TreeElement* NavMesh::RayCast( const Ray& ray,float* pOutDistance /*= NULL*/ )
	{
		return m_Tree.RayCast(ray,RayCastTriangleFunc,(void*)this,pOutDistance);
	}

	Air::U1 NavMesh::FindPath( TreeElement*	pBeginElement,const Float3& vBegin,const Float3& vEnd,WalkPath* pPath /*= NULL*/)
	{
		//TreeElement*	pBeginElement	=	m_Tree.FindElement(vBegin,FindTriangleElementFunc,this);
		TreeElement*	pEndElement		=	m_Tree.FindElement(vEnd,FindTriangleElementFunc,this);

		if(pBeginElement	==	NULL	||
			pEndElement		==	NULL)
		{
			return false;
		}
		m_DebugIndex.clear();
		AddDebugTriangle((TriangleElement*)pBeginElement);

		//Float3* pVBuffer	=	(Float3*)GetVB();
		
		//标记所有为-1
		MaskVector	vecMask;
		//vecMask.resize(m_vecEdge.size());
		for(U32 i=0;i<m_vecEdge.size();i++){
			m_vecEdge[i].weight	=	-1.0f;
		}
		U1	bFinded	=	false;
		Edge* pEndEdge =	NULL;

		EdgeTriangleVector	vecEdge;
		EdgeTriangleVector	vecTempEdge;

		for(U32 i=0;i<3;i++){
			TriangleElement* pTriangle	=	(TriangleElement*)pBeginElement;
			Edge*	pEdge	=	&m_vecEdge[ pTriangle->m_Edge[i]	];

			float fDistance	=	pEdge->vCenter.Distance(vBegin);
			//距离Mask
			//vecMask[pEdge->uiIndex]	=	fDistance;
			pEdge->weight				=	fDistance;
			EdgeTriangle	etri;
			etri.pEdge		=	pEdge;
			etri.pTriangle	=	pEdge->GetNeighbor((TriangleElement*)pBeginElement);
			if(etri.pTriangle!=NULL){
				vecEdge.push_back(etri);
				AddDebugTriangle((TriangleElement*)etri.pTriangle);
			}
			

		}

		if(Find(vecEdge,vecTempEdge,(TriangleElement*)pEndElement,vecMask,pEndEdge)){
			//只是检测是否可以到达 不需要生成具体的路径
			if(pPath==NULL){
				return true;
			}
			//WalkMask	vecWalked;
			//vecWalked.resize(vecMask.size());
			////生成边路径
			//EdgePtrVector	vecPath;
			//if(BuildEdgePath((TriangleElement*)pBeginElement,(TriangleElement*)pEndElement,vecMask,vecWalked,vecPath)){
			//	//WalkPath	path;
			//	pPath->push_back(vBegin);
			//	if(OptimizePath(vBegin,vEnd,vecPath,*pPath)){
			//		pPath->push_back(vEnd);
			//		return true;
			//	}else{
			//		pPath->clear();
			//	}
			//}
			OutputDebugStringA("Path Finded!\n");
		};

		return false;
	}

	U32 NavMesh::AddEdge( U32 v0,U32 v1,TriangleElement* pTriangle )
	{

		U32	uiIndex	=	0;
		Edge*	pEdge	=	NULL;
		U32	uiHash	=	(v0<<16) | v1;
		if(v1<v0){
			uiHash	=	(v1<<16)|v0;
		}
		EdgeMap::iterator	i	=	m_mapEdge.find(uiHash);
		if(i!=m_mapEdge.end()){
			uiIndex	=	i->second;
			pEdge	=	&m_vecEdge[uiIndex];
			if(pEdge->pTriangle[0]==NULL){
				pEdge->pTriangle[0]	=	pTriangle;
			}else	if(pEdge->pTriangle[1]==NULL && pEdge->pTriangle[0] != pTriangle){
				pEdge->pTriangle[1]	=	pTriangle;
			}
		}else{
			m_vecEdge.push_back(Edge());
			uiIndex	=	m_vecEdge.size()-1;
			pEdge	=	&m_vecEdge[uiIndex];
			pEdge->vertexIdx[0]	=	v0;
			pEdge->vertexIdx[1]	=	v1;
			pEdge->uiIndex	=	uiIndex;
			pEdge->pTriangle[0]	=	pTriangle;
			pEdge->vCenter		=	(m_VB[v0] + m_VB[v1])*0.5f;
			m_mapEdge[uiHash]	=	uiIndex;
			m_EDGEVB.push_back(pEdge->vCenter);
		}
		return uiIndex;
	}

	struct EdgeWeight{
		EdgeWeight(){
			for(int i=0;i<4;i++){
				pEdge[i]	=	NULL;
				fWeight[i]	=	-1.0f;
			}
			uiCount	=	0;
		};
		void	Add(Edge* edge,float w){
			for(U32 i=0;i<uiCount;i++){
				if(edge==pEdge[i])
					return;
			}
			pEdge[uiCount]		=	edge;
			fWeight[uiCount]	=	w;
			uiCount++;
		};
		Edge* pEdge[4];
		float fWeight[4];
		U32	  uiCount;
	};

	U1 NavMesh::Find( EdgeTriangleVector& vecEdge,EdgeTriangleVector& tempEdge,TriangleElement* pEnd,MaskVector& vecMask,Edge*& pEndEdge )
	{
		if(vecEdge.empty()	||	pEnd==NULL)
			return false;
		tempEdge	=	vecEdge;
		vecEdge.clear();


		std::map<Edge*,EdgeWeight>	mapNextEdge;
		//vecNextEdge.resize(vecEdge.size());

		unsigned int	uiSize	=	tempEdge.size();
		for(U32	i=0;i<uiSize;i++){
			EdgeTriangle&	etri	=	tempEdge[i];
			if(etri.pEdge==NULL)
				continue;

			mapNextEdge[etri.pEdge]	=	EdgeWeight();
			std::map<Edge*,EdgeWeight>::iterator	itr	=	mapNextEdge.find(etri.pEdge);
			EdgeWeight& vecWeight	=	itr->second;

			float fLastDistance	=	etri.pEdge->weight;//vecMask[pEdge->uiIndex];

			TriangleElement* pTri	=	etri.pTriangle;

				if(pTri	==	pEnd){
					pEndEdge	=	etri.pEdge;

					return true;
				}
				for(U32 k=0;k<3;k++){
					Edge*	pNextEdge	=	&m_vecEdge[pTri->m_Edge[k]];
					if(pNextEdge	==	etri.pEdge)
						continue;
					if(pNextEdge->weight	<0.0f){
						float	fTempWeight	=	fLastDistance	+	pNextEdge->vCenter.Distance(etri.pEdge->vCenter);
						EdgeTriangle	edgetri;
						edgetri.pEdge		=	pNextEdge;
						edgetri.pTriangle	=	pNextEdge->GetNeighbor(pTri);
						if(edgetri.pTriangle!=NULL){
							vecEdge.push_back(edgetri);
							AddDebugTriangle(edgetri.pTriangle);
						}
						vecWeight.Add(pNextEdge,fTempWeight);
					}
				}
			
		}

		std::map<Edge*,EdgeWeight>::iterator	itr	=	mapNextEdge.begin();
		for(;itr!=mapNextEdge.end();itr++){
			Edge*	pSrcEdge	=	itr->first;
			EdgeWeight& vec	=	itr->second;

			for(U32 i=0;i<vec.uiCount;i++){

				float& weight	=	vec.pEdge[i]->weight;//vecMask[vec.pEdge[i]->uiIndex];
				float w			=	vec.fWeight[i];
				if(weight	<	0	){
					weight	=	w;
				}else if(w	<	weight){
					weight	=	w;
				}
			}
		}

		tempEdge.clear();
		return Find(vecEdge,tempEdge,pEnd,vecMask,pEndEdge);
	}

	Air::U1 NavMesh::BuildEdgePath( TriangleElement* pBegin,TriangleElement* pEnd,MaskVector& vecWeight,WalkMask& vecWalked,EdgePtrVector& outPath )
	{
		float weight	=	99999.0f;
		U32		uiIndex	=	0xffffffff;
		for(U32 i=0;i<3;i++){
			U32	idx	=	pEnd->m_Edge[i];
			//判断这条边 是否已经被遍历
			if(vecWalked[idx]==1)
				continue;
			float w	=	vecWeight[idx];
			//判断权重值 W必须是计算过的边 然后取权重最小的 
			if(w	<	weight	&& w > 0.0f){
				weight	=	w;
				uiIndex	=	idx;
			}
		}
		if(uiIndex==0xffffffff){
			return false;
		}
		Edge* pEdge	=	&m_vecEdge[uiIndex];
		vecWalked[uiIndex]	=	1;
		//存到 路径列表中
		outPath.push_back(pEdge);
		TriangleElement* pNextTri	=	NULL;

		for(U32 i=0;i<2;i++){
			TriangleElement* pTri	=	pEdge->pTriangle[i];
			if(pTri!=NULL && pTri!=pEnd){
				pNextTri	=	pTri;
				break;
			}
		}

		if(pNextTri!=NULL){

			if(pNextTri	==	pBegin){
				return true;
			}else{
				return	BuildEdgePath(pBegin,pNextTri,vecWeight,vecWalked,outPath);
			}
		}

		return false;
	}

	Air::U1 NavMesh::OptimizePath( const Float3& vBegin,const Float3& vEnd,EdgePtrVector& edgePath,WalkPath& outPath )
	{
		U32 uiSize	=	edgePath.size();
		for(U32 i=0;i<uiSize;i++){
			outPath.push_back(edgePath[i]->vCenter);
		}
		return true;
	}

	void NavMesh::AddDebugTriangle( TriangleElement* pTriangle )
	{
		if(pTriangle==NULL)
			return;
		U32 uiFaceIndex	=	pTriangle->m_pData;

		U32* pIBuffer	=	(U32*)GetIB();

		for(U32 i=0;i<3;i++){
			m_DebugIndex.push_back(pIBuffer[uiFaceIndex*3+i]);
		}
	}

}