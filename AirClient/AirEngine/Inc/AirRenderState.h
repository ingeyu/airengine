/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/03/27
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceRenderState.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACERENDERSTATE_HEAD_FILE
#define INTERFACERENDERSTATE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderCommon.h"

namespace	Air{
	namespace Client{
	
		namespace	Render{
			/**	\brief	×´Ì¬
			*
			*	×´Ì¬
			*
			***/
			class	ENGINE_EXPORT	State	:	
				public	Common::IProduct{
			public:
				State(CAString&	strName,StateInfo*	pInfo);

				/**	\brief	´´½¨×´Ì¬
				*   
				*	@remarks 	´´½¨×´Ì¬
				*	@see		IState
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	´Ý»Ù×´Ì¬
				*   
				*	@remarks 	´Ý»Ù×´Ì¬
				*	@see		IState
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
				
				/**	\brief	»ñÈ¡×´Ì¬Ö¸Õë
				*   
				*	@remarks 	»ñÈ¡×´Ì¬Ö¸Õë
				*	@see		IState
				*	@return   	void*
				*	@note
				*
				**/
				virtual	void*	GetState();

				enumRenderStateType	GetType();

				StateInfo	m_Info;
				U1			m_bCostom;
			};
			typedef	State	ISamplerState;
			typedef	State	IRasterizerState;
			typedef	State	IDepthStencilState;
			typedef	State	IBlendState;

		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // INTERFACERENDERSTATE_HEAD_FILE