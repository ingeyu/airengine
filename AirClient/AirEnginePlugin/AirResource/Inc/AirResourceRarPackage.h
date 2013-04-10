#ifndef RESOURCEPACKAGE_HEAD_FILE
#define RESOURCEPACKAGE_HEAD_FILE

#include "AirResourceHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Resource{
			/**	\brief	资源包
			*
			*	资源包
			*
			***/
			class	RarPackage	:
				public	IPackage{
			public:
				typedef	Data	FileData;
			public:
				static AString ProductTypeName;
				RarPackage(CAString&	strName);
	
				/**	\brief	数据包创建
				*   
				*	@remarks 	数据包创建
				*	@see		Package
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Create();
	
				/**	\brief	数据包摧毁
				*   
				*	@remarks 	数据包摧毁
				*	@see		Package
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Destroy();
	
				/**	\brief	查找资源
				*   
				*	@remarks 	查找资源
				*	@see		Package
				*	@return   	Data*	
				*	@param		AString & strName
				*	@note
				*
				**/
				virtual	U32			Find(CAString&	strName,Data&	data);
	
				/**	\brief	查找后缀名文件
				*   
				*	@remarks 	查找后缀名文件
				*	@see		ISystem
				*	@return   	void
				*	@param		CAString& strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);
	
				/**	\brief	合并数据
				*   
				*	@remarks 	合并数据
				*	@see		RarPackage
				*	@return   	Data*
				*	@note
				*
				**/
				Data*			CombineData();
	
			public:
	
			};

		}
	
	};
};
#endif // RESOURCEPACKAGE_HEAD_FILE