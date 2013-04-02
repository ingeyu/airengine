#include "AirInterfaceUIElement.h"

namespace Air{
	
	namespace	Engine{
		namespace	UI{
			IElement::IElement( ){
				m_vPositionSize	=	Float4(0,0,0,0);		///<	位置和大小
				m_vUV			=	Float4(0,0,0,0);		///<	图片位置和大小
				m_vColor		=	Float4(0,0,0,0);		///<	设置颜色
				m_vCustom		=	Float4(0,0,0,0);		///<	自定义
	
				m_uiMark		=	-1;
			}	
		}
	}
};




