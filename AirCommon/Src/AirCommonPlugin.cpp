#include "AirCommonPlugin.h"
namespace Air{
	
	namespace	Common{
		
	
	
		Plugin::Plugin( CAString& strName ,void*	pParam):IProduct(strName){
			m_pParam	=	pParam;
			m_Func[0]	=	NULL;
			m_Func[1]	=	NULL;
			m_Func[2]	=	NULL;
			m_Func[3]	=	NULL;
		}
		Plugin::~Plugin(){
		}
		U1 Plugin::Create(){
			HINSTANCE h	=	LoadLibraryA(m_strProductName.c_str());
			if(h==NULL)
				return false;
			m_pObject	=	h;
	
			m_Func[0]	=	(Func)GetProcAddress(h,"DllInit");
			m_Func[1]	=	(Func)GetProcAddress(h,"DllStart");
			m_Func[2]	=	(Func)GetProcAddress(h,"DllStop");
			m_Func[3]	=	(Func)GetProcAddress(h,"DllRelease");

			if(m_Func[enInit]!=NULL){
				(*m_Func[enInit])(m_pParam);
			}else{
				return	false;
			}
	
			return true;
		}
		U1 Plugin::Destroy(){
			if(m_Func[enRelease]!=NULL){
				(*m_Func[enRelease])(m_pParam);
			}
			if(m_pObject==NULL)
				return false;
			BOOL	bRet	=	FreeLibrary((HINSTANCE)m_pObject);
			return bRet != FALSE;
		}
	
		U1 Plugin::Excute( enumFuncType funcType ){
			if(m_Func[funcType]!=NULL){
				return	(*m_Func[funcType])(m_pParam);
			}
			return	false;
		}
	
		Common::Func Plugin::GetFunction( AString strName ){
			return	(Func)GetProcAddress((HINSTANCE)m_pObject,strName.c_str());
		}
		PluginFactory::PluginFactory(){
			m_strTypeName	=	"Plugin";
		}
		IProduct* PluginFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
			return new	Plugin(strName,lstParam);
		}
	}
};