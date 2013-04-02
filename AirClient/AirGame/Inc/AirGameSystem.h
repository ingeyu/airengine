#ifndef GAMESYSTEM_HEAD_FILE
#define GAMESYSTEM_HEAD_FILE

#include "AirGame.h"
#include "AirInterfaceGameSystem.h"
#include "AirEngineSceneNode.h"

#include "AirInterfaceInputSystem.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Game{
			class	Section;
			/**	\brief	游戏系统
			*
			*	游戏系统
			*
			***/
			class GAME_EXPORT	System	:
				public	Common::ISystem,
				public	OIS::KeyListener,
				public	OIS::MouseListener,
				public	OIS::JoyStickListener{
			public:
				System();
				virtual ~System();
	
				/**	\brief	初始化
				*   
				*	@remarks 	初始化
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
	
				/**	\brief	开始
				*   
				*	@remarks 	开始
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Start();
	
				/**	\brief	停止
				*   
				*	@remarks	停止
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Stop();
	
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
				/**	\brief	帧回调通知
				*   
				*	@remarks 	帧回调通知
				*	@see		ISystem
				*	@return   	void
				*	@param		Real fTotalTime
				*	@param		Real fDeltaTime
				*	@note
				*
				**/
				virtual void	OnFrameMove(Real fTotalTime,Real fDeltaTime);
				/**	\brief	渲染前通知
				*   
				*	@remarks 	渲染通知
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnBeforeRender();
				/**	\brief	渲染通知
				*   
				*	@remarks 	渲染通知
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnRender();
				/**	\brief	渲染后通知
				*   
				*	@remarks 	渲染后通知
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnAfterRender();
	
				/**	\brief	GUI事件回调
				*   
				*	@remarks 	GUI事件回调
				*	@see		IEngine
				*	@return   	void
				*	@param		UINT nEvent
				*	@param		int nControlID
				*	@param		CDXUTControl * pControl
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void	OnGUIEvent( UINT nEvent, int nControlID, void* pControl, void* pUserContext );
	
	
	
				//键盘
				virtual bool keyPressed( const OIS::KeyEvent &arg );
				virtual bool keyReleased( const OIS::KeyEvent &arg );
				//鼠标
				virtual bool mouseMoved( const OIS::MouseEvent &arg );
				virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
				virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
				//手柄
				virtual bool buttonPressed( const OIS::JoyStickEvent &arg, int button );
				virtual bool buttonReleased( const OIS::JoyStickEvent &arg, int button );
				virtual bool axisMoved( const OIS::JoyStickEvent &arg, int axis );
	
				void		SwitchSection(AString	strName);
	
	
				void		SetNextSection(AString	strSectionName);
	
				void		SetDebugString(AString	strDebugString);
	
			protected:
				U1	LoadPlugin();
				U1	UnLoadPlugin();
	
				U1	LoadSection();
				U1	UnLoadSection();
			protected:
				SceneNode*		m_pRootNode;
			private:
				Section**		m_ppSection;
				Section**		m_ppLoadingSection;
				Section*		m_pCurrentSection;
				Section*		m_pTempSection;
				StringArray			m_strPluginNameArray;
				Common::PluginFactory*	m_pPluginMgr;
	
				std::map<AString,Plugin*>	m_mapSection;
				Plugin*			m_pCurrentPlugin;
	
				CriticalSection	m_CS;
				AString			m_strNextSectionName;
	
				AString			m_strFirstSectionName;
			};
		}
	
	};
};
#endif // GAMESYSTEM_HEAD_FILE