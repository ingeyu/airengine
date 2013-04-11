/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/20
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  AirInterfaceResourceStream.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRINTERFACERESOURCESTREAM_HEAD_FILE
#define AIRINTERFACERESOURCESTREAM_HEAD_FILE

#include "AirEngineHeader.h"

namespace	Air{
	namespace Engine{
	
		namespace	Resource{
			enum	enumStreamState{
				enSS_UnKnown,
				enSS_UnLoad,
				enSS_Loading,
				enSS_Loaded,
				enSS_UnLoading,
				enSS_Reloading,
				enSS_ForceLoading,
				enSS_ForceUnLoading,

				enSS_Max
			};

			class	ENGINE_EXPORT	Stream	:
				public	Common::IProduct{
			public:
				static AString ProductTypeName;
				Stream(CAString&	strName);

				virtual	U1				Create();
				virtual	U1				Destroy();

				/**	\brief	后台释放
				*   
				*	@remarks 	后台释放
				*	@see		IStream
				*	@return   	void
				*	@note
				*
				**/
				virtual	void			PushRecycle();

				/**	\brief	强制加载
				*   
				*	@remarks 	后台加载线程会调用此函数	前台用户也可以手动调用
				*	@see		IStream
				*	@return   	Air::U1
				*	@note
				*
				**/
				U1						ForceLoad();
				/**	\brief	强制卸载
				*   
				*	@remarks 	强制卸载	可以手动调用
				*	@see		IStream
				*	@return   	Air::U1
				*	@note
				*
				**/
				U1						ForceUnLoad();
				void					ForceReLoad();

				inline	enumStreamState	GetState(){
					return	m_State;
				};
				inline	void*			GetData(){
					return	m_Data.buff;
				};
				inline	U32				GetSize(){
					return	m_Data.size;
				};
			protected:
				Data					m_Data;
				enumStreamState			m_State;
				CriticalSection			m_DataCS;
			};


		}
		typedef	STD_LIST<Resource::Stream*>		StreamList;
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRINTERFACERESOURCESTREAM_HEAD_FILE