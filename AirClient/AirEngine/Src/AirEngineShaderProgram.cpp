#include "AirEngineShaderProgram.h"
#include "AirRenderSystem.h"
#include "AirEngineSystem.h"
#include "AirEngineMaterialCommon.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{

		static AString	strTypeName[6]={
			".vs11",
			".gs11",
			".ps11",
			".cs11",
			".hs11",
			".ds11"
		};


		ShaderProgram::ShaderProgram( ShaderParamInfo* pInfo,enumShaderType type ){
			m_pInfo		=	pInfo;
			if(pInfo!=NULL){
				int	iLength	=	pInfo->strName.size();
				if(iLength	>	2){
					m_strName.resize(iLength-2);
					memcpy(&m_strName[0],&pInfo->strName[1],iLength-2);
				
				}
			}
			m_Type		=	type;
		}
		Air::U1 ShaderProgram::Create(){
			if(m_strName.empty())
				return	false;
			Render::System*	pRenderSys	=	Render::System::GetSingleton();	

			if(pRenderSys==NULL)
				return	false;

			m_pShader	=	pRenderSys->CreateProduct<Shader*>(m_strName	+	strTypeName[m_Type],"Shader");
			if(m_pShader==NULL)
				return	false;
			
			U32	uiSize	=	m_pInfo->m_vecTextureInfo.size();
			if(uiSize>0)
				m_vecSamplerState.resize(uiSize);
			AString		strSS;
			for(U32	i=0;i<uiSize;i++){
				strSS	=	m_pInfo->m_vecTextureInfo[i].strSamplerState;
				m_vecSamplerState[i]	=	Render::System::GetSingleton()->CreateProduct<SamplerState*>(strSS,"State");
			}
			
			return	true;
		}



		Air::U1 ShaderProgram::Destroy(){
			if(m_pShader!=NULL){
				m_pShader->ReleaseRef();
				m_pShader	=	NULL;
			}


			U32	uiSize		=	m_vecSamplerState.size();
			for(U32	i=0;i<uiSize;i++){
				if(m_vecSamplerState[i]!=NULL)
					m_vecSamplerState[i]->ReleaseRef();
			}
			m_vecSamplerState.clear();
			return	true;
		}

		void ShaderProgram::UpdateTextureArray( TextureArray& vecTexture ){
			U32	uiSize				=	m_pInfo->m_vecTextureInfo.size();
			Render::Device*	pDevice	=	Render::System::GetSingleton()->GetDevice();
			for(U32	i=0;i<uiSize;i++){
				const TextureUnitInfo&	tInfo	=	m_pInfo->m_vecTextureInfo[i];
				if(tInfo.index < vecTexture.size()){
					Render::Texture*	pTex	=	vecTexture[tInfo.index];
					if(pTex!=NULL)
						pDevice->SetSRV(m_Type,tInfo.uiRigister,pTex->GetSRV());
					else
						pDevice->SetSRV(m_Type,tInfo.uiRigister,NULL);
				}
			}
		}

		void ShaderProgram::UpdateShader_SamplerState(){
			RenderSystem*	pSys	=	Render::System::GetSingleton();

			pSys->GetDevice()->SetShader(m_Type,m_pShader);

			U32	uiSize				=	m_vecSamplerState.size();
			for(U32	i=0;i<uiSize;i++){
				pSys->GetDevice()->SetSS(m_Type,i,m_vecSamplerState[i]);
			}
		}
	}
}