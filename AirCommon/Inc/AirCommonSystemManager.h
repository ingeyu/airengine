#ifndef COMMONSYSTEMMANAGER_HEAD_FILE
#define COMMONSYSTEMMANAGER_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirInterfaceObject.h"
#include "AirCommonFactory.h"
#include "AirCommonListener.h"

namespace Air{
	namespace Common{
		
		/**	\brief	基本系统类
		*
		*	基本系统类
		*
		***/
		class	ISystem
			:	public	IObject,
				public	IFactoryManager{
		public:
			ISystem(CAString&	strType):m_strType(strType){
			};
			virtual	~ISystem(){};

			/**	\brief	初始化系统
			*   
			*	@remarks 	初始化系统
			*	@see		ISystem
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Initialization()=	NULL;
			/**	\brief	释放系统
			*   
			*	@remarks 	释放系统
			*	@see		ISystem
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Release()		=	NULL;
			/**	\brief	开始
			*   
			*	@remarks 	开始
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Start()			=	NULL;
			/**	\brief	停止
			*   
			*	@remarks 	停止
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Stop()			=	NULL;

			AString		GetType(){
				return	m_strType;
			}

			AString		m_strType;
		};
	
		typedef	std::map<AString,ISystem*>	SystemMap;
		typedef	SystemMap::iterator			SystemMapItr;
		typedef	std::list<ISystem*>			SystemList;
		typedef	SystemList::iterator		SystemListItr;


		class	ISystemManager;
		/**	\brief	系统管理监听器
		*
		*	系统管理监听器
		*
		***/
		class	COMMON_EXPORT	SystemManagerListener{
		public:
			/**	\brief	切换系统前
			*   
			*	@remarks 	切换系统前
			*	@see		SystemManagerListener
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		ISystem * pOldSys
			*	@param		ISystem * pNewSystem
			*	@note
			*
			**/
			virtual	void	BeforeSwitchSystem(ISystemManager*	pSystemMgr,ISystem*	pOldSys,ISystem*	pNewSystem)	=	NULL;
			/**	\brief	切换系统中
			*   
			*	@remarks 	切换系统中
			*	@see		SystemManagerListener
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		ISystem * pOldSys
			*	@param		ISystem * pNewSystem
			*	@note
			*
			**/
			virtual	void	OnSwitchSystem(ISystemManager*	pSystemMgr,ISystem*	pOldSys,ISystem*	pNewSystem)		=	NULL;
			/**	\brief	切换系统完成后
			*   
			*	@remarks 	切换系统完成后
			*	@see		SystemManagerListener
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		ISystem * pOldSys
			*	@param		ISystem * pNewSystem
			*	@note
			*
			**/
			virtual	void	AfterSwitchSystem(ISystemManager*	pSystemMgr,ISystem*	pOldSys,ISystem*	pNewSystem)	=	NULL;
		};

		/**	\brief	系统管理器
		*
		*	系统管理器
		*
		***/
		class	COMMON_EXPORT	ISystemManager
			:	public	IObject,
			public	SimpleListenManager<SystemManagerListener>{
		public:
			ISystemManager(CAString&	strTypeName);
			virtual	~ISystemManager();

			/**	\brief	初始化管理器
			*   
			*	@remarks 	并且初始化设置的
			*	@see		ISystemManager
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Initialization();

			/**	\brief	释放
			*   
			*	@remarks 	释放 并且会释放当前激活的插件
			*	@see		ISystemManager
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Release();

			/**	\brief	返回当前激活的系统
			*   
			*	@remarks 	返回当前激活的系统
			*	@see		ISystemManager
			*	@return   	ISystem*
			*	@note
			*
			**/
			inline	ISystem*	GetActiveSystem(){
				return	m_pActiveSys;
			};
			
			/**	\brief	返回当前激活的系统
			*   
			*	@remarks 	返回当前激活的系统
			*	@see		ISystemManager
			*	@return   	T_System*
			*	@note
			*
			**/
			template<typename	T_System>
			T_System*			GetActiveSystem(){
				if(m_pActiveSys==NULL)
					return	NULL;
				else
					return	dynamic_cast<T_System*>(m_pActiveSys);
			}
			/**	\brief	设置激活系统
			*   
			*	@remarks 	设置激活系统	但是不初始化系统
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			inline	void		SetActiveSystem(ISystem*	pSys){
				if(m_pActiveSys!=NULL){
					m_pActiveSys->Release();
				}
				m_pActiveSys	=	pSys;
			};

			/**	\brief	切换系统
			*   
			*	@remarks 	切换系统	会直接初始化新的系统
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			void				SwitchSystem(ISystem*	pSys);
			/**	\brief	返回当前已经添加的系统列表
			*   
			*	@remarks 	返回当前已经添加的系统列表
			*	@see		ISystemManager
			*	@return   	Air::Common::SystemList
			*	@note
			*
			**/
			SystemList			GetSystemList();

			/**	\brief	添加系统
			*   
			*	@remarks 	添加系统
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			virtual	void		AddSystem(ISystem*	pSys);
			/**	\brief	移除系统
			*   
			*	@remarks 	移除系统
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			virtual	void		RemoveSystem(ISystem*	pSys);

			
			inline	CAString&	GetName(){return m_strName;};
		protected:
			SystemList	m_lstSystem;		///<	系统列表
			ISystem*	m_pActiveSys;		///<	当前激活的系统
			AString		m_strName;
		};

		typedef	std::map<AString,ISystemManager*>	SystemManagerMap;
		typedef	SystemManagerMap::iterator			SystemManagerMapItr;
		typedef	std::list<ISystemManager*>			SystemManagerList;
		typedef	SystemManagerList::iterator			SystemManagerListItr;

		/**	\brief	系统管理器集合
		*
		*	系统管理器集合
		*
		***/
		class	COMMON_EXPORT	SystemManagerGroup
			:	public	SystemManagerListener{
		public:
			SystemManagerGroup();
			virtual	~SystemManagerGroup();

			/**	\brief	添加一个系统指针
			*   
			*	@remarks 	添加一个系统指针
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystem * pSys
			*	@param		U1	bInitWhenNewManager
			*	@note
			*
			**/
			void		AddSystem(ISystem*	pSys,U1	bInitWhenNewManager	=	false);
			/**	\brief	移除一个系统
			*   
			*	@remarks 	移除一个系统
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			void		RemoveSystem(ISystem*	pSys);
			/**	\brief	返回当前激活的系统
			*   
			*	@remarks 	返回当前激活的系统
			*	@see		ISystemManager
			*	@return   	T_System*
			*	@note
			*
			**/
			template<typename	T_System>
			T_System*			GetActiveSystem(AString	strSysType){
				SystemManagerMapItr i	=	m_mapSystemMgr.find(strSysType.c_str());
				if(i!=m_mapSystemMgr.end()){
					ISystemManager*	pSystemMgr	=	i->second;
					if(pSystemMgr!=NULL){
						return	pSystemMgr->GetActiveSystem<T_System>();
					}
				}
				return	NULL;
			};

			/**	\brief	添加一个系统管理器
			*   
			*	@remarks 	添加一个系统管理器
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		U1	bInit
			*	@note
			*
			**/
			void	AddSystemManager(ISystemManager*	pSystemMgr,U1	bInit	=	false);
			/**	\brief	移除一个系统管理器
			*   
			*	@remarks 	移除一个系统管理器
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@note
			*
			**/
			void	RemoveSystemManager(ISystemManager*	pSystemMgr);

			/**	\brief	初始化所有系统管理器
			*   
			*	@remarks 	初始化所有系统管理器
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	InitAllSystemManager();
			/**	\brief	释放所有系统管理器
			*   
			*	@remarks 	释放所有系统管理器
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	ReleaseAllSystemManager();

			/**	\brief	启动所有系统管理
			*   
			*	@remarks 	启动所有系统管理
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	StartAllSystemManager();

			/**	\brief	停止所有系统管理器
			*   
			*	@remarks 	停止所有系统管理器
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	StopAllSystemManager();

			SystemManagerMap	m_mapSystemMgr;		///<	查询表
			SystemManagerList	m_lstSystemMgr;		///<	顺序表

		};
	
	};
};
#endif // COMMONSYSTEMMANAGER_HEAD_FILE