#ifndef AUDIOBUFFER_HEAD_FILE
#define AUDIOBUFFER_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Client{
	
		namespace	Audio{
			/**	\brief	声音缓冲区
			*
			*	声音缓冲区
			*
			***/
			class	Buffer	:
				public	IProduct{
			public:
				Buffer(CAString&	strName);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Buffer
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Buffer
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	获取缓冲区
				*   
				*	@remarks 	获取缓冲区
				*	@see		Buffer
				*	@return   	U8*
				*	@note
				*
				**/
				U8*		GetBuffer(){
					return	m_pBuffer;
				};
				/**	\brief	获取缓冲区大小
				*   
				*	@remarks 	获取缓冲区大小
				*	@see		Buffer
				*	@return   	UInt
				*	@note
				*
				**/
				UInt	GetBufferSize(){
					return	m_uiSize;
				};
	
				/**	\brief	获取音频格式
				*   
				*	@remarks 	获取音频格式
				*	@see		Buffer
				*	@return   	SInt
				*	@note
				*
				**/
				SInt	GetFormat(){
					return	m_uiFormat;
				};
				/**	\brief	获取序列
				*   
				*	@remarks 	获取序列
				*	@see		Buffer
				*	@return   	SInt
				*	@note
				*
				**/
				SInt	GetFreqBuffer(){
					return	m_uiFreqBuffer;
				}
	
			protected:
				/**	\brief	载入WAV格式文件
				*   
				*	@remarks 	载入WAV格式文件
				*	@see		Buffer
				*	@return   	U1
				*	@param		Data * pData
				*	@note
				*
				**/
				U1		LoadWAVFromMemory(Data*	pData);
			protected:
				U8*		m_pBuffer;			///<	音频缓冲
				UInt	m_uiSize;			///<	音频缓冲大小
				SInt	m_uiFormat;			///<	音频格式
				SInt	m_uiFreqBuffer;		///<	序列
			};
	
			/**	\brief	音频缓冲工厂
			*
			*	音频缓冲工厂
			*
			***/
			class	BufferFactory	:
				public	IFactory{
			public:
				BufferFactory();
	
				/**	\brief	创建音频缓冲
				*   
				*	@remarks 	创建音频缓冲
				*	@see		BufferFactory
				*	@return   	IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
			};
		}
	
	};
};
#endif // AUDIOBUFFER_HEAD_FILE