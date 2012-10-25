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
	};
	typedef	std::hash_map<U32,Edge*>		EdgeMap;
	typedef	std::vector<Edge>				EdgeVector;

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
		void*				GetVB(){return pVB;};
		void*				GetIB(){return pIB;};

		U1					FindPath(const Float3&	vBegin,const Float3& vEnd,ElementList* lstElement	=	NULL);
	protected:
		U1			LoadAME0();
		U1			BuildElement();
		U32			AddEdge(U32	v0,U32	v1,TriangleElement* pTriangle);

		U1			Find(Edge* pEdge,TriangleElement* pEnd,MaskVector& vecMask,float fLastDistance,Edge*& pEndEdge);

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
	};
}
#endif // AirNavMesh_h__
