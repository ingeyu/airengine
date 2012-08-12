#ifndef COMMONNETFILE_HEAD_FILE
#define COMMONNETFILE_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonFile.h"
namespace Air{
	
	namespace Common{
	
		typedef	File::Data	Buffer;
	
		/**	\brief	网络文件类接口
		*
		*	网络文件类接口	用于文件传输
		*
		***/
		class	NetFile{
		public:
			NetFile(){
				m_Type	=	0;
			};
			virtual	~NetFile(){
	
			};
	
			/**	\brief	获取类型
			*   
			*	@remarks 	获取类型
			*	@see		NetFile
			*	@return   	int
			*	@note
			*
			**/
			int					GetType(){
				return	m_Type;
			};
			/**	\brief	设置类型
			*   
			*	@remarks 	设置类型
			*	@see		NetFile
			*	@return   	void
			*	@param		int iType
			*	@note
			*
			**/
			void				SetType(int iType){
				m_Type	=	iType;
			};
	
			/**	\brief	加载文件
			*   
			*	@remarks 	加载文件
			*	@see		NetFile
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1			Load()								=	NULL;
			/**	\brief	保存
			*   
			*	@remarks 	保存
			*	@see		NetFile
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1			Save()								=	NULL;
	
			/**	\brief	从资源加载
			*   
			*	@remarks 	从内存加载
			*	@see		NetFile
			*	@return   	U1
			*	@param		Buffer * pBuffer
			*	@note
			*
			**/
			virtual	U1			LoadFromBuffer(Buffer*	pBuffer)	=	NULL;
			/**	\brief	序列化为内存
			*   
			*	@remarks 	序列化为内存
			*	@see		NetFile
			*	@return   	Buffer*
			*	@note
			*
			**/
			virtual	Buffer*		BuildBuffer()						=	NULL;
	
			int			m_Type;
			AString		m_strName;
		};
	
	};
};
#endif // COMMONNETFILE_HEAD_FILE