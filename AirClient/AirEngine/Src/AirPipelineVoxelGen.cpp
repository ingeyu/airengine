#include "AirPipelineVoxelGen.h"
#include "AirEngineSystem.h"
#include "AirEngineCamera.h"
#include "AirEngineMaterial.h"
#include "AirMeshEntity.h"
#include "AirBoxRenderable.h"

#define GPU_DEBUG



namespace	Air{
	const static U32	VOXEL_DEPTH				=	7;
	const static float	VOXEL_BOUND_SIZE		=	powf(2.0f,VOXEL_DEPTH);
	const static float	VOXEL_HALF_BOUND_SIZE	=	powf(2.0f,VOXEL_DEPTH-1);

	namespace	Engine{
		struct Voxel{
			Voxel(){
				uiMask		=	0;
				uiOffset	=	0;
				uiColor		=	0;
			};
			U32 uiMask:8;
			U32	uiOffset:24;
			U32	uiColor;
		};


		struct VoxelTree{
			VoxelTree(){
				vecVoxel.resize(1);
			};
			U32	Add(const Float3& vPos,U32	uiColor,Voxel* pVoxle	=	NULL,BoundingBox*	pBoundingBox=NULL,int iLevel	=	0){

				if(iLevel	==	0){
					pVoxle	=	&vecVoxel[0];
				}
				if(iLevel>15){
					if(pVoxle->uiColor==0)
						pVoxle->uiColor	=	uiColor;
					return iLevel;
				}
				if(pBoundingBox==NULL)
					pBoundingBox	=	&m_Bound;
				Float3 vSize	=	pBoundingBox->GetHalfSize();
				Float3 vCenter	=	pBoundingBox->GetCenter();
				int x	=	vPos.x > vCenter.x;
				int y	=	vPos.y > vCenter.y;
				int z	=	vPos.z > vCenter.z;
				int idx	=	(x<<2) | (y <<1) | z;

				if(pVoxle->uiMask==0){
					pVoxle->uiOffset	=	vecVoxel.size();
					pVoxle->uiMask|=idx;
					int Offset	=	pVoxle->uiOffset;
					pVoxle=NULL;
					vecVoxel.resize(Offset + 8);
					pVoxle	=	&vecVoxel[Offset+idx];
				}else{
					pVoxle->uiMask|=idx;
					int Offset	=	pVoxle->uiOffset;
					pVoxle	=	&vecVoxel[Offset+idx];
				}

				Float3 vHalfSize	=	vSize*0.5f;
				Float3 vMin			=	(vCenter-vSize)+vSize*Float3(x,y,z);

				BoundingBox box(vMin,vMin+vSize);
				Add(vPos,uiColor,pVoxle,&box,iLevel+1);

			};
			std::vector<Voxel>	vecVoxel;;
			BoundingBox			m_Bound;
		};

		VoxelGenerator::VoxelGenerator()
		{
			m_pVoxel			=	NULL;
			m_pNodeTree			=	NULL;
			m_pGenVoxelTree		=	NULL;
			m_pMipVoxelTree		=	NULL;
			m_pRT				=	NULL;
			m_pDebugSVO			=	NULL;
			m_pDebugSVORenderable=NULL;
			m_pDebugSVOMaterial=NULL;
		}

		Air::U1 VoxelGenerator::Initialize( Render::Window* pMainWindow )
		{
			RenderTarget::Info rtinfo;
			rtinfo.SetSingleTarget(VOXEL_BOUND_SIZE,VOXEL_BOUND_SIZE,enTFMT_R8G8B8A8_UNORM);

			m_pRT		=	RenderSystem::GetSingleton()->CreateProduct<Render::Target>("SVO_Test",&rtinfo);

			Render::Buffer::Info info;
			info.SetStructureBuffer(1048576,sizeof(U32));
			info.SetViewFlag(enVF_SRV|enVF_UAV|enVF_Counter);
			m_pVoxel	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer>("SVO_Counter",&info);
			
			info.SetByteAddressBuffer(1048576,sizeof(U32));
			info.SetViewFlag(enVF_SRV|enVF_UAV);
			m_pNodeTree	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer>("SVO_Octree",&info);
			
			Data data;
			Common::File::Load("../Data/AirMesh/Teapot.svo",data);

			info.SetByteAddressBuffer(data.size/sizeof(U32),sizeof(U32));
			info.SetViewFlag(enVF_SRV);
			info.InitData	=	data.buff;
			m_pDebugSVO	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer>("SVO_DebugBuffer",&info);
			//m_pDebugSVO->UpdateData(data.buff);

			m_pCamera	=	EngineSystem::GetSingleton()->CreateProduct<Camera>("SVO_Camera");
			m_pCamera->SetNear(1);
			m_pCamera->SetFar(129);
			m_pCamera->SetDir(0,0,1);
			m_pCamera->SetWidth(128);
			m_pCamera->SetHeight(128);
			m_pCamera->SetOrtho(true);
			m_pCamera->SetPosition(0,0,-64);

			m_pGenVoxelTree	=	EngineSystem::GetSingleton()->CreateProduct<Material>("SVO_Build_NoSkin");	//"SVO_Test"

			m_pRT->AddCamera(m_pCamera);


			m_pDebugSVORenderable	=	new BoxRenderable();
#ifdef GPU_DEBUG
			m_pDebugSVOMaterial		=	EngineSystem::GetSingleton()->CreateProduct<Material>("SVO_Debug");
#else
			m_pDebugSVOMaterial		=	EngineSystem::GetSingleton()->CreateProduct<Material>("WorldHelperWireFrame");
#endif
			return true;
		}

		Air::U1 VoxelGenerator::Release()
		{
			SAFE_RELEASE_REF(m_pVoxel);
			SAFE_RELEASE_REF(m_pNodeTree);
			SAFE_RELEASE_REF(m_pCamera);
			SAFE_RELEASE_REF(m_pGenVoxelTree);
			SAFE_RELEASE_REF(m_pRT);
			SAFE_RELEASE_REF(m_pDebugSVO);
			delete m_pDebugSVORenderable;
			m_pDebugSVORenderable=NULL;
			return true;
		}

		int OrderSortCompare(const void* pSrc0,const void* pSrc1){
			const Float3* p0 = (const Float3*)pSrc0;
			const Float3* p1 = (const Float3*)pSrc1;
			return p0->x > p1->x;
		}

		void VoxelGenerator::Update( Renderable* pRenderable ,Camera* pMainCamera)
		{
			static MeshEntity*	pEnt = NULL;
			if(pEnt==NULL){
				MeshEntity::Info	info;
				info.strMaterial	=	"SVO_Test";
				info.strMeshName	=	"AirMesh/Strom/Wolf.AME";
				pEnt	=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity>(info.strMeshName,&info);;
				;
				pEnt->GetWorldMatrix()->SetPosition(-pEnt->GetOrginBoundingBox().GetCenter()*10);
				pEnt->GetWorldMatrix()->m00	=	10;
				pEnt->GetWorldMatrix()->m11	=	10;;
				pEnt->GetWorldMatrix()->m22	=	10;;

			}

			

			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
#if 1
			static bool bVoxel	=	false;
			if(!bVoxel){
				bVoxel=true;


				
				Float3 vCameraPos[3]={Float3(0,0,-VOXEL_HALF_BOUND_SIZE-1),Float3(0,-VOXEL_HALF_BOUND_SIZE-1,0),Float3(-VOXEL_HALF_BOUND_SIZE-1,0,0)};
				Float3 vCameraDir[3]={Float3(0,0,1),Float3(0,1,0),Float3(1,0,0)};
				Float3 vCameraUp[3]	={Float3(0,1,0),Float3(1,0,0),Float3(0,1,0)};


				m_pRT->SetClearFlag(true,true,true);
				if(m_pRT->BeforeUpdate()){
						void* pRTV[1]={m_pRT->GetRTV()};
						void* pDSV=NULL;
						void* pUAV[2]={m_pVoxel->GetUAV(),m_pNodeTree->GetUAV()};
						U32	clearValue[4]={0};
						pDevice->ClearUAV(pUAV[1],clearValue);
						pDevice->SetRTV_DSV_UAV(1,pRTV,pDSV,1,2,pUAV,0);					
						m_pCamera->SetFar(VOXEL_BOUND_SIZE+1);
						for(U32 i=0;i<3;i++){
						m_pCamera->SetPosition(vCameraPos[i]);
						m_pCamera->SetDir(vCameraDir[i]);
						m_pCamera->SetUpDir(vCameraUp[i]);
						m_pCamera->SetWidth(VOXEL_BOUND_SIZE);
						m_pCamera->Render2D(VOXEL_BOUND_SIZE,VOXEL_BOUND_SIZE);



						if(m_pGenVoxelTree)
							m_pGenVoxelTree->RenderOneObject(pEnt);
					}
					m_pRT->AfterUpdate();
				}
			}

#else
			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
			pDevice->SetVP(0,0,128,128);

			//m_pCamera->Render2D(128,128);
			m_pRT->SetClearFlag(true,true,true);
			if(m_pRT->BeforeUpdate()){
				m_pCamera->Render2D(128,128);

				m_pGenVoxelTree->RenderOneObject(pEnt);

				m_pRT->AfterUpdate();
			}

#endif

#ifdef GPU_DEBUG
			pDevice->SetVP(0,0,800,600);
			RenderSystem::GetSingleton()->GetMainWindow()->BeforeUpdate();
			pMainCamera->Render2D();

			pDevice->SetSRV(enPS,0,m_pNodeTree->GetSRV());
			struct{
				Matrix matViewProjInv;
				U32 uiOrder;
			}CBMaterial;
			pMainCamera->GetViewProjMatrix(CBMaterial.matViewProjInv);
			CBMaterial.matViewProjInv.Inverse();

			Float3 vDir	=	pMainCamera->GetRealDirection();
			vDir.Normalize();
			Float3 vTest[8]={
				Float3(0,0,0),
				Float3(0,0,1),
				Float3(0,1,0),
				Float3(0,1,1),

				Float3(1,0,0),
				Float3(1,0,1),
				Float3(1,1,0),
				Float3(1,1,1)
			};

			for(U32 i=0;i<8;i++){
				vTest[i].x = vTest[i].Dot(vDir);
				vTest[i].y	=	i;
			}
			std::qsort(vTest,8,sizeof(Float3),OrderSortCompare);
			CBMaterial.uiOrder=0;
			for(U32 i=0;i<8;i++){
				CBMaterial.uiOrder	|=	((U32)(vTest[i].y))<<(i*3);
			}
			m_pDebugSVOMaterial->GetConstantBuffer()->UpdateData(&CBMaterial);
			m_pDebugSVOMaterial->RenderOneObject(pRenderable);

			RenderSystem::GetSingleton()->GetMainWindow()->AfterUpdate(false);
#else
			U32 iLevel	=	GetTimer().m_FrameTime.fTotalTime;
			iLevel=iLevel>>1;
			iLevel%=4;
			iLevel+=2;
			static Data data;
			if(data.IsNull())
				Common::File::Load("../Data/AirMesh/Teapot.svo",data);
			U32*	pSVO	=	(U32*)data.buff;

			U32 uiDepth=0;
			U32 uiOffset[10]={0};
			U32	uiStack[10]={0};
			Float3 vOffset[8]={
				Float3(0,0,0),
				Float3(0,0,1),
				Float3(0,1,0),
				Float3(0,1,1),

				Float3(1,0,0),
				Float3(1,0,1),
				Float3(1,1,0),
				Float3(1,1,1),
			};
			Float3 vMin(-64,-64,-64);
			Float3 vHalfSize(64,64,64);
			float	fMaxDis		=	10000;
			while(1){
				for(U32 i=uiStack[uiDepth];i<8;){
					U32 addr		=	(uiOffset[uiDepth]+i);
					U32 uiChild	=	pSVO[addr];
					if(uiChild==0){
						i++;
						continue;
					}
					Float3	vNewMin	=	vMin+vOffset[i]*vHalfSize;
					Float3	vNewMax	=	vNewMin+vHalfSize;
					if(uiDepth	==	iLevel){
						((BoxRenderable*)m_pDebugSVORenderable)->m_WorldMatrix	=	Float44((vNewMin+vNewMax)*0.5,vHalfSize*0.5,Float4(0,0,0,1));
						m_pDebugSVOMaterial->RenderOneObject(m_pDebugSVORenderable);
						i++;
						continue;
					}else{
						uiStack[uiDepth]	=	i+1;
						uiDepth++;
						uiStack[uiDepth]	=	0;
						uiOffset[uiDepth]	=	uiChild;
						vHalfSize	/=	2.0f;
						vMin		=	vNewMin;
						i=0;
					}

				}
				if(uiDepth==0){
					break;
				}else{
					uiDepth--;
					vHalfSize*=2.0f;
					vMin	-=	vOffset[uiStack[uiDepth]-1]*vHalfSize;
				}
			}
#endif
		}

	}
}