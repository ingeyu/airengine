#ifndef AirEnginePipeline_h__
#define AirEnginePipeline_h__

#include "AirRenderSystem.h"

#include "AirInterfaceInputSystem.h"

namespace	Air{
	namespace	Client{
		class QuadRenderable;
		class Material;
		class Light;

		struct ENGINE_EXPORT	FrameState 
		{
			FrameState();

			void	FrameEnd();
			U32		uiFrameNumber;
			float	fTimeDelta;
			double	fTotalTime;
			double	fLastTime;
		};

		class	FrameListener{
		public:
			virtual	U1	OnBeforeRenderFrame(const	FrameState&	frame){return	true;};
			virtual	U1	OnAfterRenderFrame(const	FrameState&	frame){return	true;};
		};

		class	ENGINE_EXPORT	Pipeline	:	
			public	IProduct,
			public	OIS::MouseListener,
			public	Common::MutilListenerManager<FrameListener>{
		public:

			Pipeline(CAString&	strName);
			virtual	~Pipeline();

			virtual	U1	Create();
			virtual	U1	Destroy();


			virtual	U1	RenderOneFrame();

			virtual	U1	SetCurrentScene(Scene*	pCurrentScene);
			Scene*		GetCurrentScene();

			inline	RenderWindow*		GetMainWindow(){
				return	m_pMainWindow;
			};
			inline	const	FrameState&	GetFrameState()const{
				return	m_FrameState;
			}

			virtual bool mouseMoved( const OIS::MouseEvent &arg );
			virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		protected:
			RenderWindow*	m_pMainWindow;
			RenderTarget*	m_pMRT;
			RenderTarget*	m_pShadowDepth;
			RenderTarget*	m_pRT_ShadowMask;
			Light*			m_pMainLight;


			Scene*			m_pScene;
			FrameState		m_FrameState;
			QuadRenderable*	m_pQuad;
			Material*		m_pQuadCopy;
			Material*		m_pSSAO;
			Material*		m_pShadowMask;
		};
	}
}
#endif // AirEnginePipeline_h__
