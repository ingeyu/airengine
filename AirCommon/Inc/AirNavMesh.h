#ifndef AirNavMesh_h__
#define AirNavMesh_h__

#include "AirCommonHeader.h"
#include "AirOctree.h"
#include "AirCommonProduct.h"
#include "AirCommonFile.h"

namespace	Air{
	class TriangleElement;
	struct Edge{
		Edge(){
			vertexIdx[0]	=	0;
			vertexIdx[1]	=	0;
			pTriangle[0]	=	0;
			pTriangle[1]	=	0;
			uiIndex			=	0;

		};
		TriangleElement*	GetNeighbor(TriangleElement* p){
			if(p==NULL){
				return NULL;
			}
			for(U32 i=0;i<2;i++){
				if(pTriangle[i]!=p&&pTriangle[i]!=NULL){
					return pTriangle[i];
				}
			}
			return NULL;
		};
		U32	vertexIdx[2];
		TriangleElement*	pTriangle[2];
		U32					uiIndex;
		Float3				vCenter;
		float				weight;
	};
	typedef	std::hash_map<U32,U32>			EdgeMap;
	typedef	std::vector<Edge>				EdgeVector;
	typedef	std::vector<Edge*>				EdgePtrVector;

	struct EdgeTriangle{
		Edge*				pEdge;
		TriangleElement*	pTriangle;
	};
	typedef std::vector<EdgeTriangle>	EdgeTriangleVector;

	class	COMMON_EXPORT	TriangleElement	:	public	TreeElement{
	public:
		TriangleElement(const Float3& v0,const Float3&v1,const Float3& v2,U32	uiFaceIndex){
			m_Bound.BuildFrom3Point(v0,v1,v2);
			m_pData	=	uiFaceIndex;
			m_Edge[0]	=	0;
			m_Edge[1]	=	0;	
			m_Edge[2]	=	0;	
		}
		virtual	BoundingBox*	GetBoundingBox(){return	&m_Bound;};
		BoundingBox	m_Bound;
		U32		m_Edge[3];
	};

	class Octree;
	typedef std::vector<float>	MaskVector;
	typedef std::vector<Float3>	WalkPath;
	typedef std::vector<U8>		WalkMask;
	typedef std::vector<U32>	DebugTriangleIndex;

	class	COMMON_EXPORT	NavMesh	:	public	Common::IProduct{
	public:
		struct Info{
			void*	pData;
			U32		uiSize;
		};
	public:
		NavMesh(CAString& strName,Info* pInfo);

		virtual	~NavMesh();

		virtual	U1	Create();
		virtual	U1	Destroy();

		TreeElement*		RayCast(const Ray& ray,float* pOutDistance	=	NULL);
		void*				GetVB(){return &m_VB[0];};
		void*				GetIB(){return &m_IB[0];};
		Float3*				GetEdgeVB(){return &m_EDGEVB[0];};
		//基于广度优先 没有任何优化
		U1					FindPath(TreeElement*	pBeginElement,const Float3& vBegin,const Float3& vEnd,WalkPath* pPath	=	NULL);

		DebugTriangleIndex&	GetDebugIndex(){return m_DebugIndex;};
	protected:
		U1			LoadAME0();
		U1			BuildElement();
		U32			AddEdge(U32	v0,U32	v1,TriangleElement* pTriangle);

		U1			Find(EdgeTriangleVector& vecEdge,EdgeTriangleVector& tempEdge,TriangleElement* pEnd,MaskVector& vecMask,Edge*& pEndEdge);
		U1			BuildEdgePath(TriangleElement* pBegin,TriangleElement* pEnd,MaskVector& vecWeight,WalkMask& vecWalked,EdgePtrVector& outPath);
		U1			OptimizePath(const Float3& vBegin,const Float3& vEnd,EdgePtrVector& edgePath,WalkPath& outPath);

		void		AddDebugTriangle(TriangleElement* pTriangle);
		void		AddDebugLine(Edge* pEdge0,Edge* pEdge1);

		U32			m_uiNumVertex;
		U32			m_uiNumFace;
		void*		pVB;
		void*		pIB;

		Common::Data	m_MeshData;
		BoundingBox		m_BoundingBox;
		ElementVector	m_vecTriangle;

		RelaxBinaryTree	m_Tree;

		EdgeVector		m_vecEdge;
		EdgeMap			m_mapEdge;
		std::vector<Float3>		m_VB;
		std::vector<U32>		m_IB;
		std::vector<Float3>		m_EDGEVB;

		DebugTriangleIndex	m_DebugIndex;
	};
}
#endif // AirNavMesh_h__
