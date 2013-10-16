#include "AirCommonReference.h"
namespace Air{
	
	namespace	Common{
	
	
		IReference::IReference(){
			m_pObject	=	NULL;
			m_uiNumRef	=	0;
		}
	
		IReference::~IReference(){
			//::OutputDebugStringA("IReference::~IReference()\n");
			//强制清理
			//不在放在基类处理  因为Destroy是个纯虚函数 
			//在基类析构函数中调用 可能会导致实现部分代码已经释放 
			//报出纯虚函数没有实现 无效调用的错误
	// 		if(m_pObject!=NULL){
	// 			m_uiNumRef	= 1;
	// 			ReleaseRef();
	// 		}
		}
	
		U32 IReference::AddRef(){
			if(m_uiNumRef<=0){
				//这里要考虑多线程的加载
				if(!Create())
					return false;
			}
			m_uiNumRef++;
			return m_uiNumRef;
		}
	
		U32 IReference::ReleaseRef(){
			if(m_uiNumRef<=0)
				return true;
			m_uiNumRef--;
			//这里要考虑多线程的卸载
			if(m_uiNumRef<=0){
				Destroy();
			}
			return m_uiNumRef;
		}
	}
};