// /*****************************************************/
// /* @All Right Reserved (C), 2009-2012, AIR TECO CO.
// 
// 
//  \author    InterfalHell	Xinhe
//  \date      2011/04/16
//  \version   ver 0.6.0.0
//  \filepath  f:\EngineSource\Air\AirClient\AirEnginePlugin\AirResource
//  \filename  ResourceFileStream.h
//  \note     
//        
//  \attention:
// 			
//  \remarks    created by InterfalHell version 0.6.0.0 
//  \History:
//    <author>      <time>      <version>         <desc>
// ******************************************************/
// #ifndef RESOURCEFILESTREAM_HEAD_FILE
// #define RESOURCEFILESTREAM_HEAD_FILE
// 
// #include "AirResourceHeader.h"
// 
// namespace	Air{
// 	namespace Client{
// 	
// 		namespace	Resource{
// 			/**	\brief	文件流
// 			*
// 			*	文件流
// 			*
// 			***/
// 			class	FileStream	:
// 				public	IFileStream{
// 			public:
// 				FileStream(CAString&	strName,Info*	pInfo):IFileStream(strName,pInfo){
// 
// 				};
// 
// 				/**	\brief	创建
// 				*   
// 				*	@remarks 	创建
// 				*	@see		FileStream
// 				*	@return   	Air::U1
// 				*	@note
// 				*
// 				**/
// 				virtual	U1	Create();
// 			};
// 
// 			/**	\brief	文件流工厂类
// 			*
// 			*	文件流工厂类
// 			*
// 			***/
// 			class	FileStreamFactory	:
// 				public	IFactory{
// 			public:
// 				FileStreamFactory(){
// 					m_strTypeName	=	"FileStream";
// 				};
// 				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */){
// 					if(strName.empty()){
// 						return	NULL;
// 					}
// 					return	new	FileStream(strName,(IFileStream::Info*)lstParam);
// 				};
// 			};
// 		};
// 	
// 	};//end of	namespace	Client
// };//end of namespace Air
// #endif // RESOURCEFILESTREAM_HEAD_FILE