#include "AirInterfaceAlphaObjectManager.h"
#include "AirGlobalSetting.h"
namespace Air{
	
	
	namespace	Engine{
		
	
		IAlphaObjectManager::IAlphaObjectManager(){
			m_pCameraPosition	=	&GetGlobalSetting().m_ShaderParam.m_vCurrentPosition;
		}
	
		void IAlphaObjectManager::PushAlphaObject( AlphaObject obj ){
			if(obj.pRenderObj==NULL)
				return;
// 			static	Float3	vOjectPos	=	Float3(0,0,0);//::ZERO;
// 			//这里没有使用std::list::sort 测试发现用整形排序（std::list<int> 10000个以内） 这种方法快4倍左右
// 			vOjectPos	=	obj.mat.transpose().getTrans();
// 			obj.fDistance	=	vOjectPos.distance(*m_pCameraPosition);
// 	
// 			AObjectListItr	i	=	m_lstAlphaObject.begin();
// 			for(;i!=m_lstAlphaObject.end();i++){
// 				AlphaObject&	object	=	(AlphaObject)(*i);
// 				if(obj.fDistance	<	object.fDistance){
// 					m_lstAlphaObject.insert(i,obj);
// 					return;
// 				}
// 			}
// 			m_lstAlphaObject.push_back(obj);
			//::OutputDebugStringA("插入半透明物体\n");
		}
		void IAlphaObjectManager::RenderAlphaObject(){
			//从最远的距离开始渲染半透明物体
// 			AObjectListRItr	i	=	m_lstAlphaObject.rbegin();
// 			for(;i!=m_lstAlphaObject.rend();i++){
// 				AlphaObject&	obj	=	(AlphaObject)(*i);
// 				GetGlobalSetting().m_ShaderParam.UpdataWorldMatrix(&obj.mat);
// 				obj.pRenderObj->RenderAlpha();
// 				//::OutputDebugStringA("渲染半透明物体\n");
// 			}
// 			m_lstAlphaObject.clear();
		}
	}
};