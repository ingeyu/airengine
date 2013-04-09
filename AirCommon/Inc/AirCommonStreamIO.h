/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/13
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonStream.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONSTREAM_HEAD_FILE
#define COMMONSTREAM_HEAD_FILE

#include "AirCommonData.h"

namespace	Air{

	namespace Common{
		/**	\brief	流输入输出
		*
		*	流输入输出
		*
		***/
		class	COMMON_EXPORT	StreamIO	:	public MemoryObject{
		public:
			StreamIO();
			virtual	~StreamIO();

			/**	\brief	定位指针
			*   
			*	@remarks 	定位指针
			*	@see		StreamIO
			*	@return   	void
			*	@param		S32 iOffset
			*	@note
			*
			**/
			void	Seek(S32	iOffset);
			/**	\brief	移动指针到头部
			*   
			*	@remarks 	移动指针到头部
			*	@see		StreamIO
			*	@return   	void
			*	@note
			*
			**/
			void	SeekBegin();
			/**	\brief	移动指针到尾部
			*   
			*	@remarks 	移动指针到尾部
			*	@see		StreamIO
			*	@return   	void
			*	@note
			*
			**/
			void	SeekEnd();
			/**	\brief	流大小
			*   
			*	@remarks 	流大小
			*	@see		StreamIO
			*	@return   	Air::U32
			*	@note
			*
			**/
			U32		Size();

			/**	\brief	是否有效
			*   
			*	@remarks 	是否有效
			*	@see		StreamIO
			*	@return   	Air::U1
			*	@note
			*
			**/
			U1		IsVaild();

			U8*		m_pBegin;
			U8*		m_pEnd;
			U8*		m_pCurrent;
		};
		/**	\brief	读取流
		*
		*	读取流
		*
		***/
		class	COMMON_EXPORT	StreamReader	:
			public	StreamIO{
		public:
			StreamReader();
			StreamReader(const	void*		pData,U32		uiSize);
			/**	\brief	读取一段内存
			*   
			*	@remarks 	读取数据	前4字节 数据长度 后面 内容
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		File::Data & data
			*	@note
			*
			**/
			U1		ReadData(Data&	data);
			/**	\brief	读取指定大小的一块内存
			*   
			*	@remarks 	读取指定大小的一块内存	需要申请好内存 以及尺寸
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		Data & data
			*	@note
			*
			**/
			U1		ReadDataNoSize(Data&	data);
			/**	\brief	读取字符串
			*   
			*	@remarks 	读取字符串	前4字节 字符串长度 后面 字符内容
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		AString & str
			*	@note
			*
			**/
			U1		ReadString(AString&	str);
			/**	\brief	读取一段数据
			*   
			*	@remarks 	内存需要自己申请，再传入地址 和 读取的大小
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		void * p
			*	@param		U32 uiSize
			*	@note
			*
			**/
			U1		ReadBufferNoSize(void*	p,U32	uiSize);
			template<typename T>
			U1		ReadStruct(T&	t){
				return	ReadBufferNoSize(&t,sizeof(T));
			};
			/**	\brief	读取基本常量
			*   
			*	@remarks 	例如 bool char short int float double 之类
			*	@see		StreamReader
			*	@return   	T
			*	@note
			*
			**/
			template<typename	T>
			T		Read(){
				T	val		=	*(T*)m_pCurrent;
				m_pCurrent+=sizeof(T);
				return	val;
			};
			/**	\brief	读取基本常量
			*   
			*	@remarks 	例如 bool char short int float double 之类
			*	@see		StreamReader
			*	@return   	T
			*	@note
			*
			**/
			template<typename	T>
			void	Read(T&	t){
				t	=	*(T*)m_pCurrent;
				m_pCurrent+=sizeof(T);
			}

		};
		/**	\brief	写入流
		*
		*	写入流
		*
		***/
		class	COMMON_EXPORT	StreamWriter	:	
			public	StreamIO{
		public:
			//WriteAPI
			template<typename	T>
			void	Write(const	T&	val){
				*(T*)m_pCurrent	=	val;
				m_pCurrent+=sizeof(T);
			};
			/**	\brief	写入指定大小的数据
			*   
			*	@remarks 	前4字节 数据长度 后面 数据
			*	@see		StreamWriter
			*	@return   	void
			*	@param		const void * val
			*	@param		U32 uiSize
			*	@note
			*
			**/
			void	WriteBuffer(const void*		val,U32	uiSize);
			/**	\brief	写入指定大小的数据
			*   
			*	@remarks 	只写入数据
			*	@see		StreamWriter
			*	@return   	void
			*	@param		const void * val
			*	@param		U32 uiSize
			*	@note
			*
			**/
			void	WriteBufferNoSize(const void*		val,U32	uiSize);
			/**	\brief	写入字符串
			*   
			*	@remarks 	前4字节 数据长度 后面 数据
			*	@see		StreamWriter
			*	@return   	void
			*	@param		const AString & str
			*	@note
			*
			**/
			void	WriteString(const	AString&	str);
			/**	\brief	写入数据
			*   
			*	@remarks 	前4字节 数据长度 后面 数据
			*	@see		StreamWriter
			*	@return   	void
			*	@param		File::Data & data
			*	@note
			*
			**/
			void	WriteData(Data&	data);
			/**	\brief	写入数据
			*   
			*	@remarks 	仅写数据
			*	@see		StreamWriter
			*	@return   	void
			*	@param		Data & data
			*	@note
			*
			**/
			void	WriteDataNoSize(Data&	data);
			/**	\brief	写入结构体
			*   
			*	@remarks 	纯数据 不会写入4字节的 结构体大小
			*	@see		StreamWriter
			*	@return   	void
			*	@param		T & t
			*	@note
			*
			**/
			template<typename T>
			void	WriteStruct(const	T& t){
					WriteBufferNoSize(&t,sizeof(T));
			};
		};

		class	COMMON_EXPORT	MemoryWriter	:	public	StreamWriter{
		public:
			MemoryWriter(U32	uiSize);
			virtual	~MemoryWriter();

			const	void*	GetDataPtr();
			U32				GetDataSize();
		};

		class	COMMON_EXPORT	FileReader	:	public	StreamReader{
		public:
			FileReader(CAString&	strName);
			virtual	~FileReader();


		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONSTREAM_HEAD_FILE