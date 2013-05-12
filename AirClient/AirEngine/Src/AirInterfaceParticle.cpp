#include "AirInterfaceParticle.h"
//#include "AirInterfaceParticleManager.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
#include "AirRenderSystem.h"

#include "AirEngineSceneNode.h"
namespace Air{
	
	namespace	Engine{
		
		IParticle::IParticle( CAString& strName,Info* pInfo )
			:m_fTotalTime(GetGlobalSetting().m_ShaderParam.m_fTotalTime),
			TProduct(strName){

			m_Info			=	*pInfo;
			m_fLife			=	0.0f;
			m_fCreateTime	=	0.0f;
			m_bDeath		=	false;
		}
	
		U1 IParticle::Create(){
// 			File file(m_Info.strParticleFile);
// 			file.Open();
// 	
// 	
// 			IniFile cfgFile;
// 			cfgFile.LoadFileFromMemory(file.GetData());
// 	
// 			//AString	strParticleCount	=	cfgFile.Get("Particle","Count");
// 			AString	strMeshName			=	cfgFile.Get("Particle","Mesh");
// 			//获取粒子的生命
// 			AString	strLife				=	cfgFile.Get("Particle","fLife");
// 			if(strLife.empty()){
// 				m_fLife	=	1000;
// 			}else{
// 				m_fLife	=	Converter::ToFloat(strLife);
// 			}
// 	
// 	
// 			m_DrawBuff.m_pXObject		=	Render::System::GetSingleton()->CreateProduct<Render::IXObject*>(strMeshName,AString("XObject"));
// 			if(m_DrawBuff.m_pXObject==NULL)
// 				return false;
// 	
// 			m_pMaterial					=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(m_Info.strParticleFile,AString("Material"));
// 			if(m_pMaterial==NULL){
// 				return false;
// 			}
// 	
// 			m_Bound		=	m_DrawBuff.m_pXObject->ComputeBoundBox();
// 			//m_DrawBuff.m_pXObject->ComputeNormalTangent();
// 			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DS;
// 			m_pObject	=	(UInt*)m_DrawBuff.m_pXObject;
// 	
// 	//  		::OutputDebugStringA(m_strProductName.c_str());
// 	//  		::OutputDebugStringA("粒子被创建\n");
// 	
// 			//获取创建时间
// 			m_fCreateTime	=	GetGlobalSetting().m_ShaderParam.m_fTotalTime;
			return true;
		}
	
		U1 IParticle::Destroy(){
// 			if(m_DrawBuff.m_pXObject!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pXObject);
// 				m_DrawBuff.m_pXObject	=	NULL;
// 			}
// 			if(m_pMaterial!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_pMaterial);
// 				m_pMaterial	=	NULL;
// 			}
// 			m_pObject	=	NULL;
	//  		::OutputDebugStringA(m_strProductName.c_str());
	//  		::OutputDebugStringA("粒子被摧毁\n");
			return	true;
		}
	
		void IParticle::Update(const FrameTime& frameTime){
			if(m_bDeath)
				return;
			__super::Update(frameTime);
	
			if(m_fTotalTime>m_fLife+m_fCreateTime){
	 			if(m_pParentNode!=NULL){
	 				GetParentSceneNode()->detachObject(this);
	 			}
	 			EngineSystem::GetSingleton()->PushObject2Release(this);
				m_bDeath	=	true;
				//SetVisiable(false);
	// 			::OutputDebugStringA(m_strProductName.c_str());
	// 			::OutputDebugStringA("粒子死亡\n");
			}
		}
	
		void IParticle::RenderAlpha(){
			if(m_bDeath)
				return;
			//设置参数
			SetParticleParam();
			//__super::RenderAlpha();
// 			if(m_pMaterial!=NULL){
// 				m_pMaterial->Render(m_DrawBuff);
// 			}
		}
	
		void IParticle::SetParticleParam(){
		//	Render::IMaterial::Technique*	pTech	=	m_pMaterial->GetTechnique();
// 			pTech->SetParam("fLife",		m_fLife);
// 			pTech->SetParam("fCreateTime",	m_fCreateTime);
// 			pTech->SetParam("vVelocity",	m_Info.vVelocity);
// 			pTech->SetParam("vPosition",	m_Info.vPosition);
		}
	
		void IParticle::Render(){
	
			if(m_bDeath){
	// 			::OutputDebugStringA(m_strProductName.c_str());
	// 			::OutputDebugStringA("死亡状态 不渲染\n");
				return;
			}
			if(!IsInView() /*|| !IsVisiable()*/){
	// 			::OutputDebugStringA(m_strProductName.c_str());
	// 			::OutputDebugStringA("不可见\n");
				return;
			}
			if(/*m_pMaterial==*/NULL){
	// 			::OutputDebugStringA(m_strProductName.c_str());
	// 			::OutputDebugStringA("材质为空\n");
				return;
			}
			//如果是半透明物体 延迟渲染
// 			if(m_pMaterial->IsAlphaBlend()){
// 				AlphaObject obj;
// // 				if(m_pParentNode!=NULL)
// // 					obj.mat			=	m_ResultMatrix;
// // 				else
// // 					obj.mat			=	Float44::getTrans(0,0,0);
// 				obj.pRenderObj		=	this;
// 				EngineSystem::GetSingleton()->PushAlphaObject(obj);
// 				return;
// 			}
		}

	}
};