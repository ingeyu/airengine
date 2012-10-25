#include "AirOctree.h"
namespace	Air{


	Octree::Octree( Octree* pParent /*= NULL*/ )
	{
		m_pParent	=	pParent;
		for(int i=0;i<8;i++){
			m_pChild[i]	=	NULL;
		}

		if(m_pParent!=NULL){
			m_uiDepth	=	m_pParent->GetDepth()+1;
		}else{
			m_uiDepth	=	0;
		}
	}

	Octree::~Octree()
	{
		for(int i=0;i<8;i++){
			SAFE_DELETE(m_pChild[i]);
		}
		m_lstElement.clear();
	}

	Air::S32 Octree::AddElement( TreeElement* pElement )
	{
		if(pElement==NULL)
			return	-1;
		BoundingBox*	pBox	=	pElement->GetBoundingBox();
		if(pBox==NULL)
			return	-1;
		if(m_BoundingBox.IsInclude(*pBox)){

			Float3	vSize	=	m_BoundingBox.GetHalfSize();
			Float3	vCenter	=	m_BoundingBox.GetCenter();
			U32		idx		=	0;

			BoundingBox	box;
			box.vMin	=	m_BoundingBox.vMin;
			

			int	iXSide	=	pBox->GetSide(vCenter.x,enPT_X);
			int	iYSide	=	pBox->GetSide(vCenter.y,enPT_Y);
			int	iZSide	=	pBox->GetSide(vCenter.z,enPT_Z);

			//与切分平面相交
			if(iXSide	==	0	||	iYSide	==	0	||	iZSide	==	0){
				m_lstElement.push_back(pElement);
				pElement->m_pParent	=	this;
				return	m_uiDepth;
			}
				
			if(iXSide	==	1){
				idx+=4;
				box.vMin.x	=	m_BoundingBox.vMax.x;
			}
			if(iYSide	==	1){
				idx+=2;
				box.vMin.y	=	m_BoundingBox.vMax.y;
			}
			if(iZSide	==	1){
				idx+=1;
				box.vMin.z	=	m_BoundingBox.vMax.z;
			}

			box.vMax		=	box.vMin	+	vSize;

			Octree*&	pTree	=	m_pChild[idx];
			if(pTree==NULL){
				pTree	=	new Octree(this);
				pTree->m_BoundingBox	=	box;

			}
			return	pTree->AddElement(pElement);

		}

		return	-1;
	}

	U32	RelaxBinaryTree::m_MaxElement	=	5;
	RelaxBinaryTree::RelaxBinaryTree( RelaxBinaryTree* pParent )
	{
		m_pParent	=	pParent;
		if(m_pParent==NULL){
			m_uiDepth	=	0;
		}else{
			m_uiDepth	=	m_pParent->m_uiDepth+1;
		}
		m_pChild[0]	=	0;
		m_pChild[1]	=	0;
	}

	void RelaxBinaryTree::Build( const ElementVector& vecElement )
	{
		//节点深度太大 或者 元素个数小于最大元素个数
		if(vecElement.size()	<=	m_MaxElement	||	m_uiDepth	>=	31){
			m_vecElement	=	vecElement;
			return;
		}
		int	iSplitePlane		=	0;
		Float2	vSplitePlane	=	FindBestSplitePlane(vecElement,m_BoundingBox,iSplitePlane);

		ElementVector	vecChild[2];
		BoundingBox		childBox[2];
		bool			bInit[2]={false,false};
		for(int i=0;i<vecElement.size();i++){
			TreeElement*	pElement	=	vecElement[i];
			const BoundingBox*	box	=	pElement->GetBoundingBox();
			int	iChildType	=	1;
			if(box->vMax[iSplitePlane]	<=	vSplitePlane.x){
				iChildType	=	0;
			}

			vecChild[iChildType].push_back(pElement);
			if(bInit[iChildType]){
				childBox[iChildType].Add(*box);
			}else{
				childBox[iChildType]	=	*box;
				bInit[iChildType]		=	true;
			}
		}
		//无法继续细分
		if(vecChild[0].empty()){
			m_vecElement	=	vecElement;
			return;
		}else{
			for(int i=0;i<2;i++){
				if(!vecChild[i].empty()){
					m_pChild[i]	=	new RelaxBinaryTree(this);
					m_pChild[i]->m_BoundingBox		=	childBox[i];
					m_pChild[i]->Build(vecChild[i]);
				}
			}
		}

	}

	Air::Float2 RelaxBinaryTree::FindBestSplitePlane( const ElementVector& vecElement ,const BoundingBox&	box,int&	iSpliteType)
	{
		

		Float2	vSplite[3];
		for(int	i=0;i<3;i++){
			Float2	fTempSplite[2];
			float	fBegin	=	box.vMin[i];
			float	fEnd	=	box.vMax[i];
			fTempSplite[0]	=	CalcBestSplitePlane(vecElement,box,i,fBegin,fEnd);
			fTempSplite[1]	=	CalcBestSplitePlane(vecElement,box,i,fBegin,fEnd);
			vSplite[i]	=	fTempSplite[0];
			if(fTempSplite[1].y	<	fTempSplite[0].y){
				vSplite[i]	=	fTempSplite[1];
			}
		}

		iSpliteType	=	0;
		for(int i=1;i<3;i++){
			if(vSplite[i].y	<	vSplite[0].y){
				vSplite[0]	=	vSplite[i];
				iSpliteType	=	i;
			}
		}
		return	vSplite[0];
	}

	Air::Float2 RelaxBinaryTree::CalcBestSplitePlane( const ElementVector& vecElement,const BoundingBox&	box,int iSpliteType,float& fBegin,float& fEnd )
	{
		Float3	vHalfSize	=	box.vMax	-	box.vMin;
		double	fTotalArea	=	vHalfSize.x*vHalfSize.y+vHalfSize.x*vHalfSize.z+vHalfSize.y*vHalfSize.z;

		int iSpliteStep	=	8;
		float	fRange	=	fEnd	-	fBegin;
		Float2	vSplite[8];
		for(int i=1;i<iSpliteStep;i++){
			float	testSplite	=	fBegin	+	fRange*i/iSpliteStep;
			vSplite[i].x		=	testSplite;
			double	dCount[2]	=	{0,0};
			double	dTotalCount	=	vecElement.size();
			BoundingBox	childbox[2];
			bool		bInit[2]	=	{false,false};
			for(int j=0;j<vecElement.size();j++){
				TreeElement*	pElement	=	vecElement[j];
				const	BoundingBox*	pBox	=	pElement->GetBoundingBox();
				int	iChildType	=	1;
				if(pBox->vMax[iSpliteType]	<=	testSplite){
					iChildType	=	0;
				}
				dCount[iChildType]	+=	1.0f;
				if(bInit[iChildType]){
					childbox[iChildType].Add(*pBox);
				}else{
					childbox[iChildType]=	*pBox;
					bInit[iChildType]	=	true;
				}	
			}
			Float3	vLeftSize	=	childbox[0].vMax	-	childbox[0].vMin;
			double	fLeftArea	=	vLeftSize.x*vLeftSize.y+vLeftSize.x*vLeftSize.z+vLeftSize.y*vLeftSize.z;
			Float3	vRightSize	=	childbox[1].vMax	-	childbox[1].vMin;
			double	fRightArea	=	vRightSize.x*vRightSize.y+vRightSize.x*vRightSize.z+vRightSize.y*vRightSize.z;

			vSplite[i].y		=	(fLeftArea/fTotalArea)*(dCount[0]/dTotalCount)	+	(fRightArea/fTotalArea)*(dCount[1]/dTotalCount);
		}

		int iPlane	=	1;
		vSplite[0]	=	vSplite[1];

		for(int i=2;i<8;i++){
			if(vSplite[i].y	<	vSplite[0].y){
				vSplite[0]	=	vSplite[i];
				iPlane		=	i;
			}
		}

		if(iPlane==1){
			fEnd	=	vSplite[2].x;
		}else	if(iPlane	==	7){
			fBegin	=	vSplite[6].x;
		}else{
			fEnd	=	vSplite[iPlane+1].x;
			fBegin	=	vSplite[iPlane-1].x;
			
		}

		return	vSplite[0];
	}

	RelaxBinaryTree::~RelaxBinaryTree()
	{
		for(int i=0;i<2;i++){
			delete m_pChild[i];
			m_pChild[i]	=	NULL;
		}
	}

	void RelaxBinaryTree::SaveToMemory( RBTVector&	vecNode,void*&	pData,U32&	iDataCount )
	{
// 		int ii	=	vecNode.size();
// 		char str[32];
// 		sprintf(str,"%d\n",ii);
// 		OutputDebugStringA(str);
		if(m_pParent==NULL){
			RelaxBinaryNode	newnode;
			vecNode.push_back(newnode);
		}

		U32	iCurrentNodeIndex	=	vecNode.size()-1;


		RelaxBinaryNode&	node	=	vecNode[iCurrentNodeIndex];
		node.vMin	=	m_BoundingBox.vMin;
		node.vMax	=	m_BoundingBox.vMax;
// 		if(m_pParent!=NULL)
// 			node.uiParent	=	vecNode.size()-2;

		U8*	pOutData	=	(U8*)pData;
		
		if(!m_vecElement.empty()){
			U32	uiElementDataSize	=	m_vecElement[0]->GetDataSize();
			node.uiSize				=	m_vecElement.size();
			//node.
			
			node.uiStart			=	iDataCount;
			

			for(int i=0;i<node.uiSize;i++){
				m_vecElement[i]->WriteDataToBuffer(pOutData);
				pOutData+=	uiElementDataSize;
				iDataCount++;
			}
		}

		pData	=	pOutData;
		if(m_pChild[0]!=NULL){
			node.uiLeft			=	vecNode.size();
			RelaxBinaryNode	newnode;
			newnode.uiParent	=	iCurrentNodeIndex;
			vecNode.push_back(newnode);

			m_pChild[0]->SaveToMemory(vecNode,pData,iDataCount);
		}
		if(m_pChild[1]!=NULL){
			node.uiRight			=	vecNode.size();
			RelaxBinaryNode	newnode;
			newnode.uiParent	=	iCurrentNodeIndex;
			vecNode.push_back(newnode);
			m_pChild[1]->SaveToMemory(vecNode,pData,iDataCount);
		}
		


	}

	Air::U32 RelaxBinaryTree::GetTotalNodeCount()
	{
		U32	iCount	=	1;
		for(int i=0;i<2;i++){
			if(m_pChild[i]!=NULL)
				iCount+=m_pChild[i]->GetTotalNodeCount();
		}
		return	iCount;
	}

	TreeElement* RelaxBinaryTree::RayCast( const Ray& ray,RayCastFunc pFunc,void* pUserData /*= NULL*/,float* pOutDistance /*= NULL*/ )
	{
		TreeElement* pElement	=	NULL;
		float fDistance	=	999999.0f;
		U32	uiElementCount	=	m_vecElement.size();
		for(U32	i=0;i<uiElementCount;i++){
			float fDis	=	9999999.0f;
			if(pFunc(ray,m_vecElement[i],&fDis,pUserData)){
				if(fDis<fDistance){
					pElement	=	m_vecElement[i];
					fDistance	=	fDis;
				}
			}
		}

		for(int i=0;i<2;i++){
			if(m_pChild[i]!=NULL)
				if(m_pChild[i]->m_BoundingBox.RayCast(ray.GetOrigin(),ray.GetDirection(),fDistance))
				{
					float fDis	=	9999999.0f;
					TreeElement*	p	=	m_pChild[i]->RayCast(ray,pFunc,pUserData,&fDis);
					if(p!=NULL){
						if(fDis	<	fDistance){
							pElement	=	p;
							fDistance	=	fDis;
						}
					}
				}
		}
		if(pOutDistance!=NULL){
			*pOutDistance	=	fDistance;
		}
		return pElement;
	}

	TreeElement* RelaxBinaryTree::FindElement( const Float3& vPos, FindElementFunc pFunc,void* pUserData)
	{
		if(m_BoundingBox.IsInclude(vPos)){
			U32	uiElementCount	=	m_vecElement.size();
			for(U32	i=0;i<uiElementCount;i++){
				if(pFunc(vPos,m_vecElement[i],pUserData)){
					return m_vecElement[i];
				}
			}
		}
		for(U32 i=0;i<2;i++){
			if(m_pChild[i]!=NULL){
				TreeElement* pElement	=	m_pChild[i]->FindElement(vPos,pFunc,pUserData);
				if(pElement!=NULL){
					return pElement;
				}
			}
		}
		return	NULL;
	}

}