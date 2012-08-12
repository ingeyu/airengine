#ifndef INTERFACERESOURCESYSTEM_HEAD_FILE
#define INTERFACERESOURCESYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirCommonThread.h"
#include "AirInterfaceResourceStream.h"

namespace Air{
	namespace Client{
	
		namespace	Resource{
			class	IFindFileListener{
			public:
				virtual	void	OnFindFile(CAString&	strName,Data*	pData)=	NULL;
			};
			/**	\brief	资源管理系统
			*
			*	资源管理系统
			*
			***/
			class	ENGINE_EXPORT	ISystem	:
				public	Common::ISystem,
				public	Common::Thread{
			public:	
				ISystem(CAString&	strType);

				virtual	U1		Initialization();
				virtual	U1		Release();

				virtual	U1		Start();
				virtual	U1		Stop();
				/**	\brief	查找后缀名文件
				*   
				*	@remarks 	查找后缀名文件
				*	@see		ISystem
				*	@return   	void
				*	@param		AString strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);
	
				/**	\brief	添加一个资源包
				*   
				*	@remarks 	添加一个资源包
				*	@see		ISystem
				*	@return   	U1
				*	@param		CAString& strPackageName
				*	@note
				*
				**/
				virtual	U1			AddPackage(CAString&	strPackageName);
				/**	\brief	判断文件是否存在
				*   
				*	@remarks 	判断文件是否存在
				*	@see		ISystem
				*	@return   	Air::U32
				*	@param		CAString & strFileName
				*	@note
				*
				**/
				virtual	U32		Find(CAString&	strFileName);
				virtual	U32		Find(CAString&	strFileName,Data&	outData);
				/**	\brief	子类需要重写的循环调用函数
				*   
				*	@remarks 	线程自身的执行函数
				*	@see		Thread
				*	@return   	bool
				*	@note
				*
				**/
				virtual bool	RepetitionRun();
				/**	\brief	放入后台加载队列
				*   
				*	@remarks 	放入后台加载队列
				*	@see		ISystem
				*	@return   	Air::U1
				*	@param		IStream * pFile
				*	@note
				*
				**/
				virtual	U1		LoadBackground(IStream*	pFile);
				/**	\brief	放到回收站
				*   
				*	@remarks 	放到回收站
				*	@see		ISystem
				*	@return   	Air::U1
				*	@param		IProduct * pFile
				*	@note
				*
				**/
				virtual	U1		PushRecycle(IProduct*	p);
				void			SetMaxRecycleSize(U32	uiSize);
				U32				GetMaxRecycleSize();
			protected:
				CriticalSection	m_LoadCS;
				CriticalSection	m_UnLoadCS;
				//Event			m_Event;
				StreamList		m_lstLoad[2];			///<	加载队列
				U32				m_uiLoadIndex;
				ProductList		m_lstUnLoad[2];		///<	卸载队列	回收机制
				U32				m_uiUnloadLoadIndex;
				U32				m_uiRecycleSize;	///<	当前回收站大小
				U32				m_uiMaxRecycle;		///<	回收站最大限制	大于会摧毁
			};
		}
	
	};
};
#endif // INTERFACERESOURCESYSTEM_HEAD_FILE