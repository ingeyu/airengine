//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  g:\tj.src\Client0400\Engine
 \filename  EngineSystem.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINESYSTEM_HEAD_FILE
#define ENGINESYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineSystem.h"
#include "AirEngineScene.h"
#include "AirInterfaceAlphaObjectManager.h"
#include "AirInterfaceAutoReleaseManager.h"


namespace Air{
	
	
	namespace Engine{
		
	
		class ENGINE_EXPORT	System	
			:	public	IFactoryManager,
				public	IAutoReleaseManager,
				public	Common::SystemManagerGroup,
				public	Singleton<System>{
		public:
			System();
			virtual	~System();
			/**	\brief	初始化
			*   
			*	@remarks 	初始化
			*	@see		IPlugin
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool	Initialization();
			/**	\brief	开始
			*   
			*	@remarks 	开始
			*	@see		IPlugin
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool	Start();
	
			/**	\brief	停止
			*   
			*	@remarks 	停止
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Stop();
			/**	\brief	释放
			*   
			*	@remarks 	释放
			*	@see		IPlugin
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool	Release();
			/**	\brief	渲染前的更新函数回调
			*   
			*	@remarks 	渲染前的更新函数回调
			*	@see		IEngine
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	ExecuteOneFrame(const FrameTime& frameTime);
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
			virtual	void	BeforeSwitchSystem(	Common::ISystemManager*	pSystemMgr,
												Common::ISystem*		pOldSys,
												Common::ISystem*		pNewSystem);
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
			virtual	void	OnSwitchSystem(	Common::ISystemManager*	pSystemMgr,
											Common::ISystem*		pOldSys,
											Common::ISystem*		pNewSystem);
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
			virtual	void	AfterSwitchSystem(	Common::ISystemManager*	pSystemMgr,
												Common::ISystem*		pOldSys,
												Common::ISystem*		pNewSystem);


		protected:
			/**	\brief	创建窗口
			*   
			*	@remarks 	创建窗口
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	CreateWin();
			/**	\brief	解析显示配置文件
			*   
			*	@remarks 	解析显示配置文件
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	ParseDisplayParam();
	
			/**	\brief	载入插件
			*   
			*	@remarks 	载入插件
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	LoadPlugin();

			U1	LoadPlugin(CAString&	strPluginName);
	
			/**	\brief	卸载插件
			*   
			*	@remarks 	卸载插件
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	UnLoadPlugin();
		private:
			STD_VECTOR<AString>			m_strPluginNameArray;
			STD_VECTOR<Common::Plugin*>	m_vecPlugin;
			AString						m_strWindowName;
		};
	
		
	
	};
	typedef Engine::System EngineSystem;
};
#endif // ENGINESYSTEM_HEAD_FILE