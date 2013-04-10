#include "AirScreenSpaceTessellation.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"

namespace	Air{
	namespace	Engine{

#define TESS_WIDTH	800
#define TESS_HEIGHT	600
#define TESS_WIDTH1		(TESS_WIDTH+1)
#define TESS_HEIGHT1	(TESS_HEIGHT+1)
#define TESS_TOTAL_VERTEX	(TESS_WIDTH1*TESS_HEIGHT1)
#define TESS_TOTAL_INDEX	(TESS_WIDTH*TESS_HEIGHT*6)
		TessellationRenderable::TessellationRenderable()
		{
			STD_VECTOR<Float2> vb;
			vb.resize(TESS_TOTAL_VERTEX);
			for(int j=0;j<TESS_HEIGHT1;j++){
				int iLine	=	j*TESS_WIDTH1;
				float y	=	1.0f-2.0f*(float)j/TESS_HEIGHT;
				for(int i=0;i<TESS_WIDTH1;i++){
					int iElement	=	iLine+i;
					vb[iElement]	=	Float2((float)i*2.0f/TESS_WIDTH-1.0f,y);
				}
			}

			STD_VECTOR<U32>	ib;
			ib.resize(TESS_TOTAL_INDEX);
			int iQuad	=	0;
			for(int j=0;j<TESS_HEIGHT;j++){
				int iLine		=	j*TESS_WIDTH1;
				int iNextLine	=	(j+1)*TESS_WIDTH1;
				for(int i=0;i<TESS_WIDTH;i++){
					int i0	=	iLine+i+0;
					int i1	=	iLine+i+1;
					int i2	=	iNextLine+i+0;
					int i3	=	iNextLine+i+1;
					ib[iQuad*6]			=	i0;
					ib[iQuad*6+1]		=	i1;
					ib[iQuad*6+2]		=	i2;

					ib[iQuad*6+3]		=	i2;
					ib[iQuad*6+4]		=	i1;
					ib[iQuad*6+5]		=	i3;
					ib[iQuad*6]		=	i0;


					iQuad++;

				}
			}

			Render::System*	pSys	=	Render::System::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(TESS_TOTAL_VERTEX,8);
			vbInfo.InitData			=	&vb[0];
			//vbInfo.
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer>("TessVB",&vbInfo);

			vbInfo.SetIndexBuffer32(TESS_TOTAL_INDEX);
			vbInfo.InitData			=	&ib[0];
			m_DrawBuff.m_pIndexBuff			=	pSys->CreateProduct<Buffer>("TessIB",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP2();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare>("QuadVD",&vdInfo);


			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;
			m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	TESS_TOTAL_VERTEX;
			m_DrawBuff.m_DrawOption.m_uiIndexCount	=	TESS_TOTAL_INDEX;
		}

		TessellationRenderable::~TessellationRenderable()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pIndexBuff);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);
		}


		ScreenSpaceTessellation::ScreenSpaceTessellation()
		{
			m_pTessRenderable		=	NULL;
			m_pTessellationTarget	=	NULL;
			m_pTessellationMaterial	=	NULL;
		}

		Air::U1 ScreenSpaceTessellation::Init()
		{
			if(m_pTessRenderable==NULL){
				m_pTessRenderable	=	AirNew<TessellationRenderable>();
			}
			if(m_pTessellationMaterial==NULL){
				m_pTessellationMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material>("ScreenSpaceTessellation");
			}

			enumTextureFormat	fmt[5]={
				enTFMT_R32_FLOAT,
				enTFMT_R8G8B8A8_UNORM,
				enTFMT_R8G8B8A8_UNORM,
				enTFMT_R8G8B8A8_UNORM,
				enTFMT_R8G8B8A8_UNORM
			};

			RenderTarget::Info rtinfo;
			rtinfo.SetMutilTargetScreen(5,fmt,1.0f,TRUE,RenderSystem::GetSingleton()->GetMainWindow());
			m_pTessellationTarget	=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("TessMRT",&rtinfo);
			m_pTessellationTarget->SetClearFlag(true,true,true);
			m_pTessellationTarget->SetBKColor(Float4(1.0f,1.0f,1.0f,1.0f));
			
			return true;
		}

		Air::U1 ScreenSpaceTessellation::Release()
		{
			AirDelete(m_pTessRenderable		 );
			SAFE_RELEASE_REF(m_pTessellationTarget	 );
			SAFE_RELEASE_REF(m_pTessellationMaterial );
			return true;
		}

		ScreenSpaceTessellation::~ScreenSpaceTessellation()
		{

		}

		Air::U1 ScreenSpaceTessellation::UpdateTarget(Camera* pMainCamera)
		{
			if(m_pTessellationTarget!=NULL){

				Float44	matVP[2];
				matVP[0]	=	pMainCamera->GetViewProjMatrix();
				matVP[1]	=	matVP[0];
				matVP[0].Inverse();
				m_pTessellationMaterial->GetConstantBuffer()->UpdateData(matVP);
				if(m_pTessellationTarget->BeforeUpdate()){
					m_pTessellationMaterial->RenderOneObject(m_pTessRenderable);
					m_pTessellationTarget->AfterUpdate();
				}
			}

			return true;
		}

	}
}

