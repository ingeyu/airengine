#ifndef AirOctree_h__
#define AirOctree_h__

#include "AirBoundingBox.h"
#include "AirRay.h"

namespace Air{

	

	class	TreeElement{
	public:
		TreeElement(){
			m_pParent	=	NULL;
			m_pData		=	NULL;
		};
		virtual	BoundingBox*	GetBoundingBox(){return	NULL;};
		void					SetParent(void*	pParent){
			m_pParent	=	NULL;
		};
		virtual	void			WriteDataToBuffer(U8*&	p){*p	=	m_pData;};
		virtual	U32				GetDataSize(){return	sizeof(U32);};
		void*	m_pParent;
		U32		m_pData;
	};
	//Ray
	//Element
	//OutDistance
	//UserData
	typedef U1	(*RayCastFunc)(const Ray&,TreeElement*,float*,void*);
	//Position
	//Element
	//UserData
	typedef U1	(*FindElementFunc)(const Float3&,TreeElement*,void*);

	typedef	std::list<TreeElement*>	ElementList;
	typedef	std::vector<TreeElement*>	ElementVector;

	class	COMMON_EXPORT	Octree{
	public:

	public:
		Octree(Octree*	pParent	=	NULL);
		virtual	~Octree();


		S32	AddElement(TreeElement*	pElement);

		U32	GetDepth()const{
			return	m_uiDepth;
		};
		const BoundingBox&	GetBoundingBox()const{
			return	m_BoundingBox;
		};

		U32			m_uiDepth;
		ElementList	m_lstElement;
		Octree*		m_pChild[8];
		Octree*		m_pParent;
		BoundingBox	m_BoundingBox;
	};
	struct	RelaxBinaryNode{
		RelaxBinaryNode(){
			uiParent	=	0;
			uiLeft		=	0;
			uiRight		=	0;
			uiStart		=	0;
			uiSize		=	0;
		};
		U32		uiParent;
		U32		uiLeft;
		U32		uiRight;
		U32		uiStart;
		U32		uiSize;
		Float3	vMin;
		Float3	vMax;
	};
	typedef	std::vector<RelaxBinaryNode>	RBTVector;
	typedef	std::vector<U8>					RBTData;
	//松散二叉树 针对光线追踪优化
	class	COMMON_EXPORT	RelaxBinaryTree{
	public:
		RelaxBinaryTree(RelaxBinaryTree*	pParent);
		virtual	~RelaxBinaryTree();

		void				Build(const ElementVector&	vecElement);

		static	Float2		FindBestSplitePlane(const ElementVector&	vecElement,const BoundingBox&	box,int&	iSpliteType);
		static	Float2		CalcBestSplitePlane(const ElementVector&	vecElement,const BoundingBox&	box,int	iSpliteType,float&	fBegin,float&	fEnd);

		void				SaveToMemory(RBTVector&	vecNode,void*&	pData,U32&	iDataCount);
		TreeElement*		RayCast(const Ray& ray,RayCastFunc pFunc,void*	pUserData	=	NULL,float* pOutDistance	=	NULL);
		TreeElement*		FindElement(const Float3& vPos,FindElementFunc pFunc,void* pUserData);
		U32					GetTotalNodeCount();
		static	U32			m_MaxElement;
		U32					m_uiDepth;
		ElementVector		m_vecElement;
		RelaxBinaryTree*	m_pChild[2];
		RelaxBinaryTree*	m_pParent;
		BoundingBox			m_BoundingBox;
	};


}
#endif // AirOctree_h__
