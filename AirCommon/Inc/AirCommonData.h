/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/20
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  AirCommonData.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRCOMMONDATA_HEAD_FILE
#define AIRCOMMONDATA_HEAD_FILE

#include "AirCommonHeader.h"
namespace	Air{
	namespace Common{
	
		/**	\brief	数据类
		*
		*	数据类
		*
		***/
		class	COMMON_EXPORT	Data	:	public	MemoryObject{
		public:
			Data();
			Data(void* p,U32 uiSize);
			template	<typename	T_Type>
			Data(const T_Type&	p){
				Fill(&p,sizeof(T_Type));
			};
			~Data();
			void	Fill(void*	p,U32 uiSize);

			Data*	Clone();
			/**	\brief	是否为空
			*   
			*	@remarks 	是否为空
			*	@see		Data
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsNull(){return	(buff==NULL || size	== 0);};
			/**	\brief	获取数据长度
			*   
			*	@remarks 	获取数据长度
			*	@see		Data
			*	@return   	Size
			*	@note
			*
			**/
			inline	U32	GetSize(){return	size;};
			/**	\brief	获取数据
			*   
			*	@remarks 	获取数据
			*	@see		Data
			*	@return   	Common::File::Data::Buff
			*	@note
			*
			**/
			inline	U8*	GetBuff(){return	buff;};

			/**	\brief	重新申请空间
			*   
			*	@remarks 	重新申请空间
			*	@see		Data
			*	@return   	Air::Common::File::Data::Buff
			*	@param		U32 s
			*	@note
			*
			**/
			U8*		ReSize(U32	s);
			void	Clear();
			U8*				buff;					///<	数据
			U32				size;					///<	大小
		};

		typedef	std::list<Data*>			DataList;
		typedef	DataList::iterator			DataListItr;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRCOMMONDATA_HEAD_FILE