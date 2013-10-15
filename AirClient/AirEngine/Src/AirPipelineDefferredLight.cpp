#include "AirPipelineDefferredLight.h"
#include "AirEngineSystem.h"
#include "AirMeshEntity.h"
#include "AirEngineMaterial.h"
#include "AirEnginePipeline.h"
#include "AirQuadRenderable.h"
#include "AirGlobalSetting.h"
#include <omp.h>
#define OPENMP_FOR	


namespace	Air{
	namespace	Engine{


		DefferredLight::DefferredLight()
		{
			m_pPointMaterial	=	NULL;
			m_pLightBuffer		=	NULL;
			m_pSphere			=	NULL;
			m_pPipeline			=	NULL;
		}

		Air::U1 DefferredLight::Initialization(Pipeline* pPipeline)
		{
			m_pPipeline			=	pPipeline;
			RenderTarget::Info	info;
			info.SetSingleTargetScreen(enTFMT_R16G16B16A16_FLOAT,1.0f,true,pPipeline->GetMainWindow());
			m_pLightBuffer		=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("DefferredLight",&info);
			m_pLightBuffer->AddPhaseFlag(enPI_DeferredLight);
			m_pLightBuffer->AddCamera(pPipeline->GetMainCamera());
			m_pLightBuffer->SetClearFlag(false,true,false);
			

			m_pPointMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material>("PointLight");
			MeshEntity::Info meshInfo;
			meshInfo.strMeshName	=	"AirMesh/Sphere.ame";
			meshInfo.strMaterial	=	"NoMaterial";
			m_pSphere			=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity>("PointLight",&meshInfo);


			return true;
		}

		Air::U1 DefferredLight::Release()
		{
			m_pPipeline	=	nullptr;
			SAFE_RELEASE_REF(m_pPointMaterial);
			SAFE_RELEASE_REF(m_pSphere);
			SAFE_RELEASE_REF(m_pLightBuffer);
			return true;
		}

		void DefferredLight::Update(const FrameTime& frameTime)
		{
			
			if(m_pLightBuffer->BeforeUpdate()){
				if(m_vecPointLight.empty()){
					m_pLightBuffer->AfterUpdate();
					return;
				}
					
				Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();

				struct {
					Float4	vParam[2];
					Float44 matViewProjInv;
				}cb;

				cb.matViewProjInv	=	m_pPipeline->GetMainCamera()->GetViewProjMatrix();
				cb.matViewProjInv.Inverse();
				memcpy(cb.vParam,&m_vecPointLight[0],sizeof(PointLightInfo));
				m_pPointMaterial->GetConstantBuffer()->UpdateData(&cb);

				m_pPointMaterial->RenderOneObject(m_pSphere);

				
				U32 uiCount	=	m_vecPointLight.size();
				for(U32 i=1;i<uiCount;i++){
					PointLightInfo& info	=	m_vecPointLight[i];
					memcpy(cb.vParam,&info,sizeof(info));
					m_pPointMaterial->GetConstantBuffer()->UpdateData(&cb);
					pDevice->DrawOpt(m_pSphere->GetMesh()->GetDrawBuffer().m_DrawOption);
				}

				m_pLightBuffer->AfterUpdate();
			}
			//m_vecPointLight.clear();
			
		}

		void DefferredLight::AddPointLight( const Float3& pos,float fSize,const Float3& vColor )
		{
			PointLightInfo	point;
			point.vPos		=	pos;
			point.fSize		=	fSize;
			point.vColor	=	vColor;
			m_vecPointLight.push_back(point);
		}


		TileBaseLight::TileBaseLight()
		{
			m_pCSRenderable	=	NULL;
			m_pLightPosColor=	NULL;
			m_pLayerBuffer	=	NULL;
			m_vecPointLight.reserve(1024);
			memset(m_LayerInfo,0,sizeof(LayerInfo)*256);
			m_MainWaitBackEvent.Reset();
		}
		
		Air::U1 TileBaseLight::Initialization( Pipeline* pPipeline )
		{
			m_pCSRenderable		=	new	CSRenderable;
			m_pPipeline			=	pPipeline;
			RenderTarget::Info	info;
			info.SetSingleTargetScreen(enTFMT_R16G16B16A16_FLOAT,1.0f,true,pPipeline->GetMainWindow());
			info.vecTextureInfo[0].SetViewFlag(enVF_SRV|enVF_UAV);
			m_pLightBuffer		=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("TileBaseLighting",&info);
			m_pLightBuffer->AddPhaseFlag(enPI_DeferredLight);
			m_pLightBuffer->AddCamera(pPipeline->GetMainCamera());
			m_pLightBuffer->SetClearFlag(false,true,false);

			Buffer::Info binfo;
			binfo.SetStructureBuffer(32768,sizeof(PointLightInfo));
			binfo.SetViewFlag(enVF_SRV);
			m_pLightPosColor		=	RenderSystem::GetSingleton()->CreateProduct<Buffer>("TBL_PosColor",&binfo);
			binfo.SetStructureBuffer<LayerInfo>(256);
			m_pLayerBuffer			=	RenderSystem::GetSingleton()->CreateProduct<Buffer>("TBL_Layer",&binfo);

			m_pPointMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material>("TileBaseLighting");
			m_pSphere			=	NULL;//EngineSystem::GetSingleton()->CreateProduct<MeshEntity>("PointLight",&meshInfo);

			
			for(U32 i=0;i<32768;i++){
				Float3 vPos(
					Common::Number::RandomF(),
					0,
					Common::Number::RandomF()
					);
				vPos	=	vPos*2-Float3(1,1,1);
				vPos.y=0.003;
				Float3 vColor(
					Common::Number::RandomF(),
					Common::Number::RandomF(),
					Common::Number::RandomF()
					);
				AddPointLight(vPos*100,2,vColor*10);
			}
			StartThread();
			return true;
		}

		Air::U1 TileBaseLight::Release()
		{
			SAFE_DELETE(m_pCSRenderable);
			SAFE_RELEASE_REF(m_pLayerBuffer);
			//StopThread();
			TerminateThread(GetHandle(),-1);
			StopThread();
			return __super::Release();
		}

		void TileBaseLight::Update( const FrameTime& frameTime )
		{
			if(m_vecPointLight.empty()){
				m_vecLayeredLight.resize(32768);
				memset(m_LayerInfo,0,sizeof(LayerInfo)*256);
			}

#ifdef _OPENMP
			omp_set_dynamic(1); 
			omp_set_num_threads(2); 
#pragma message("OPENMP Enable!")
#else
#pragma message("OPENMP Closed!")
#endif
			//BuildSO();

			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
			void* p	=	m_pLightBuffer->GetUAV();
			pDevice->SetUAV(1,(void**)&p);

			

			
			m_MainWaitBackEvent.Wait();

			m_pLightPosColor->UpdateData(&m_vecLayeredLight[0]);
			m_pLayerBuffer->UpdateData(m_LayerInfo);



			pDevice->SetSRV(enCS,2,m_pLightPosColor->GetSRV());
			pDevice->SetSRV(enCS,3,m_pLayerBuffer->GetSRV());

			Float4 v[10];
			v[0]=Float4(m_pLightBuffer->GetWidth(),m_pLightBuffer->GetHeight(),0,0);
			Matrix* pProjInvMat	=	(Matrix*)&v[1];
			m_pPipeline->GetMainCamera()->GetProjMatrix(*pProjInvMat);
			pProjInvMat->Inverse();
			Matrix* pViewMat	=	(Matrix*)&v[5];
			m_pPipeline->GetMainCamera()->GetViewMatrix(*pViewMat);


			Float3 v1=(*pProjInvMat)*Float3(1,1,0);
			
			v[0].z=	v1.x;
			v[0].w=v1.y;
			
			v[9]	=	Float4(
				Engine::GetGlobalSetting().m_pInputSystem->m_iX,
				Engine::GetGlobalSetting().m_pInputSystem->m_iY,
				m_vecPointLight.size(),
				0
				);


			m_pPointMaterial->GetConstantBuffer()->UpdateData(v);
			int x	=	(m_pLightBuffer->GetWidth()+15)>>4;
			int y	=	(m_pLightBuffer->GetHeight()+15)>>4;
			m_pCSRenderable->m_Dispatch[0]	=	x;
			m_pCSRenderable->m_Dispatch[1]	=	y;
			m_pPointMaterial->RenderOneObject(m_pCSRenderable);

			pDevice->SetShader(enCS,NULL);
			p=NULL;
			pDevice->SetUAV(1,(void**)&p);

			//m_vecPointLight.clear();
		}
		void TileBaseLight::AddPointLight( const Float3& pos,float fSize,const Float3& vColor )
		{
			
			PointLightInfo	point;
			point.vPos		=	pos;
			point.fSize		=	fSize;
			point.vColor	=	vColor;
			m_vecPointLight.push_back(point);
		}

		U32	XYZPlaneIntersectSphere(const Float3& xyz,const Float3& center,float fRadius){
			Float3 v =	xyz	- center;
			if(	abs(v.x)<fRadius	||	
				abs(v.y)<fRadius	||
				abs(v.z)<fRadius)
			{
				return 0xffffffff;
			}

			U32 X	=	v.x	<=	fRadius;
			U32	Y	=	v.y	<=	fRadius;
			U32	Z	=	v.z	<=	fRadius;

			return X<<2|Y<<1|Z;
		}

		class LightNode{
		public:
			LightNode(U32 depth=0){
				for(U32 i=0;i<8;i++){
					pChild[i]=NULL;
				}
				uiDepth	=	depth;
			};
			LightNode*	InjectLight(const Float3& pos,float fRadius){
				
				U32 uiChildIndex	=	XYZPlaneIntersectSphere(bound.GetCenter(),pos,fRadius);
				if(uiChildIndex==0xffffffff){
					vecLight.push_back(Float4(pos.x,pos.y,pos.z,fRadius));
					return this;
				}
				if(pChild[uiChildIndex]==NULL){
					pChild[uiChildIndex]	=	new LightNode(uiDepth+1);
					Float3 vHalfSize		=	bound.GetHalfSize();
					Float3 vChildMin		=	vHalfSize*Float3(uiChildIndex>>2,(uiChildIndex>>1)&1,uiChildIndex&1);
					BoundingBox& B			=	pChild[uiChildIndex]->bound;
					B.vMin					=	bound.vMin+vChildMin;
					B.vMax					=	B.vMin+vHalfSize;
				}
				return pChild[uiChildIndex]->InjectLight(pos,fRadius);
			}
			void	DebugPrint(){
				char str[]="--------------------------------------";
				sprintf(&str[uiDepth+1],"%d\n",vecLight.size());
				OutputDebugStringA(str);
				for(U32 i=0;i<8;i++){
					if(pChild[i]!=NULL){
						pChild[i]->DebugPrint();
					}
				}

			}
			U32					uiDepth;
			LightNode*			pChild[8];
			BoundingBox			bound;
			STD_VECTOR<Float4>	vecLight;
			
		};

		void TileBaseLight::BuildSLO()
		{
			U32	uiLightCount	=	m_vecTempLight.size();
			if(uiLightCount==0)
				return;
			const Matrix& mView	=	m_pPipeline->GetMainCamera()->GetViewMatrix();
			//calc boundingbox
			LightNode lightNode;
			BoundingBox& box	=	lightNode.bound;
			for(U32 i=0;i<m_vecTempLight.size();i++){
				Float3& vPos	=	m_vecTempLight[i].vPos;
				if(i==0){
					box.vMin	=	vPos;
					box.vMax	=	vPos;
				}else{
					box.Add(vPos);
				}
			}
			//translate cuboid to cube
			Float3 vSize		=	box.vMax-box.vMin;
			float fMaxSize		=	max(vSize.x,max(vSize.y,vSize.z));
			vSize				=	Float3(fMaxSize,fMaxSize,fMaxSize);
			box.vMax			=	box.vMin+vSize;



			STD_VECTOR<U16>	LightNodeOctree;
			LightNodeOctree.resize(32760);
			U32	uiCount	=	8;

			STD_VECTOR<U32>&		lightIndex	=	m_vecLightIndex;
			lightIndex.resize(uiLightCount);

			U32 iDepth	=	6;

			float fInv	=	pow(2,(float)iDepth)/fMaxSize;
			for(U32 i=0;i<m_vecTempLight.size();i++){
				Float3 v	= m_vecTempLight[i].vPos	-	box.vMin;
				v*=fInv;
				S32 X	=	v.x;
				S32 Y	=	v.y;
				S32 Z	=	v.z;
				U32 uiNode	=	0;
				for(int j=iDepth;j>=0;j--){
					U32 idx =	((X>>j)&1)<<2 | 
								((Y>>j)&1)<<1 |
								((Z>>j)&1);
					idx+=uiNode;
					if(j==0){
						LightNodeOctree[idx]	=	0xffff;
						lightIndex[i]=idx;
						break;
					}else{	
						U16& child	=	LightNodeOctree[idx];
						if(child==0){
							
							child	=	uiCount;
							uiCount	+=	8;
							uiNode=	child;
						}else	if(child==0xffff){
							lightIndex[i]=idx;
							break;
						}else{
							uiNode=	child;
						}
					}
				}
			}

			
			

			

			//U32 uiMaxDepth	=	10;
			//for(U32 i=0;i<m_vecPointLight.size();i++){
			//	Float3	vLightPos	=	m_vecPointLight[i].vPos;
			//	float	fLightSize	=	m_vecPointLight[i].fSize;
			//	lightNode.InjectLight(vLightPos,fLightSize);
			//}

			//lightNode.DebugPrint();
		}

		bool TileBaseLight::RepetitionRun()
		{
			m_BackWaitMainEvent.Wait();

			
			SpliteLayer();

			//BuildSLO();
			
			m_MainWaitBackEvent.Reset();
			return true;
		}

		void TileBaseLight::SpliteLayer()
		{
			U32	uiLightCount	=	m_vecPointLight.size();
			if(uiLightCount==0)
				return;

			PointLightVector& vecLight	=	m_vecTempLight;
			vecLight.resize(uiLightCount);
			memcpy(&vecLight[0],&m_vecPointLight[0],sizeof(PointLightInfo)*uiLightCount);

			//translate light position from world to view
			const Matrix& mView	=	m_pPipeline->GetMainCamera()->GetViewMatrix();
			float	MinNear	=	10000000.0f;
			float	MaxFar	=	-1000000.0f;
			//
			for(U32 i=0;i<uiLightCount;i++){
				vecLight[i].vPos	=	mView*vecLight[i].vPos;
				float fLightNear	=	vecLight[i].vPos.z-vecLight[i].fSize;
				float fLightFar		=	vecLight[i].vPos.z+vecLight[i].fSize;
				if(fLightNear	<	MinNear)	MinNear	=	fLightNear;
				if(fLightFar	>	MaxFar)		MaxFar	=	fLightFar;
			}

			//splite layer
			float	fInv	=	256.0f/(MaxFar	-	MinNear);

			memset(m_LayerInfo,0,sizeof(LayerInfo)*256);
			STD_VECTOR<U32>&		lightIndex	=	m_vecLightIndex;
			lightIndex.resize(uiLightCount*2);

			for(U32 i=0;i<uiLightCount;i++){
				float z	=	vecLight[i].vPos.z - vecLight[i].fSize;
				z		=	(z-MinNear)*fInv;
				if(z<0)z=0;
				U32 idx	=	(U32)z;
				if(idx>255)idx=255;
				lightIndex[i*2]		=	idx;
				lightIndex[i*2+1]	=	m_LayerInfo[idx].uiSize++;
			}
			for(U32 i=1;i<256;i++){
				m_LayerInfo[i].uiOffset	=	m_LayerInfo[i-1].uiOffset+m_LayerInfo[i-1].uiSize;
			}
			PointLightVector& vecLightLayered	=	m_vecLayeredLight;//=vecLight;
			vecLightLayered.resize(uiLightCount);

			for(U32 i=0;i<uiLightCount;i++){
				U32 uiLayerIndex	=	lightIndex[i*2];
				U32 uiIndex			=	lightIndex[i*2+1];
				U32 dstIndex		=	m_LayerInfo[uiLayerIndex].uiOffset+uiIndex;
				memcpy(&vecLightLayered[dstIndex],&vecLight[i],sizeof(PointLightInfo));
			}
			for(U32 i=0;i<256;i++){
				LayerInfo& layer	=	m_LayerInfo[i];
				if(layer.uiSize!=0){
					U32 uiStart	=	layer.uiOffset;
					U32	uiEnd	=	layer.uiSize;
					for(U32 j=0;j<uiEnd;j++){
						U32	uiIndex	=	j+uiStart;
						float fLightNear	=	vecLightLayered[uiIndex].vPos.z-vecLightLayered[uiIndex].fSize;
						float fLightFar		=	vecLightLayered[uiIndex].vPos.z+vecLightLayered[uiIndex].fSize;
						if(j==0){
							layer.fNear	=	fLightNear;
							layer.fFar	=	fLightFar;
						}else{
							if(fLightNear	<	layer.fNear)layer.fNear	=	fLightNear;
							if(fLightFar	>	layer.fFar)	layer.fFar	=	fLightFar;
						}
					}
				}
			}
		}

		void TileBaseLight::StartBackProcess()
		{
			U32	uiLightCount	=	m_vecPointLight.size();
			if(uiLightCount==0){
				m_MainWaitBackEvent.Reset();
				return;
			}
			m_BackWaitMainEvent.Reset();
		}

	}
}