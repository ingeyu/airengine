#include "AirPhysicsSystem.h"
#include "AirPhysicsSVO.h"
#include "AirPhysicsObject.h"
namespace	Air{
	namespace	Physics{


		System::System()
		{
			m_pSVO	=	NULL;
			m_vGravity	=	Float3(0,-9.8,0);
		}

		Air::U1 System::Initialization()
		{
			m_pSVO	=	new SVO("SVO");
			m_pSVO->AddRef();

			AddFactory(new ParamFactory<Object>());
			return true;
		}

		Air::U1 System::Release()
		{
			SAFE_RELEASE_REF(m_pSVO);
			return true;
		}

		void System::Update( const FrameTime& frameTime )
		{

		}

		U32 System::CollisionDetect( const Float3& p,Float3& v ,U32 uiMask,Object** ppObj)
		{
			static float& fTimeDelta	=	GetTimer().m_FrameTime.fTimeDelta;
			if(uiMask&enPCM_Gravity){
				v +=	m_vGravity*fTimeDelta;
			}
			if(uiMask&enPCM_DynamicObject){
				class PhysicsCD:public Common::TraversalCallback{
				public:
					PhysicsCD(const Float3& p,Float3& v,U32 uiMask):tempP(p),tempV(v),mask(uiMask){
						pHitObj=NULL;
					};
					virtual	Common::enumTraversalState	OnTraversal(Common::IProduct* pProduct){
						Object* p = (Object*)pProduct;
						if(p->CollosionDetect(tempP,tempV,mask)){
							pHitObj	=	p;
							return Common::enTS_Break;
						}
						return Common::enTS_Continue;
					}
					U32 mask;
					const Float3&	tempP;
					Float3&			tempV;	
					Object*			pHitObj;
				};

				Common::IFactory* pFactory	=	GetFactory(Object::ProductTypeName);
				if(pFactory!=NULL){
					PhysicsCD tempCD(p,v,uiMask);
					//if return false, CollosionDetect Hit Some Object
					if(pFactory->TraversalProduct(&tempCD)== Common::enTS_Break){
						if(ppObj!=NULL){
							*ppObj	=	tempCD.pHitObj;
						}
						return enPCM_DynamicObject;
					};
				}
			}
			if(uiMask&enPCM_Environment){
				if(m_pSVO->CollisionDetect(p,&v)){
					return enPCM_Environment;
				}
			}
			return 0;
		}

		void System::UpdateSVO( U32* svoData,U32 uiDepth,float fScale )
		{
			m_pSVO->Update(svoData,uiDepth,fScale);
		}

		Air::U1 System::Silumation( Float3& p,float fRadius,float fHeight,Float3& v,U1 bGravity /*= false*/ )
		{
			static float& fTimeDelta	=	GetTimer().m_FrameTime.fTimeDelta;

			Float3 vOffset	=	v*fTimeDelta;
			Float3 vTestPos	=	p+vOffset;

			Float3 vHalfSize	=	Float3(0.5,1,0.5)*fRadius;
			Float3 vCenter		=	vTestPos+Float3(0,0.5,0);
			BoundingBox bound(vCenter-vHalfSize,vCenter+vHalfSize);



			Shape	moveShape;
			moveShape.m_Type	=	enPST_Box;
			moveShape.m_vHalfSize			=	bound.GetHalfSize()*Float3(1,0.5,1);
			moveShape.m_vPosition			=	bound.GetCenter();
			Shape	gravityShape;
			gravityShape.m_Type	=	enPST_Box;
			gravityShape.m_vHalfSize		=	bound.GetHalfSize()*Float3(0.5,1,0.5);
			gravityShape.m_vPosition		=	bound.GetCenter();
			
			Float3 vNormal;
			Float3 vCorrectOffset;
			if(m_pSVO->CollisionDetect(&moveShape,&gravityShape,&vNormal,&vCorrectOffset)){
				//if(vCorrectOffset.y	>	0){
					v.y = 0;
				//}
				
				Float3 vCorrect	=	v	+	vNormal*v.Dot(-vNormal);
				p	+=(vCorrect+vNormal)*fTimeDelta;
				p.y = vCorrectOffset.y;
				
				v.y += m_vGravity.y*fTimeDelta;
				return true;
			}else{
				p=vTestPos;
				v.y+=m_vGravity.y*fTimeDelta;
				return false;
			}


			
		}

	}
}