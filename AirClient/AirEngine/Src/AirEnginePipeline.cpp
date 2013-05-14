#include "AirEnginePipeline.h"
#include "AirGlobalSetting.h"
#include "AirEngineCamera.h"
#include "AirEngineScene.h"

#include "AirMeshEntity.h"
#include "AirManualMeshEntity.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirQuadRenderable.h"
#include "AirEngineMaterial.h"
#include "AirEngineLight.h"

#include "AirResourceSystem.h"


#include "AirNavMesh.h"
#include "AirHelperRenderable.h"
#include "AirEngineCharacterAnimationModel.h"

namespace	Air{
	namespace	Engine{
		NavMesh*	pMesh	=	NULL;
		extern SceneNode* pMNode;
		extern Character::Animation::Model*	pModel;
		AString	Pipeline::ProductTypeName="Pipeline";
		Pipeline::Pipeline( CAString& strName):IProduct(strName)
		{
			m_pMainWindow	=	NULL;
			m_pScene		=	NULL;
			m_pQuad			=	NULL;
			m_pMainCamera	=	NULL;
		}

		Air::U1 Pipeline::Create()
		{
			m_pMainCamera	=	EngineSystem::GetSingleton()->CreateProduct<Camera>(m_strProductName+"_Camera");
			if(m_pMainCamera==NULL)
				return false;
			m_pMainCamera->SetType(enCT_MAIN);
			RenderSystem*	pRenderSys	=	Render::System::GetSingleton();

			m_pMainCamera->SetPosition(0,0,-10);
			m_pMainCamera->SetDir(0,0,1);

			m_pMainWindow	=	pRenderSys->GetMainWindow();
			m_pMainWindow->AddRef();
			m_pMainWindow->AddCamera(m_pMainCamera);


			m_pQuad			=	new QuadRenderable();

			return true;
		}

		Air::U1	Pipeline::Destroy(){

			SAFE_RELEASE_REF(	m_pMainWindow	);
			SAFE_DELETE(		m_pQuad			);
			SAFE_RELEASE_REF(	m_pMainCamera	);
			return true;
		}
		void	Pipeline::Update(const FrameTime& frameTime)
		{

		};
		U1		Pipeline::RenderOneFrame(const FrameTime& frameTime)
		{
			m_pMainWindow->Update();
			return true;
		};

		void Pipeline::SetCurrentScene( Scene* pCurrentScene )
		{
			m_pScene	=	pCurrentScene;
		}

		AString	DefaultPipeline::ProductTypeName="DefaultPipeline";
		DefaultPipeline::DefaultPipeline( CAString& strName):Pipeline(strName)
		{
			m_pMRT			=	NULL;
			m_pQuad			=	NULL;
			m_pQuadCopy		=	NULL;
			m_pSSAO			=	NULL;
			m_pRT_AO		=	NULL;
			m_pSSSO			=	NULL;
			m_pRT_SO		=	NULL;

			m_pRT_EnvSphere	=	NULL;
			m_pRT_EnvSAT	=	NULL;
			m_pCombine		=	NULL;

			m_pSky			=	NULL;
			m_pCubeToViewSphere=	NULL;
			m_pViewSphereSAT=	NULL;
			m_pAmbientLight	=	NULL;


			fVolocity		=	10.0f;

			m_cbFrame.vAmbient		=	Float4(1,1,1,1);
			m_cbFrame.vSunDiffuse	=	Float4(1,0.9,0.8,1);
			m_cbFrame.vSunDir		=	Float3(-1,-1,-1).NormalizeCopy();
			m_cbFrame.vMainCamPos	=	Float3(0,0,0);
		}

		Air::U1 DefaultPipeline::Create()
		{
			__super::Create();

			OIS::KeyListener*	pKey	=	this;
			OIS::MouseListener*	pMouse	=	this;
			GetGlobalSetting().m_pInputSystem->Add(pKey);
			GetGlobalSetting().m_pInputSystem->Add(pMouse);



			
			//pVP->SetCamera(m_pScene->GetMainCamera());


			//MeshEntity*	pEnt[100];
			//for(int i=-5;i<5;i++){
				//for(int j=-5;j<5;j++){
					//long iIndex	=	0;//(i+5)*10+j+5;

					//AString	strName = Common::Converter::ToString(iIndex);
					//
					//pTestManualEnt	=	EngineSystem::GetSingleton()->CreateProduct<ManualMeshEntity*>("Test","ManualMeshEntity",&info);
					//pTest	=	m_pScene->GetRootNode()->CreateChildSceneNode(strName);
					//pTest->attachObject(pTestEnt);
					//pTest->SetPosition(Float3(j*21,i*20,0));
					//pTest->SetScale(Float3(0.5f,0.5f,0.5f));
				//}
			//}
					/*
					ManualMeshEntity::Info mmeInfo;
					mmeInfo.uiVertexCount	=	pTestEnt->GetMesh()->GetVertexCount();
					mmeInfo.uiVertexSize	=	sizeof(Float3);
					mmeInfo.uiFaceCount		=	pTestEnt->GetMesh()->GetFaceCount();
					mmeInfo.strMaterial		=	"WorldHelper";
					mmeInfo.vdInfo.SetDeclP3();
					pTestManualEnt	=	EngineSystem::GetSingleton()->CreateProduct<ManualMeshEntity*>(strName,"ManualMeshEntity",&mmeInfo);

					std::vector<Float3> vVertex;
					vVertex.resize(mmeInfo.uiVertexCount);
					U8*	pVB	=	(U8*)pTestEnt->GetMesh()->GetVB();
					for(U32 i=0;i<mmeInfo.uiVertexCount;i++){
						memcpy(&vVertex[i],pVB,sizeof(Float3));
						pVB+=44;
					}
					pTestManualEnt->UpdateVB(&vVertex[0],mmeInfo.uiVertexCount);
					pTestManualEnt->UpdateIB(pTestEnt->GetMesh()->GetIB(),mmeInfo.uiFaceCount);
					pTest->attachObject(pTestManualEnt);
					*/
// 					StaticMesh*	pMesh	=	pTestEnt->GetMesh();
// 					float*	pVB	=	(float*)pMesh->GetVB();
// 					U32*	pIB	=	(U32*)pMesh->GetIB();
				
			//StaticMesh*	pmesh	=	new StaticMesh("..\\Data\\AirMesh\\Car.ame");
			//pmesh->Create();
			//pmesh->SetMaterialName("Test2");

			//pTest	=	m_pScene->GetRootNode()->CreateChildSceneNode("TestNode");
			//pTest->attachObject(pEnt);
					Data data;
					ResourceSystem::GetSingleton()->Find("AirMesh/NAV2.ame",data);
					NavMesh::Info navinfo;
					navinfo.pData	=	data.buff;
					navinfo.uiSize	=	data.size;
							
					pMesh	=	new NavMesh("testnav",&navinfo);
					pMesh->AddRef();

					//g_pController	=	new ObjectController;
					//m_pScene->GetRootNode()->attachObject(g_pController);

					//ManualMeshEntity::Info	info;
					//info.uiVertexCount	=	890;
					//info.uiIndexCount	=	980;
					//info.uiVertexSize	=	sizeof(Float3);
					//info.vdInfo.SetDeclP3();
					//info.strMaterial	=	"RedHelper";
					//info.enDrawType		=	Render::Draw::enPT_LINELIST;
					//pTestManualEnt	=	EngineSystem::GetSingleton()->CreateProduct<ManualMeshEntity*>("Test","ManualMeshEntity",&info);

					//pTestManualEnt->UpdateVB(pMesh->GetEdgeVB(),185);
					////pTestManualEnt->UpdateIB(pMesh->GetIB(),98);
					//m_pScene->GetRootNode()->attachObject(pTestManualEnt);

			RenderTarget::Info	rtinfo;
			Render::TFormat fmtArray[]={
				enTFMT_R32_FLOAT,
				enTFMT_B8G8R8A8_UNORM,
				enTFMT_B8G8R8A8_UNORM,
				enTFMT_B8G8R8A8_UNORM,
				enTFMT_B8G8R8A8_UNORM,
			};
			rtinfo.SetMutilTargetScreen(5,fmtArray,1.0f,true,m_pMainWindow);
			//rtinfo.vecTextureInfo[0].mipmap	=	3;
			//rtinfo.vecTextureInfo[0].bAutoMipMap	=	true;
			m_pMRT	=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("MRT",&rtinfo);
			rtinfo	=	RenderTarget::Info();
			
			m_pMRT->SetClearFlag(true,true,true);
			m_pMRT->AddPhaseFlag(enPI_MRT);
			m_pMRT->SetBKColor(Float4(1,1,1,1));

			m_pMRT->AddCamera(m_pMainCamera);


			rtinfo.SetSingleTargetScreen(enTFMT_R16G16B16A16_FLOAT,1.0f,true,m_pMainWindow);
			m_pRT_AO			=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("AO",&rtinfo);
			m_pRT_AO->SetClearFlag(false,true,false);





			rtinfo.SetSingleTargetScreen(enTFMT_R8G8B8A8_UNORM,1.0f,false);
			m_pRT_SO	=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("SO",&rtinfo);
			m_pRT_SO->SetClearFlag(false,true,false);

			rtinfo.SetSingleTarget(1024,64,enTFMT_R8G8B8A8_UNORM);
			m_pRT_EnvSphere	=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("EnvSphere",&rtinfo);
			m_pRT_EnvSphere->SetClearFlag(false,true,false);
			rtinfo.SetSingleTarget(256,16,enTFMT_R16G16B16A16_FLOAT);
			m_pRT_EnvSAT	=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("EnvSAT",&rtinfo);
			m_pRT_EnvSAT->SetClearFlag(false,true,false);

			//m_Tesellation.Init();
			m_CSM.Init(m_pMainCamera,3);
			m_OIT.Initialize(m_pMainWindow);
			m_VoxelGen.Initialize(m_pMainWindow);


			
			m_pQuadCopy		=	EngineSystem::GetSingleton()->CreateProduct<Material>("QuadCopy");
			m_pSSAO			=	EngineSystem::GetSingleton()->CreateProduct<Material>("SSAO");
			m_pCombine		=	EngineSystem::GetSingleton()->CreateProduct<Material>("Combine");
			m_pSky			=	EngineSystem::GetSingleton()->CreateProduct<Material>("Sky");
			m_pSSSO			=	EngineSystem::GetSingleton()->CreateProduct<Material>("SSSO");

			m_pCubeToViewSphere	=	EngineSystem::GetSingleton()->CreateProduct<Material>("CubeToViewSphere");
			m_pViewSphereSAT	=	EngineSystem::GetSingleton()->CreateProduct<Material>("ViewSphereSAT");
			m_pAmbientLight		=	EngineSystem::GetSingleton()->CreateProduct<Material>("AmbientLight");
			return	true;
		}

		Air::U1 DefaultPipeline::Destroy()
		{
			//SAFE_DELETE(g_pController);
			m_OIT.Release();
			m_CSM.Release();
			m_VoxelGen.Release();
			//m_Tesellation.Release();

			SAFE_RELEASE_REF(pMesh);



			SAFE_RELEASE_REF(m_pQuadCopy);
			SAFE_RELEASE_REF(m_pSSAO);

			SAFE_RELEASE_REF(m_pRT_AO);
			SAFE_RELEASE_REF(m_pCombine);
			SAFE_RELEASE_REF(m_pSky);
			SAFE_RELEASE_REF(m_pCubeToViewSphere);
			SAFE_RELEASE_REF(m_pViewSphereSAT);
			SAFE_RELEASE_REF(m_pAmbientLight);

			SAFE_RELEASE_REF(m_pSSSO);
			SAFE_RELEASE_REF(m_pRT_SO);
			SAFE_RELEASE_REF(m_pRT_EnvSphere);
			SAFE_RELEASE_REF(m_pRT_EnvSAT);

			SAFE_RELEASE_REF(m_pMRT);


			return	__super::Destroy();
		}

		Air::U1 DefaultPipeline::RenderOneFrame(const FrameTime& frameTime)
		{

			//pTest->SetPosition(Float3(sin(m_FrameState.fTotalTime)*10,0,cos(m_FrameState.fTotalTime)*10));
			//Float4	vQuat	=	Float4(Float3(0,1,0),m_FrameState.fTotalTime);
			//pTest->SetQuat(vQuat);
			Render::Device*	pDevice	=	Render::System::GetSingleton()->GetDevice();//
			pDevice->ResetCounter();




			ListenerList::iterator	itr	=	m_lstListener.begin();
			for(;itr!=m_lstListener.end();itr++){
				(*itr)->OnBeforeRenderFrame(frameTime);
			}

			m_CSM.UpdateCamera(m_pMainCamera);

			//if(m_pScene!=NULL){
			//	m_pScene->UpdateSceneTree(frameTime);
			//}

			RenderSystem*	pSys	=	Render::System::GetSingleton();
			//清理渲染队列中的物体
			pSys->ClearRenderObject();

			m_pMainWindow->ClearPhaseFlag();
			m_pMainWindow->AddPhaseFlag(enPI_Alpha);
			m_pMainWindow->AddPhaseFlag(enPI_Helper);
			m_pMainWindow->AddPhaseFlag(enPI_UI);
			m_pMainWindow->AddPhaseFlag(enPI_Overlay);


			//查找所有摄像机
			CameraSet	setCamera;
			pSys->FindActiveCamera(setCamera);

			m_pMainCamera->FindMovableObject(m_pScene);

			CameraSet::iterator	i	=	setCamera.begin();
			for(;i!=setCamera.end();i++){
				if(m_pMainCamera	!=	(*i))
					(*i)->FindMovableObject(m_pScene,NULL);
			}

			setCamera.clear();

			m_pScene->UpdateMovableObject(frameTime);

			m_pMRT->SetClearFlag(true,true,true);
			m_pMRT->Update();

			m_pMRT->SetClearFlag(false,false,false);
			if(m_pMRT->BeforeUpdate()){
				Float44 matVPInv	=	m_pMainCamera->GetViewProjMatrix();
				matVPInv.Inverse();
				m_pSky->GetConstantBuffer()->UpdateData(&matVPInv);
				m_pSky->RenderOneObject(m_pQuad);
				m_pMRT->AfterUpdate();
			}
			//
			//m_Tesellation.UpdateTarget(pMainCamera);
			//m_VoxelGen.Update(NULL);

			m_CSM.UpdateTarget();
			


			//CubeToViewSphere
			if(m_pRT_EnvSphere->BeforeUpdate()){

				Float44	matInvV	=	m_pMainCamera->GetViewMatrix();
				matInvV.Inverse();

				m_pCubeToViewSphere->GetConstantBuffer()->UpdateData(&matInvV);

				m_pCubeToViewSphere->RenderOneObject(m_pQuad);
				m_pRT_EnvSphere->AfterUpdate();
			}
			//ViewSphereSAT
			if(m_pRT_EnvSAT->BeforeUpdate()){

				m_pViewSphereSAT->RenderOneObject(m_pQuad);
				m_pRT_EnvSAT->AfterUpdate();
			}
			//SSAO
			if(m_pRT_AO->BeforeUpdate()){
				m_pMainCamera->Render2D(m_pMainWindow->GetWidth(),m_pMainWindow->GetHeight());

				//m_pAmbientLight->GetConstantBuffer()->GetBuffer();
				Float44	matInvVP	=	m_pMainCamera->GetViewProjMatrix();
				matInvVP.Inverse();

				m_pAmbientLight->GetConstantBuffer()->UpdateData(&matInvVP);
				m_pAmbientLight->RenderOneObject(m_pQuad);

				m_pRT_AO->AfterUpdate();
			}

			//SSSO
			/*
			if(m_pRT_SO->BeforeUpdate()){
	
				Float44	matInvVP	=	m_pMainCamera->GetViewProjMatrix();
				matInvVP.Inverse();

				m_pSSSO->GetConstantBuffer()->UpdateData(&matInvVP);
				m_pSSSO->RenderOneObject(m_pQuad);

				m_pRT_SO->AfterUpdate();
			}
			*/

			

			//SSAO
			m_pMainWindow->SetClearFlag(false,true,false);
			if(m_pMainWindow->BeforeUpdate()){

				//m_pSSAO->RenderOneObject(m_pQuad);
				//m_pQuadCopy->RenderOneObject(m_pQuad);
				m_pCombine->RenderOneObject(m_pQuad);
				//m_pMainWindow->AfterUpdate();
			//	if(RenderSystem::GetSingleton()->GetDevice()->GetHWVersion() == enRSV_11)
			//		m_OIT.Update(m_pQuad);
				
				m_pMainWindow->AfterUpdate(false);
			}
			if(RenderSystem::GetSingleton()->GetDevice()->GetHWVersion() == enRSV_11)
				m_VoxelGen.Update(m_pQuad,this);

			m_pMainWindow->ClearPhaseFlag();
			m_pMainWindow->AddPhaseFlag(enPI_Helper);
			m_pMainWindow->AddPhaseFlag(enPI_UI);
			m_pMainWindow->AddPhaseFlag(enPI_Overlay);
			m_pMainWindow->SetClearFlag(false,false,false);
			m_pMainWindow->Update();
			//调用监听器
			itr	=	m_lstListener.begin();
			for(;itr!=m_lstListener.end();itr++){
				(*itr)->OnAfterRenderFrame(frameTime);
			}

#if 0
			AString	strBatch	=	Common::Converter::ToString(pDevice->GetDrawBatch())+"[批次]\n";
			OutputDebugStringA(strBatch.c_str());
#endif
			return	true;
		}

		bool DefaultPipeline::mouseMoved( const OIS::MouseEvent &arg )
		{
			
			S8*	pMouseArray	=	GetGlobalSetting().m_pInputSystem->m_MouseArray;
			
			if(pMouseArray[OIS::MB_Right]){
				Float3	dir		=	GetMainCamera()->GetDir();
				Float3	pos		=	GetMainCamera()->GetPosition();
				Float3 vRelativePos;//	=	pos	-	TargetPos;

				Float3	updir	=	GetMainCamera()->GetUpDir();
				Float3	right	=	updir.Cross(dir);

				Common::Quaternion	quat(updir,arg.state.X.rel*0.0025f);


				Common::Quaternion	quat2(right,arg.state.Y.rel*0.0025f);

				

				vRelativePos	=	quat2*dir;


				vRelativePos	=	quat*vRelativePos;

				if(abs(vRelativePos.Dot(updir))	<0.99f){

					//dir	=	-vRelativePos.NormalizeCopy();
					GetMainCamera()->SetDir(vRelativePos);

					//TargetPos	+=	dir*(arg.state.Z.rel*0.05f);
					//pos =	vRelativePos + TargetPos;//
					//m_pMainCamera->SetPosition(pos);
				}
			}else	if(pMouseArray[OIS::MB_Middle]){
				Float3	dir		=	GetMainCamera()->GetDir();
				Float3	pos		=	GetMainCamera()->GetPosition();
				//Float3 vRelativePos	=	pos	-	TargetPos;

				Float3	updir	=	GetMainCamera()->GetUpDir();
				Float3	right	=	updir.Cross(dir);
				Float3  vRealUp	=	dir.Cross(right);

				Float3	Offset	=	-right*arg.state.X.rel*0.1f	+	vRealUp*arg.state.Y.rel*0.1f;
				//TargetPos		+=	Offset;
				GetMainCamera()->SetPosition(pos+Offset);
			}
			Float3	dir		=	GetMainCamera()->GetDir();
			Float3	pos		=	GetMainCamera()->GetPosition();
			GetMainCamera()->SetPosition(pos+dir*arg.state.Z.rel*0.1f);
			
			//if(g_pController!=NULL){
			//	Float3 vPorjPos	=	Float3(
			//		(float)arg.state.X.abs/(float)m_pMainWindow->GetWidth(),
			//		(float)arg.state.Y.abs/(float)m_pMainWindow->GetHeight(),
			//		1.0f);
			//	vPorjPos.x	=	vPorjPos.x*2-1;
			//	vPorjPos.y	=	1-2*vPorjPos.y;

			//	Float44 matVP	= m_pMainCamera->GetViewProjMatrix();
			//	matVP.Inverse();
			//	vPorjPos	=	matVP*vPorjPos;
			//	vPorjPos	-=	pos;
			//	vPorjPos.Normalize();

			//	g_pController->ChangeType(pos,vPorjPos);
			//}
			return true;
		}
		static Float3 vEnd;
		bool DefaultPipeline::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			POINT	p;
			p.x	=	arg.state.X.abs;
			p.y	=	arg.state.Y.abs;

			RECT	r;
			GetClientRect(GetGlobalSetting().m_EngineParam.hWnd,&r);

			POINT	size;
			size.x	=	r.right		-	r.left;
			size.y	=	r.bottom	-	r.top;

			Ray	ray	=	GetMainCamera()->BuildRay(p.x/(float)size.x,p.y/(float)size.y);

			float	fDis	=	9999999.0f;

			if(id	==	OIS::MB_Middle){

				if(GetCurrentScene()->GetStaticSceneNode()->RayCast(ray,&fDis))
				//TreeElement* pElement	=	pMesh->RayCast(ray,&fDis);
				//if(pElement)
				{
					Float3	vPos	=	ray.m_vStart+ray.m_vDirection*fDis;
					vEnd			=	vPos;
					pMNode->SetPosition(vPos);
				}
				//Ray	ray	=	GetGlobalSetting().GetCursorPostionRay(p);
				//if(ray.Intersect(pTestEnt->GetWorldBoundingBox())){

				//	OutputDebugStringA("OK\n");
				//}else{
				//	OutputDebugStringA("ERROR\n");
				//}
			}else if(id == OIS::MB_Left){
				TreeElement* pElement	=	NULL;//pMesh->RayCast(ray,&fDis);
				if(pElement)
				{
					Float3	vPos	=	ray.m_vStart+ray.m_vDirection*fDis;
					WalkPath path;
					//char str[256];
					if(pMesh->FindPath(pElement,vPos,vEnd,&path)){
						//WalkPath::iterator	itr	=	path.begin();
						//for(;itr!=path.end();itr++){
						//	sprintf(str,"pos(%f %f %f)\n",itr->x,itr->y,itr->z);
						//	OutputDebugStringA(str);
						//}
						//OutputDebugStringA("Reached!\n");
						
					}
					//U32* pIndex	=	(U32*)pMesh->GetIB();
					//U32 idx[3];
					//for(int i=0;i<3;i++){
					//	idx[i]	=	pIndex[pElement->m_pData*3+i];
					//}
					DebugTriangleIndex& IDX	=	pMesh->GetDebugIndex();
					//if(!IDX.empty())
					//	pTestManualEnt->UpdateIB(&IDX[0],IDX.size());
				}
				if(pModel)
					pModel->PlayAction("shootlow.CAF",0.1);
			}

			return true;
		}

		bool DefaultPipeline::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{

			return true;
		}

		bool DefaultPipeline::keyPressed( const OIS::KeyEvent &arg )
		{
			switch(arg.key){
				case OIS::KC_LEFT:{
					fVolocity	+=	1.0f;
							   }break;
				case OIS::KC_RIGHT:{
					fVolocity	-=	1.0f;
					if(fVolocity<1.0f)
						fVolocity	=	1.0f;
							   }break;
				case OIS::KC_UP:{

							   }break;
				case OIS::KC_DOWN:{

							   }break;
			}
			return true;
		}

		bool DefaultPipeline::keyReleased( const OIS::KeyEvent &arg )
		{
			switch(arg.key){

			case OIS::KC_UP:{
				//g_mgr.NextState();
							}break;
			case OIS::KC_DOWN:{
				//g_mgr.NextAction();
							  }break;
			case OIS::KC_M:{
				__asm int 3;
						   }break;
			}
			return true;
		}

		void DefaultPipeline::Update(const FrameTime& frameTime)
		{
			if(GetGlobalSetting().m_pInputSystem->m_KeyArray[OIS::KC_A]){
				vMoveDirection.x=	-fVolocity;
			}else if(GetGlobalSetting().m_pInputSystem->m_KeyArray[OIS::KC_D]){
				vMoveDirection.x=	fVolocity;
			}else{
				vMoveDirection.x=	0.0f;
			}

			if(GetGlobalSetting().m_pInputSystem->m_KeyArray[OIS::KC_S]){
				vMoveDirection.z=	-fVolocity;
			}else if(GetGlobalSetting().m_pInputSystem->m_KeyArray[OIS::KC_W]){
				vMoveDirection.z=	fVolocity;
			}else{
				vMoveDirection.z=	0.0f;
			}

			Camera*	pCam	=	GetMainCamera();
			Float3	vUp	=	pCam->GetUpDir();
			Float3	vDir	=	pCam->GetDir();
			Float3	vRight	=	vUp.Cross(vDir);
			vUp				=	vDir.Cross(vRight);
			Float3	x	=	vRight*vMoveDirection.x*frameTime.fTimeDelta;
			Float3	y	=	vUp*vMoveDirection.y*frameTime.fTimeDelta;
			Float3	z	=	vDir*vMoveDirection.z*frameTime.fTimeDelta;

			pCam->SetPosition(pCam->GetPosition()+x+y+z);

			m_cbFrame.vTime.x	=	frameTime.fTimeDelta;
			m_cbFrame.vTime.y	=	frameTime.fTotalTime;
			m_cbFrame.vTime.z	=	frameTime.uiFrameIndex;//sin(frameTime.fTotalTime);
			double	daytime	=	(frameTime.fTotalTime/3600/24);
			m_cbFrame.vTime.w	=	daytime	-	floor(daytime);
			m_cbFrame.vMainCamPos	=	pCam->GetPosition();

			RenderSystem::GetSingleton()->SetCBFrame(m_cbFrame);
		}



	}
}