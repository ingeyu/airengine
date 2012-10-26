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
		U32	vertexIdx[2];
		TriangleElement*	pTriangle[2];
		U32					uiIndex;
		Float3				vCenter;
	};
	typedef	std::hash_map<U32,U32>			EdgeMap;
	typedef	std::vector<Edge>				EdgeVector;
	typedef	std::vector<Edge*>				EdgePtrVector;

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

		U1					FindPath(const Float3&	vBegin,const Float3& vEnd,WalkPath* pPath	=	NULL);
	protected:
		U1			LoadAME0();
		U1			BuildElement();
		U32			AddEdge(U32	v0,U32	v1,TriangleElement* pTriangle);

		U1			Find(EdgePtrVector& vecEdge,EdgePtrVector& tempEdge,TriangleElement* pEnd,MaskVector& vecMask,Edge*& pEndEdge);
		U1			BuildEdgePath(TriangleElement* pBegin,TriangleElement* pEnd,MaskVector& vecWeight,WalkMask& vecWalked,EdgePtrVector& outPath);
		U1			OptimizePath(const Float3& vBegin,const Float3& vEnd,EdgePtrVector& edgePath,WalkPath& outPath);
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
	};
}
#endif // AirNavMesh_h__
