//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InterfalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.4.0.0
 \filepath  f:\tj.src\Client0400\Render
 \filename  RenderFactory.h
 \note     
       
 \attention:
			渲染组件的工厂基类
 \remarks    created by InterfalHell version 0.4.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef RENDERFACTORY_HEAD_FILE
#define RENDERFACTORY_HEAD_FILE

#include "AirRenderHeader11.h"
#include "AirRenderDevice11.h"


namespace Air{
	
	namespace Client{
	
		namespace	Render{
	
			/**	\brief	渲染产品基类
			*
			*	渲染产品基类
			*
			***/
			class	Product	:	
				public	IProduct{
			public:
				Product(CAString&	strName):IProduct(strName){
					m_Pool					=	POOL_MANAGED;
					m_bDestroyByLostDevice	=	false;
					m_bLoaded				=	false;
				};
				//virtual	~Product(){};
	
		
				/**	\brief	需要重载的创建
				*   
				*	@remarks 	需要重载的创建
				*	@see		Product
				*	@return   	U1
				*	@param		U1 bBackThread
				*	@note
				*
				**/
				virtual	U1	Create( )	=	NULL;
				/**	\brief	需要重载的摧毁
				*   
				*	@remarks 	参数为是否为多线程创建
				*	@see		Product
				*	@return   	U1
				*	@param		U1 bBackThread
				*	@note
				*
				**/
				virtual	U1	Destroy( )	=	NULL;
	
				/**	\brief	设备丢失回调函数
				*   
				*	@remarks 	参数为是否为多线程创建
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnLostDevice(){
					if(m_Pool == POOL_DEFAULT){
						Destroy();
						m_bDestroyByLostDevice	=	true;
					}
					return	true;
				};
				/**	\brief	重置设备回调函数
				*   
				*	@remarks 	重置设备回调函数
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnResetDevice(){
					if(m_Pool == POOL_DEFAULT	&&	m_bDestroyByLostDevice){
						Create();
						m_bDestroyByLostDevice	=	false;
					}
					return	true;
				};
	
				inline	U1	IsLoad(){
					return	m_bLoaded;
				};
				/**	\brief	DirextX的资源释放模板函数
				*   
				*	@remarks 	DirextX的资源释放模板函数
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				template	<typename	T_DirectXType>
				U1	DirectXDestroy(){
	
	
					T_DirectXType	pDirectXObject	=	(T_DirectXType)m_pObject;
					if(pDirectXObject	!=	NULL){
						pDirectXObject->Release();
						pDirectXObject=NULL;
					}
					m_pObject	=	NULL;
					return true;
				};
	
				#ifndef DirectXImplement
				#define DirectXImplement(Type,Function)	\
					Type	p	=	(Type)m_pObject;\
					if(p!=NULL)p->Function;\
					return true;
				#endif
				/**	\brief	丢失设备模板函数
				*   
				*	@remarks 	丢失设备模板函数
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				template	<typename	T_DirectXType>
				U1	DirectXOnLostDevice(){
					DirectXImplement(T_DirectXType,OnLostDevice());
				};
				/**	\brief	重置设备模板函数
				*   
				*	@remarks 	重置设备模板函数
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				template	<typename	T_DirectXType>
				U1	DirectXOnResetDevice(){
					DirectXImplement(T_DirectXType,OnResetDevice());
				};
	
				/**	\brief	判断是否为空
				*   
				*	@remarks 	判断是否为空
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	IsNull(){
					U1	b	=	(m_pObject	==	NULL);
					return	b;
				}
			protected:
				enumPool			m_Pool;					///<	资源管理方式
				U1					m_bDestroyByLostDevice;	///<	是否被丢失设备时摧毁
				U1					m_bLoaded;				///<	是否已经载入
			private:
			};
			class	Factory	:	public	IFactory
			{
			public:
				virtual	~Factory(){};
				/**	\brief	设备丢失回调函数
				*   
				*	@remarks 	设备丢失回调函数
				*	@see		Factory
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnLostDevice(){
					ProductMapItr	i	=	m_mapProduct.begin();
					for(;i!=m_mapProduct.end();i++){
						Product*	pProduct	=	(Product*)i->second;
						if(pProduct==NULL)
							continue;
						if(pProduct->IsNull())
							continue;
						pProduct->OnLostDevice();
					}
					return	true;
				};
				/**	\brief	设备重置回调函数
				*   
				*	@remarks 	设备重置回调函数
				*	@see		Factory
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnResetDevice(){
					ProductMapItr	i	=	m_mapProduct.begin();
					for(;i!=m_mapProduct.end();i++){
						Product*	pProduct	=	(Product*)i->second;
						if(pProduct==NULL)
							continue;
	
						pProduct->OnResetDevice();
					}
					return	true;
				};
			protected:
				
			private:
				
			};
	
			
		}
	
	};
};
#endif // RENDERFACTORY_HEAD_FILE