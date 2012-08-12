#ifndef GAMESECTION_HEAD_FILE
#define GAMESECTION_HEAD_FILE

#include "AirGame.h"
#include "AirGameHeader.h"
#include "AirGameControl.h"
namespace Air{
	
	namespace Client{
	
		namespace	Game{
			/**	\brief	加载回调
			*
			*	加载回调
			*
			***/
			class	ILoadingCallback{
			public:
				/**	\brief	开始加载
				*   
				*	@remarks 	开始加载
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnLoadingStart(){};
				/**	\brief	加载进程中
				*   
				*	@remarks 	加载进程中
				*	@see		ILoadingCallback
				*	@return   	void
				*	@param		Real fPercent
				*	@note
				*
				**/
				virtual	void	OnLoadingProcess(Real	fPercent){};
				/**	\brief	加载结束
				*   
				*	@remarks 	加载结束
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnLoadingFinished(){};
	
				/**	\brief	进入场景前的调用
				*   
				*	@remarks 	进入场景前的调用
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnEnter(){};
	
				/**	\brief	离开场景的调用
				*   
				*	@remarks 	离开场景的调用
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnLeave(){};
			};
			/**	\brief	游戏关卡类
			*
			*	游戏关卡类
			*
			***/
			class	GAME_EXPORT	Section	:
				public	Common::IProduct,
				public	Control,
				public	ILoadingCallback{
			public:
	
			public:
				Section(CAString&	strName);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Section
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Section
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Destroy();
	
				/**	\brief	渲染
				*   
				*	@remarks 	渲染
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnRender();
	
				/**	\brief	更新
				*   
				*	@remarks 	更新
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnUpdata();
	
				/**	\brief	渲染目标
				*   
				*	@remarks 	渲染目标
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnRenderTarget();
	
				/**	\brief	加载关卡
				*   
				*	@remarks 	加载关卡
				*	@see		Section
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual	U1		Load(AString	strName);
				/**	\brief	卸载关卡
				*   
				*	@remarks 	卸载关卡
				*	@see		Section
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		UnLoad();
				/**	\brief	GUI事件回调
				*   
				*	@remarks 	GUI事件回调
				*	@see		Section
				*	@return   	void
				*	@param		UINT nEvent
				*	@param		int nControlID
				*	@param		CDXUTControl * pControl
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void	OnGUIEvent( UINT nEvent, int nControlID, void* pControl, void* pUserContext );
	
				/**	\brief	获取场景指针
				*   
				*	@remarks 	获取场景指针
				*	@see		Section
				*	@return   	Scene*
				*	@note
				*
				**/
				inline	Scene*			GetScene(){return	m_pScene;};
				/**	\brief	获取音频场景指针
				*   
				*	@remarks 	获取音频场景指针
				*	@see		Section
				*	@return   	Audio::IScene*
				*	@note
				*
				**/
				inline	Audio::IScene*	GetAudioScene(){return	m_pAudioScene;};
				/**	\brief	获取物理场景指针
				*   
				*	@remarks 	获取物理场景指针
				*	@see		Section
				*	@return   	Physx::IScene*
				*	@note
				*
				**/
				//inline	Physx::IScene*	GetPhysxScene(){return	m_pPhysxScene;};
	
				/**	\brief	设置当前关卡的主摄像机
				*   
				*	@remarks 	设置当前关卡的主摄像机
				*	@see		Section
				*	@return   	void
				*	@param		Camera * pCamera
				*	@note
				*
				**/
				virtual	void	SetCamera(Camera*	pCamera);
				/**	\brief	创建默认摄像机
				*   
				*	@remarks 	创建默认摄像机
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	Camera*	CreateDefaultCamera();
				/**	\brief	创建默认控制器
				*   
				*	@remarks 	创建默认控制器
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	Control*	CreateDefaultControl(Camera*	pSceneCamera);
	
				/**	\brief	进入场景
				*   
				*	@remarks 	进入场景
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		OnEnter();
			protected:
				Scene*			m_pScene;			///<	场景类
				Audio::IScene*	m_pAudioScene;		///<	音频场景
				//Physx::IScene*	m_pPhysxScene;		///<	物理场景
	
				Camera*			m_pDefaultCamera;	///<	默认摄像机
				Control*		m_pDefaultControl;	///<	默认控制器
	
			};
	
			class	SectionFactory	:
				public	Common::IFactory{
			public:
				SectionFactory();
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		BuffFactory
				*	@return   	Common::IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam =	NULL);
			};
		}
	};
};
#endif // GAMESECTION_HEAD_FILE