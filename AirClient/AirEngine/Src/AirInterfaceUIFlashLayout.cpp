#include "AirInterfaceUIFlashLayout.h"
#include "AirCommonConverter.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
			namespace	Flash{
	
	
				void ILayout::SetCallback( AString strFunction,VoidCallVoid p ){
					SetCallback(Converter::Acsi2WideByte(strFunction),p);
				}
	
				Union4 ILayout::CallFunction( AString strFunction ){
					return	CallFunction(Converter::Acsi2WideByte(strFunction));
				}
			}
			
		}
	}
};