#ifndef INTERFACEUIFLASHLAYOUT_HEAD_FILE
#define INTERFACEUIFLASHLAYOUT_HEAD_FILE

#include "AirInterfaceUISystem.h"
namespace Air{
	
	namespace Engine{
	
		typedef	void	(*VoidCallVoid)(void);
	
		namespace	UI{
			namespace	Flash{
				class	ENGINE_EXPORT	ILayout{
				public:
					struct	Info{
						Float4		vBKColor;
						AString		strName;
					};
	
				public:
	
	 				/**	\brief	设置回调
	 				*   
	 				*	@remarks 	设置回调
	 				*	@see		ILayout
	 				*	@return   	void
	 				*	@param		WString strFunction
	 				*	@param		VoidCallVoid*	p
	 				*	@note
	 				*
	 				**/
	 				virtual	void	SetCallback(WString	strFunction,VoidCallVoid	p)			=	NULL;
					void			SetCallback(AString	strFunction,VoidCallVoid	p);
	// 				virtual	void	SetCallback(WString	strFunction,void*	pObj,void*	pFunction)		=	NULL;
	 				/**	\brief	调用函数
	 				*   
	 				*	@remarks 	调用函数
	 				*	@see		ILayout
	 				*	@return   	Client::Union4
	 				*	@param		WString strFunction
	 				*	@note
	 				*
	 				**/
	 				virtual	Union4	CallFunction(WString	strFunction)	=	NULL;
					virtual	Union4	CallFunction(AString	strFunction);
	
					virtual	U1		Play(AString	strID)	=	NULL;
				};
			}
		}
	
	};
};
#endif // INTERFACEUIFLASHLAYOUT_HEAD_FILE