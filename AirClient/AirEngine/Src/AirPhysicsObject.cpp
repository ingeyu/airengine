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

			m_uiMask	=	0;
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

		Air::U1 Object::CollosionDetect( const Float3& p,Float3& v,U32 uiMask )
		{
			if(m_uiMask&uiMask){
				U32 uiShapeCount	=	m_pInfo->uiShapeCount;
				for(U32 i=0;i<uiShapeCount;i++){
					PointShape* pShape	=	m_pInfo->pShapeArray[i];
					switch(pShape->m_Type){
						case 	enPST_Point:	{

												}break;
						case	enPST_Triangle:	{}break;
						case	enPST_Box:		{}break;
						case	enPST_Sphere:	{}break;
						case	enPST_Cylinder:	{}break;
						case	enPST_Plane:	{}break;
					}
				}
			}
			return false;
		}

	}
}