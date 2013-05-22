#include "AirPhysicsSVO.h"

namespace	Air{
	namespace	Physics{


		SVO::SVO( CAString& strName ):Common::IProduct(strName)
		{
			m_uiDepth	=	0;
			m_BoundingBox.vMin	=	Float3(0,0,0);
			m_BoundingBox.vMax	=	Float3(0,0,0);
			m_vHalfSize			=	Float3(0,0,0);
			m_fScale			=	1.0f;
		}

		Air::U1 SVO::Create()
		{
			return true;
		}

		Air::U1 SVO::Destroy()
		{
			m_SVO.clear();
			m_uiDepth	=	0;
			m_fScale	=	1.0f;
			return true;
		}

		void SVO::Updata( const STD_VECTOR<U32>& svoData ,U32 uiDepth,float fScale)
		{
			m_uiDepth	=	uiDepth;
			m_fScale	=	fScale;
			float fBoundSize	=	powf(2.0f,m_uiDepth-1);
			m_BoundingBox.vMin	=	Float3(-1,-1,-1)*fBoundSize;
			m_BoundingBox.vMax	=	Float3(1,1,1)*fBoundSize;
			m_vHalfSize			=	Float3(1,1,1)*fBoundSize;
			m_SVO				=	svoData;
		}

		U1	SVO::IsIntersect(PointShape* shape,const BoundingBox& box){

			switch(shape->m_Type){
			case	enPST_Point:{
				return	box.IsInclude(shape->m_vPosition*m_fScale);
								}break;
			case	enPST_Triangle:{

								   }break;
			case	enPST_Box:{
				Float3& vCenter		= shape->m_vPosition;
				Float3& vHalfSize	=	((BoxShape*)shape)->m_vHalfSize;
				BoundingBox bIntersect=	box;
				bIntersect.Intersect(BoundingBox(vCenter-vHalfSize,vCenter+vHalfSize));
				if(	bIntersect.vMin.x < bIntersect.vMax.x &&
					bIntersect.vMin.y < bIntersect.vMax.y&&
					bIntersect.vMin.z < bIntersect.vMax.z)
				{
					return true;
				}
							  }break;
			case	enPST_Sphere:{
				Float3& vCenter		= shape->m_vPosition;
				float  fRadius	=	((SphereShape*)shape)->fRadius;
				if(	box.vMin.x	-	vCenter.x	>	fRadius	||
					box.vMin.y	-	vCenter.y	>	fRadius	||
					box.vMin.z	-	vCenter.z	>	fRadius	||
					vCenter.x	-	box.vMax.x 	>	fRadius	||
					vCenter.y	-	box.vMax.y 	>	fRadius	||
					vCenter.z	-	box.vMax.z 	>	fRadius
					)
				{
					return false;
				}else{
					return true;
				}
								 }break;
			case	enPST_Cylinder:{
				Float3& vCenter		= shape->m_vPosition;
				float  fRadius	=	((CylinderShape*)shape)->fRadius;
				float  fHeight	=	((CylinderShape*)shape)->fHeight;
				if(	box.vMin.x	-	vCenter.x	>	fRadius	||
					box.vMin.z	-	vCenter.z	>	fRadius	||
					vCenter.x	-	box.vMax.x 	>	fRadius	||
					vCenter.z	-	box.vMax.z 	>	fRadius	||
					vCenter.y	>	box.vMax.y				||
					box.vMin.y	-	vCenter.y	>	fHeight
					)
				{
					return false;
				}else{
					return true;
				}
								   }break;
			case	enPST_Plane:{

								}break;
			}
			return false;
		}

		Air::U1 SVO::CollisionDetect( PointShape* shape,Float3* pV/*=NULL*/ )
		{
			if(m_uiDepth==0	||	m_SVO.empty()){
				return false;
			}

				U32&			uiMaxDepth	=	m_uiDepth;
				BoundingBox&	bound		=	m_BoundingBox;

				if(!IsIntersect(shape,bound)){
					return false;
				}

				Float3 VoxelIndex = shape->m_vPosition*m_fScale-bound.vMin;
				Common::IntVec3 vIndex(VoxelIndex.x,VoxelIndex.y,VoxelIndex.z);
				U32 offset	=	0;
				for(int i=0;i<uiMaxDepth;i++){
					U32 uiSHR	=	(uiMaxDepth-1-i);
					Common::IntVec3	maskValue(vIndex.x>>uiSHR,vIndex.y>>uiSHR,vIndex.z>>uiSHR);//mask;
					maskValue	=	Common::IntVec3(maskValue.x&1,maskValue.y&1,maskValue.z&1);

					U32 idx	=	(maskValue.x<<2)+(maskValue.y<<1)+maskValue.z;

					U32	address			=	(offset+idx);

					U32& uiValue	=	m_SVO[address];
					if(uiValue==0){
						return false;
					}else if(i==(uiMaxDepth-1)){
						if(pV!=NULL){
							Float3 vNormal = Float3(((uiValue&0x00ff0000)>>16)/255.0f,
								((uiValue&0x0000ff00)>>8)/255.0f,
								((uiValue&0x000000ff))/255.0f);
							vNormal	=	vNormal*2-1;
							Float3 vDir	=	*pV;
							vDir.Normalize();
							if(vNormal.Dot(vDir)>0){
								vNormal	*=-1;
							}
							Float3 vReflect	=	vNormal*2*vNormal.Dot(-vDir)+vDir;
							*pV	=	vReflect*(pV->Length());
						}
						return true;
					}else{
						offset	=	uiValue;
					}
				}

				return false;
			//}
		}

	}
}