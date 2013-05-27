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
			m_SVO				=	NULL;
		}

		Air::U1 SVO::Create()
		{
			return true;
		}

		Air::U1 SVO::Destroy()
		{
			m_SVO=NULL;
			m_uiDepth	=	0;
			m_fScale	=	1.0f;
			return true;
		}

		void SVO::Update( U32* svoData ,U32 uiDepth,float fScale)
		{
			m_uiDepth	=	uiDepth;
			m_fScale	=	fScale;
			float fBoundSize	=	powf(2.0f,m_uiDepth-1);
			m_BoundingBox.vMin	=	Float3(-1,-1,-1)*fBoundSize;
			m_BoundingBox.vMax	=	Float3(1,1,1)*fBoundSize;
			m_vHalfSize			=	Float3(1,1,1)*fBoundSize;
			m_SVO				=	svoData;
		}

		U1	SVO::IsIntersect( Shape* shape,const BoundingBox& box){

			switch(shape->m_Type){
			case	enPST_Point:{
				return	box.IsInclude(shape->m_vPosition*m_fScale);
								}break;
			case	enPST_Triangle:{

								   }break;
			case	enPST_Box:{
				const Float3& vCenter		= shape->m_vPosition;
				const Float3& vHalfSize	=	shape->m_vHalfSize;
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
				const Float3& vCenter		= shape->m_vPosition;
				float  fRadius	=	shape->m_vHalfSize.x;
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
				const Float3& vCenter		= shape->m_vPosition;
				float  fRadius	=	shape->m_vHalfSize.x;
				float  fHeight	=	shape->m_vHalfSize.y;
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

		Air::U1 SVO::CollisionDetect( const Float3& p,Float3* pV/*=NULL*/ )
		{
			if(m_uiDepth==0	||	m_SVO==NULL){
				return false;
			}

				U32&			uiMaxDepth	=	m_uiDepth;
				BoundingBox&	bound		=	m_BoundingBox;

				if(!bound.IsInclude(p)){
					return false;
				}

				Float3 VoxelIndex = p*m_fScale-bound.vMin;
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

		Air::U1 SVO::CollisionDetect( Shape*  pMove,Shape* pGravity,Float3* pNormal ,Float3* pCorrect)
		{

			if(m_uiDepth==0	||	m_SVO==NULL){
				return false;
			}

			U32&			uiMaxDepth	=	m_uiDepth;
			
			ScaleShape(pMove);
			ScaleShape(pGravity);

			Float3 vCenter = pMove->m_vPosition;
			//BoundingBox boxMove(vCenter-((BoxShape*)pMove)->m_vHalfSize,vCenter+((BoxShape*)pMove)->m_vHalfSize);
			BoundingBox boxGravity(vCenter-pGravity->m_vHalfSize,vCenter+pGravity->m_vHalfSize);

			if(!IsIntersect(pMove,m_BoundingBox)&&!IsIntersect(pGravity,m_BoundingBox)){
				return false;
			}


			Float3 vMin			=	m_BoundingBox.vMin;
			Float3 vHalfSize	=	m_vHalfSize;
			BoundingBox	tempBound;

			U32 i=0;
			U32 j=0;
			U32 uiStack=0;
			U32	uiOffsetStack[10]={0};

			

			Float3 vRetNormal;
			float fWeight	=	-1.0f;

			float& fGravity	=	pCorrect->y;
			fGravity		=	boxGravity.vMin.y;

			U1		bRet	=	false;

			for(;;){

				for(;j<8;){
					U32 addr		=	uiOffsetStack[i]+j;
					U32& uiValue	=	m_SVO[addr];
					if(uiValue==0){
						j++;
						continue;
					}
					
					tempBound.vMin	=	vMin+Float3(j>>2,1&(j>>1),1&j)*vHalfSize;
					tempBound.vMax	=	tempBound.vMin+vHalfSize;

					U1	bHitMove	=	IsIntersect(pMove,tempBound);
					U1	bHitGravity	=	IsIntersect(pGravity,tempBound);

					if(!bHitMove&&!bHitGravity){
						j++;
						continue;
					}

					if(i	==	uiMaxDepth-1){
						
						if(pNormal!=NULL){

#if 0
#else
							if(bHitGravity){
								float f	=	tempBound.vMax.y;
								if(f > fGravity){
									fGravity	=	f;
									bRet		=	true;
								}
							}

							if(bHitMove){
								bRet	=	true;
								Float3 vNormal = (vCenter - tempBound.GetCenter());
								vNormal.y=0;
								//vNormal.Normalize();
								if(fWeight	<	0){
									vRetNormal	=	vNormal;//*vSize.Length();
									fWeight=1;//vSize.Length();
								}else{
									vRetNormal+=vNormal;//*vSize.Length();
									fWeight+=1;//vSize.Length();
								}
							}
#endif
							j++;
						}else{
							return true;
						}
						
					}else{
						uiStack&=0xfffffff8;
						uiStack|=j;
						i++;
						uiOffsetStack[i]	=	uiValue;
						vMin		=	tempBound.vMin;
						vHalfSize	*=	0.5;
						j=0;
						uiStack<<=3;
					}
				}
				if(i!=0){
					i--;
					vHalfSize	*=	2;
					uiStack>>=3;
					j	=	(uiStack&7);
					vMin	-=	Float3(j>>2,1&(j>>1),1&j)*vHalfSize;
					j++;
				}else{
					break;
				}
			}
			if(pNormal==NULL){
				return false;
			}
			fGravity/=m_fScale;
			if(fWeight>0){
				vRetNormal/=fWeight;
				vRetNormal.Normalize();
			}
			*pNormal	=	vRetNormal;
				
			return bRet;
			
		}

		void SVO::ScaleShape( Shape* shape )
		{
			shape->m_vPosition*=m_fScale;
			switch(shape->m_Type){
			case	enPST_Point:{
				;
								}break;
			case	enPST_Triangle:{

								   }break;
			case	enPST_Box:{
				
				Float3& v = shape->m_vHalfSize;
				v*=m_fScale;
							  }break;
			case	enPST_Sphere:{
				
				float&  fRadius	=	shape->m_vHalfSize.x;
				fRadius*=m_fScale;
								 }break;
			case	enPST_Cylinder:{

				float&  fRadius	=	shape->m_vHalfSize.x;
				float&  fHeight	=	shape->m_vHalfSize.y;
				fRadius*=m_fScale;
				fHeight*=m_fScale;
				
								   }break;
			case	enPST_Plane:{

								}break;
			}
		}
		int Float2Compare(const void* p0,const void* p1){
			const Float2*	_p0	=	(const Float2*)p0;
			const Float2*	_p1	=	(const Float2*)p1;
			return (_p0->x - _p1->x)*1000000;
		}
		U32	PositionToIndex(const Float3& vCamPos,
							const Float3& vDir,
							float fNear,
							const Float3& vMin,
							const Float3& vHalfSize)
		{
			Float3 vTemp			=	vCamPos-vMin-vHalfSize;
			Float3	fFirstInterSect	=	vDir*fNear+vTemp;
			U32	fFirstIndex		=	0;
			if(fFirstInterSect.x>0)
				fFirstIndex+=4;
			if(fFirstInterSect.y>0)
				fFirstIndex+=2;
			if(fFirstInterSect.z>0)
				fFirstIndex+=1;
			return fFirstIndex;
		};
		void BuildOrder(const Float3& vDir,U32& uiOrder,U32& uiOrderToIndex){

			float aData[8];
			U32  anIndex[8]={0,1,2,3,4,5,6,7};
			
			for(U32 i=0;i<8;i++){
				aData[i]=Float3(i>>2,1&(i>>1),1&i).Dot(vDir);	
			}
			U32 N2=8;
			// Bitonic sort
			for( U32 k = 2; k <= N2; k = 2*k )
			{
				for( U32 j = k>>1; j > 0 ; j = j>>1 ) 
				{
					for( U32 i = 0; i < N2; i++ ) 
					{
						float di = aData[ anIndex[ i ] ];
						U32 ixj = i^j;
						if ( ( ixj ) > i )
						{
							float dixj = aData[ anIndex[ ixj ] ];
							if ( ( i&k ) == 0 && di > dixj )
							{ 
								int temp = anIndex[ i ];
								anIndex[ i ] = anIndex[ ixj ];
								anIndex[ ixj ] = temp;
							}
							if ( ( i&k ) != 0 && di < dixj )
							{
								int temp = anIndex[ i ];
								anIndex[ i ] = anIndex[ ixj ];
								anIndex[ ixj ] = temp;
							}
						}
					}
				}
			}
			uiOrder=0;
			for(U32 i=0;i<8;i++){
				uiOrder|=anIndex[i]<<(i*3);
			}
			uiOrderToIndex=0;
			for(U32 i=0;i<8;i++){
				U32 uiIdx	=	(uiOrder>>(i*3))&0x7;
				uiOrderToIndex|=i<<(3*uiIdx);
			}	
		}

		Float4	U32_F32(U32 uiColor){
			return	Float4(
				((uiColor&0x00ff0000)>>16)/255.0f,
				((uiColor&0x0000ff00)>>8)/255.0f,
				((uiColor&0x000000ff))/255.0f,
				((uiColor&0xff000000)>>24)/255.0f
				);
		}
		Air::U1 SVO::RayCast( const Float3& vStart,const Float3& vDir,float& fOutDistance,Float3* pNormal /*= NULL*/ )
		{

			Float3 vScaleStart	=	vStart*m_fScale;

			U32 uiOffset[10];
			uiOffset[0]=0;
			U32 uiStack=0;

			int	uiDepth	=	0;
			Float3	vHalfSize	=	m_vHalfSize;
			Float3  vMin		=	-vHalfSize;

			float fNear	=	0.0f;
			float fFar	=	10000.0f;
			if(!m_BoundingBox.RayCast(vScaleStart,vDir,&fNear,&fFar)){
				return false;
			}

			U32 uiOrder=0;
			U32	uiOrderToIndex=0;
			BuildOrder(vDir,uiOrder,uiOrderToIndex);

			U32 uiFirst	=	PositionToIndex(vScaleStart,vDir,fNear,vMin,vHalfSize);
			U32	itr		=	(uiOrderToIndex>>(3*uiFirst))&0x7;
			while(true){
				for(;itr<=7;){
					U32 childidx	=	(uiOrder>>(itr*3))&0x7;

					U32 addr		=	(uiOffset[uiDepth]+childidx);
					U32 uiChild		=	m_SVO[addr];

					//float fCmp=uiChild*1.001f;
					if(uiChild==0){
						itr++;
						continue;
					}
					BoundingBox	tempBound;
					tempBound.vMin	=	vMin+Float3(childidx>>2,1&(childidx>>1),1&childidx)*vHalfSize;
					tempBound.vMax	=	tempBound.vMin+vHalfSize;
					float	fTempNear	=	0;
					float	fTempFar	=	10000.0f;
					if(!tempBound.RayCast(vScaleStart,vDir,&fTempNear,&fTempFar)){
						itr++;
						continue;
					}
					if(uiDepth	==	m_uiDepth-1){
						if(pNormal!=NULL){
							*pNormal	=	U32_F32(uiChild);
						}
						fOutDistance	=	fTempNear/m_fScale;
						itr		=	8;
						uiDepth	=	0;
						return true;
						continue;
					}else{
						uiStack&=0xfffffff8;
						uiStack|=itr;
						uiStack<<=3;
						uiDepth++;


						uiOffset[uiDepth]	=	uiChild;
						vHalfSize	/=	2.0f;
						vMin		=	tempBound.vMin;


						U32	uiNearIndex		=	PositionToIndex(vScaleStart,vDir,fTempNear,vMin,vHalfSize);;
						
						itr=(uiOrderToIndex>>(uiNearIndex*3))&0x7;

						continue;
					}
				}
				if(uiDepth<=0){
					break;
				}else{
					uiDepth--;
					vHalfSize*=2.0f;
					uiStack>>=3;
					int iIDX	=	(uiStack&0x7);
					U32 childidx	=	(uiOrder>>(iIDX*3))&0x7;
					vMin	-=	Float3(childidx>>2,1&(childidx>>1),1&childidx)*vHalfSize;
					itr=iIDX+1;
				}
			}
			return false;
		}

	}
}