#include "AirPhysicsObject.h"

namespace	Air{
	namespace	Physics{

		AString	Object::ProductTypeName	=	"PhysicsObject";
		Object::Object( CAString& strName,Info* pInfo ):Common::IProduct(strName)
		{
			if(pInfo!=NULL){
				if(pInfo->uiBufferSize==0){
					m_pInfo	=	pInfo;
				}else{
					m_pInfo	=	(Info*)__Alloc(pInfo->uiBufferSize);
					m_pInfo->RelativeToAbs();
				}
			}else{
				m_pInfo	=	NULL;
			}
		}

		Air::U1 Object::Create()
		{
			if(m_pInfo==NULL)
				return false;
			return true;
		}

		Air::U1 Object::Destroy()
		{
			if(m_pInfo->uiBufferSize!=0){
				__Free(m_pInfo);
				m_pInfo=NULL;
			}
			return true;
		}

	}
}