#include "AirEngineCamera.h"
#include "AirCommonMath.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirEngineScene.h"
#include "AirCommonCollision.h"




namespace Air{
	const	Real	PI	=	4.0 * atan( 1.0 );
	namespace	Engine{

		enum	enumHighKeyCode{
			enHKC_SHIFT	=	1,
			enHKC_ALT	=	1<<1,
			enHKC_CTRL	=	1<<2,

		};
		enum	enumLowKeyCode{
			enLKC_A		=	0,
		};

		struct	KeyCode{
			union{
				struct{
					U8	high;
					U8	low;
				};
				U16	key;
			};
			U1	IsHighKeyDown(enumHighKeyCode	k){
				return	(high	&	(1<<k))>0;
			};
			U1	IsLowKeyDown(enumLowKeyCode		k){
				return	low	==	k;
			}
		};
	
	
		Camera::Camera(CAString&	strName):Common::IProduct(strName){

			m_pScene			=	NULL;
			m_bReflect			=	false;
			m_PhaseFlag			=	0;
			m_pConstantBuffer	=	NULL;

			AddFlag(enMOF_UPDATE);
			AddFlag(enMOF_DYNAMIC);

			//未知类型的摄像机
			SetType(enCT_UNKNOWN);
		}
	
		void Camera::Render2D(SInt uiWidth,SInt uiHeight){

				float	fAspect	=	float(uiWidth)/float(uiHeight);
				if(fAspect	!=	m_fAspect){
					SetAspect(fAspect);
				}
			
			if(m_bDirty){
				ReBuild();
				m_bDirty	=	false;
			}

// 			Render::CBCamera&	cb	=	Render::System::GetSingleton()->m_CBCamera;
 			if(m_pConstantBuffer==NULL){
				Buffer::Info	info;
				info.SetConstantBuffer(sizeof(Float4)*8);
 				m_pConstantBuffer	=	Render::System::GetSingleton()->CreateProduct<Buffer*>(m_strProductName,"Buffer",&info);
			}

			Float4	buffer[8];
			memcpy(buffer,&GetViewProjMatrix(),sizeof(Matrix));
			buffer[4]	=	GetRealDirection();
			buffer[5]	=	GetRealPosition();
			buffer[6]	=	GetRealUpDirection();
			buffer[7]	=	Float4(1.0f/uiWidth,1.0f/uiHeight,1.0f/m_fNear,1.0f/m_fFar);
			m_pConstantBuffer->GetBuffer();
			m_pConstantBuffer->UpdateData(buffer);

			Render::System::GetSingleton()->GetDevice()->SetCB(1,m_pConstantBuffer);


			//阴影部分是渲染的时候才 push到渲染树中
			if(GetType()==enCT_SHADOW){
				RenderSystem::GetSingleton()->ClearRenderObject(1<<enPI_Shadow);
				ProcessShadowObject();
			}

		}
		void Camera::RenderCubeMap( DWORD dwFace,SInt uiWidth,SInt uiHeight ){
	
			//获取本身的摄像机方向和顶方向
			Float3	vDir		=	m_vDirection;
			Float3	vUp			=	m_vUp;
			SceneNode*	pNode	=	m_pParentNode;
			m_pParentNode		=	NULL;
			float	fFov		=	m_fAngle;
	
	
			
			switch( dwFace ){
			case 0://X
				SetDir(Float3( 1.0f, 0.0f, 0.0f ));
				SetUpDir(Float3( 0.0f, 1.0f, 0.0f ));
				break;
			case 1://-X
				SetDir(Float3( -1.0f, 0.0f, 0.0f ));
				SetUpDir(Float3( 0.0f, 1.0f, 0.0f ));
				break;
			case 2://Y
				SetDir(Float3( 0.0f, 1.0f, 0.0f ));
				SetUpDir(Float3( 0.0f, 0.0f, -1.0f ));
				break;
			case 3://-Y
				SetDir(Float3( 0.0f, -1.0f, 0.0f ));
				SetUpDir(Float3( 0.0f, 0.0f, 1.0f ));
				break;
			case 4://Z
				SetDir(Float3( 0.0f, 0.0f, 1.0f ));
				SetUpDir(Float3( 0.0f, 1.0f, 0.0f ));
				break;
			case 5://-Z
				SetDir(Float3( 0.0f, 0.0f, -1.0f ));
				SetUpDir(Float3( 0.0f, 1.0f, 0.0f ));
				break;
			}
	
			m_fAngle	=	PI/2.0f;
			
			//重建矩阵
			ReBuild();

			//查找所有物体
			FindMovableObject(NULL);
	
			//渲染
			Render2D(uiWidth,uiHeight);

			//清理
			Render::System::GetSingleton()->ClearRenderObject(m_PhaseFlag);

			m_fAngle		=	fFov;
			//还原摄像机方向
			m_vDirection	=	vDir;
			m_vUp			=	vUp;
			m_pParentNode	=	pNode;

		}
	

	
		U1 Camera::Create(){
			m_pScene	=	static_cast<Scene*>(m_pFactoryMgr);

			
			return	true;
		}
	
		U1 Camera::Destroy(){
			m_pObject	=	NULL;
			if(m_pConstantBuffer!=NULL)
				m_pConstantBuffer->ReleaseRef();
			m_pConstantBuffer=NULL;
			return true;
		}




		void Camera::SetReflectPlane( Float3 normal,Real fDistance ){
			//m_ReflectPlane	=	Plane(normal,fDistance);
		}
	
		Float3 Camera::GetRealDirection(){
	// 		if(m_pParentNode!=NULL){
	// 			//m_pParentNode
	// 			return	m_WorldMatrix*m_vDirection	-	m_WorldMatrix.getTrans();
	// 		}else
			{
				return	m_vDirection;
			}
		}
	
		Float3 Camera::GetRealPosition(){
	 		if(m_pParentNode!=NULL){
	 			return	m_pParentNode->GetGlobalPosition();
			}else
			{
				return	m_vPosition;
			}
		}
	
		Float3 Camera::GetRealRightDirection(){
			Float3	vDir	=	GetRealDirection();
			Float3	vUp		=	GetRealUpDirection();
			return	vUp.Cross(vDir);
		}
	
		Float3 Camera::GetRealUpDirection(){
	// 		if(m_pParentNode!=NULL){
	// 			Float44	m	=	m_WorldMatrix;
	// 			m.setTrans(Float3::ZERO);
	// 			return	m*m_vUpDirection;
	// 		}else
			{
				return	m_vUp;
			}
		}


		void Camera::FindMovableObject( Camera* pMainCamera /*= NULL*/ ){
			BuildPlane();
			//m_vecMainMovable.clear();
			m_vecReflectMovable.clear();
			m_vecShadowMovable.clear();
			if(pMainCamera	!=NULL	&&	m_Type	!=	enCT_UNKNOWN){
				if(m_Type	==	enCT_REFLECT){
					TVector<MovableObject*>&	vec				=	pMainCamera->m_vecReflectMovable;
					TVector<MovableObject*>::iterator	i		=	vec.begin();
					TVector<MovableObject*>::iterator	iEnd	=	vec.end();
					for(;i!=iEnd;i++){
						(*i)->ProcessRenderObject(m_PhaseFlag);
					}
				}else{
					TVector<MovableObject*>&	vec				=	pMainCamera->m_vecShadowMovable;
					TVector<MovableObject*>::iterator	i		=	vec.begin();
					TVector<MovableObject*>::iterator	iEnd	=	vec.end();
					for(;i!=iEnd;i++){
						if(IsVisiable((*i)->GetWorldBoundingBox())){
							m_vecShadowMovable.push_back(*i);//(m_PhaseFlag);
						}
					}
				}
			}else{
				Scene*	pScene	=	static_cast<Scene*>(m_pFactoryMgr);
				if(pScene!=NULL){
					pScene->FindMovableObject(this);
				}
			}
		}

		void Camera::ProcessShadowObject(){
			TVector<MovableObject*>&	vec				=	m_vecShadowMovable;
			TVector<MovableObject*>::iterator	i		=	vec.begin();
			TVector<MovableObject*>::iterator	iEnd	=	vec.end();
			for(;i!=iEnd;i++){
				(*i)->ProcessRenderObject(m_PhaseFlag);
			}
		}

		void Camera::AddMovableObject( MovableObject* pObj ){
			if(m_Type	==	enCT_UNKNOWN){
				pObj->ProcessRenderObject(m_PhaseFlag);
			}else{
				if(pObj->HasFlag(enMOF_REFLECT)){
					m_vecReflectMovable.push_back(pObj);
				}
				if(pObj->HasFlag(enMOF_CASTSHADOW)){
					m_vecShadowMovable.push_back(pObj);
				}
				if(pObj->HasFlag(enMOF_DEFAULT)){
					pObj->ProcessRenderObject(m_PhaseFlag);
				}
			}
		}

		void Camera::AddPhaseFlag( U32 flag ){
			m_PhaseFlag	|=	flag;
		}

		void Camera::RemovePhaseFlag( U32 flag ){
			m_PhaseFlag	&=	~flag;
		}

		void Camera::ClearPhaseFlag(){
			m_PhaseFlag	=	0;
		}

		void Camera::SetPhaseFlag( U32 flag ){
			m_PhaseFlag	=	flag;
		}
		CameraFactory::CameraFactory(){
			m_strTypeName	=	"Camera";
		}
	
		IProduct* CameraFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
			return	new	Camera(strName);
		}
	}
};