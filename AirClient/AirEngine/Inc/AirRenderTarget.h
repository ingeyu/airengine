#ifndef INTERFACERENDERTARGET_HEAD_FILE
#define INTERFACERENDERTARGET_HEAD_FILE

#include "AirRenderTexture.h"
#include "AirEngineViewport.h"
namespace Air{
	
	namespace Engine{
	
		class	Camera;
		class	Scene;
		class	MovableObject;

	
		namespace	Render{
			enum	enumTargetClearFlag{
				enTCF_UNKNOWN,
				enTCF_STENCIL	=	1,
				enTCF_TARGET	=	2,
				enTCF_ZBUFFER	=	4,
				enTCF_MAX
			};
			typedef	enumTextureFormat		TFormat;
			typedef	std::vector<Texture*>	TextureVector;

			/**	\brief	渲染目标监听器
			*
			*	渲染目标监听器
			*
			***/
			class TargetListener{
			public:
				/**	\brief	渲染前回调
				*   
				*	@remarks 	渲染前回调
				*	@see		Listener
				*	@return   	void
				*	@note
				*
				**/
				virtual void	BeforeRender()	=	NULL;
				/**	\brief	渲染中回调
				*   
				*	@remarks 	渲染中回调
				*	@see		Listener
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnRender()		=	NULL;
				/**	\brief	渲染后回调
				*   
				*	@remarks 	渲染后回调
				*	@see		Listener
				*	@return   	void
				*	@note
				*
				**/
				virtual void	AfterRender()	=	NULL;
			};

			/**	\brief	渲染目标接口
			*
			*	渲染目标接口
			*
			***/
			class	ENGINE_EXPORT	Target	:
				public	IProduct,
				public	Common::MutilListenerManager<TargetListener>{
			public:
				/**	\brief	单渲染目标
				*
				*	单渲染目标
				*
				***/
				struct ENGINE_EXPORT	Info{
					std::vector<Texture::Info>		vecTextureInfo;	///<	多渲染目标
					TFormat							depthFormat;	///<	深度格式
					Target*							extraDepth;		///<	使用外部深度	自身不创建深度
					Float4							clearColor;		///<	清理颜色
					U1								bUseDepth;		///<	判断渲染目标是否需要深度
					HWND							extraWnd;
					HWND							parentWnd;
					U1								bFullScreen;
					

					Info();

					/**	\brief	设置为单一渲染目标
					*   
					*	@remarks 	设置为单一渲染目标
					*	@see		Info
					*	@return   	void
					*	@param		UInt uiWidth
					*	@param		UInt uiHeight
					*	@param		TFormat fmt
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetSingleTarget(	UInt		uiWidth,
												UInt		uiHeight,
												TFormat		fmt,	
												U1			bDepth	=	false,
												Target*	pExtraTarget	=	NULL);
					/**	\brief	设置为与屏幕对齐的渲染目标
					*   
					*	@remarks 	设置为与屏幕对齐的渲染目标
					*	@see		Info
					*	@return   	void
					*	@param		TFormat fmt
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetSingleTargetScreen(	TFormat		fmt,
													float		fScale	=	1.0f,
													U1			bDepth	=	false,
													Target*	pExtraTarget	=	NULL);

					/**	\brief	设置为多渲染目标
					*   
					*	@remarks 	设置为多渲染目标
					*	@see		Info
					*	@return   	void
					*	@param		UInt uiWidth
					*	@param		UInt uiHeight
					*	@param		UInt uiNumTarget
					*	@param		TFormat * pFmtArray
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetMutilTarget(	UInt		uiWidth,
											UInt		uiHeight,
											UInt		uiNumTarget,
											TFormat*	pFmtArray,
											U1			bDepth			=	false,
											Target*	pExtraTarget	=	NULL);

					/**	\brief	设置为屏幕对其的多渲染目标
					*   
					*	@remarks 	设置为屏幕对其的多渲染目标
					*	@see		Info
					*	@return   	void
					*	@param		UInt uiNumTarget
					*	@param		TFormat * pFmtArray
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetMutilTargetScreen(	UInt		uiNumTarget,
													TFormat*	pFmtArray,
													float		fScale			=	1.0f,
													U1			bDepth			=	false,
													Target*	pExtraTarget	=	NULL);

					void	SetRenderWindow(U32		uiWidth,
											U32		uiHeight,
											U1		bWindow			=	true,
											HWND	parentWindow	=	NULL,
											HWND	extraWindow		=	NULL);
				};
			public:
				static AString ProductTypeName;
				Target(CAString&	strName,	Info*	pInfo);

				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			Destroy();
				/**	\brief	开始渲染
				*   
				*	@remarks 	开始渲染
				*	@see		Target
				*	@return   	U1
				*	@param		Scene*	pScene
				*	@note
				*
				**/
				virtual U1			Update();
				/**	\brief	更新前调用
				*   
				*	@remarks 	主要是设置RT DEPTHSTENCIL BEGINSCENE之类
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			BeforeUpdate(U32	uiFace	=	0);
				/**	\brief	更新结束的处理
				*   
				*	@remarks 	更新结束的处理 EndScene之类
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			AfterUpdate(U1 bSwapBuffer	=	true);
				/**	\brief	设置背景颜色
				*   
				*	@remarks 	设置背景颜色
				*	@see		Target
				*	@return   	U1
				*	@param		Float4 uiColor
				*	@note
				*
				**/
				inline void		SetBKColor(const Float4&	color){
					m_Info.clearColor	=	color;
				};
	
				/**	\brief	设置渲染目标物体
				*   
				*	@remarks 	设置渲染目标物体
				*	@see		Target
				*	@return   	void
				*	@param		MovableObject * pObject
				*	@note
				*
				**/
				virtual	void		SetRenderObject(MovableObject*	pObject){};
	
				/**	\brief	获取渲染目标物体
				*   
				*	@remarks 	获取渲染目标物体
				*	@see		Target
				*	@return   	MovableObject*
				*	@note
				*
				**/
				virtual	MovableObject*	GetRenderObject(){return NULL;};
				/**	\brief	重建
				*   
				*	@remarks 	重建
				*	@see		Target
				*	@return   	void
				*	@param		Info & info
				*	@note
				*
				**/
				virtual	void		ReCreate(Info&	info)	=	NULL;
				/**	\brief	添加Phase信息
				*   
				*	@remarks 	添加Phase信息
				*	@see		Target
				*	@return   	void
				*	@param		enumPhaseIndex uiPhaseIndex
				*	@note
				*
				**/
				void				AddPhaseFlag(enumPhaseIndex	uiPhaseIndex);
				/**	\brief	移除Phase信息
				*   
				*	@remarks 	移除Phase信息
				*	@see		Target
				*	@return   	void
				*	@param		enumPhaseIndex uiPhaseIndex
				*	@note
				*
				**/
				void				RemovePhaseFlag(enumPhaseIndex	uiPhaseIndex);
				/**	\brief	获取Phase信息
				*   
				*	@remarks 	获取Phase信息
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				U32					GetPhaseFlag();
				/**	\brief	清理Phase信息
				*   
				*	@remarks 	清理Phase信息
				*	@see		Target
				*	@return   	void
				*	@note
				*
				**/
				void				ClearPhaseFlag();
				/**	\brief	获取纹理宽度
				*   
				*	@remarks 	获取纹理宽度
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				virtual	U32					GetWidth();
				/**	\brief	获取纹理高度
				*   
				*	@remarks 	获取纹理高度
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				virtual	U32					GetHeight();
				/**	\brief	获取纹理深度
				*   
				*	@remarks 	获取纹理深度
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				virtual	U32					GetDepth();

				/**	\brief	设置激活状态
				*   
				*	@remarks 	设置激活状态
				*	@see		Target
				*	@return   	void
				*	@param		U1 bActive
				*	@note
				*
				**/
				void				SetActive(U1	bActive);
				/**	\brief	判断当前视口激活
				*   
				*	@remarks 	如果没有激活 则不会在渲染管线中更新此RT
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				U1					IsAvtive();

				/**	\brief	添加视口
				*   
				*	@remarks 	添加视口
				*	@see		Target
				*	@return   	Viewport*
				*	@param		Camera * pCamera
				*	@param		U32 uiZOrder
				*	@param		Real x
				*	@param		Real y
				*	@param		Real w
				*	@param		Real h
				*	@note
				*
				**/
				Viewport*			AddCamera(	Camera*	pCamera,
												U32		uiZOrder	=	0,
												Real	x			=	0.0f,
												Real	y			=	0.0f,
												Real	w			=	1.0f,
												Real	h			=	1.0f);
				/**	\brief	移除视口
				*   
				*	@remarks 	移除视口
				*	@see		Target
				*	@return   	void
				*	@param		U32 uiZOrder
				*	@note
				*
				**/
				void				RemoveViewport(U32		uiZOrder);
				/**	\brief	添加视口
				*   
				*	@remarks 	添加视口
				*	@see		Target
				*	@return   	void
				*	@param		Viewport * pVP
				*	@param		U32 uiZOrder
				*	@note
				*
				**/
				void				AddViewport(Viewport*	pVP,
												U32		uiZOrder	=	0);
				/**	\brief	移除所有视口
				*   
				*	@remarks 	移除所有视口
				*	@see		Target
				*	@return   	void
				*	@note
				*
				**/
				void				RemoveAllViewport();
				/**	\brief	设置使用外部深度
				*   
				*	@remarks 	设置使用外部深度
				*	@see		Target
				*	@return   	void
				*	@param		Target * pTarget
				*	@note
				*
				**/
				void				SetUseExtraDepth(Target*	pTarget);

				/**	\brief	添加一个清理标示
				*   
				*	@remarks 	添加一个清理标示
				*	@see		Target
				*	@return   	void
				*	@param		enumTargetClearFlag flag
				*	@note
				*
				**/
				void				AddClearFlag(enumTargetClearFlag	flag);
				/**	\brief	移除一个清理标示
				*   
				*	@remarks 	移除一个清理标示
				*	@see		Target
				*	@return   	void
				*	@param		enumTargetClearFlag flag
				*	@note
				*
				**/
				void				RemoveClearFlag(enumTargetClearFlag	flag);
				/**	\brief	设置清理标示
				*   
				*	@remarks 	设置清理标示
				*	@see		Target
				*	@return   	void
				*	@param		U32 flag
				*	@note
				*
				**/
				void				SetClearFlag(U32	flag);
				/**	\brief	设置清理标示
				*   
				*	@remarks 	设置清理标示
				*	@see		Target
				*	@return   	void
				*	@param		U1 bClearStencil
				*	@param		U1 bClearTarget
				*	@param		U1 bClearZBuffer
				*	@note
				*
				**/
				void				SetClearFlag(U1	bClearStencil,U1 bClearTarget,U1 bClearZBuffer);
				/**	\brief	获取清理标示
				*   
				*	@remarks 	获取清理标示
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				U32					GetClearFlag();


				void	FindActiveCamera( CameraSet& setCamera );

				virtual		void*	GetRTV(U32	uiIdx	=	0);
				virtual		void*	GetSRV(U32	uiIdx	=	0);
				virtual		void*	GetUAV(U32	uiIdx	=	0);
				virtual		void*	GetDepthRTV()				=	NULL;
				virtual		void*	GetDepthSRV()				=	NULL;
				virtual		void*	GetBackBuffer(U32	uiIdx	=	0);
				virtual		void*	GetDepthBuffer()			=	NULL;

				virtual		void	ReSize(U32	width,U32	height);

				virtual		void	OnMainWindowSize(Window* pMainWindow);
			protected:
				Info				m_Info;						///<	创建信息
				TextureVector		m_vecTexture;				///<	纹理数组
				Camera*				m_pCamera;					///<	绑定的摄像机
				U1					m_bActive;					///<	是否激活
				PhaseOption			m_PhaseOpt;					///<	阶段属性
				U32					m_ClearFlag;				///<	清理属性
				ViewportMap			m_mapViewport;				///<	视口列表

			};
	
			typedef		std::list<Target*>		TargetList;
			typedef		TargetList::iterator	TargetListItr;
			/**	\brief	渲染目标管理器
			*
			*	渲染目标管理器
			*
			***/
			class	TargetManager{
			public:
				/**	\brief	存入一个要渲染的目标
				*   
				*	@remarks 	存入一个要渲染的目标
				*	@see		Renderer
				*	@return   	void
				*	@param		Window::IControl * pControl
				*	@note
				*
				**/
				virtual	void	AddTarget(Render::Target*	pTarget){
					if(pTarget==NULL)
						return;
					m_lstTarget.push_back(pTarget);
				};
				/**	\brief	移除一个渲染目标
				*   
				*	@remarks 	移除一个渲染目标
				*	@see		Renderer
				*	@return   	void
				*	@param		Render::Target * pTarget
				*	@note
				*
				**/
				virtual	void	RemoveTarget(Render::Target*	pTarget){
					if(pTarget==NULL)
						return;
					m_lstTarget.remove(pTarget);
				};
				/**	\brief	渲染目标
				*   
				*	@remarks 	渲染目标
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	RenderTarget(){
					class RenderTargetCall: std::unary_function<Target*, void>
					{
					public:
						result_type operator()(argument_type i){
							i->Update();
						}
					};
					std::for_each(m_lstTarget.begin(),m_lstTarget.end(),RenderTargetCall());

				};
	
				TargetList			m_lstTarget;
			};
		}
	};
};
#endif // INTERFACERENDERTARGET_HEAD_FILE