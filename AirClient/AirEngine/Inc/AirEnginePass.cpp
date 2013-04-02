#include "AirEnginePass.h"
#include "AirEngineMaterialParse.h"
#include "AirEngineSystem.h"
#include "AirRenderSystem.h"
#include "AirGlobalSetting.h"

namespace	Air{
	namespace	Engine{


		Pass::Pass( PassInfo* pInfo ){
			if(pInfo!=NULL)
				m_strName	=	pInfo->strName;
			m_pInfo		=	pInfo;

			m_pRasterizerState		=	NULL;
			m_pDepthStencilState	=	NULL;
			m_pBlendState			=	NULL;

			m_Hash.uiHash			=	0;

			for(int i=0;i<6;i++){
				m_pShaderArray[i]	=	NULL;
			}
		}

		Pass::~Pass(){

		}

		Air::U1 Pass::Create(){
			if(m_strName.empty())
				return	false;
			if(m_pInfo==NULL)
				return	false;

			Render::System*	pRenderSys	=	Render::System::GetSingleton();
			if(pRenderSys==NULL)
				return	false;
			if(!m_pInfo->strRasterizerState.empty())
				m_pRasterizerState	=	pRenderSys->CreateProduct<Render::IRasterizerState*>(m_pInfo->strRasterizerState,"State");
			if(!m_pInfo->strDepthStencilState.empty())
				m_pDepthStencilState=	pRenderSys->CreateProduct<Render::IDepthStencilState*>(m_pInfo->strDepthStencilState,"State");
			if(!m_pInfo->strBlendState.empty())
				m_pBlendState		=	pRenderSys->CreateProduct<Render::IBlendState*>(m_pInfo->strBlendState,"State");

			for(UInt i=0;i<6;i++){
				m_pShaderArray[i]	=	CreateShaderProgram(m_pInfo->pShaderArray[i],(enumShaderType)i);
				if(m_pShaderArray[i]!=NULL){
					m_Hash.uiShaderNumber++;
					m_Hash.AddShader(m_pShaderArray[i]->GetShader());
				}
			}

			if(m_pRasterizerState!=NULL){
				m_Hash.uiStateNumber++;
				m_Hash.AddState(m_pRasterizerState);
			}
			if(m_pDepthStencilState!=NULL){
				m_Hash.uiStateNumber++;
				m_Hash.AddState(m_pDepthStencilState);
			}
			if(m_pBlendState!=NULL){
				m_Hash.uiStateNumber++;
				m_Hash.AddState(m_pBlendState);
			}

			return	true;
		}

		Air::U1 Pass::Destroy(){

			for(UInt i=0;i<6;i++){
				if(m_pShaderArray[i]!=NULL){
					m_pShaderArray[i]->Destroy();
					delete m_pShaderArray[i];
					m_pShaderArray[i]	=	NULL;
				}

			}
			if(m_pRasterizerState!=NULL){
				m_pRasterizerState->ReleaseRef();
				m_pRasterizerState	=	NULL;
			}
			if(m_pDepthStencilState!=NULL){
				m_pDepthStencilState->ReleaseRef();
				m_pDepthStencilState	=	NULL;
			}
			if(m_pBlendState!=NULL){
				m_pBlendState->ReleaseRef();
				m_pBlendState	=	NULL;
			}

			m_Hash.uiHash	=	0;
			return	true;
		}

		ShaderProgram* Pass::CreateShaderProgram( ShaderParamInfo* pShaderInfo ,enumShaderType	type){
			if(pShaderInfo==NULL){
				return	NULL;
			}
			if(type	>	enDS)
				return	NULL;

			if(pShaderInfo->strName.empty())
				return	NULL;

			ShaderProgram*	pShader	=	new	ShaderProgram(pShaderInfo,type);
			if(pShader!=NULL){
				pShader->Create();
			}

			if(m_pShaderArray[type]!=NULL){
				m_pShaderArray[type]->Destroy();
				delete m_pShaderArray[type];
				m_pShaderArray[type]	=	NULL;
			}

			m_pShaderArray[type]	=	pShader;

			return	pShader;
		}

		Air::U1 Pass::DestroyShaderProgram( ShaderProgram* pShader ){
			if(pShader==NULL)
				return	false;
			enumShaderType	type	=	pShader->GetShaderType();
			if(type	>	enDS)
				return	false;

			if(m_pShaderArray[type]	==	pShader){
				pShader->Destroy();
				delete pShader;
				m_pShaderArray[type]	=	NULL;
			}
			return	true;
		}

		Air::U1 Pass::DestroyShaderProgram( enumShaderType type ){
			if(type	>	enDS)
				return	false;

			if(m_pShaderArray[type]	!=NULL){
				m_pShaderArray[type]->Destroy();
				delete m_pShaderArray[type];
				m_pShaderArray[type]	=	NULL;
			}
			return	true;
		}
		void Pass::UpdateTextureArray( TextureArray& vecTexture ){
			ShaderProgram*	pProgram	=	NULL;
			for(U32	i=0;i<6;i++){
				pProgram	=	m_pShaderArray[i];
				if(pProgram!=NULL)
					pProgram->UpdateTextureArray(vecTexture);
			}
		}

		void Pass::Begin(){
			Render::Device*	pDevice	=	Render::System::GetSingleton()->GetDevice();
 			pDevice->SetRS(m_pRasterizerState);
 			pDevice->SetDSS(m_pDepthStencilState);
 			pDevice->SetBS(m_pBlendState);

			for(U32 i=0;i<6;i++){
				if(m_pShaderArray[i]!=NULL){
					m_pShaderArray[i]->UpdateShader_SamplerState();
				}
			}
		}

		void Pass::End()
		{
			Render::Device*	pDevice	=	Render::System::GetSingleton()->GetDevice();

			if(m_pShaderArray[enGS]!=NULL){
				pDevice->SetShader(enGS,NULL);
			}
			if(m_pShaderArray[enHS]!=NULL){
				pDevice->SetShader(enHS,NULL);
			}
			if(m_pShaderArray[enDS]!=NULL){
				pDevice->SetShader(enDS,NULL);
			}
		}

	}
}