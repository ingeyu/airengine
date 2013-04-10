#include "AirEnginePostComposer.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirEngineSystem.h"
#include "AirEngineMaterial.h"
namespace Air{
	
	namespace	Engine{
		
	
		PostComposer::PostComposer( AString strName,AString* strMaterialName )
			:TProduct(strName){
			m_bEnable	=	true;
			//m_pMaterial	=	NULL;
			m_pTerget	=	NULL;
			m_strMaterialName	=	*strMaterialName;
		}
	
		U1 PostComposer::Create(){
	
			//创建材质
// 			m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<RenderMaterial*>(m_strMaterialName,AString("Material"));
// 			if(m_pMaterial==NULL)
// 				return false;
	
			//解析材质名
			AString	strFileName;
			GlobalSetting::ParsePath(m_strMaterialName,NULL,&strFileName);
	
			//创建渲染目标
			RenderTarget::Info info;
			
			//读取纹理信息中的输出纹理 格式	如A8R8G8B8 F32等等
			File	file(m_strMaterialName);
			if(!file.Open()){
				return false;
			}
			IniFile	cfgFile;
			cfgFile.LoadFileFromMemory(file.GetData());
			AString	strFormat	=	cfgFile.Get("Composer","Format");
			AString	strSize		=	cfgFile.Get("Composer","Size");
			AString	strBKColor	=	cfgFile.Get("Composer","BKColor");
// 			if(strSize.empty()){
// 				info.SetRenderToTexture(1024,700,true);
// 			}else{
// 				Float4	vSize		=	GlobalSetting::ParseFloat4(strSize);
// 				info.SetRenderToTexture(vSize.x,vSize.y);
// 			}
			
// 			if(!strFormat.empty())
// 				info..format		=	(RenderTexture::enumFormat)Converter::ToS32(strFormat);
	
			//创建渲染目标
			m_pTerget	=	Render::System::GetSingleton()->CreateProduct<RenderTarget>(strFileName,&info);
			if(m_pTerget==NULL){
				return	false;
			}
	
			if(!strBKColor.empty()){
				Float4	vColor	=	GlobalSetting::ParseFloat4(strBKColor);
				m_pTerget->SetBKColor(vColor);
			}
	
			m_pObject	=	m_pTerget;
	
			return true;
		}
	
		U1 PostComposer::Destroy(){
	
			if(m_pMaterial==NULL){
				m_pMaterial->ReleaseRef();
				m_pMaterial=NULL;
			}
		
			if(m_pTerget==NULL){
				m_pTerget->ReleaseRef();
				m_pTerget=NULL;
			}
	
			m_pObject	=	NULL;
	
			return true;
		}
	
		void PostComposer::Render(){
			if(!m_bEnable)
				return;
			if(m_pTerget!=NULL){
				//提交渲染材质
				GetGlobalSetting().m_ShaderParam.m_pCurrentPostComposerMaterial	=	m_pMaterial;
				//渲染目标
				//m_pTerget->Render();
				//获取上一帧的渲染结果
				//GetGlobalSetting().m_ShaderParam.m_pLastPostComposerResult	=	m_pTerget->GetTexture();
			}
		}
	}
};