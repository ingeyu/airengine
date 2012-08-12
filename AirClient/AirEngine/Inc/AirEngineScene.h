#ifndef ENGINESCENE_HEAD_FILE
#define ENGINESCENE_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"
#include "AirEngineLight.h"
#include "AirInterfaceParticle.h"
#include "AirSceneLoader.h"
namespace Air{
	
	namespace Client{
		namespace	Render{
			class	Target;
			class	ITexture;
			class	IMaterial;
			class	Queue;
		}
		class	Camera;
		class	Light;
		class	ScreenEntity;
		class	PostComposer;
		
	
	
	
		class	ENGINE_EXPORT	Scene	:
			public	IFactoryManager{
		public:
			Scene(CAString&	strName);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		Scene
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1			Initialization();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		Scene
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1			Release();
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		Scene
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		Updata();
			/**	\brief	获取根节点
			*   
			*	@remarks 	获取根节点
			*	@see		Scene
			*	@return   	SceneNode*
			*	@note
			*
			**/
			SceneNode*			GetRootNode();

	
			/**	\brief	设置摄像机
			*   
			*	@remarks 	设置摄像机
			*	@see		Scene
			*	@return   	void
			*	@param		Camera * pCamera
			*	@note
			*
			**/
			void				SetMainCamera(Camera*	pCamera);
			/**	\brief	获取摄像机
			*   
			*	@remarks 	获取摄像机
			*	@see		Scene
			*	@return   	Camera*
			*	@note
			*
			**/
			Camera*				GetMainCamera();
	
			/**	\brief	创建灯光
			*   
			*	@remarks 	创建灯光
			*	@see		Scene
			*	@return   	Light*
			*	@param		AString strName
			*	@param		Light::enumType type
			*	@param		U1	bCastShadow
			*	@note
			*
			**/
			Light*				CreateLight(AString	strName,Light::enumType type,U1	bCastShadow	=	false);
			/**	\brief	摧毁灯光
			*   
			*	@remarks 	摧毁灯光
			*	@see		Scene
			*	@return   	void
			*	@param		Light * pLight
			*	@note
			*
			**/
			void				DestroyLight(Light*	pLight);

	
			/**	\brief	创建摄像机
			*   
			*	@remarks 	创建摄像机
			*	@see		Scene
			*	@return   	Camera*
			*	@note
			*
			**/
			Camera*				CreateCamera(AString	strName);
			/**	\brief	摧毁摄像机
			*   
			*	@remarks 	摧毁摄像机
			*	@see		Scene
			*	@return   	void
			*	@note
			*
			**/
			void				DestroyCamera(Camera*	pCamera);
			
	
			/**	\brief	播放粒子效果
			*   
			*	@remarks 	
			*	@see		Scene
			*	@return   	void
			*	@param		AString strName
			*	@note
			*
			**/
			void				PlayParticle(AString	strName,Float3 vPosition,Float3 vNormal);
	
			void				SaveTargetToFile();


			void				UpdateSceneTree();
			void				FindMovableObject(Camera*	pCamera);


			SceneNode*			GetDynamicSceneNode();
			SceneNode*			GetStaticSceneNode();
			SceneNode*			GetParticleSceneNode();
			SceneNode*			GetTerrainSceneNode();
		protected:

	
		protected:
			//AString			m_strName;
			SceneNode		m_pRootNode;			///<	根节点
			SceneNode		m_DynamicNode;
			SceneNode		m_StaticNode;
			SceneNode		m_ParticleNode;
			SceneNode		m_TerrainNode;
			Camera*			m_pMainCamera;				///<	默认摄像机
	
			U1				m_bShadowEnable;
			typedef		std::list<Render::Target*>	RenderTargetList;
			typedef		RenderTargetList::iterator	RenderTargetListItr;
			typedef		std::list<Light*>			LightList;
			typedef		LightList::iterator			LightListItr;
			typedef		std::list<PostComposer*>	PostComposerList;
			typedef		PostComposerList::iterator	PostComposerListItr;
	
			RenderTargetList	m_lstRenderTarget;	///<	渲染目标列表
			LightList			m_lstLight;
	
			Render::Target*	m_pSceneTarget;				///<	场景目标
			Render::Target*	m_pAlphaSceneTarget;		///<	半透明场景渲染目标
			Render::ITexture*	m_pDefferedResult;
	
			ScreenEntity*		m_pScreenEntity;			///<	屏幕渲染物体
			PostComposerList	m_lstPostComposer;			///<	后期效果列表
	
//			Render::IMaterial*	m_pScreenMaterial;			///<	最终渲染到屏幕的材质
//			Render::IMaterial*	m_pDefferedMaterial;		///<	延迟作色	灯光处理材质
	
			U1					m_bRenderWithoutComposer;	///<	不使用后期效果渲染
			U1					m_bDeferredRender;			///<	是否启用延迟作色
			U1					m_bRenderAlphaObject;		///<	是否只渲染半透明物体
	
			//Render::Queue*		m_pRenderQueue;				///<	渲染队列

			SceneLoader			m_Loader;
		};
	
	};
};
#endif // ENGINESCENE_HEAD_FILE